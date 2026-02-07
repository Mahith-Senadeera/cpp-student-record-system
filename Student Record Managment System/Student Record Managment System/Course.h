#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
private:
    std::string courseCode;
    std::string courseName;
    int creditHours;
    double grade;
    bool isGraded;

public:
    Course() : creditHours(0), grade(0.0), isGraded(false) {}
    Course(const std::string& code, const std::string& name, int credits);

    std::string getCode() const { return courseCode; }
    std::string getName() const { return courseName; }
    int getCredits() const { return creditHours; }
    double getGrade() const { return grade; }
    bool hasGrade() const { return isGraded; }

    void setGrade(double g);
    void displayInfo() const;
};

#endif