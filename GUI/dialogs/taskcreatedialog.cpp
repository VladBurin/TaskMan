#include "taskcreatedialog.h"
#include "ui_taskcreatedialog.h"

TaskCreateDialog::TaskCreateDialog(Engine *engine, int char_id,
                                   int init_skill_id, int init_task_id, QWidget *parent) :
    QDialog(parent),
    CharId(char_id),
    Eng(engine),
    ui(new Ui::TaskCreateDialog)
{
    ui->setupUi(this);

    // Fill skill combobox with current skill
    std::vector<int> skills = Eng->GetSkillsByPersId(CharId);
    ui->comboBoxSkillChoice->clear();

    int task_skill = Eng->GetCharById(CharId)->GetTaskSkillId();

    ui->comboBoxSkillChoice->addItem(QString::fromStdString(Eng->GetSkillById(task_skill)->GetName()), task_skill);

    for(auto it = skills.begin(); it != skills.end(); ++it)
    {
        if((*it) == task_skill)
            continue;
        ui->comboBoxSkillChoice->addItem(QString::fromStdString(Eng->GetSkillById(*it)->GetName()),(*it));
    }

    ui->comboBoxSkillChoice->setCurrentText(QString::fromStdString(
                                            Eng->GetSkillById(init_skill_id)->GetName()));


    UpdateParentTaskBox(init_skill_id);

    // If comboBox isn't empty choose initial parent task
    if(init_task_id==-11)
        ui->comboBoxParentTaskChoice->setCurrentText("... (no parent)");
    else
        ui->comboBoxParentTaskChoice->setCurrentText(QString::fromStdString(Eng->GetTaskById(init_task_id)->GetName()));
}

TaskCreateDialog::~TaskCreateDialog()
{
    delete ui;
}

void TaskCreateDialog::UpdateParentTaskBox(int skill_id)
{
    // Fill parentTask comboBox
    std::vector<int> tasks = Eng->GetTasksBySkillId(skill_id);
    ui->comboBoxParentTaskChoice->clear();

    for(auto it = tasks.begin(); it != tasks.end(); ++it)
    {
        ui->comboBoxParentTaskChoice->addItem(QString::fromStdString(Eng->GetTaskById(*it)->GetName()), (*it));
    }

    ui->comboBoxParentTaskChoice->addItem("... (no parent)", -11);

    // If comboBox isn't empty
    if(ui->comboBoxParentTaskChoice->count())
        ui->comboBoxParentTaskChoice->setCurrentIndex(0);

}

int TaskCreateDialog::GetSkillId()
{
    return ui->comboBoxSkillChoice->currentData().toInt();
}

int TaskCreateDialog::GetParentTaskId()
{
    return ui->comboBoxParentTaskChoice->currentData().toInt();
}

std::string TaskCreateDialog::GetTaskName()
{
    return ui->lineEditTaskName->text().toUtf8().data();
}

std::string TaskCreateDialog::GetTaskDesc()
{
    return ui->textEditTaskDesc->toPlainText().toUtf8().data();
}

int TaskCreateDialog::GetTaskScore()
{
    return ui->lineEditTaskScore->text().toInt();
}

void TaskCreateDialog::on_comboBoxSkillChoice_currentIndexChanged(const QString &arg1)
{
    int skill_id = ui->comboBoxSkillChoice->currentData().toInt();
    UpdateParentTaskBox(skill_id);
}
