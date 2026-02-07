#include <iostream>
#include <limits>
#include "RecordManager.h"

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMenu() {
    std::cout << "\n=== STUDENT RECORD MANAGEMENT SYSTEM ===\n";
    std::cout << "1. Add Student\n";
    std::cout << "2. Remove Student\n";
    std::cout << "3. Update Student\n";
    std::cout << "4. Search Student\n";
    std::cout << "5. Add Course\n";
    std::cout << "6. Enroll Student in Course\n";
    std::cout << "7. Assign Grade\n";
    std::cout << "8. Display All Students\n";
    std::cout << "9. Display Available Courses\n";
    std::cout << "10. Display Student Transcript\n";
    std::cout << "11. Display Statistics\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    RecordManager manager;

    // Load mock data
    manager.loadMockData();

    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;
        clearInput();

        try {
            switch (choice) {
            case 1: {
                std::string id, name, email;
                std::cout << "Enter Student ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Email: ";
                std::getline(std::cin, email);
                manager.addStudent(id, name, email);
                break;
            }
            case 2: {
                std::string id;
                std::cout << "Enter Student ID: ";
                std::getline(std::cin, id);
                manager.removeStudent(id);
                break;
            }
            case 3: {
                std::string id, name, email;
                std::cout << "Enter Student ID: ";
                std::getline(std::cin, id);
                std::cout << "Enter New Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter New Email: ";
                std::getline(std::cin, email);
                manager.updateStudent(id, name, email);
                break;
            }
            case 4: {
                std::string id;
                std::cout << "Enter Student ID: ";
                std::getline(std::cin, id);
                Student* student = manager.searchStudent(id);
                if (student) {
                    student->displayInfo();
                }
                else {
                    std::cout << "Student not found.\n";
                }
                break;
            }
            case 5: {
                std::string code, name;
                int credits;
                std::cout << "Enter Course Code: ";
                std::getline(std::cin, code);
                std::cout << "Enter Course Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Credit Hours: ";
                std::cin >> credits;
                clearInput();
                manager.addCourse(code, name, credits);
                break;
            }
            case 6: {
                std::string studentId, courseCode;
                std::cout << "Enter Student ID: ";
                std::getline(std::cin, studentId);
                std::cout << "Enter Course Code: ";
                std::getline(std::cin, courseCode);
                manager.enrollStudentInCourse(studentId, courseCode);
                break;
            }
            case 7: {
                std::string studentId, courseCode;
                double grade;
                std::cout << "Enter Student ID: ";
                std::getline(std::cin, studentId);
                std::cout << "Enter Course Code: ";
                std::getline(std::cin, courseCode);
                std::cout << "Enter Grade (0.0-4.0): ";
                std::cin >> grade;
                clearInput();
                manager.assignGrade(studentId, courseCode, grade);
                break;
            }
            case 8:
                manager.displayAllStudents();
                break;
            case 9:
                manager.displayAvailableCourses();
                break;
            case 10: {
                std::string id;
                std::cout << "Enter Student ID: ";
                std::getline(std::cin, id);
                manager.displayStudentTranscript(id);
                break;
            }
            case 11:
                manager.displayStatistics();
                break;
            case 0:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
        catch (const RecordException& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Unexpected error: " << e.what() << "\n";
        }
    }

    return 0;
}