//
// Created by Aurangzaib on 28-01-2025.
//
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#ifdef _WIN32
  #include <winsock2.h>
  #include <windows.h>
  // On Windows, typically it's <mysql.h> directly in the 'include' folder.
  #include <mysql.h>
#else
  // On Linux or other Unix systems, it's often <mysql/mysql.h>
  #include <mysql/mysql.h>
#endif

#include <string>
#include <vector>
#include "DerivedEntity.h"

using namespace std;

class DatabaseManager
{
private:
    MYSQL* conn;

public:
    DatabaseManager();
    ~DatabaseManager();

    bool connect(const string &host,
                 const string &user,
                 const string &password,
                 const string &dbName,
                 unsigned int port = 3306);

    bool createRecord(const DerivedEntity &entity);
    bool readAllRecords(vector<DerivedEntity> &entities);
    bool updateRecord(const DerivedEntity &entity);
    bool deleteRecord(int id);

    void closeConnection();
};

#endif
