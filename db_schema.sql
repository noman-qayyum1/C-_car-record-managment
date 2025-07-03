-- Create a database for this project (if not existing):
CREATE DATABASE IF NOT EXISTS cpp_oop_db;
USE cpp_oop_db;

-- Create a simple table for 'students' (matching our DerivedEntity fields)
DROP TABLE IF EXISTS students;
CREATE TABLE students (
    id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    age INT,
    course VARCHAR(100),
    gpa DOUBLE
);

-- Optionally, insert some initial data (comment out if not needed)
-- INSERT INTO students (id, name, age, course, gpa) VALUES
-- (1, 'Alice', 20, 'Computer Science', 3.8),
-- (2, 'Bob', 22, 'Mathematics', 3.5);
