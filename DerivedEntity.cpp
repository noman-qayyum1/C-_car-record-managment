//
// Created by Aurangzaib on 28-01-2025.
//
#include "DerivedEntity.h"
#include <iostream>
#include <limits>

using namespace std;

DerivedEntity::DerivedEntity()
    : Entity(), course(""), gpa(0.0)
{
}

DerivedEntity::DerivedEntity(int id, const string &name, int age,
                             const string &course, double gpa)
    : Entity(id, name, age), course(course), gpa(gpa)
{
}

DerivedEntity::~DerivedEntity()
{
}

string DerivedEntity::getCourse() const
{
    return course;
}

void DerivedEntity::setCourse(const string &newCourse)
{
    course = newCourse;
}

double DerivedEntity::getGpa() const
{
    return gpa;
}

void DerivedEntity::setGpa(double newGpa)
{
    gpa = newGpa;
}

// Overridden methods
void DerivedEntity::inputData()
{
    // Call base method to get common fields
    Entity::inputData();

    cout << "Enter Course: ";
    getline(cin, course);

    cout << "Enter GPA: ";
    cin >> gpa;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void DerivedEntity::displayData() const
{
    // Base method
    Entity::displayData();
    cout << ", Course: " << course << ", GPA: " << gpa << endl;
}
