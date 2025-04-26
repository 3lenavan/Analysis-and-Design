/*
Name: Elena Van
Course: CS-300
Assignment: Project Two
Date: 4-19-2025
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>

using namespace std;

// Here I am creating a structure to store course details like course number, title, and prerequisites.
struct Course {
    string courseNumber;  // This will hold the course number, like "CSCI100".
    string courseTitle;   // This will hold the course title, like "Introduction to Programming".
    vector<string> prerequisites;  // This will store a list of prerequisites for the course.
};

// These functions will be used later in the program.
void displayMenu(); // This function will display the menu to the user.
void printCourseList(const vector<Course>& courses); // This function will print all courses sorted alphabetically.
void printCourseInformation(const vector<Course>& courses); // This function will print details of a specific course.

int main() {
    vector<Course> courses; // Here I am creating a vector to store all course data.
    int choice = 0; // This variable will store the user's menu choice.

    // Here this line will display a welcome message when the program starts.
    cout << "Welcome to the course planner." << endl;

    // This loop will keep running until the user chooses to exit.
    while (choice != 9) {
        displayMenu(); // Here this function will display the menu options.
        cin >> choice; // This line will take the user's input.

        // This checks if the user entered invalid input like letters instead of numbers.
        if (cin.fail()) {
            cin.clear(); // This clears the error flag.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This ignores invalid input.
            cout << "Invalid input. Please enter a number from the menu.\n"; // Here this line will display an error message.
            continue; // This will skip the rest of the loop and ask the user again.
        }

        // Here this switch statement will handle different user choices.
        switch (choice) {
        case 1:
            loadDataStructure(courses); // This will load the course data from the file.
            break;
        case 2:
            printCourseList(courses); // This will print the list of courses.
            break;
        case 3:
            printCourseInformation(courses); // This will print details of a specific course.
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl; // Here this code will exit the program.
            break;
        default:
            cout << choice << " is not a valid option." << endl; // If the user enters an invalid option, show an error message.
        }
    }

    return 0; // This line ends the program.
}

// Here this function will display the menu options to the user.
void displayMenu() {
    cout << "\n1. Load Data Structure.\n"; // Option to load course data from a file.
    cout << "2. Print Course List.\n"; // Option to print all courses.
    cout << "3. Print Course.\n"; // Option to print details of a specific course.
    cout << "9. Exit\n"; // Option to exit the program.
    cout << "What would you like to do? "; // Here this will prompt the user to enter their choice.
}

// This function will load course data from a file and store it in the vector.
void loadDataStructure(vector<Course>& courses) {
    string fileName;
    cout << "Enter the file name: "; // This will ask the user for the file name.
    cin >> fileName;

    ifstream file(fileName); // Here I am opening the file for reading.

    // If the file does not open, display an error message.
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << ". Please check the file path.\n";
        return;
    }

    string line;
    courses.clear(); // Here this will clear any existing course data before loading new data.

    // This loop will read the file line by line.
    while (getline(file, line)) {
        stringstream ss(line); // This will allow us to break the line into parts.
        Course course;
        string token;

        getline(ss, course.courseNumber, ','); // Here we read the course number.
        getline(ss, course.courseTitle, ','); // Here we read the course title.

        // This loop will read any prerequisites from the line.
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token); // Here we store each prerequisite in the vector.
        }

        courses.push_back(course); // Here this line adds the course to our list.
    }

    cout << "Data loaded successfully." << endl; // Here this confirms that the data was loaded successfully.
}

// This function will print the list of courses sorted alphabetically.
void printCourseList(const vector<Course>& courses) {
    if (courses.empty()) { // This checks if there are no courses loaded.
        cout << "No courses loaded. Please load data first." << endl;
        return;
    }

    vector<Course> sortedCourses = courses; // Here I make a copy of the courses vector.

    // Here this will sort the courses alphabetically by course number.
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    cout << "\nHere is a sample schedule:" << endl; // Here this prints the title for the list.

    // This loop will go through each course and print it.
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl; // This prints the course number and title.
    }
}

// This function will print details about a specific course when the user enters the course number.
void printCourseInformation(const vector<Course>& courses) {
    if (courses.empty()) { // This checks if there are no courses loaded.
        cout << "No courses loaded. Please load data first." << endl;
        return;
    }

    string courseNumber;
    cout << "What course do you want to know about? "; // This asks the user for the course number.
    cin >> courseNumber;

    // Here this converts the course number to uppercase to make it case-insensitive.
    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

    // This loop will go through each course in the list and check if the course exists.
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) { // If we find a match, we print the course details.
            cout << course.courseNumber << ", " << course.courseTitle << endl; // Print course number and title.

            // If the course has prerequisites, print them.
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";

                // This loop will print each prerequisite.
                for (const auto& prereq : course.prerequisites) {
                    cout << prereq << " ";
                }
                cout << endl;
            }
            else {
                cout << "No prerequisites." << endl; // If there are no prerequisites, display this message.
            }
            return; // Exit the function once we print the course details.
        }
    }

    cout << "Course not found." << endl; // If the course wasn't found, display an error message.
}
