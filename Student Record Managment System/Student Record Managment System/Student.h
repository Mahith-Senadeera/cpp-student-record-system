#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <memory>
#include <map>

class Course;

class Student { // PascalCase for class names
private:
    std::string studentId;  // camelCase for member variables
    std::string name;
    std::string email;
    std::map<std::string, std::shared_ptr<Course>> enrolledCourses; // Descriptive name

public:
    Student() = default;
    Student(const std::string& id, const std::string& name, const std::string& email);

    // camelCase for methods
    std::string getId() const { return studentId; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }

    void setName(const std::string& newName) { name = newName; }
    void setEmail(const std::string& newEmail) { email = newEmail; }

    void enrollCourse(std::shared_ptr<Course> course);
    void dropCourse(const std::string& courseCode);
    void setGrade(const std::string& courseCode, double grade);

    double calculateGPA() const;
    void displayInfo() const;
    void displayTranscript() const;

    const std::map<std::string, std::shared_ptr<Course>>& getCourses() const {
        return enrolledCourses;
    }
};

#endif