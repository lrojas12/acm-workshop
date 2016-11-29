#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

string STUDENT_FILENAME = "students-database.txt";

class Student {
private:

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

void saveFile(string filename, vector<Student> students);
void loadFile(string filename, vector<Student> &students);


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

  //Fill students with dummy data
  //students.push_back(Student(1, "Name1", 1.0));
  //students.push_back(Student(2, "Name2", 2.0));
  //students.push_back(Student(3, "Name3", 3.0));

  string input;

  while(1) {
    cout << "\n\nEnter a command: ";
    cin >> input;

    if (input.compare("print") == 0) {
      if (students.size() == 0) {
	cout << "No records available" << endl;
      }
      for (int i = 0; i < students.size(); i++) {
	cout << students.at(i) << endl;
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
      saveFile(STUDENT_FILENAME, students);
    } else if (input.compare("load") == 0) {
      loadFile(STUDENT_FILENAME, students);
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


void saveFile(string filename, vector<Student> students){
  ofstream studentFile;

  if(students.size() == 0){
    cout << "No existing records to save!" << endl;
    return;
  }

  //open the file for writing
  studentFile.open(filename);
  
  //Iterate through all the students and append them to the file
  for (int i = 0; i < students.size(); i++){
    Student currStudent = students.at(i);
    cout << "saving student.... " << currStudent << endl;    
    studentFile << currStudent.getId() << "," << currStudent.getName() << "," << currStudent.getGPA() << endl;
  }
  
  studentFile.close();

  cout << "Saved to file " << filename << endl;
}

void loadFile(string filename, vector<Student> &students){
  ifstream studentFile;
  studentFile.open(filename);

  cout << "Loading from file: " << filename << endl << endl;;
  
  string line;

  //Read the file line by line
  while(studentFile >> line){

    //Create a vector of strings to hold the student information
    vector<string> studentStr;

    //Read the student data string by string
    stringstream ss;
    ss.str(line);
    string element;
    while(getline(ss, element, ',')){
      //cout << element << endl;
      studentStr.push_back(element);
    }

    //Create the student from the strings read in
    long id = stol(studentStr.at(0));
    string name = studentStr.at(1);
    double GPA = stod(studentStr.at(2));

    Student newStudent = Student(id, name, GPA);
    cout << "Loaded student..." << newStudent << endl;

    //Update the students vector
    students.push_back(newStudent);
    
  }

  //make sure you close the file
  studentFile.close();
}
