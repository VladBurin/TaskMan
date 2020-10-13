/********************************************************************************
** Form generated from reading UI file 'personagemenu.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONAGEMENU_H
#define UI_PERSONAGEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PersonageMenu
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButton;

    void setupUi(QWidget *PersonageMenu)
    {
        if (PersonageMenu->objectName().isEmpty())
            PersonageMenu->setObjectName(QStringLiteral("PersonageMenu"));
        PersonageMenu->resize(400, 300);
        verticalLayout = new QVBoxLayout(PersonageMenu);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        verticalLayout->addLayout(gridLayout);

        pushButton = new QPushButton(PersonageMenu);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(PersonageMenu);

        QMetaObject::connectSlotsByName(PersonageMenu);
    } // setupUi

    void retranslateUi(QWidget *PersonageMenu)
    {
        PersonageMenu->setWindowTitle(QApplication::translate("PersonageMenu", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PersonageMenu", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PersonageMenu: public Ui_PersonageMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONAGEMENU_H
