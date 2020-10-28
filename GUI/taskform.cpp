#include "taskform.h"
#include "ui_taskform.h"
#include "mainwindow.h"

TaskForm::TaskForm(Engine *engine, int char_id, MainWindow* main_wind, QWidget *parent) :
    Eng(engine),
    QWidget(parent),
    CharId(char_id),
    MainWind(main_wind),
    ui(new Ui::TaskForm)
{
    ui->setupUi(this);

    UpdateSkillsBox();
    ui->comboboxSkills->setCurrentIndex(0);

    CreateAboutChar();

    ui->treeTasks->header()->resizeSection( 0, 500 );
    ui->treeTasks->header()->resizeSection( 1, 10 );
    ui->treeTasks->header()->resizeSection( 2, 10 );

    UpdateTasks();

    connect(ui->buttonBackToPers, &QPushButton::clicked, main_wind, &MainWindow::CreateCharForm);

    connect(ui->buttonCreateSkill, &QPushButton::clicked, this, &TaskForm::CreateSkill);

    ui->treeTasks->addAction(ui->actionCreate_new_task);
    ui->treeTasks->addAction(ui->actionEdit_Task);
    ui->treeTasks->addAction(ui->actionDelete_Task);
    ui->treeTasks->setContextMenuPolicy(Qt::ActionsContextMenu);
}

TaskForm::~TaskForm()
{
    delete ui;
}

void TaskForm::on_comboboxSkills_activated(int index)
{
    UpdateTasks();
    UpdateSkillDesc();
}

void TaskForm::CreateChilds(int task_id, QTreeWidgetItem* par)
{
    TaskUnit* task = Eng->GetTaskById(task_id);

    if(!task)
        return;

    //верхний уровень задач
    QTreeWidgetItem* item = new QTreeWidgetItem(par);
    item->setExpanded(true);
    item->setData(0, Qt::UserRole, task_id);
    item->setText(0, task->GetName().c_str());
    item->setText(1, QString::number(task->GetScoresForTask()));

    //дети
    std::vector<int> childs = task->GetChildTasksId();

    // task completion status
    if(task->GetCompletStatus())
        item->setCheckState(2, Qt::Checked);
    else
        item->setCheckState(2, Qt::Unchecked);

    for(auto h = childs.begin(); h != childs.end(); ++h)
    {
        CreateChilds(*h,item);
    }
}

void TaskForm::UpdateTasks()
{
    int skill_id = ui->comboboxSkills->currentData().toInt();

    ui->treeTasks->clear();

    std::vector<int> tasks = Eng->GetHighTasksBySkillId(skill_id);

    for(auto t = tasks.begin(); t != tasks.end(); ++t)
    {
        TaskUnit* task = Eng->GetTaskById(*t);

        //верхний уровень задач
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeTasks);
        item->setExpanded(true);
        item->setData(0,Qt::UserRole,(*t));
        item->setText(0, task->GetName().c_str());
        item->setText(1, QString::number(task->GetScoresForTask()));

        //дети и далее
        std::vector<int> childs = task->GetChildTasksId();

        // task completion status
        if(task->GetCompletStatus())
            item->setCheckState(2, Qt::Checked);
        else
            item->setCheckState(2, Qt::Unchecked);

        for(auto h = childs.begin(); h != childs.end(); ++h)
        {
            CreateChilds(*h,item);
        }
    }
}

void TaskForm::UpdateSkillsBox()
{
    // Get pers skills
    std::vector<int> skills = Eng->GetSkillsByPersId(CharId);
    ui->comboboxSkills->clear();

    int task_skill = Eng->GetCharById(CharId)->GetTaskSkillId();

    ui->comboboxSkills->addItem(QString::fromStdString(Eng->GetSkillById(task_skill)->GetName()),
                                task_skill);

    for(auto it = skills.begin(); it != skills.end(); ++it)
    {
        if((*it) == task_skill)
            continue;
        ui->comboboxSkills->addItem(QString::fromStdString(Eng->GetSkillById(*it)->GetName()),
                             Eng->GetSkillById(*it)->GetId());
    }

}

void TaskForm::CreateSkill()
{
    QString skill_name;

    SkillCreateDialog * dialog = new SkillCreateDialog;
    if(dialog->exec() == QDialog::Accepted)
    {
        Eng->CreateSkill(CharId, dialog->GetSkillName(), dialog->GetSkillDesc());
        skill_name = dialog->GetSkillName().c_str();
    }
    delete dialog;

    UpdateSkillsBox();

    if(!skill_name.isEmpty())
        ui->comboboxSkills->setCurrentText(skill_name);

    UpdateTasks();
}

void TaskForm::CreateAboutChar()
{
    ui->textPersDesc->clear();

    Character* pers = Eng->GetCharById(CharId);

    std::string name = pers->GetName();
    std::string descript = pers->GetDescript();
    int level = pers->GetLevel();
    int current_score = pers->GetCurrentLevelScore();
    int score_for_next_lev = pers->GetScoresToNextLevel();

    QString text;
    text += "Name: \t\t" + QString::fromStdString(name) + "\n";
    text += "Description: \t" + QString::fromStdString(descript) + "\n";
    text += "Level: \t\t" + QString::number(level) + "\n";
    text += "Score: \t" + QString::number(current_score) + " / " + QString::number(score_for_next_lev) + "\n";

    ui->textPersDesc->setText(text);

}

void TaskForm::UpdateSkillDesc()
{
    int skill_id = ui->comboboxSkills->currentData().toInt();

    ui->textSkillDesc->clear();

    if(skill_id == Eng->GetCharById(CharId)->GetTaskSkillId())
        return;

    Skill* skill = Eng->GetSkillById(skill_id);

    std::string name = skill->GetName();
    std::string descript = skill->GetDescript();
    int level = skill->GetLevel();
    int current_score = skill->GetCurrentLevelScore();
    int score_for_next_lev = skill->GetScoresToNextLevel();

    QString text;
    text += "Name: \t\t" +QString::fromStdString(name) + "\n";
    text += "Description: \t" +QString::fromStdString(descript) + "\n";
    text += "Level: \t\t" +QString::number(level) + "\n";
    text += "Score: \t" + QString::number(current_score) + " / " + QString::number(score_for_next_lev) + "\n";

    ui->textSkillDesc->setText(text);

}

void TaskForm::on_treeTasks_itemSelectionChanged()
{
    if(!ui->treeTasks->currentItem())
        return;

    int task_id = ui->treeTasks->currentItem()->data(0,Qt::UserRole).toInt();
    TaskUnit* task = Eng->GetTaskById(task_id);

    if(!task)
        return;

    ui->textAboutTask->clear();
    QString text = QString::fromStdString(task->GetDescript());
    ui->textAboutTask->setText(text);
}

void TaskForm::on_treeTasks_itemClicked(QTreeWidgetItem *item, int column)
{
    if(!item || column != 2)
    {
        return;
    }

    ui->treeTasks->setCurrentItem(item);

    int id_task = ui->treeTasks->currentItem()->data(0, Qt::UserRole).toInt();

    // If task wasn't completed
    if(!(Eng->GetTaskById(id_task)->GetCompletStatus()))
    {
        // If it is attempt of completion task with incompleted childs
        if(!Eng->CheckChildCompleted(id_task))
        {
            item->setCheckState(2, Qt::Unchecked);
            return;
        }
        TaskComplete(id_task);
    }
    // If task was completed
    else
    {
        TaskIncomplete(id_task);
    }
}

void TaskForm::TaskComplete(int id)
{
    Eng->TaskComplete(id);
    UpdateTasks();
    UpdateSkillDesc();
    CreateAboutChar();
}

void TaskForm::TaskIncomplete(int id)
{
    Eng->TaskIncomplete(id,true);
    UpdateTasks();
    UpdateSkillDesc();
    CreateAboutChar();
}

void TaskForm::on_actionCreate_new_task_triggered()
{
    int skill_id = ui->comboboxSkills->currentData().toInt();
    int task_id = -11;
    QTreeWidgetItem* task = ui->treeTasks->currentItem();
    if(task)
        task_id = task->data(0,Qt::UserRole).toInt();

    int final_skill_id = skill_id;

    TaskCreateDialog* dialog = new TaskCreateDialog(Eng,CharId,skill_id,task_id);
    if(dialog->exec() == QDialog::Accepted)
    {
        Eng->CreateTask(dialog->GetTaskName(),dialog->GetTaskDesc(),
                        dialog->GetTaskScore(),dialog->GetSkillId(),dialog->GetParentTaskId());
        final_skill_id = dialog->GetSkillId();
    }
    delete dialog;

    //Update skill if changed
    ui->comboboxSkills->setCurrentText(QString::fromStdString(Eng->GetSkillById(final_skill_id)->GetName()));
    on_comboboxSkills_activated(0);

}

void TaskForm::on_actionEdit_Task_triggered()
{

}

void TaskForm::on_actionDelete_Task_triggered()
{
    QTreeWidgetItem* task = ui->treeTasks->currentItem();
    if(!task)
        return;

    int task_id = task->data(0,Qt::UserRole).toInt();

    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Warning",
                                  "Are you sure you want to delete task \""
                                  +QString::fromStdString(Eng->GetTaskById(task_id)->GetName())
                                  +"\" and all subtasks of this one?",
                                  QMessageBox::Yes|QMessageBox::Cancel);
    if(reply == QMessageBox::Cancel)
        return;

    // Deleting task
    Eng->DeleteTask(task_id);

    on_comboboxSkills_activated(0);
}
