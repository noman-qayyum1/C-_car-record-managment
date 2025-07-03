//
// Created by Aurangzaib on 28-01-2025.
//
#include "DatabaseManager.h"
#include <iostream>
#include <sstream>

using namespace std;

DatabaseManager::DatabaseManager()
{
    conn = mysql_init(nullptr);
}

DatabaseManager::~DatabaseManager()
{
    closeConnection();
}

bool DatabaseManager::connect(const string &host,
                              const string &user,
                              const string &password,
                              const string &dbName,
                              unsigned int port)
{
    if (!conn)
    {
        cerr << "MySQL init failed!" << endl;
        return false;
    }

    MYSQL *p = mysql_real_connect(conn, host.c_str(), user.c_str(),
                                  password.c_str(), dbName.c_str(),
                                  port, nullptr, 0);

    if (!p)
    {
        cerr << "MySQL Connection Error: " << mysql_error(conn) << endl;
        return false;
    }

    cout << "Connected to MySQL successfully." << endl;
    return true;
}

bool DatabaseManager::createRecord(const DerivedEntity &entity)
{
    if (!conn)
        return false;

    // Prepare query
    // Table structure: id INT PRIMARY KEY, name VARCHAR, age INT, course VARCHAR, gpa DOUBLE
    // Insert
    ostringstream oss;
    oss << "INSERT INTO students (id, name, age, course, gpa) VALUES ("
        << entity.getId() << ", '"
        << entity.getName() << "', "
        << entity.getAge() << ", '"
        << entity.getCourse() << "', "
        << entity.getGpa() << ");";

    string query = oss.str();
    if (mysql_query(conn, query.c_str()) != 0)
    {
        cerr << "CreateRecord Error: " << mysql_error(conn) << endl;
        return false;
    }
    return true;
}

bool DatabaseManager::readAllRecords(vector<DerivedEntity> &entities)
{
    entities.clear();
    if (!conn)
        return false;

    string query = "SELECT id, name, age, course, gpa FROM students;";
    if (mysql_query(conn, query.c_str()) != 0)
    {
        cerr << "ReadAllRecords Error: " << mysql_error(conn) << endl;
        return false;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res)
    {
        cerr << "StoreResult Error: " << mysql_error(conn) << endl;
        return false;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)))
    {
        // row[0] = id, row[1] = name, etc.
        DerivedEntity ent;
        ent.setId(stoi(row[0] ? row[0] : "0"));
        ent.setName(row[1] ? row[1] : "");
        ent.setAge(stoi(row[2] ? row[2] : "0"));
        ent.setCourse(row[3] ? row[3] : "");
        ent.setGpa(stod(row[4] ? row[4] : "0.0"));

        entities.push_back(ent);
    }

    mysql_free_result(res);
    return true;
}

bool DatabaseManager::updateRecord(const DerivedEntity &entity)
{
    if (!conn)
        return false;

    ostringstream oss;
    oss << "UPDATE students SET "
        << "name='" << entity.getName() << "', "
        << "age=" << entity.getAge() << ", "
        << "course='" << entity.getCourse() << "', "
        << "gpa=" << entity.getGpa()
        << " WHERE id=" << entity.getId() << ";";

    string query = oss.str();
    if (mysql_query(conn, query.c_str()) != 0)
    {
        cerr << "UpdateRecord Error: " << mysql_error(conn) << endl;
        return false;
    }
    return true;
}

bool DatabaseManager::deleteRecord(int id)
{
    if (!conn)
        return false;

    ostringstream oss;
    oss << "DELETE FROM students WHERE id=" << id << ";";

    string query = oss.str();
    if (mysql_query(conn, query.c_str()) != 0)
    {
        cerr << "DeleteRecord Error: " << mysql_error(conn) << endl;
        return false;
    }
    return true;
}

void DatabaseManager::closeConnection()
{
    if (conn)
    {
        mysql_close(conn);
        conn = nullptr;
    }
}
