#pragma once

#include <iostream>
#include <ctime>
#include <fstream>

class GeneratorID // класс который генерирует уникальный ID для каждого студента
{
private:
      int unique_id;
      
public:
      int GenerateUniqueID();
};