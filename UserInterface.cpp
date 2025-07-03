//
// Created by Aurangzaib on 28-01-2025.
//
#include "UserInterface.h"
#include <iostream>
#include <limits>

using namespace std;

UserInterface::UserInterface()
    : fileManager("data.txt"), dbManager(), syncManager(nullptr)
{
    // Initialize DB connection
    initDatabaseConnection();

    // Create the sync manager once DB is connected
    syncManager = new SyncManager(fileManager, dbManager);
}

UserInterface::~UserInterface()
{
    if (syncManager)
    {
        delete syncManager;
        syncManager = nullptr;
    }
    dbManager.closeConnection();
}

// Connect to MySQL (adjust host, user, password, dbName, port to your environment)
void UserInterface::initDatabaseConnection()
{
    bool success = dbManager.connect("localhost", "root", "password", "cpp_oop_db", 3306);
    if (!success)
    {
        cerr << "Warning: Could not connect to DB. Database features will fail.\n";
    }
}

void UserInterface::run()
{
    bool exitRequested = false;
    while (!exitRequested)
    {
        showMenu();
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            handleAddRecord();
            break;
        case 2:
            handleViewRecords();
            break;
        case 3:
            handleEditRecord();
            break;
        case 4:
            handleDeleteRecord();
            break;
        case 5:
            handleSync();
            break;
        case 0:
            exitRequested = true;
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

void UserInterface::showMenu()
{
    cout << "\n========== MAIN MENU ==========\n";
    cout << "1. Add a record\n";
    cout << "2. View records\n";
    cout << "3. Edit a record\n";
    cout << "4. Delete a record\n";
    cout << "5. Synchronize data (File <-> DB)\n";
    cout << "0. Exit\n";
    cout << "==============================\n";
}

void UserInterface::handleAddRecord()
{
    DerivedEntity newEntity;
    cout << "\n-- Add New Record --\n";
    newEntity.inputData();

    // Ask user: "File, DB, or Both?"
    cout << "Where do you want to store the record?\n";
    cout << "1. File only\n";
    cout << "2. Database only\n";
    cout << "3. Both file and database\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool success = false;
    switch (choice)
    {
    case 1:
        success = fileManager.saveToFile(newEntity, true);
        break;
    case 2:
        success = dbManager.createRecord(newEntity);
        break;
    case 3:
        success = fileManager.saveToFile(newEntity, true);
        if (success)
        {
            success = dbManager.createRecord(newEntity);
        }
        break;
    default:
        cout << "Invalid choice, record not added.\n";
        return;
    }

    if (success)
        cout << "Record added successfully.\n";
    else
        cout << "Failed to add record.\n";
}

void UserInterface::handleViewRecords()
{
    cout << "\n-- View Records --\n";
    cout << "1. View from file\n";
    cout << "2. View from database\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice)
    {
    case 1:
    {
        vector<DerivedEntity> entities;
        if (!fileManager.loadFromFile(entities))
        {
            cout << "No records (or error loading file).\n";
            return;
        }
        cout << "Loaded " << entities.size() << " record(s) from file:\n";
        for (auto &e : entities)
        {
            e.displayData();
        }
        break;
    }
    case 2:
    {
        vector<DerivedEntity> entities;
        if (!dbManager.readAllRecords(entities))
        {
            cout << "Error reading from database.\n";
            return;
        }
        cout << "Loaded " << entities.size() << " record(s) from DB:\n";
        for (auto &e : entities)
        {
            e.displayData();
        }
        break;
    }
    default:
        cout << "Invalid choice.\n";
    }
}

void UserInterface::handleEditRecord()
{
    cout << "\n-- Edit a Record --\n";
    cout << "Enter ID of the record to edit: ";
    int editId;
    cin >> editId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Ask user: file, db or both?
    cout << "Edit in:\n";
    cout << "1. File only\n";
    cout << "2. Database only\n";
    cout << "3. Both\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // We need the old data to show or we can just input new data from scratch
    cout << "Now input new data:\n";
    DerivedEntity updatedEntity;
    updatedEntity.setId(editId);
    updatedEntity.inputData();

    bool success = false;
    switch (choice)
    {
    case 1:
        // Update in file
        success = fileManager.updateInFile(updatedEntity);
        break;
    case 2:
        // Update in DB
        success = dbManager.updateRecord(updatedEntity);
        break;
    case 3:
        // Update in both
        success = fileManager.updateInFile(updatedEntity);
        if (success)
        {
            success = dbManager.updateRecord(updatedEntity);
        }
        break;
    default:
        cout << "Invalid choice, no update performed.\n";
        return;
    }

    if (success)
        cout << "Record updated successfully.\n";
    else
        cout << "Failed to update record.\n";
}

void UserInterface::handleDeleteRecord()
{
    cout << "\n-- Delete a Record --\n";
    cout << "Enter ID of the record to delete: ";
    int delId;
    cin >> delId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Delete from:\n";
    cout << "1. File only\n";
    cout << "2. Database only\n";
    cout << "3. Both\n";
    cout << "Choice: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool success = false;
    switch (choice)
    {
    case 1:
        success = fileManager.removeFromFile(delId);
        break;
    case 2:
        success = dbManager.deleteRecord(delId);
        break;
    case 3:
        success = fileManager.removeFromFile(delId);
        if (success)
        {
            success = dbManager.deleteRecord(delId);
        }
        break;
    default:
        cout << "Invalid choice, no deletion performed.\n";
        return;
    }

    if (success)
        cout << "Record deleted successfully.\n";
    else
        cout << "Failed to delete record.\n";
}

void UserInterface::handleSync()
{
    cout << "\n-- Synchronize File and Database --\n";
    if (!syncManager)
    {
        cout << "SyncManager not initialized.\n";
        return;
    }

    bool success = syncManager->syncFileAndDatabase();
    if (success)
        cout << "Synchronization complete.\n";
    else
        cout << "Synchronization failed.\n";
}
