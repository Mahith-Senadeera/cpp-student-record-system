#include "Course.h"
#include <iostream>
#include <iomanip>

Course::Course(const std::string& code, const std::string& name, int credits)
    : courseCode(code), courseName(name), creditHours(credits),
    grade(0.0), isGraded(false) {
}

void Course::setGrade(double g) {
    grade = g;
    isGraded = true;
}

void Course::displayInfo() const {
    std::cout << "Course Code: " << courseCode << "\n"
        << "Course Name: " << courseName << "\n"
        << "Credit Hours: " << creditHours << "\n";

    if (isGraded) {
        std::cout << "Grade: " << std::fixed << std::setprecision(2) << grade << "\n";
    }
    else {
        std::cout << "Grade: Not assigned\n";
    }
}