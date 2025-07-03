//
// Created by Aurangzaib on 28-01-2025.
//
#ifndef ENTITY_H
#define ENTITY_H

#include <string>

using namespace std;

class Entity
{
protected:
    int id;           // Unique ID
    string name;      // Example attribute
    int age;          // Example attribute

public:
    Entity();
    Entity(int id, const string &name, int age);
    virtual ~Entity();

    // Getters and Setters
    virtual int getId() const;
    virtual void setId(int newId);

    virtual string getName() const;
    virtual void setName(const string &newName);

    virtual int getAge() const;
    virtual void setAge(int newAge);

    // For input/output and display
    virtual void inputData();   // Basic data input
    virtual void displayData() const; // Basic data output

    // Could add more methods for polymorphism or override in subclasses
};

#endif
