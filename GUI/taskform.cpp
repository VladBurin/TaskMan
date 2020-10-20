#include "taskform.h"
#include "ui_taskform.h"
#include "mainwindow.h"

TaskForm::TaskForm(Engine *engine, int pers_id, MainWindow* main_wind, QWidget *parent) :
    Eng(engine),
    PersId(pers_id),
    QWidget(parent),
    MainWind(main_wind),
    ui(new Ui::TaskForm)
{
    ui->setupUi(this);

    UpdateSkillsBox();

    CreateAboutPers();

    ui->comboboxSkills->setCurrentIndex(0);

    ui->treeTasks->header()->resizeSection( 0, 500 );
    ui->treeTasks->header()->resizeSection( 1, 10 );
    ui->treeTasks->header()->resizeSection( 2, 10 );

    UpdateTasks();

    connect(ui->buttonBackToPers, &QPushButton::clicked, main_wind, &MainWindow::CreatePersForm);

    connect(ui->buttonCreateSkill, &QPushButton::clicked, this, &TaskForm::CreateSkill);
}

TaskForm::~TaskForm()
{
    delete ui;
}

void TaskForm::CreateChilds(int task_id, QTreeWidgetItem* par)
{
    //верхний уровень задач
    QTreeWidgetItem* item = new QTreeWidgetItem(par);
    item->setExpanded(true);
    item->setData(0, Qt::UserRole, task_id);
    item->setText(0, Eng->GetTaskById(task_id)->GetName().c_str());
    item->setText(1, QString::number(Eng->GetTaskById(task_id)->GetScoresForTask()));
    //дети
    std::vector<int> childs = Eng->GetTaskById(task_id)->GetChildTasksId();

    if(childs.empty())
        item->setCheckState(2,Qt::Unchecked);

    for(auto h = childs.begin(); h != childs.end(); ++h)
    {
        CreateChilds(*h,item);
    }
}

void TaskForm::on_comboboxSkills_activated(int index)
{
    UpdateTasks();
    UpdateSkillDesc();
}

void TaskForm::UpdateTasks()
{
    int skill_id = ui->comboboxSkills->currentData().toInt();

    if(skill_id == -11)
    {
        ui->treeTasks->clear();

        std::vector<int> tasks = Eng->GetHighIncompTasksByPersId(PersId);

        for(auto t = tasks.begin(); t != tasks.end(); ++t)
        {
            //верхний уровень задач
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeTasks);
            item->setExpanded(true);
            item->setData(0,Qt::UserRole,(*t));
            item->setText(0, Eng->GetTaskById(*t)->GetName().c_str());
            item->setText(1, QString::number(Eng->GetTaskById(*t)->GetScoresForTask()));

            //дети и далее
            std::vector<int> childs = Eng->GetTaskById(*t)->GetChildTasksId();

            if(childs.empty())
                item->setCheckState(2,Qt::Unchecked);

            for(auto h = childs.begin(); h != childs.end(); ++h)
            {
                CreateChilds(*h,item);
            }
        }
    }
    else
    {
        ui->treeTasks->clear();

        std::vector<int> tasks = Eng->GetHighIncompTasksBySkillId(skill_id);

        for(auto t = tasks.begin(); t != tasks.end(); ++t)
        {
            //верхний уровень задач
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeTasks);
            item->setExpanded(true);
            item->setData(0,Qt::UserRole,(*t));
            item->setText(0, Eng->GetTaskById(*t)->GetName().c_str());
            item->setText(1, QString::number(Eng->GetTaskById(*t)->GetScoresForTask()));

            //дети и далее
            std::vector<int> childs = Eng->GetTaskById(*t)->GetChildTasksId();

            if(childs.empty())
                item->setCheckState(2,Qt::Unchecked);

            for(auto h = childs.begin(); h != childs.end(); ++h)
            {
                CreateChilds(*h,item);
            }
        }
    }

}

void TaskForm::UpdateSkillsBox()
{
    // Get pers skills
    std::vector<int> skills = Eng->GetSkillsByPersId(PersId);
    ui->comboboxSkills->clear();
    ui->comboboxSkills->addItem("Tasks",-11);

    for(auto it = skills.begin(); it != skills.end(); ++it)
    {
        ui->comboboxSkills->addItem(QString::fromStdString(Eng->GetSkillById(*it)->GetName()),
                             Eng->GetSkillById(*it)->GetId());
    }

}

void TaskForm::CreateSkill()
{
    SkillCreateDialog * dialog = new SkillCreateDialog;
    if(dialog->exec() == QDialog::Accepted)
    {
        Eng->CreateSkill(PersId, dialog->GetPersName(), dialog->GetPersDesc());
        ui->comboboxSkills->setCurrentIndex(ui->comboboxSkills->count()-1);
    }
    delete dialog;

    UpdateSkillsBox();

    UpdateTasks();
}

void TaskForm::CreateAboutPers()
{
    ui->textPersDesc->clear();

    Personage* pers = Eng->GetPersById(PersId);

    std::string name = pers->GetName();
    std::string descript = pers->GetDescript();
    int level = pers->GetLevel();
    int score_sum = pers->GetScoresSum();

    QString text;
    text += "Name: \t\t" +QString::fromStdString(name) + "\n";
    text += "Description: \t" +QString::fromStdString(descript) + "\n";
    text += "Level: \t\t" +QString::number(level) + "\n";
    text += "Sum of score: \t" +QString::number(score_sum) + "\n";

    ui->textPersDesc->setText(text);

}

void TaskForm::UpdateSkillDesc()
{
    int skill_id = ui->comboboxSkills->currentData().toInt();

    ui->textSkillDesc->clear();

    if(skill_id == -11)
        return;

    Skill* skill = Eng->GetSkillById(skill_id);

    std::string name = skill->GetName();
    std::string descript = skill->GetDescript();
    int level = skill->GetLevel();
    int score_sum = skill->GetScoresSum();

    QString text;
    text += "Name: \t\t" +QString::fromStdString(name) + "\n";
    text += "Description: \t" +QString::fromStdString(descript) + "\n";
    text += "Level: \t\t" +QString::number(level) + "\n";
    text += "Sum of score: \t" +QString::number(score_sum) + "\n";

    ui->textSkillDesc->setText(text);

}

void TaskForm::on_treeTasks_itemSelectionChanged()
{
    int task_id = ui->treeTasks->currentItem()->data(0,Qt::UserRole).toInt();
    TaskUnit* task = Eng->GetTaskById(task_id);

    ui->textAboutTask->clear();
    QString text = QString::fromStdString(task->GetDescript());
    ui->textAboutTask->setText(text);


}
