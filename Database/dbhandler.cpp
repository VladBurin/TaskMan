#include "dbhandler.h"

DBhandler::DBhandler()
{
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setUserName("vlad");
    db.setPassword("2021");
    db.open();

}

DBhandler::~DBhandler()
{

}


void DBhandler::CreateBase(std::string base_name)
{
    // Создание database
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.exec("CREATE DATABASE IF NOT EXISTS " + QString::fromStdString(base_name) + ";");
        db.setDatabaseName(QString::fromStdString(base_name));
    }
}

void DBhandler::CreateTable(std::string full_description)
{
    if(db.open())
    {
        QString str = "CREATE TABLE IF NOT EXISTS " + QString::fromStdString(full_description) + ";";
        QSqlQuery Query(str);
        Query.exec();
        return;
    }
}


void DBhandler::AddCharacter(Character* pers)
{
    ll id = pers->GetId();

    std::string name = pers->GetName();

    std::string descript = pers->GetDescript();

    ll level = pers->GetLevel();

    ll current_score = pers->GetCurrentLevelScore();

    ll task_skill_id = pers->GetTaskSkillId();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO characters (id, name, description, level, current_score, task_skill_id) "
                      "VALUES(:id, :name, :description, :level, :current_score, :task_skill_id);");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":current_score", current_score);
        Query.bindValue(":task_skill_id", task_skill_id);
        Query.exec();
        return;
    }

}

void DBhandler::AddSkill(Skill* skill)
{
    ll id = skill->GetId();

    std::string name = skill->GetName();

    std::string descript = skill->GetDescript();

    ll level = skill->GetLevel();

    ll current_score = skill->GetCurrentLevelScore();

    ll char_id = skill->GetCharId();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO skills (id, name, description, level, current_score, char_id) "
                      "VALUES(:id, :name, :description, :level, :current_score, :char_id);");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":current_score", current_score);
        Query.bindValue(":char_id", char_id);
        Query.exec();
        return;
    }

}

void DBhandler::AddTask(TaskUnit* task)
{
    ll id = task->GetId();

    std::string name = task->GetName();

    std::string descript = task->GetDescript();

    ll score = task->GetScoresForTask();

    ll belong_skill_id = task->GetBelongId();

    ll parent_task = task->GetParentId();

    bool complete = task->GetCompletStatus();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("INSERT INTO tasks "
                      "( id, name, description, score, belong_skill_id, parent_task, complete ) "
                      "VALUES(:id, :name, :description, :score, :belong_skill_id, :parent_task, :complete); ");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":score", score);
        Query.bindValue(":belong_skill_id", belong_skill_id);
        Query.bindValue(":parent_task", parent_task);
        Query.bindValue(":complete", complete);
        Query.exec();
        return;
    }
}


void DBhandler::CharUpdate(Character* pers)
{
    ll id = pers->GetId();

    std::string name = pers->GetName();

    std::string descript = pers->GetDescript();

    ll level = pers->GetLevel();

    ll current_score = pers->GetCurrentLevelScore();

    ll task_skill_id = pers->GetTaskSkillId();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("UPDATE characters "
                      "SET name = :name, "
                      "description = :description, "
                      "level =  :level,"
                      "current_score = :current_score, "
                      "task_skill_id = :task_skill_id "
                      "WHERE id = :id;");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":current_score", current_score);
        Query.bindValue(":task_skill_id", task_skill_id);
        Query.exec();
        return;
    }
}

void DBhandler::SkillUpdate(Skill* skill)
{
    ll id = skill->GetId();

    std::string name = skill->GetName();

    std::string descript = skill->GetDescript();

    ll level = skill->GetLevel();

    ll current_score = skill->GetCurrentLevelScore();

    ll char_id = skill->GetCharId();

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("UPDATE skills "
                      "SET name = :name, "
                      "description = :description, "
                      "level =  :level, "
                      "current_score = :current_score,"
                      "char_id = :char_id "
                      "WHERE id = :id;");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":level", level);
        Query.bindValue(":current_score", current_score);
        Query.bindValue(":char_id", char_id);
        Query.exec();
        return;
    }
}

void DBhandler::TaskUpdate(TaskUnit* task)
{
    ll id = task->GetId();

    std::string name = task->GetName();

    std::string descript = task->GetDescript();

    ll score = task->GetScoresForTask();

    ll belong_skill_id = task->GetBelongId();

    ll parent_task = task->GetParentId();

    bool complete = task->GetCompletStatus();

    if(db.open())
    {
        QSqlQuery Query(db);

        Query.prepare("UPDATE tasks "
                      "SET name = :name, "
                      "description = :description, "
                      "score =  :score, "
                      "belong_skill_id = :belong_skill_id,"
                      "parent_task = :parent_task, "
                      "complete = :complete "
                      "WHERE id = :id;");

        Query.bindValue(":id", id);
        Query.bindValue(":name", QString::fromStdString(name));
        Query.bindValue(":description", QString::fromStdString(descript));
        Query.bindValue(":score", score);
        Query.bindValue(":belong_skill_id", belong_skill_id);
        Query.bindValue(":parent_task", parent_task);
        Query.bindValue(":complete", complete);
        Query.exec();
        return;
    }
}


void DBhandler::DeleteCharacter(ll id)
{
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("DELETE FROM characters "
                      "WHERE id = :id;");
        Query.bindValue(":id",id);
        Query.exec();
        return;
    }
}

void DBhandler::DeleteSkill(ll id)
{
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("DELETE FROM skills "
                      "WHERE id = :id;");
        Query.bindValue(":id",id);
        Query.exec();
        return;
    }
}

void DBhandler::DeleteTask(ll id)
{
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("DELETE FROM tasks "
                      "WHERE id = :id;");
        Query.bindValue(":id",id);
        Query.exec();
        return;
    }
}


std::vector<Character> DBhandler::LoadCharacters()
{
    std::vector<Character> result;
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT * FROM characters;");

        Query.exec();
        QSqlRecord rec = Query.record();

        ll id = 0;
        std::string name;
        std::string descript;
        ll task_skill_id = 0;
        ll level = 0;
        ll current_score = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toLongLong();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            task_skill_id = Query.value(rec.indexOf("task_skill_id")).toString().toLongLong();
            level = Query.value(rec.indexOf("level")).toLongLong();
            current_score = Query.value(rec.indexOf("current_score")).toLongLong();

            result.push_back(Character(id, name, descript, task_skill_id, level, current_score));
        }
    }
    return result;
}

std::vector<Skill> DBhandler::LoadSkills()
{
    std::vector<Skill> result;
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT * FROM skills;");

        Query.exec();
        QSqlRecord rec = Query.record();

        ll id = 0;
        std::string name;
        std::string descript;
        ll level = 0;
        ll current_score = 0;
        ll char_id = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toLongLong();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            level = Query.value(rec.indexOf("level")).toLongLong();
            current_score = Query.value(rec.indexOf("current_score")).toLongLong();
            char_id = Query.value(rec.indexOf("char_id")).toLongLong();
            result.push_back(Skill(id,char_id,name,descript,level,current_score));
        }
    }
    return result;
}

std::vector<TaskUnit> DBhandler::LoadTasks()
{
    std::vector<TaskUnit> result;
    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT * FROM tasks;");

        Query.exec();
        QSqlRecord rec = Query.record();

        ll id = 0;
        std::string name;
        std::string descript;
        ll score = 0;
        ll belong_id = 0;
        ll par_id = 0;
        bool complete = false;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toLongLong();
            name = Query.value(rec.indexOf("name")).toString().toUtf8().data();
            descript = Query.value(rec.indexOf("description")).toString().toUtf8().data();
            score = Query.value(rec.indexOf("score")).toLongLong();
            belong_id = Query.value(rec.indexOf("belong_skill_id")).toLongLong();
            par_id = Query.value(rec.indexOf("parent_task")).toLongLong();
            complete = Query.value(rec.indexOf("complete")).toBool();

            result.push_back(TaskUnit(id, name, descript, score, belong_id, par_id, complete));
        }
    }
    return result;
}


std::vector<ll> DBhandler::GetChildsById(ll parent_id)
{
    std::vector<ll> result;

    if(db.open())
    {
        QSqlQuery Query(db);
        Query.prepare("SELECT id FROM tasks WHERE parent_task = :parent_id;");
        Query.bindValue(":parent_id", parent_id);

        Query.exec();
        QSqlRecord rec = Query.record();

        ll id = 0;

        while(Query.next())
        {
            id = Query.value(rec.indexOf("id")).toLongLong();
            result.push_back(id);
        }

        return result;
    }

}
