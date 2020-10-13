#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>
#include "../Core/engine.h"

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(Engine *engine, int pers_id, QWidget *parent = nullptr);
    ~TaskForm();

private:
    Engine* Engine_instance;
    Ui::TaskForm *ui;
};

#endif // TASKFORM_H
