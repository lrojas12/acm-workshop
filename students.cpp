#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//Define the name of the file that will be used to save and load student data in
string STUDENT_FILENAME = "students-database.txt";

//Define the Student Class
class Student {
private:
  //Members
  long studentId;
  string name;
  double GPA;

public: 
  //Constructor
  Student(long id, string name, double GPA) {
    this->studentId = id;
    this->name = name;
    this->GPA = GPA;
  }

  //Getters
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


//Overload the << Operator to print the Student Class
ostream& operator<<(ostream &strm, Student &s);

//COMMAND FUNCTIONS
void printRecords(vector<Student> students);
Student createStudent();
void deleteStudentById(vector<Student> &students, long id);
void saveFile(string filename, vector<Student> students);
void loadFile(string filename, vector<Student> &students);
void printHelpMenu();


int main(void) {
   
  cout << "Welcome to the Student Manager\n\n";

  printHelpMenu();

  vector<Student> students;

  string input;

  while(1) {
    //Obtain the command from the user
    cout << "\n\nEnter a command: ";
    cin >> input;

    //--------------PRINT--------------
    if (input.compare("print") == 0) {
      printRecords(students);      
      //--------------CREATE--------------
    } else if (input.compare("create") == 0) {
      Student s = createStudent(); 
      cout << s << " created successfully." << endl;
      students.push_back(s);
      //--------------DELETE--------------
    } else if (input.compare("delete") == 0) {
      long id;
      cout << "Enter the student ID of the student to delete: ";
      cin >> id;
      deleteStudentById(students, id);
      //--------------SAVE--------------
    } else if (input.compare("save") == 0) {
      saveFile(STUDENT_FILENAME, students);
      //--------------LOAD--------------
    } else if (input.compare("load") == 0) {
      loadFile(STUDENT_FILENAME, students);
      //--------------HELP--------------
    } else if (input.compare("help") == 0) {
      printHelpMenu();
      //--------------EXIT--------------
    } else if (input.compare("exit") == 0) {
      cout << "Good bye!\n";
      break;
    } else {
      //--------------INVALID COMMAND--------------
      cout << "Unknown command. Type 'exit' to exit or 'help' for options.\n";
    }
  }

  return 0;
}

//--------------PRINT--------------
void printRecords(vector<Student> students){
  //Check if the number of students is 0, don't print anything if so
  if (students.size() == 0) {
    cout << "No records available" << endl;
    return;
  }
  //If not 0 then print the existing students
  for (int i = 0; i < students.size(); i++) {
    cout << students.at(i) << endl;
  }
}

//--------------CREATE--------------
Student createStudent() {
  //Create variables that we will be using to collect information
  long studentId;
  string name;
  double GPA;

  //Collect the student information from the user
  cout << "\nEnter Student ID: ";
  cin >> studentId;

  cout << "\nEnter Name: ";
  cin >> name;

  cout << "\nEnter GPA: ";
  cin >> GPA;

  //Create the student object with the collected information
  Student newStudent = Student(studentId, name, GPA);
  
  //Return the object 
  return newStudent;
}
//--------------DELETE--------------
void deleteStudentById(vector<Student> &students, long id){
  //Iterate through all the students available
  for (int i = 0; i < students.size(); i++) {
    //Obtain the current student 
    Student currStudent = students.at(i);
    //Check if current student has the matching id provided by the user
    if (id == currStudent.getId()) {
      //Found the correct id, delete the student from the vector
      students.erase(students.begin() + i);
      cout << currStudent << " deleted." << endl;
    }
  }  
}

//--------------SAVE--------------
void saveFile(string filename, vector<Student> students){
  //Create an output file stream
  ofstream studentFile;

  //Check if there are no students, if none then just exit - nothing to save
  if(students.size() == 0){
    cout << "No existing records to save!" << endl;
    return;
  }

  //open the file for writing
  studentFile.open(filename);
  
  //Iterate through all the students in the vector
  for (int i = 0; i < students.size(); i++){
    //Obtain the current student
    Student currStudent = students.at(i);
    //Save the current student information to the file in the csv format: id,name,gpa
    cout << "saving student.... " << currStudent << endl;    
    studentFile << currStudent.getId() << "," << currStudent.getName() << "," << currStudent.getGPA() << endl;
  }
  cout << "Saved to file " << filename << endl;
  
  //make sure to close the output file stream
  studentFile.close();
}

//--------------LOAD--------------
void loadFile(string filename, vector<Student> &students){
  //create and open an input file stream
  ifstream studentFile;
  studentFile.open(filename);
  cout << "Loading from file: " << filename << endl << endl;;

  //Define a string that will be used a a single line read from the file
  string line;

  //Read the file line by line
  while(studentFile >> line){

    //Create a vector of strings to hold the student information
    vector<string> studentStr;

    //Read the line word by word, in our case should be 3 words per line: id,name,gpa
    stringstream ss; //http://www.cplusplus.com/reference/sstream/stringstream/
    ss.str(line);
    //This will be used as a placeholder for the words being read in
    string element;
    //Iterate through every word in the line, using the ',' as a delimiter
    while(getline(ss, element, ',')){
      //Add the word read in to a vector of strings
      studentStr.push_back(element);
    }

    //Create the student from the strings read in
    long id = stol(studentStr.at(0));
    string name = studentStr.at(1);
    double GPA = stod(studentStr.at(2));

    //Create the student object from the information read above
    Student newStudent = Student(id, name, GPA);
    cout << "Loaded student..." << newStudent << endl;

    //Update the students vector
    students.push_back(newStudent);    
  }

  //make sure you close the input file stream
  studentFile.close();
}

//--------------HELP--------------
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


//----<< overload------
ostream& operator<<(ostream &strm, Student &s) {
  return strm << "Student(ID: " << s.getId() << ", Name: "
	      << s.getName() << ", GPA: " << s.getGPA() << ")";
}

