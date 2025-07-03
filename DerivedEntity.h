//
// Created by Aurangzaib on 28-01-2025.
//
#ifndef DERIVEDENTITY_H
#define DERIVEDENTITY_H

#include "Entity.h"
#include <string>

using namespace std;

// Example derived class: "Student"
class DerivedEntity : public Entity
{
private:
    string course;
    double gpa;

public:
    DerivedEntity();
    DerivedEntity(int id, const string &name, int age, const string &course, double gpa);
    virtual ~DerivedEntity();

    // Getters/Setters
    string getCourse() const;
    void setCourse(const string &newCourse);

    double getGpa() const;
    void setGpa(double newGpa);

    // Overridden input and display
    void inputData() override;
    void displayData() const override;
};

#endif
