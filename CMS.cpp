
/*
    Project Name : "Course Management System"
    Project Aurthor : "Syed Rifat"
    Gmail : "syedrifat411@gmail.com"

*/

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <dirent.h>
#include <algorithm>



using namespace std;

static string AccessKey;


class CMS {
private:
    string code,title, duration;

public:
void AddCourse(const string& c, const string& t, const string& d) {
    string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\"+AccessKey+"_courses.txt";
    ifstream checkFile(filePath);
    string line;

    // Check if the course code or title already exists
    while (getline(checkFile, line)) {
        stringstream ss(line);
        getline(ss, code, ',');
        getline(ss, title, ',');
        getline(ss, duration, ',');

        if (code == c || title == t) {
            cout << "Course with code " << c << " or title " << t << " already exists. Cannot add duplicate courses." << endl;
            checkFile.close();
            return;
        }
    }

    checkFile.close();

    // If the course code and title do not exist, add the new course
    code = c;
    title = t;
    duration = d;

    ofstream wFile(filePath, ios::app);
    wFile << code << "," << title << "," << duration << endl;
    wFile.close();

    cout << "Course added successfully." << endl;
}

void DisplayCourses() {
    system("cls");
    string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\"+AccessKey+"_courses.txt";
    ifstream rFile(filePath);

    if (!rFile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string line;
    int i = 1;
    cout << "Course List:" << endl << endl;

    if (rFile.peek() == ifstream::traits_type::eof()) {
        cout << "No courses available." << endl;
    } else {
        while (getline(rFile, line)) {
            stringstream ss(line);
            getline(ss, code, ',');
            getline(ss, title, ',');
            getline(ss, duration, ',');

            cout << "SL NO : " << i << endl << "Code : " << code << endl << "Title : " << title << endl << "Duration : " << duration << endl << endl;
            i++;
        }
    }

    rFile.close();
}
void DeleteCourse(const string& identifier, bool byCode = true) {
        string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\"+AccessKey+"_courses.txt";
        string tempfilePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\"+AccessKey+"_temp.txt";
        ifstream inFile(filePath);
        ofstream outFile(tempfilePath);

        if (!inFile.is_open() || !outFile.is_open()) {
            cout << "Unable to open file." << endl;
            return;
        }

        string line;
        bool found = false;
        int serialNumber = 1;

        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, code, ',');
            getline(ss, title, ',');
            getline(ss, duration, ',');

            if ((byCode && code == identifier) || (!byCode && to_string(serialNumber) == identifier)) {
                found = true;
                cout << "Course deleted successfully." << endl;
            } else {
                outFile << line << endl;
            }

            serialNumber++;
        }

        inFile.close();
        outFile.close();


        // Rename temp.txt to courses.txt

      //  if (remove(filePath.c_str()) == 0) {
      //  }
        remove(filePath.c_str());
        rename(tempfilePath.c_str(), filePath.c_str());

        if (!found) {
            cout << "Course not found." << endl;
        }
    }

        void EditCourse(int serialNumber, const string& newCode, const string& newTitle, const string& newDuration) {

        string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\"+AccessKey+"_courses.txt";
        string tempfilePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\"+AccessKey+"_temp.txt";

        ifstream inFile(filePath);
        ofstream outFile(tempfilePath);

        if (!inFile.is_open() || !outFile.is_open()) {
            cout << "Unable to open file." << endl;
            return;
        }

        string line;
        int currentSerialNumber = 1;
        bool found = false;

        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, code, ',');
            getline(ss, title, ',');
            getline(ss, duration, ',');

            if (currentSerialNumber == serialNumber) {
                found = true;
                // Edit the course information
                code = newCode;
                title = newTitle;
                duration = newDuration;
                cout << "Course edited successfully." << endl;
            }

            outFile << code << "," << title << "," << duration << endl;
            currentSerialNumber++;
        }

        inFile.close();
        outFile.close();

        // Rename temp.txt to courses.txt
        remove(filePath.c_str());
        rename(tempfilePath.c_str(), filePath.c_str());

        if (!found) {
            cout << "Course with serial number " << serialNumber << " not found." << endl;
        }
    }

        void SearchCourse(const string& searchKey) {
        string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\"+AccessKey+"_courses.txt";

        ifstream inFile(filePath);

        if (!inFile.is_open()) {
            cout << "Unable to open file." << endl;
            return;
        }

        string line;
        int serialNumber = 1;
        bool found = false;

        cout << "Search Results:" << endl;

        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, code, ',');
            getline(ss, title, ',');
            getline(ss, duration, ',');

            // Check if the search key matches course code or title
            if (code == searchKey || title == searchKey) {
                found = true;
                cout << "Serial Number: " << serialNumber << endl;
                cout << "Code: " << code << endl;
                cout << "Title: " << title << endl;
                cout << "Duration: " << duration << endl << endl;
                break;  // Stop searching once a match is found
            }

            serialNumber++;
        }

        inFile.close();

        if (!found) {
            cout << "Course not found." << endl;
        }
    }

    
    
    
    bool createFolder(const string& path, const string& folderName) {
        string folderPath = path + folderName;

        if (_mkdir(folderPath.c_str()) == 0) return true;
        else return false;
    }




    void AddStudent(const string& userID) {
        // Check if the student is already added
        ifstream crfile("C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + AccessKey +"\\"+ userID + ".txt");
        if (crfile.is_open()) {
            crfile.close();
            cout << "Student " << userID << " is already added." << endl;
            return;
        }

            string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Requested_Student\\"+ AccessKey +"\\"+ userID + ".txt";


        // Check if the student is requested
        ifstream rfile(filePath);
        
        
        if (rfile.is_open()) {
            rfile.close();

            // first we have to create  a folder where i want to save txt file
            string path = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\";
            createFolder(path,AccessKey);

            // Remove the requested file and move it to the added directory
            ofstream wfile("C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + AccessKey +"\\"+ userID + ".txt");
            cout << "Student " << userID << " added successfully." << endl;
            //for delete txt file from Requested_Student
            if (remove(filePath.c_str()) == 0) {     
            } 


        } else {
            cout << "Student " << userID << " is not requested." << endl;
        }
    }

    void RemoveStudent(const string& userID) {
        // Build the file path for the student's file in the "Added_Student" directory
        string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + AccessKey +"\\"+ userID + ".txt";

        // Check if the file exists
        ifstream studentFile(filePath);
        if (!studentFile.is_open()) {
            cout << "Student with userID " << userID << " not found." << endl;
            return;
        }

        // Close the file before removal
        studentFile.close();

        // Attempt to remove the file
        if (remove(filePath.c_str()) == 0) {
            cout << "Student with userID " << userID << " removed successfully." << endl;
        } else {
            cout << "Error removing student with userID " << userID << "." << endl;
        }
    }
    
    
    
    void DisplayAllStudents() {
        // Specify the directory path for added students
        string directoryPath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + AccessKey ;

        // Open the directory
        DIR* directory = opendir(directoryPath.c_str());

        if (directory) {
            dirent* entry;
            cout << "Added Students are : " << endl;
            while ((entry = readdir(directory)) != nullptr) {
                if (entry->d_type == DT_REG) {
                    // Extract the filename (which is the userID) from the dirent structure
                    string fileName = entry->d_name;

                    // Remove the ".txt" extension
                    size_t dotPosition = fileName.find_last_of('.');
                    if (dotPosition != string::npos) {
                        fileName.erase(dotPosition);
                    }

                    // Display information about the student (you can customize this part)
                    cout << fileName << endl;
                }
            }

            closedir(directory);
        } else {
            cout << "Error opening directory." << endl;
        }

    }



    void RequestForAdmision(const string& userID){
        string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + userID +"\\"+ AccessKey + ".txt";
        string filePath1 = "C:\\Users\\User\\Desktop\\Course_Management_System\\Requested_Student\\" + userID +"\\"+ AccessKey + ".txt";
        string path="C:\\Users\\User\\Desktop\\Course_Management_System\\Requested_Student\\";
        ifstream chkAdded(filePath);
        if(chkAdded.is_open()){
            cout<<"Alredy Added."<<endl;
        }

        ifstream rFile(filePath1);
        if(rFile.is_open()){
            rFile.close();
            cout<< "Alredy Requested."<<endl;
        }
        else {
            // first we have to create the folder userID name 

            createFolder(path,userID);
            // then we create a txt file
            ofstream wFile(filePath1);
            wFile.close();
            cout<< "Successfully request sent" << endl;
        }

    }


    void SearchStudent(const string& userID,bool rs = true){
        string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + AccessKey +"\\"+ userID + ".txt";
        string filePath1 = "C:\\Users\\User\\Desktop\\Course_Management_System\\Requested_Student\\" + AccessKey +"\\"+ userID + ".txt";

        ifstream rsFile(filePath1);
        ifstream asFile(filePath);

        //ifstream rsFile("C:\\Users\\User\\Desktop\\Course_Management_System\\Requested_Student\\" + userID + ".txt");
        //ifstream asFile("C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + userID + ".txt");

        if(rsFile.is_open() && rs == true){
            cout<<endl<<userID<<" Requested Student is found."<<endl;
        }
        else if(asFile.is_open() && rs == false){
            cout<<endl<<userID<<" Added Student is found."<<endl;
        }
        else{
            cout<<endl<<userID<<" Student is not found."<<endl;
        }

    }


    void AddStudentCourses(const string& InCode,int courseSlNo){
        // for check student is added or not . if not then student can not add course .
        string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + InCode + "\\" + AccessKey +".txt";
        string filePathA = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\" + InCode + "_courses.txt";
        ifstream chkExist(filePath);
        if(!chkExist.is_open()){
            cout<<"You have no access to this Institute."<<endl;
            return;
        }


        // check if there exist 5 course already then we will do a specific task
        bool chkLine = true;
        string line;
        int lineCount = 0;
        while (getline(chkExist,line)) {
            lineCount++;
            if (lineCount >= 5) {
                chkLine = false;
            }
        }


        if(chkLine==false){
            cout<<"You have already added 5 course."<<endl;
            return;
        }

        string courseLine;
        int currentLine = 0;
        bool lineExists = false;

        // Check if the line exists in the destination file
        while (getline(chkExist,courseLine)) {
            if (++currentLine == courseSlNo) {
                lineExists = true;
                break;
            }
        }

        ifstream copyFrom(filePathA);

        if (lineExists) {
            cout << "Course already added" << endl;
        }
        else {
            currentLine = 0;
            // Copy the line from the source file to the destination file
            ofstream wFile(filePath, ios::app);  // Append mode
            while (getline(copyFrom, courseLine)) {
                if (++currentLine == courseSlNo) {
                    wFile << courseLine << endl;
                    cout << "Course added successfully" << endl;
                    break;
                }

            }
        }

    }


    //another add student course function

    bool isStudentAccessAllowed(const string& studentCode) {
        string accessFilePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + studentCode + "\\" + AccessKey + ".txt";
        ifstream accessFile(accessFilePath.c_str());
        return accessFile.is_open();
    }

    bool hasStudentReachedMaxCourses(const string& studentCode) {
        string coursesFilePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + studentCode + "\\" + AccessKey + ".txt";
        ifstream coursesFile(coursesFilePath.c_str());
        int courseCount = 0;
        string line;

        while (getline(coursesFile, line)) {
            courseCount++;
            if (courseCount >= 5) {
                return true;
            }
        }

        return false;
    }

    void copyLineToFile(const string& sourceFilePath, const string& destinationFilePath, int lineToCopy) {
    ifstream sourceFile(sourceFilePath.c_str());
    ofstream destinationFile(destinationFilePath.c_str(), ios::app);  // Append mode

    if (!sourceFile.is_open()) {
        cout << "Failed to open the source file: " << sourceFilePath << endl;
        return;
    }

    if (!destinationFile.is_open()) {
        cout << "Failed to open the destination file: " << destinationFilePath << endl;
        return;
    }

    string line;
    int currentLine = 0;

    while (getline(sourceFile, line)) {
        currentLine++;
        if (currentLine == lineToCopy) {
            destinationFile << line << endl;
            cout << "Course Added successfully" << endl;
            break;
        }
    }

    sourceFile.close();
    destinationFile.close();
}


    void addStudentCourse(const string& studentCode, int courseNumber) {
        if (!isStudentAccessAllowed(studentCode)) {
            cout << "You have no access to this Institute." << endl;
        } else if (hasStudentReachedMaxCourses(studentCode)) {
            cout << "You have already added 5 courses." << endl;
        } else {
            string coursesFilePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\" + studentCode + "_courses.txt";
            string destinationFilePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + studentCode + "\\" + AccessKey + ".txt";

            copyLineToFile(coursesFilePath, destinationFilePath, courseNumber);
        }
    }




    //for show added courses
    void ShowMyCourses(const string& studentCode) {
        string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + studentCode + "\\" + AccessKey + ".txt";

        ifstream studentFile(filePath.c_str());

        if (!studentFile.is_open()) {
            cout << "Failed to open the student file: " << filePath << endl;
        }
        else if (studentFile.peek() == ifstream::traits_type::eof()) {
            cout << "No courses available." << endl;
        }
        else{
            cout << "Courses for Student " << studentCode << ":" << endl;
            string line;

            while (getline(studentFile, line)) {
                cout << line << endl;
            }
        }

        studentFile.close();
    }



    // Function to delete a specific line from a text file
    void DeleteMyCourse(const string& studentCode, int lineToDelete) {
        string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + studentCode + "\\" + AccessKey + ".txt";

        ifstream inputFile(filePath.c_str());
        if (!inputFile.is_open()) {
            cout << "Failed to open the file: " << filePath << endl;
            return;
        }
        if (inputFile.peek() == ifstream::traits_type::eof()) {
            cout << "No courses available." << endl;
            return;
        }

        vector<string> lines;  // Store the lines to keep

        string line;
        int currentLine = 0;

        while (getline(inputFile, line)) {
            currentLine++;
            if (currentLine != lineToDelete) {
                lines.push_back(line);
            }
        }

        inputFile.close();

        // Now, write the modified lines back to the file
        ofstream outputFile(filePath.c_str());

        if (!outputFile.is_open()) {
            cout << "Failed to open the file for writing: " << filePath << endl;
            return;
        }

        for (const string& line : lines) {
            outputFile << line << endl;
        }

        cout << "Course " << lineToDelete << " deleted successfully." << endl;
    }

    void showAllCourse(const string& Incode){
        //string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Added_Student\\" + Incode + "\\" + AccessKey + ".txt";
        string filePathA ="C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\" + Incode + "_courses.txt";

        if(!isStudentAccessAllowed(Incode)){
            cout<< "You have no access to this Institute." << endl ;
        }
        else{
            system("cls");
            string filePath = "C:\\Users\\User\\Desktop\\Course_Management_System\\Courses_Info\\" + Incode + "_courses.txt";
            ifstream rFile(filePath);

            if (!rFile.is_open()) {
                cout << "Unable to open file." << endl;
                return;
            }

            string line;
            int i = 1;
            cout << "Course List:" << endl << endl;

            if (rFile.peek() == ifstream::traits_type::eof()) {
                cout << "No courses available." << endl;
            } else {
                while (getline(rFile, line)) {
                    stringstream ss(line);
                    getline(ss, code, ',');
                    getline(ss, title, ',');
                    getline(ss, duration, ',');

                    cout << "SL NO : " << i << endl << "Code : " << code << endl << "Title : " << title << endl << "Duration : " << duration << endl << endl;
                    i++;
                }
            }

            rFile.close();


        }



    }


};






    class User {
    public:
        virtual void login(const string& userID, const string& password) = 0;
        virtual void signup(const string& userID, const string& password) = 0;
        virtual void forgotPassword(const string& userID, const string& newPassword) = 0;
        virtual ~User() = default;
    };

    class Admin : public User {
    public:
        void adminMenu();
        void login(const string& userID, const string& password) override {
            ifstream read("C:\\Users\\User\\Desktop\\Course_Management_System\\Admin_Info\\" + userID + ".txt");
            string storedPassword;

            if (read.is_open()) {
                getline(read, storedPassword);
                read.close();

                if (storedPassword == password) {
                    system("cls");
                    cout << "Login successful" << endl;
                    AccessKey = userID;
                    adminMenu();
                } else {
                    cout << "Login error." << endl;
                }
            } else {
                cout << "userID not found. Please sign up." << endl;
            }
        }

        void signup(const string& userID, const string& password) override {
            ifstream read("C:\\Users\\User\\Desktop\\Course_Management_System\\Admin_Info\\" + userID + ".txt");

            if (read.is_open()) {
                read.close();
                cout << "userID is already taken." << endl;
            } else {
                ofstream write(("C:\\Users\\User\\Desktop\\Course_Management_System\\Admin_Info\\" + userID + ".txt").c_str());  // Added .c_str() for compatibility
                write << password << endl;
                write.close();
                cout << "Registration is successful." << endl;
            }
        }

        void forgotPassword(const string& userID, const string& newPassword) override {
            ifstream read(userID + ".txt");

            if (read.is_open()) {
                read.close();
                ofstream temp(("C:\\Users\\User\\Desktop\\Course_Management_System\\Admin_Info\\" + userID + "_temp.txt").c_str());  // Added .c_str() for compatibility
                temp << newPassword << endl;
                temp.close();
                remove(("C:\\Users\\User\\Desktop\\Course_Management_System\\Admin_Info\\" + userID + ".txt").c_str());
                rename(("C:\\Users\\User\\Desktop\\Course_Management_System\\Admin_Info\\" + userID + "_temp.txt").c_str(), ("C:\\Users\\User\\Desktop\\Course_Management_System\\Admin_Info\\" + userID + ".txt").c_str());
                cout << "Password reset successfully." << endl;
            } else {
                cout << "userID not found. Password reset failed." << endl;
            }
        }

};



void Admin::adminMenu() {
        CMS cms;
        int slno,ch;
        string slb,IDNO;
        string searchKey;
        string code,title,duration;
        string studentID;


        while (true) {

            cout << "\nAdmin Menu:\n";
            cout << "1. Display All Courses\n";
            cout << "2. Add Course\n";
            cout << "3. Remove Course\n";
            cout << "4. Edit Course\n";
            cout << "5. Search Course\n";
            cout << "6. Add Student\n";
            cout << "7. Remove Student\n";
            cout << "8. Search Student\n";
            cout << "9. Display All Students\n";
            cout << "10. Logout\n";

            int adminChoice;
            cout << "Enter your choice: ";
            cin >> adminChoice;

            switch (adminChoice) {
                case 1:
                    system("cls");
                    cms.DisplayCourses();
                    break;
                case 2:
                    // Add Course
                    system("cls");
                    cin.ignore();
                    cout << "Enter Course Code : ";
                    getline(cin,code);
                    cout << "Enter Course Title : ";
                    getline(cin,title);
                    cout << "Enter Course Duration : ";
                    getline(cin,duration);
                    cms.AddCourse(code,title,duration);
                    break;
                case 3:
                    // Remove Course
                    system("cls");
                    cin.ignore();
                    cout<< "Delete course by Serial Number (Enter 1) by Course Code (Enter 2)"<<endl;
                    cin>>ch;

                    switch (ch)
                    {
                        case 1:
                            system("cls");
                            cout<<"Enter Serial Number : ";
                            cin>>slb;
                            cms.DeleteCourse(slb, false);
                            break;
                        case 2:
                            system("cls");
                            cout<<"Enter Course Code : ";
                            cin.ignore();
                            getline(cin,slb);
                            cms.DeleteCourse(slb);
                            cin.ignore();
                            break;

                        default:
                            system("cls");
                            cout<<"Wrong key!"<<endl;
                            break;
                        }
                        break;

                case 4:
                    // Edit Course
                    system("cls");
                    cin.ignore();
                    cout<<"Enter Serial No :";
                    cin>>slno;
                    cout << "Enter New Course Code : ";
                    cin.ignore();
                    getline(cin,code);
                    cout << "Enter New Course Title : ";
                    cin.ignore();
                    getline(cin,title);
                    cout << "Enter New Course Duration : ";
                    getline(cin,duration);

                    cms.EditCourse(slno,code,title,duration);
                    break;
                case 5:
                    system("cls");
                    cin.ignore();
                    cout<<"Enter Search Key : ";
                    getline(cin,searchKey);
                    cms.SearchCourse(searchKey);
                    // Search Course
                    break;
                case 6:
                    // Add Student
                    system("cls");
                    cin.ignore();
                    cout<<"Enter Student studentID : ";
                    cin>>studentID;
                    cms.AddStudent(studentID);
                    break;
                case 7:
                    // Remove Student
                    system("cls");
                    cin.ignore();
                    cout<<"Enter Student studentID : ";
                    getline(cin,studentID);
                    cms.RemoveStudent(studentID);
                    break;
                case 8:
                    // Search Student
                    system("cls");
                    cout<<"Search Student : "<<endl<<"1. From Requested Student."<<endl<<"2. From Added Student."<<endl<<"Enter Your Option :";
                    cin>>ch;
                    switch (ch)
                    {
                        cin.ignore();
                        case 1 :
                            system("cls");
                            cout<<"Enter Student ID : ";
                            cin>>IDNO;
                            cms.SearchStudent(IDNO);
                            break;
                        case 2 :
                            system("cls");
                            cout<<"Enter Student ID : ";
                            cin>>IDNO;
                            cms.SearchStudent(IDNO,false);
                            break;
                        default:
                            system("cls");
                            cout<<"Key is not found."<<endl;
                            break;
                    }
                    break;
                case 9:
                    // Display All Students
                    system("cls");
                    cms.DisplayAllStudents();
                    break;
                case 10:
                    system("cls");
                    // Go back to (1. Admin)
                    return;
                default:
                    system("cls");
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
}


//string getAccess(const string& userID);
class Student : public User {
public:

    //void studentMenu();
    void login(const string& userID, const string& password) override {
        AccessKey=userID;
        ifstream read("C:\\Users\\User\\Desktop\\Course_Management_System\\Student_Info\\" + userID + ".txt");
        string storedPassword;

        if (read.is_open()) {
            getline(read, storedPassword);
            read.close();

            if (storedPassword == password) {
                system("cls");
                cout << "Login successful" << endl;

                AccessKey = userID;
                studentMenu();
            } else {
                cout << "Login error." << endl;
            }
        } else {
            cout << "userID not found. Please sign up." << endl;
        }
    }

    void signup(const string& userID, const string& password) override {
        ifstream read("C:\\Users\\User\\Desktop\\Course_Management_System\\Student_Info\\" + userID + ".txt");

        if (read.is_open()) {
            read.close();
            cout << "userID is already taken." << endl;
        } else {
            ofstream write(("C:\\Users\\User\\Desktop\\Course_Management_System\\Student_Info\\" + userID + ".txt").c_str());  // Added .c_str() for compatibility
            write << password << endl;
            write.close();
            cout << "Registration is successful." << endl;
        }
    }

    void forgotPassword(const string& userID, const string& newPassword) override {
        ifstream read("C:\\Users\\User\\Desktop\\Course_Management_System\\Student_Info\\" + userID + ".txt");

        if (read.is_open()) {
            read.close();
            ofstream temp(("C:\\Users\\User\\Desktop\\Course_Management_System\\Student_Info\\" + userID + "_temp.txt").c_str());  // Added .c_str() for compatibility
            temp << newPassword << endl;
            temp.close();
            remove(("C:\\Users\\User\\Desktop\\Course_Management_System\\Student_Info\\" + userID + ".txt").c_str());
            rename(("C:\\Users\\User\\Desktop\\Course_Management_System\\Student_Info\\" + userID + "_temp.txt").c_str(), ("C:\\Users\\User\\Desktop\\Course_Management_System\\Student_Info\\" + userID + ".txt").c_str());
            cout << "Password reset successfully." << endl;
        } else {
            cout << "userID not found. Password reset failed." << endl;
        }
    }
    void studentMenu(){
        CMS cms;
        int chn;
        int CS;
        string InCode;

        while(true){
            cout<<"Student Menu : "<<endl;
            cout<<"1. Request For Admission"<<endl;
            cout<<"2. Show Access List"<<endl;
            cout<<"3. Show All course"<<endl;
            cout<<"4. Add Course"<<endl;
            cout<<"5. Remove Course"<<endl;
            cout<<"6. Show Added Course"<<endl;
            cout<<"7. Logout"<<endl;
            cout<<endl<<"Choose Your Option : ";
            cin>>chn;
            switch(chn){
                cin.ignore();
                case 1:
                    system("cls");
                    cout<<"Enter an Institute Code : ";
                    cin>>InCode;
                    cms.RequestForAdmision(InCode);
                    break;
                case 2:
                    system("cls");
                    cout<<"This function is not added.\n";
                    break;
                case 3:
                    system("cls");
                    cout<<"Enter Your Institute Code : ";
                    cin>>InCode;
                    cms.showAllCourse(InCode);
                    break;
                case 4:
                    system("cls");
                    cin.ignore();
                    cout<<"For Add Course\n";
                    cout<<"Enter Your Institute Code : ";
                    cin>>InCode;
                    cout<<"Enter The Course Sl No : ";
                    cin.ignore();
                    cin>>CS;
                    cms.addStudentCourse(InCode, CS);
                    break;
                case 5:
                    system("cls");
                    cin.ignore();
                    cout<<"Enter Your Institute Code : ";
                    cin>>InCode;
                    cout<<"Enter Course No : ";
                    cin>>CS;
                    cms.DeleteMyCourse(InCode,CS);
                    break;
                case 6:
                    system("cls");
                    cin.ignore();
                    cout<<"Enter Your Institute Code : ";
                    cin>>InCode;
                    cms.ShowMyCourses(InCode);
                    break;
                case 7:
                    system("cls");
                    return;
                default :
                    system("cls");
                    cout<<"Wrong key!\n";
                    break;
            }
        }

    }
};






int main() {
    //bool status = true;
    while (true) {
        cout << "Select User Type:\n";
        cout << "1. Admin\n";
        cout << "2. Student\n";
        cout << "3. Exit\n";
        cout << "Enter Your Type : ";

        int userType;
        cin >> userType;

        if (userType == 3) {
            cout << "Exiting program...\n";
            break;
        }

        User* user = nullptr;  // Initialize to nullptr

        switch (userType) {
            case 1:
                system("cls");
                user = new Admin();
                break;
            case 2:
                system("cls");
                user = new Student();
                break;
            default:
                system("cls");
                cout << "Invalid choice\n";
                continue;
        }
        //cout << Mode << endl << endl;
        cout << "1. Login\n";
        cout << "2. Registration\n";
        cout << "3. Forgot Password\n";
        cout << "4. Main Menu\n";

        int choice;
        cin >> choice;

        string userID, password, newPassword;

    switch (choice) {
        case 1:
            system("cls");
            cout << "Enter userID: ";
            cin>>userID;
            cout << "Enter password: ";
            cin>>password;
            user->login(userID, password);
            break;
        case 2:
            system("cls");
            cout << "Enter userID: ";
            cin>>userID;
            cout << "Enter password: ";
            cin>>password;
            user->signup(userID, password);
            break;
        case 3:
            system("cls");
            cout << "Enter userID: ";
            cin>> userID;
            cout << "Enter new password: ";
            cin>> newPassword;
            user->forgotPassword(userID, newPassword);
            break;
        case 4:
            system("cls");
            // Go back to the main user type selection
            break;
        default:
            system("cls");
            cout << "Invalid choice\n";
            break;
    }

    delete user;  // Free the allocated memory

    }

    return 0;
}
