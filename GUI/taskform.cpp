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

    // Get pers skills
    std::vector<int> skills = Eng->GetSkillsByPersId(PersId);

    ui->comboBox->addItem("Tasks",-11);

    for(auto it = skills.begin(); it != skills.end(); ++it)
    {
        ui->comboBox->addItem(QString::fromStdString(Eng->GetSkillById(*it)->GetName()),
                             Eng->GetSkillById(*it)->GetId());
    }

    ui->comboBox->setCurrentIndex(0);

    ui->treeWidget->clear();

    std::vector<int> tasks = Eng->GetHighIncompTasksByPersId(PersId);

    for(auto t = tasks.begin(); t != tasks.end(); ++t)
    {
        //верхний уровень задач
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
        item->setExpanded(true);
        item->setData(0,Qt::UserRole,(*t));
        item->setText(0, Eng->GetTaskById(*t)->GetName().c_str());


        //дети и далее
        std::vector<int> childs = Eng->GetTaskById(*t)->GetChildTasksId();
        for(auto h = childs.begin(); h != childs.end(); ++h)
        {
            CreateChilds(*h,item);
        }
    }

     connect(ui->pushButton_2, &QPushButton::clicked, main_wind, &MainWindow::CreatePersForm);
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

    //дети
    std::vector<int> childs = Eng->GetTaskById(task_id)->GetChildTasksId();
    for(auto h = childs.begin(); h != childs.end(); ++h)
    {
        CreateChilds(*h,item);
    }
}

void TaskForm::on_comboBox_activated(int index)
{
    int skill_id = ui->comboBox->currentData().toInt();

    if(skill_id == -11)
    {
        ui->treeWidget->clear();

        std::vector<int> tasks = Eng->GetHighIncompTasksByPersId(PersId);

        for(auto t = tasks.begin(); t != tasks.end(); ++t)
        {
            //верхний уровень задач
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
            item->setExpanded(true);
            item->setData(0,Qt::UserRole,(*t));
            item->setText(0, Eng->GetTaskById(*t)->GetName().c_str());


            //дети и далее
            std::vector<int> childs = Eng->GetTaskById(*t)->GetChildTasksId();
            for(auto h = childs.begin(); h != childs.end(); ++h)
            {
                CreateChilds(*h,item);
            }
        }
    }
    else
    {
        ui->treeWidget->clear();

        std::vector<int> tasks = Eng->GetHighIncompTasksBySkillId(skill_id);

        for(auto t = tasks.begin(); t != tasks.end(); ++t)
        {
            //верхний уровень задач
            QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
            item->setExpanded(true);
            item->setData(0,Qt::UserRole,(*t));
            item->setText(0, Eng->GetTaskById(*t)->GetName().c_str());

            //дети и далее
            std::vector<int> childs = Eng->GetTaskById(*t)->GetChildTasksId();
            for(auto h = childs.begin(); h != childs.end(); ++h)
            {
                CreateChilds(*h,item);
            }
        }
    }

}

void TaskForm::on_pushButton_2_clicked()
{

}
