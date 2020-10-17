#include "personcreatedialog.h"
#include "ui_personcreatedialog.h"

PersonCreateDialog::PersonCreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonCreateDialog)
{
    ui->setupUi(this);
}

PersonCreateDialog::~PersonCreateDialog()
{
    delete ui;
}
