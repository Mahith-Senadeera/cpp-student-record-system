#ifndef RECORD_MANAGER_H
#define RECORD_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <exception>
#include "Student.h"
#include "Course.h"

class RecordException : public std::exception {
private:
    std::string message;
public:
    explicit RecordException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class RecordManager {
private:
    std::vector<std::unique_ptr<Student>> students;
    std::vector<std::shared_ptr<Course>> availableCourses;

    Student* findStudent(const std::string& id);
    std::shared_ptr<Course> findCourse(const std::string& code);
    bool isValidEmail(const std::string& email) const;
    bool isValidGrade(double grade) const;

public:
    void addStudent(const std::string& id, const std::string& name, const std::string& email);
    void removeStudent(const std::string& id);
    void updateStudent(const std::string& id, const std::string& name, const std::string& email);
    Student* searchStudent(const std::string& id);

    void addCourse(const std::string& code, const std::string& name, int credits);
    void enrollStudentInCourse(const std::string& studentId, const std::string& courseCode);
    void assignGrade(const std::string& studentId, const std::string& courseCode, double grade);

    void displayAllStudents() const;
    void displayAvailableCourses() const;
    void displayStudentTranscript(const std::string& studentId);

    void displayStatistics() const;
    void loadMockData();
};

#endif