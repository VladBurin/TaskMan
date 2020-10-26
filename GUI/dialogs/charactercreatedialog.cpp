#include "charactercreatedialog.h"

CharCreateDialog::CharCreateDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Create new character");

    EnterNameLabel = new QLabel("Character name");
    CharName = new QLineEdit;

    EnterDescLabel = new QLabel("Character description");
    CharDescript = new QTextEdit;

    OkButton = new QPushButton("Ok");
    CancelButton = new QPushButton("Cancel");


    connect(OkButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(CancelButton,SIGNAL(clicked()),this, SLOT(reject()));

    QHBoxLayout* hbox_layout = new QHBoxLayout;
    hbox_layout->addWidget(OkButton);
    hbox_layout->addWidget(CancelButton);

    QVBoxLayout* vbox_layout = new QVBoxLayout;
    vbox_layout->addWidget(EnterNameLabel);
    vbox_layout->addWidget(CharName);
    vbox_layout->addWidget(EnterDescLabel);
    vbox_layout->addWidget(CharDescript);
    vbox_layout->addLayout(hbox_layout);
    setLayout(vbox_layout);
}

CharCreateDialog::~CharCreateDialog()
{
}

std::string CharCreateDialog::GetPersName()
{
    QString text = CharName->text();
    return text.toUtf8().data();
}

std::string CharCreateDialog::GetPersDesc()
{
    QString text = CharDescript->toPlainText();
    return text.toUtf8().data();
}
