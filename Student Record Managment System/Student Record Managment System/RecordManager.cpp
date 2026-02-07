#include "RecordManager.h"
#include <iostream>
#include <algorithm>
#include <regex>
#include <iomanip>  

Student* RecordManager::findStudent(const std::string& id) {
    for (auto& student : students) {
        if (student->getId() == id) {
            return student.get();
        }
    }
    return nullptr;
}

std::shared_ptr<Course> RecordManager::findCourse(const std::string& code) {
    for (auto& course : availableCourses) {
        if (course->getCode() == code) {
            return course;
        }
    }
    return nullptr;
}

bool RecordManager::isValidEmail(const std::string& email) const {
    const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
    return std::regex_match(email, pattern);
}

bool RecordManager::isValidGrade(double grade) const {
    return grade >= 0.0 && grade <= 4.0;
}

void RecordManager::addStudent(const std::string& id, const std::string& name,
    const std::string& email) {
    if (findStudent(id)) {
        throw RecordException("Student with ID " + id + " already exists");
    }

    if (!isValidEmail(email)) {
        throw RecordException("Invalid email format");
    }

    students.push_back(std::make_unique<Student>(id, name, email));
    std::cout << "Student added successfully!\n";
}

void RecordManager::removeStudent(const std::string& id) {
    auto it = std::remove_if(students.begin(), students.end(),
        [&id](const std::unique_ptr<Student>& s) {
            return s->getId() == id;
        });

    if (it != students.end()) {
        students.erase(it, students.end());
        std::cout << "Student removed successfully!\n";
    }
    else {
        throw RecordException("Student not found");
    }
}

void RecordManager::updateStudent(const std::string& id, const std::string& name,
    const std::string& email) {
    Student* student = findStudent(id);
    if (!student) {
        throw RecordException("Student not found");
    }

    if (!isValidEmail(email)) {
        throw RecordException("Invalid email format");
    }

    student->setName(name);
    student->setEmail(email);
    std::cout << "Student updated successfully!\n";
}

Student* RecordManager::searchStudent(const std::string& id) {
    return findStudent(id);
}

void RecordManager::addCourse(const std::string& code, const std::string& name, int credits) {
    if (findCourse(code)) {
        throw RecordException("Course with code " + code + " already exists");
    }

    if (credits <= 0) {
        throw RecordException("Invalid credit hours");
    }

    availableCourses.push_back(std::make_shared<Course>(code, name, credits));
    std::cout << "Course added successfully!\n";
}

void RecordManager::enrollStudentInCourse(const std::string& studentId,
    const std::string& courseCode) {
    Student* student = findStudent(studentId);
    if (!student) {
        throw RecordException("Student not found");
    }

    auto course = findCourse(courseCode);
    if (!course) {
        throw RecordException("Course not found");
    }

    student->enrollCourse(course);
    std::cout << "Student enrolled in course successfully!\n";
}

void RecordManager::assignGrade(const std::string& studentId,
    const std::string& courseCode, double grade) {
    if (!isValidGrade(grade)) {
        throw RecordException("Invalid grade (must be between 0.0 and 4.0)");
    }

    Student* student = findStudent(studentId);
    if (!student) {
        throw RecordException("Student not found");
    }

    student->setGrade(courseCode, grade);
    std::cout << "Grade assigned successfully!\n";
}

void RecordManager::displayAllStudents() const {
    if (students.empty()) {
        std::cout << "No students in the system.\n";
        return;
    }

    std::cout << "\n=== ALL STUDENTS ===\n";
    for (const auto& student : students) {
        student->displayInfo();
        std::cout << std::string(50, '-') << "\n";
    }
}

void RecordManager::displayAvailableCourses() const {
    if (availableCourses.empty()) {
        std::cout << "No courses available.\n";
        return;
    }

    std::cout << "\n=== AVAILABLE COURSES ===\n";
    std::cout << std::left << std::setw(10) << "Code"
        << std::setw(30) << "Name"
        << std::setw(10) << "Credits" << "\n";
    std::cout << std::string(50, '-') << "\n";

    for (const auto& course : availableCourses) {
        std::cout << std::left << std::setw(10) << course->getCode()
            << std::setw(30) << course->getName()
            << std::setw(10) << course->getCredits() << "\n";
    }
}

void RecordManager::displayStudentTranscript(const std::string& studentId) {
    Student* student = findStudent(studentId);
    if (!student) {
        throw RecordException("Student not found");
    }

    student->displayTranscript();
}

void RecordManager::displayStatistics() const {
    if (students.empty()) {
        std::cout << "No data available for statistics.\n";
        return;
    }

    double totalGPA = 0.0;
    double maxGPA = 0.0;
    double minGPA = 4.0;

    for (const auto& student : students) {
        double gpa = student->calculateGPA();
        totalGPA += gpa;
        maxGPA = std::max(maxGPA, gpa);
        minGPA = std::min(minGPA, gpa);
    }

    std::cout << "\n=== SYSTEM STATISTICS ===\n";
    std::cout << "Total Students: " << students.size() << "\n";
    std::cout << "Total Courses: " << availableCourses.size() << "\n";
    std::cout << "Average GPA: " << std::fixed << std::setprecision(2)
        << totalGPA / students.size() << "\n";
    std::cout << "Highest GPA: " << maxGPA << "\n";
    std::cout << "Lowest GPA: " << minGPA << "\n";
}

void RecordManager::loadMockData() {
    try {
        // Add courses 
        addCourse("CSP3341", "Programming Languages", 3);
        addCourse("CSP2348", "Data Structures", 3);
        addCourse("CSG2344", "Project Management", 3);

        // Add student
        addStudent("S001", "Mahith Pathiraja", "mahithe@ecu.edu.au");
        addStudent("S002", "Ganul Madumage", "ganul@ecu.edu.au");
        addStudent("S003", "Poojana White", "poojana@ecu.edu.au");

        // Enroll students in courses
        enrollStudentInCourse("S001", "CSP3341");
        enrollStudentInCourse("S001", "CSP2348");
        enrollStudentInCourse("S002", "CSP2348");
        enrollStudentInCourse("S002", "CSG2344");
        enrollStudentInCourse("S003", "CSP3341");
        enrollStudentInCourse("S003", "CSP2348");
        enrollStudentInCourse("S003", "CSG2344");

        // Assign grades 
        assignGrade("S001", "CSP3341", 3.7);  
        assignGrade("S001", "CSP2348", 3.4);  

        assignGrade("S002", "CSP2348", 3.9);  
        assignGrade("S002", "CSG2344", 3.5);  

        assignGrade("S003", "CSP3341", 3.2);  
        assignGrade("S003", "CSP2348", 3.0);  
        assignGrade("S003", "CSG2344", 3.8);  

        std::cout << "\n=== Mock data loaded successfully ===\n";
        std::cout << "3 students enrolled in 3 courses with grades assigned.\n\n";

    }
    catch (const RecordException& e) {
        std::cerr << "Error loading mock data: " << e.what() << "\n";
    }
}
