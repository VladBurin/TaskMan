#ifndef SKILLCREATEDIALOG_H
#define SKILLCREATEDIALOG_H

#include <QDialog>

namespace Ui {
class SkillCreateDIalog;
}

class SkillCreateDIalog : public QDialog
{
    Q_OBJECT

public:
    explicit SkillCreateDIalog(QWidget *parent = nullptr);
    ~SkillCreateDIalog();

private:
    Ui::SkillCreateDIalog *ui;
};

#endif // SKILLCREATEDIALOG_H
