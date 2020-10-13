#include "taskform.h"
#include "ui_taskform.h"

TaskForm::TaskForm(Engine *engine, int pers_id, QWidget *parent) :
    Engine_instance(engine),
    QWidget(parent),
    ui(new Ui::TaskForm)
{
    ui->setupUi(this);

    // Get pers skills
    std::vector<int> skills = Engine_instance->GetSkillsByPersId(pers_id);

    ui->comboBox->addItem("Tasks");
    for(auto it = skills.begin(); it != skills.end(); ++it)
    {
        ui->comboBox->addItem(QString::fromStdString(Engine_instance->GetSkillById(*it)->GetName()));
    }
    ui->treeWidget->clear();

    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    item->setExpanded(true);
    int id = 9;
    item->setData(0,Qt::UserRole,QVariant(id));
    int check = item->data(0,Qt::UserRole).toInt();
    item->setText(0, "str");

    QTreeWidgetItem* item1 = new QTreeWidgetItem(item);
    item1->setExpanded(true);
    item1->setText(0, "str11");

    QTreeWidgetItem* item2 = new QTreeWidgetItem(item1);
    item2->setExpanded(true);
    item2->setText(0, "str22");


}

TaskForm::~TaskForm()
{
    delete ui;
}
