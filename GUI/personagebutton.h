#ifndef PERSONAGEBUTTON_H
#define PERSONAGEBUTTON_H

#include <QPushButton>
#include <QAction>
//TODO create actions for delete and edit personage

class PersonageButton : public QPushButton
{
    Q_OBJECT
public:
    PersonageButton(int id, std::string name, QWidget *parent = nullptr);
    virtual ~PersonageButton();

    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);

signals:
       void clicked(int id);

       void PersEnter(int id);

       void PersLeave();

       void DeletePers(int id);

       void EditPersonage(int id);


private slots:
    void reemitClicked();

    void reemitEditPers();

    void reemitDelPers();

private:
    int PersId;
};

#endif // PERSONAGEBUTTON_H
