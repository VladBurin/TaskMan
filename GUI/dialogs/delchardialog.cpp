#include "delchardialog.h"

DelCharDialog::DelCharDialog(std::string name,  QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("Deleting character");

    Massage = new QLabel("You're going to delete character: " + QString::fromStdString(name) +"\n"
                         +"all skills and tasks belong to this character will be deleted");

    OkButton = new QPushButton("Ok");
    CancelButton = new QPushButton("Cancel");

    connect(OkButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(CancelButton,SIGNAL(clicked()),this, SLOT(reject()));

    QHBoxLayout* hbox_layout = new QHBoxLayout;
    hbox_layout->addWidget(OkButton);
    hbox_layout->addWidget(CancelButton);

    QVBoxLayout* vbox_layout = new QVBoxLayout;
    vbox_layout->addWidget(Massage);
    vbox_layout->addLayout(hbox_layout);
    setLayout(vbox_layout);
}

DelCharDialog::~DelCharDialog()
{
}
