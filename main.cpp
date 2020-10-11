//#include "mainwindow.h"

//#include <QApplication>
#include <iostream>
#include "Core/engine.h"
#include <QtSql>

int main(int argc, char *argv[])
{
     //QApplication a(argc, argv);

//    MainWindow w;
//    w.show();

//    return a.exec();

    Engine* MainEngine = Engine::getInstance();

    MainEngine->CreatePers("Vlad","new description");
    MainEngine->CreatePers("Juliy","new description");
    MainEngine->CreatePers("Igor","new description");
    //MainEngine->CreatePers("Rob","no");

    /*
    MainEngine->CreateSkill(1,"Ability","Just Descript");
    MainEngine->CreateSkill(1,"Jump","Just Descript pop");
    MainEngine->CreateSkill(0,"Strength","Just Descript tup");
    */
    /*
    // Для 1-го персонажа
    // Добавление двух задач в 1 персонажа
    MainEngine->CreateTask(1,-11,"Task0","Descript1",500,true);
    MainEngine->CreateTask(1,-11,"Task1","Descript11",1000,true);

    // Добавление 2-ух подзадач для 2-ой задачи и для 3-ой
    MainEngine->CreateTask(1,1,"Task2", "Descript2",700,true);
    MainEngine->CreateTask(1,1,"Task3", "Descript22",900,true);
    MainEngine->CreateTask(1,2,"Task4","Descript3",800,true);
    MainEngine->CreateTask(1,2,"Task5","Descript5",800,true);

    // Для 2-го скила (у о-го персонажа)
    MainEngine->CreateTask(2,-11,"Task6", "Descript2",700,true);
    MainEngine->CreateTask(2,6,"Task7", "Descript22",900,true);
    MainEngine->CreateTask(2,6,"Task8","Descript3",800,true);
    */

    MainEngine->TaskComplete(4);
    MainEngine->TaskComplete(3);
    MainEngine->TaskComplete(0);

    /*
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString path = "/home/vladburin/TaskMan/Database";

    db.setHostName("localhost");
    //db.setDatabaseName("dbname");
    db.setUserName("vlad");
    db.setPassword("2021");
    bool ok = db.open();

    // Создание database
    if(db.open())
    {
        QSqlQuery Query(db);
        if (Query.exec("CREATE DATABASE IF NOT EXISTS TaskManDB"))
          qDebug() << "Ok";
        else
            qDebug() << "Error query";
    }
    else
        qDebug() << "Error open";

    QSqlQuery Query(db);

    //Query.exec("CREATE TABLE IF NOT EXISTS ")

    if(!ok)
        std::cout << db.lastError().text().toUtf8().data() << std::endl;
    else
        std::cout << "done" <<std::endl;

    QStringList lst = db.tables();

    foreach (QString str, lst)
    {
        std::cout << str.toUtf8().data() << std::endl;
    }
    //Personage* curr_pers = MainEngine->GetPersById(0);
    */

    return 0;
}
