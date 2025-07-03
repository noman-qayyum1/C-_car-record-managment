//
// Created by Aurangzaib on 28-01-2025.
//
#include "Entity.h"
#include <iostream>
#include <limits>  // <-- Needed for numeric_limits<streamsize>::max()

using namespace std;

// Default constructor
Entity::Entity() : id(0), name(""), age(0)
{
}

// Parameterized constructor
Entity::Entity(int id, const string &name, int age)
    : id(id), name(name), age(age)
{
}

// Destructor
Entity::~Entity()
{
}

// Getters/Setters
int Entity::getId() const
{
    return id;
}
void Entity::setId(int newId)
{
    id = newId;
}

string Entity::getName() const
{
    return name;
}
void Entity::setName(const string &newName)
{
    name = newName;
}

int Entity::getAge() const
{
    return age;
}
void Entity::setAge(int newAge)
{
    age = newAge;
}

// Input and display
void Entity::inputData()
{
    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
}

void Entity::displayData() const
{
    cout << "ID: " << id << ", Name: " << name << ", Age: " << age;
}
