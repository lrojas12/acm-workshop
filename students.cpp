#include <iostream>
#include <vector>

using namespace std;


class Student {
    long studentId;
    string name;
    double GPA;

    public: 
    
    Student(long id, string name, double GPA) {
        this->studentId = id;
        this->name = name;
        this->GPA = GPA;
    }

	long getId() {
		return this->studentId;
	}

    string getName() {
        return this->name;
    }

	double getGPA() {
		return this->GPA;
	}
};

ostream& operator<<(ostream &strm, Student &s) {
	return strm << "Student(ID: " << s.getId() << ", Name: "
			<< s.getName() << ", GPA: " << s.getGPA() << ")";
}


void printHelpMenu() {
    cout << "Enter one of the following commands:\n";
    cout << "    print  - Print all records.\n";
    cout << "    create - Create a new record.\n";
    cout << "    delete - Delete a record by ID.\n";
    cout << "    save   - Save all records to file.\n";
    cout << "    load   - Load all records from file.\n";
    cout << "    help   - Reprint this menu.\n";
    cout << "    exit   - Exit this program.\n\n";

}

Student createStudent() {
    long studentId;
    string name;
    double GPA;

    cout << "\nEnter Student ID: ";
    cin >> studentId;

    cout << "\nEnter Name: ";
    cin >> name;

    cout << "\nEnter GPA: ";
    cin >> GPA;
    
    Student s = Student(studentId, name, GPA);
    return s;
}


int main(void) {
   
    cout << "Welcome to the Student Manager\n\n";

    printHelpMenu();

    vector<Student> students;

    string input;

    while(1) {
        cout << "\n\nEnter a command: ";
        cin >> input;

        if (input.compare("print") == 0) {
            if (students.size() == 0) {
                cout << "No records available" << endl;
            }
            for (int i = 0; i < students.size(); i++) {
				cout << students.at(i);
            }
        } else if (input.compare("create") == 0) {
            Student s = createStudent(); 
            cout << s << " created successfully." << endl;
            students.push_back(s);
        } else if (input.compare("delete") == 0) {
            long id;
            cout << "Enter the student ID of the student to delete: ";
            cin >> id;
            for (int i = 0; i < students.size(); i++) {
                Student s = students.at(i);
                if (id == s.getId()) {
                    students.erase(students.begin() + i);
                    cout << s << " deleted." << endl;
                }
            }

        } else if (input.compare("save") == 0) {

        } else if (input.compare("load") == 0) {
            //saveRecords();
        } else if (input.compare("help") == 0) {
            printHelpMenu(); 
        } else if (input.compare("exit") == 0) {
            cout << "Good bye!\n";
            break;
        } else {
            cout << "Unknown command. Type 'exit' to exit or 'help' for options.\n";
        }
    }

    return 0;
}
