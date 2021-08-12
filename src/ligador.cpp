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
   this->assembly_code_linked = "";
}

Linker::~Linker()
{

}

void Linker::concatenate_modules_in_code()
{
   std::string new_assembly_code = "";
   int reading_code_size = 0;

   for (size_t i = 0; i < this->assembly_code_concatenated.length(); ++i)
   {

      if (this->assembly_code_concatenated[i] == ':')
      {
         size_t end_of_label_index = -1;

         for (size_t j = i; j < this->assembly_code_concatenated.length(); ++j)
         {
            if (this->assembly_code_concatenated[j] == ' ')
            {
               end_of_label_index = j;
               break;
            }
         }

         std::string needed_label = this->assembly_code_concatenated.substr(i + 1, end_of_label_index - i - 1);

         std::pair<int, int> info_of_label = this->labels_table[needed_label];

         int position_of_label = this->get_position_of_label(info_of_label);


         std::string stringfied_final_position = std::to_string(position_of_label - reading_code_size - 1);

         // (position_of_label > reading_code_size) ?
         //    stringfied_final_position = std::to_string(position_of_label - reading_code_size - 1) :
         //    stringfied_final_position = std::to_string(position_of_label - reading_code_size + 1);

         new_assembly_code += stringfied_final_position;

         i = end_of_label_index - 1;
         reading_code_size++;
      }
      else
      {
         new_assembly_code += this->assembly_code_concatenated[i];

         if (this->assembly_code_concatenated[i] == ' ') continue;
         else 
         {
            for (size_t j = i + 1; j < this->assembly_code_concatenated.length(); ++j)
            {
               if (this->assembly_code_concatenated[j] == ' ')
               {
                  reading_code_size++;
                  i = j - 1;
                  break;
               }
               else
               {
                  new_assembly_code += this->assembly_code_concatenated[j];
               }
            }
         }

      }
   }

   this->assembly_code_linked = new_assembly_code;
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

int Linker::get_main_position()
{
   std::pair<int, int> info_of_label = this->labels_table["main"];

   int position_of_label = this->get_position_of_label(info_of_label);

   return position_of_label;
}

int Linker::get_code_total_size()
{
   int total_size = 0;

   for (auto file : this->assembly_files)
   {
      total_size += file->assembly_code_size;
   }

   return total_size;
}

void Linker::output()
{
   std::cout << "MV-EXE" << std::endl;

   std::cout << std::endl;

   std::string stringfied_program_details =
      std::to_string(this->get_code_total_size()) +
      " " +
      std::to_string(N) +
      " " +
      std::to_string(N + this->get_code_total_size() + 1000) +
      " " +
      std::to_string(N + this->get_main_position());

   std::cout << stringfied_program_details << std::endl;

   std::cout << std::endl;

   std::cout << this->assembly_code_linked << std::endl;
}