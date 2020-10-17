#include "skillcreatedialog.h"
#include "ui_skillcreatedialog.h"

SkillCreateDIalog::SkillCreateDIalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SkillCreateDIalog)
{
    ui->setupUi(this);
}

SkillCreateDIalog::~SkillCreateDIalog()
{
    delete ui;
}
