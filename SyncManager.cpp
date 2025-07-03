//
// Created by Aurangzaib on 28-01-2025.
//
#include "SyncManager.h"
#include <iostream>
#include <unordered_map>  // <--- IMPORTANT: Add this to use std::unordered_map

using namespace std;

SyncManager::SyncManager(FileManager &fm, DatabaseManager &dbm)
    : fileManager(fm), dbManager(dbm)
{
}

SyncManager::~SyncManager()
{
}

bool SyncManager::syncFileAndDatabase()
{
    // Load from file
    vector<DerivedEntity> fileEntities;
    fileManager.loadFromFile(fileEntities);

    // Load from DB
    vector<DerivedEntity> dbEntities;
    dbManager.readAllRecords(dbEntities);

    // Simple approach: build maps by ID for quick lookups
    // Then add or update as needed
    unordered_map<int, DerivedEntity> fileMap;
    for (auto &fe : fileEntities)
    {
        fileMap[fe.getId()] = fe;
    }

    unordered_map<int, DerivedEntity> dbMap;
    for (auto &de : dbEntities)
    {
        dbMap[de.getId()] = de;
    }

    // 1) For each file record, check if it's in the DB map
    for (auto &fPair : fileMap)
    {
        int id = fPair.first;
        DerivedEntity fileEntity = fPair.second;

        // If not in DB, add to DB
        if (dbMap.find(id) == dbMap.end())
        {
            cout << "Sync: Adding file record ID " << id << " to DB.\n";
            dbManager.createRecord(fileEntity);
        }
        else
        {
            // Exists in DB, check if data is different
            DerivedEntity dbEntity = dbMap[id];
            if (dbEntity.getName()   != fileEntity.getName()  ||
                dbEntity.getAge()    != fileEntity.getAge()   ||
                dbEntity.getCourse() != fileEntity.getCourse()||
                dbEntity.getGpa()    != fileEntity.getGpa())
            {
                cout << "Sync: Updating DB record ID " << id << " from file.\n";
                dbManager.updateRecord(fileEntity);
            }
        }
    }

    // 2) For each DB record, check if it's in the file map
    for (auto &dPair : dbMap)
    {
        int id = dPair.first;
        DerivedEntity dbEntity = dPair.second;

        // If not in file, add to file
        if (fileMap.find(id) == fileMap.end())
        {
            cout << "Sync: Adding DB record ID " << id << " to file.\n";
            fileManager.saveToFile(dbEntity, true); // append
        }
        else
        {
            // Exists in file, check if data is different
            DerivedEntity fileEntity = fileMap[id];
            if (dbEntity.getName()   != fileEntity.getName()  ||
                dbEntity.getAge()    != fileEntity.getAge()   ||
                dbEntity.getCourse() != fileEntity.getCourse()||
                dbEntity.getGpa()    != fileEntity.getGpa())
            {
                cout << "Sync: Updating file record ID " << id << " from DB.\n";
                fileManager.updateInFile(dbEntity);
            }
        }
    }

    cout << "Sync completed.\n";
    return true;
}
