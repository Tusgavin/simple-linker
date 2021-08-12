#include <iostream>
#include <fstream>
#include <string>

#include "montador.h"

int main(int argc, char *argv[]) {
  /*
  * Ler arquivo texto e separar cada instrução por linhas => 
  * gerar um std::vector<std::string> com cada posição sendo uma instrução  
  */

  if (argc <= 1) {
    log_error("argc insufficient - need filename");
    exit(EXIT_FAILURE);
  }

  std::vector<std::string> instructions_in_file;

  const std::string assembly_file_name = std::string(argv[1]);

  std::ifstream assembly_file_pointer(assembly_file_name);

  if (assembly_file_pointer.is_open())
  {
    std::string file_line;

    while(std::getline(assembly_file_pointer, file_line))
    {
      instructions_in_file.push_back(file_line);
    }
    assembly_file_pointer.close();
  }
  else
  {
    log_error("unable to open file " + assembly_file_name);
    exit(EXIT_FAILURE);
  }

  // std::cout << "Antes: " << std::endl;
  // for (auto i : instructions_in_file)
  // {
  //   std::cout << i << std::endl;
  // }

  /**
   * Tratamento de linhas vazias, espaços desnecessários e comentários
   */
  Assembler::remove_empty_lines_from_file_input(instructions_in_file);
  Assembler::remove_whitespaces_from_file_input(instructions_in_file);
  Assembler::remove_comments_from_file_input(instructions_in_file);
  
  // std::cout << "Depois: " << std::endl;
  // for (auto i : instructions_in_file)
  //  {
  //     std::cout << i << std::endl;
  //  }

  /**
   *  Cria operações a partir das linhas presentes no arquivo
   */
  std::vector<Operation> operations_in_file;

  for (auto instruction_stringfied : instructions_in_file)
  {
    Operation * op = new Operation(instruction_stringfied);
    operations_in_file.push_back(*op);
  }

  /**
   * Cria uma instância do Assembler e passa as operações para serem montadas
   */
  Assembler *assembler = new Assembler();

  assembler->convert_code(operations_in_file);

  return 0;
}
