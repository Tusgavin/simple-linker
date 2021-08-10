#ifndef LIGADOR_H
#define LIGADOR_H

#include <vector>
#include <iostream>
#include <map>
#include <string>

#define N 100
struct File
{
   std::vector<std::pair<std::string, int>> labels_in_file;
   std::string assembly_code;
   int assembly_code_size;
   int assembly_code_start;
   int file_index;

   File
   (
      std::vector<std::pair<std::string, int>> labels_in_file,
      std::string assembly_code,
      int assembly_code_size,
      int assembly_code_start,
      int file_index
   )
   {
      this->labels_in_file = labels_in_file;
      this->assembly_code = assembly_code;
      this->assembly_code_size = assembly_code_size;
      this->assembly_code_start = assembly_code_start;
      this->file_index = file_index;
   }
};

class Linker
{
private:
   std::vector<File *> assembly_files;
   std::string assembly_code_concatenated;
   std::string assembly_code_linked;
   std::map<std::string, std::pair<int, int>> labels_table;

public:
   Linker(std::vector<File *> assembly_files);
   ~Linker();

   void concatenate_modules_in_code();
   int get_position_of_label(std::pair<int, int> label_info);
   int get_main_position();
   int get_code_total_size();
   void output();
};

#endif
