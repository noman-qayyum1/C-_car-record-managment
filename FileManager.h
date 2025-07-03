//
// Created by Aurangzaib on 28-01-2025.
//
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "DerivedEntity.h"

using namespace std;

class FileManager
{
private:
    string fileName; // The path to your data file

public:
    FileManager(const string &fileName);
    ~FileManager();

    // Write
    bool saveToFile(const DerivedEntity &entity, bool append = true);
    // Overwrite the entire file with a list
    bool overwriteFile(const vector<DerivedEntity> &entities);

    // Read
    bool loadFromFile(vector<DerivedEntity> &entities);

    // Utility to remove a record by ID (we can do by reading everything, rewriting)
    bool removeFromFile(int id);

    // Utility to update a record in the file
    bool updateInFile(const DerivedEntity &entity);

private:
    // Helper to parse a line into a DerivedEntity
    DerivedEntity parseLine(const string &line);
};

#endif
