/********************************************************************************
** Form generated from reading UI file 'taskform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKFORM_H
#define UI_TASKFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TaskForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *TaskForm)
    {
        if (TaskForm->objectName().isEmpty())
            TaskForm->setObjectName(QStringLiteral("TaskForm"));
        TaskForm->resize(450, 340);
        verticalLayout = new QVBoxLayout(TaskForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_2 = new QPushButton(TaskForm);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        comboBox = new QComboBox(TaskForm);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_3->addWidget(comboBox);

        pushButton = new QPushButton(TaskForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_3);

        treeWidget = new QTreeWidget(TaskForm);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setEnabled(true);
        treeWidget->setHeaderHidden(true);

        verticalLayout->addWidget(treeWidget);


        retranslateUi(TaskForm);

        QMetaObject::connectSlotsByName(TaskForm);
    } // setupUi

    void retranslateUi(QWidget *TaskForm)
    {
        TaskForm->setWindowTitle(QApplication::translate("TaskForm", "Form", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("TaskForm", "Back To Pers", Q_NULLPTR));
        pushButton->setText(QApplication::translate("TaskForm", "add new", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("TaskForm", "Tasks", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TaskForm: public Ui_TaskForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKFORM_H
