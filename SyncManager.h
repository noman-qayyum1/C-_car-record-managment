//
// Created by Aurangzaib on 28-01-2025.
//
#ifndef SYNCMANAGER_H
#define SYNCMANAGER_H

#include <vector>
#include "DerivedEntity.h"
#include "FileManager.h"
#include "DatabaseManager.h"

using namespace std;

class SyncManager
{
private:
    FileManager &fileManager;
    DatabaseManager &dbManager;

public:
    SyncManager(FileManager &fm, DatabaseManager &dbm);
    ~SyncManager();

    // Synchronize data between file and database
    // Strategy:
    // 1) Load file records, load DB records
    // 2) If record is missing in DB, add it
    // 3) If record is missing in file, add it
    // 4) If record is outdated, update it accordingly
    // (For demonstration, we keep it simple)
    bool syncFileAndDatabase();
};

#endif
