#include "skillcreatedialog.h"

SkillCreateDialog::SkillCreateDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Create new skill");

    EnterNameLabel = new QLabel("Skill name");
    SkillName = new QLineEdit;

    EnterDescLabel = new QLabel("Skill description");
    SkillDescript = new QTextEdit;

    OkButton = new QPushButton("Ok");
    CancelButton = new QPushButton("Cancel");


    connect(OkButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(CancelButton,SIGNAL(clicked()),this, SLOT(reject()));

    QHBoxLayout* hbox_layout = new QHBoxLayout;
    hbox_layout->addWidget(OkButton);
    hbox_layout->addWidget(CancelButton);

    QVBoxLayout* vbox_layout = new QVBoxLayout;
    vbox_layout->addWidget(EnterNameLabel);
    vbox_layout->addWidget(SkillName);
    vbox_layout->addWidget(EnterDescLabel);
    vbox_layout->addWidget(SkillDescript);
    vbox_layout->addLayout(hbox_layout);
    setLayout(vbox_layout);
}

SkillCreateDialog::~SkillCreateDialog()
{
}

std::string SkillCreateDialog::GetSkillName()
{
    QString text = SkillName->text();
    return text.toUtf8().data();
}

std::string SkillCreateDialog::GetSkillDesc()
{
    QString text = SkillDescript->toPlainText();
    return text.toUtf8().data();
}
