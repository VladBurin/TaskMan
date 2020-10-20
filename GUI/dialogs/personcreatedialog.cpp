#include "personcreatedialog.h"


PersonCreateDialog::PersonCreateDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Create new character");

    EnterNameLabel = new QLabel("Character name");
    PersName = new QLineEdit;

    EnterDescLabel = new QLabel("Character description");
    PersDescript = new QTextEdit;

    OkButton = new QPushButton("Ok");
    CancelButton = new QPushButton("Cancel");


    connect(OkButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(CancelButton,SIGNAL(clicked()),this, SLOT(reject()));

    QHBoxLayout* hbox_layout = new QHBoxLayout;
    hbox_layout->addWidget(OkButton);
    hbox_layout->addWidget(CancelButton);

    QVBoxLayout* vbox_layout = new QVBoxLayout;
    vbox_layout->addWidget(EnterNameLabel);
    vbox_layout->addWidget(PersName);
    vbox_layout->addWidget(EnterDescLabel);
    vbox_layout->addWidget(PersDescript);
    vbox_layout->addLayout(hbox_layout);
    setLayout(vbox_layout);
}

PersonCreateDialog::~PersonCreateDialog()
{
}

std::string PersonCreateDialog::GetPersName()
{
    QString text = PersName->text();
    return text.toUtf8().data();
}

std::string PersonCreateDialog::GetPersDesc()
{
    QString text = PersDescript->toPlainText();
    return text.toUtf8().data();
}
