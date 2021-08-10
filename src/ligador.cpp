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
         _labels_table[label.first] = std::make_pair(label.second, file->file_index);
      }
   }

   this->assembly_code_concatenated = _assembly_code_concatenated;
   this->labels_table = _labels_table;
}

Linker::~Linker()
{

}

std::string Linker::concatenate_modules_in_code()
{
   std::string new_assembly_code = "";
   int reading_code_size = 0;

   for (size_t i = 0; i < this->assembly_code_concatenated.length(); ++i)
   {
      if (this->assembly_code_concatenated[i] == ':')
      {
         reading_code_size++;

         int end_of_label_index = -1;

         for (size_t j = i; j < this->assembly_code_concatenated.length(); ++j)
         {
            if (this->assembly_code_concatenated[j] == ' ')
            {
               end_of_label_index = j;
               break;
            }
         }

         std::string needed_label = this->assembly_code_concatenated.substr(i + 1, end_of_label_index);

         std::pair<int, int> info_of_label = this->labels_table[needed_label];

         int position_of_label = this->get_position_of_label(info_of_label);

         std::string stringfied_final_position = std::to_string(position_of_label - reading_code_size);

         new_assembly_code += stringfied_final_position;

         i = end_of_label_index - 1;
      }
      else
      {
         new_assembly_code += this->assembly_code_concatenated[i];

         if (this->assembly_code_concatenated[i]) continue;
         else
         {
            for (size_t j = i + 1; j < this->assembly_code_concatenated.length(); ++j)
            {
               new_assembly_code += this->assembly_code_concatenated[j];

               if (this->assembly_code_concatenated[j] == ' ')
               {
                  reading_code_size++;
                  i = j - 1;
                  break;
               }
            }  
         }
      }
   }

   return new_assembly_code;
}

int Linker::get_position_of_label(std::pair<int, int> label_info)
{
   int label_position_in_file = label_info.first;
   int file_id = label_info.second;
   int total_bytes_until_label = 0;

   for (int i = 0; i < file_id; ++i)
   {
      total_bytes_until_label += this->assembly_files[i]->assembly_code_size;
   }

   total_bytes_until_label += label_position_in_file;

   return total_bytes_until_label;
}