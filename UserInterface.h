//
// Created by Aurangzaib on 28-01-2025.
//
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "FileManager.h"
#include "DatabaseManager.h"
#include "SyncManager.h"

class UserInterface
{
private:
    // We’ll manage these objects here
    FileManager fileManager;
    DatabaseManager dbManager;
    SyncManager *syncManager; // pointer to manage lifetime easily

public:
    UserInterface();
    ~UserInterface();

    void run(); // main menu

private:
    void showMenu();
    void handleAddRecord();
    void handleViewRecords();
    void handleEditRecord();
    void handleDeleteRecord();
    void handleSync();

    // Helpers
    void initDatabaseConnection();
};

#endif
