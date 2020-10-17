#ifndef PERSONAGEBUTTON_H
#define PERSONAGEBUTTON_H

#include <QPushButton>

class PersonageButton : public QPushButton
{
    Q_OBJECT
public:
    PersonageButton(int digit, QWidget *parent);
    ~PersonageButton();
signals:
       void clicked(int digit);

private slots:
    void reemitClicked();

private:
    int PersId;
};

#endif // PERSONAGEBUTTON_H
