#include "GeneratorID.h"
#include "Student.h"

int GeneratorID:: GenerateUniqueID ()
{
      Student student;
      srand(time(NULL));
      
      unique_id = rand();

      std::fstream studentFile("StudentFile.txt", std::ios:: in);

            studentFile.seekg(0, std::ios:: beg); 

            while(studentFile.read((char*)&student, sizeof(student))) 
            {
                  if(unique_id == student.GetStudentID())
                  {
                        unique_id = rand();
                  }
            }

      return unique_id;
}