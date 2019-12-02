#pragma once
#include <fstream>

class Student // класс хранит данные о каждом студенте
{
private:
      int StudentID;
      char first_name[15];
      char last_name[15];
      char faculty[30];
      char group[10];

public:
      friend std::ostream & operator << (std::ostream & out, const Student & student_obj);
      friend std::istream & operator >> (std::istream & is, Student & student_obj);

      void SetStudentID();

      int GetStudentID();

      char* GetFirstName();

      void SetFirstName();

      char* GetLastName();

      void SetLastName();

      char* GetFaculty();

      void SetFaculty();

      char* GetGroup();

      void SetGroup();
};
