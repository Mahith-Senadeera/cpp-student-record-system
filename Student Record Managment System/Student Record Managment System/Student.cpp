#include "Student.h"
#include "Course.h"
#include <iostream>
#include <iomanip>

Student::Student(const std::string& id, const std::string& name, const std::string& email)
    : studentId(id), name(name), email(email) {
}

void Student::enrollCourse(std::shared_ptr<Course> course) {
    if (course) {
        enrolledCourses[course->getCode()] = course;
    }
}

void Student::dropCourse(const std::string& courseCode) {
    enrolledCourses.erase(courseCode);
}

void Student::setGrade(const std::string& courseCode, double grade) {
    auto it = enrolledCourses.find(courseCode);
    if (it != enrolledCourses.end()) {
        it->second->setGrade(grade);
    }
}

double Student::calculateGPA() const {
    if (enrolledCourses.empty()) return 0.0;

    double totalPoints = 0.0;
    int totalCredits = 0;

    for (const auto& [code, course] : enrolledCourses) {
        if (course->hasGrade()) {
            totalPoints += course->getGrade() * course->getCredits();
            totalCredits += course->getCredits();
        }
    }

    return totalCredits > 0 ? totalPoints / totalCredits : 0.0;
}

void Student::displayInfo() const {
    std::cout << "Student ID: " << studentId << "\n"
        << "Name: " << name << "\n"
        << "Email: " << email << "\n"
        << "GPA: " << std::fixed << std::setprecision(2) << calculateGPA() << "\n"
        << "Enrolled Courses: " << enrolledCourses.size() << "\n";
}

void Student::displayTranscript() const {
    std::cout << "\n=== TRANSCRIPT ===\n";
    std::cout << "Student: " << name << " (ID: " << studentId << ")\n";
    std::cout << "Email: " << email << "\n\n";

    std::cout << std::left << std::setw(10) << "Code"
        << std::setw(30) << "Course Name"
        << std::setw(10) << "Credits"
        << std::setw(10) << "Grade" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (const auto& [code, course] : enrolledCourses) {
        std::cout << std::left << std::setw(10) << course->getCode()
            << std::setw(30) << course->getName()
            << std::setw(10) << course->getCredits();

        if (course->hasGrade()) {
            std::cout << std::fixed << std::setprecision(2) << course->getGrade();
        }
        else {
            std::cout << "N/A";
        }
        std::cout << "\n";
    }

    std::cout << std::string(60, '-') << "\n";
    std::cout << "GPA: " << std::fixed << std::setprecision(2) << calculateGPA() << "\n";
}