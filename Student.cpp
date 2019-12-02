#include "GeneratorID.h"
#include "Student.h"


void Student:: SetStudentID()
{
      GeneratorID student;
      this->StudentID = student.GenerateUniqueID();
}

int Student:: GetStudentID()
{
      return StudentID;
}

char* Student:: GetFirstName()
{
      return first_name;
}

void Student:: SetFirstName()
{
      std::cin.getline(first_name, 15);
}

char* Student:: GetLastName()
{
      return last_name;
}

void Student:: SetLastName()
{
      std::cin.getline(last_name, 15);
}

char* Student:: GetFaculty()
{
      return faculty;
}

void Student:: SetFaculty()
{
      std::cin.getline(faculty, 30);
}

char* Student:: GetGroup()
{
      return group;
}

void Student:: SetGroup()
{
      std::cin.getline(group, 10);
}
