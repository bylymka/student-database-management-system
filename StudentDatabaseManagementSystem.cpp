// STUDENT DATABASE MANAGEMENT SYSTEM

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <list>

#include "Student.h"
#include "GeneratorID.h"

using namespace std;

// показать меню и сделать выбор
void ShowMenu(); 

// пользователь выбирает опцию из меню
int GetUserChoice(int user_choice);

// добавить запись о студенте
void AddRecord(string file, bool continue_for_another_student);

// показать записи о всех студентах
void ShowAllRecords(string file);

// изменить данные о студенте
void ModifyRecord(string file, bool continue_for_another_student); 

// удалить студента из базы
void DeleteRecord(string file, bool continue_for_another_student);

// выйти из программы
void QuitProgram();

// продолжить использовать приложение
bool ShouldContinue(bool continue_using_this_software);



int main()
{
      int user_choice; 
      bool continue_for_another_student = true; 
      bool continue_using_this_software = true;
      string file = "StudentFile.txt"; // файл в котором мы будем хранить данные о студентах

      do
      {
            ShowMenu();

            switch(GetUserChoice(user_choice))
            {
                  case 1:
                  {
                        AddRecord(file, continue_for_another_student);
                        break;
                  }

                  case 2:
                  {
                        ShowAllRecords(file);
                        break;     
                  }
      
                  case 3:
                  {
                        ModifyRecord(file, continue_for_another_student);
                        break;
                  }      
      
                  case 4:
                  {
                        DeleteRecord(file, continue_for_another_student);
                        break;
                  }

                  case 5:
                  {
                        QuitProgram();
                        break;
                  }
            }

      } while(ShouldContinue(continue_using_this_software) == true);
}


ostream & operator << (ostream & os, const Student & student_obj) // перегружаем оператор вывода << для класса Student
{
      os << setw(15) << student_obj.StudentID;
      os << setw(15) << student_obj.first_name; 
      os << setw(15) << student_obj.last_name;
      os << setw(30) << student_obj.faculty;
      os << setw(10) << student_obj.group << endl;

      return os;
}


istream & operator >> (istream & is, Student & student_obj) // перегружаем оператор ввода >> для класса Student
{
      is >> student_obj.StudentID >> student_obj.first_name >> student_obj.last_name  >> student_obj.faculty >> student_obj.group;
      return is; 
}



void ShowMenu() // показываем пользователю меню и даем ему возможность сделать выбор
{
      cout << "\nSTUDENT DATABASE MANAGEMENT SYSTEM\n" << endl;
      cout << "1. Add Records" << endl;
      cout << "2. Show Records" << endl;
      cout << "3. Modify Records" << endl;
      cout << "4. Delete Records " << endl;
      cout << "5. Exit" << endl;
      cout << "\n";

      cout << "Select your choice => ";
}



int GetUserChoice(int user_choice) // получаем выбор пользователя
{
      cin >> user_choice;
      return user_choice;
}



void AddRecord(string file, bool continue_for_another_student) // добавляем нового студента в базу
{
      do
      {
            Student student;

            cin.ignore();
            student.SetStudentID(); 
            cout << "Enter the first name: ";
            student.SetFirstName();
            cout << "Enter the last name: ";
            student.SetLastName();
            cout << "Enter the faculty: ";
            student.SetFaculty();
            cout << "Enter the group: ";
            student.SetGroup();


            fstream file_for_writing(file, fstream:: out | fstream:: app);

            if(!file_for_writing.is_open())
            {
                  cout << "Cannot open the file" << endl;
                  break;
            }
            else
            {
                  file_for_writing.write((char*)&student, sizeof(student));
            }

            file_for_writing.close();


            cout << "Add another record? (if 'yes' enter 1, if 'no' enter 0)" << endl;
            cin >> continue_for_another_student;

      } while(continue_for_another_student == true);
}



void ShowAllRecords(string file) // выводим на консоль информацию о всех студентах 
{
      Student student;


      fstream file_for_reading(file, fstream:: in);

      if(!file_for_reading.is_open())
      {
            cout << "Cannot open the file!" << endl;
      }
      else
      {
            cout << setw(15) << "ID" << setw(15) << "FirstName" << setw(15) << "LastName" << setw(30) << "Faculty" << setw(10) << "Group" << endl;

            
            file_for_reading.seekg(0,ios::beg);

            while(file_for_reading.read((char*)&student, sizeof(student)))
            {    
                 cout << student;
            }
      }
      
      file_for_reading.close();
}



void ModifyRecord(string file, bool continue_for_another_student)  // изменяем данные о студенте
{
      Student student;

      do
      {
            int searched_student_id;

            cout << " Enter student ID to be modified: ";
            cin >> searched_student_id;         

            fstream file_for_modification(file, ios:: in | ios:: out | ios:: binary);

            file_for_modification.seekg(0, ios_base:: beg); 

            while(file_for_modification.read((char*)&student, sizeof(student))) 
            {
                  if(searched_student_id == student.GetStudentID())
                  {
                        cin.ignore();
                        cout << "Enter the new first name: ";
                        student.SetFirstName();
                        cout << "Enter the new last name: ";
                        student.SetLastName();
                        cout << "Enter the new faculty: ";
                        student.SetFaculty();
                        cout << "Enter the new group: ";
                        student.SetGroup();

                        // устанавливаем файл поинтер на начало изменяемого обьекта
                        file_for_modification.seekp((file_for_modification.tellg() - sizeof(student)), ios:: beg); 

                        //записываем  новый обьект вместо старого
                        file_for_modification.write((char*) &student,sizeof(student));
                  }
            }

            file_for_modification.close();

            cout << "Do you want to change the data of another student? (if 'yes' enter 1, if 'no' enter 0)" << endl;
            cin >> continue_for_another_student;
            
      }while(continue_for_another_student == true);
}


void DeleteRecord(string file, bool continue_for_another_student) // удаляем запись о студенте из базы
{
      do
      {
            Student student;

            string new_file = "NewStudentFile.txt";
            int studentID_to_delete;

            fstream studentFile(file, ios:: in);

            fstream newStudentFile(new_file, fstream:: out | fstream:: app);

            cout << "Enter ID of the student you want to delete: ";
            cin >> studentID_to_delete;

            while(studentFile.read((char*) &student, sizeof(student)))
            {
                  if (student.GetStudentID() == studentID_to_delete)
                  {
                        continue;
                  }
                  else
                  {
                        newStudentFile.write((char*) &student, sizeof(student));
                  }
            }

            studentFile.close();
            newStudentFile.close();

            remove("StudentFile.txt");
            rename("NewStudentFile.txt", "StudentFile.txt");

            cout << "Do you want to delete another student? (if 'yes' enter 1, if 'no' enter 0)" << endl;
            cin >> continue_for_another_student;

      }while(continue_for_another_student == true);
}

void QuitProgram()
{
      cout << "\n\nThank you for using this software!\n\n";
      exit(0);      
}

bool ShouldContinue(bool continue_using_this_software)
{
      cout << "\nDo you want to continue using this software? (enter 1 - if yes, 0 - if no)" << endl;
      cin >> continue_using_this_software;
      return continue_using_this_software;
}

