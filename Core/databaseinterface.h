#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H
#include <string>

class DataBaseInterface
{
public:
    DataBaseInterface();
    virtual ~DataBaseInterface();
    virtual void CreateBase(std::string base_name) = 0;
    virtual void CreateTable(std::string full_description) = 0;
};

#endif // DATABASEINTERFACE_H
