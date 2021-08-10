#include "ligador.h"

Linker::Linker(std::vector<File *> assembly_files)
{
   this->assembly_files = assembly_files;

   std::string _assembly_code_concatenated = "";
   std::map<std::string, std::pair<int, int>> _labels_table;

   for (auto file : assembly_files)
   {
      _assembly_code_concatenated += file->assembly_code + " ";

      for (auto label : file->labels_in_file)
      {
         
      }
   }

   this->assembly_code_concatenated = _assembly_code_concatenated;
}

Linker::~Linker()
{

}