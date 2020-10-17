#ifndef PERSONAGEBUTTON_H
#define PERSONAGEBUTTON_H

#include <QPushButton>

class PersonageButton : public QPushButton
{
    Q_OBJECT
public:
    PersonageButton(int id, std::string name, QWidget *parent = nullptr);
    ~PersonageButton();
signals:
       void clicked(int id);

private slots:
    void reemitClicked();

private:
    int PersId;
};

#endif // PERSONAGEBUTTON_H
