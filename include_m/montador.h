#ifndef MONTADOR_H
#define MONTADOR_H

#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>

#define NOARG -1
#define REG 0
#define MEM 1
#define N 100

// TODO: structs, classes, e outras definições.


void log_error(const std::string message);

bool is_number(const std::string& s);

std::string left_trim(const std::string &str);

std::string right_trim(const std::string &str);

// Remove unecessary whitespaces in the beggining and end of string
std::string trim(const std::string &str);
class Operation
{
private:
   std::string label;
   std::string operador;
   std::string operando1;
   std::string operando2;

public:
   Operation(std::string operation_stringfied);
   ~Operation() { };

   // GET
   std::string get_label() const { return this->label; }
   std::string get_operador() const { return this->operador; }
   std::string get_operando1() const { return this->operando1; }
   std::string get_operando2() const { return this->operando2; }

   // SET
   void set_label(std::string label) { this->label = label; }
   void set_operador(std::string operador) { this->operador = operador; }
   void set_operando1(std::string operando1) { this->operando1 = operando1; }
   void set_operando2(std::string operando2) { this->operando2 = operando2; }

   int calculate_operation_size();
};

typedef struct VMInstructions
{
   std::string symbol;
   int code;
   int first_arg;
   int second_arg;
   int size;

   VMInstructions(std::string symbol, int code, int first_arg, int second_arg, int size)
   {
      this->symbol = symbol;
      this->code = code;
      this->first_arg = first_arg;
      this->second_arg = second_arg;
      this->size = size;
   }
} VMInstructions;

class Assembler
{
private:
   std::vector<VMInstructions> vm_instructions;

public:
   Assembler();
   ~Assembler() { };

   std::vector<VMInstructions> get_vm_instructions() const { return this->vm_instructions; }

   std::vector<std::string> convert_code(std::vector<Operation> ops);
   VMInstructions find_instruction_by_symbol(std::string symbol);
   static int convert_register_to_machine_code(std::string registerName);
   
   static void remove_comments_from_file_input(std::vector<std::string> &input_str);
   static void remove_empty_lines_from_file_input(std::vector<std::string> &input_str);
   static void remove_whitespaces_from_file_input(std::vector<std::string> &input_str);
   static void write_converted_code(
      std::vector<std::string> stringfied_intructions,
      int code_total_size,
      int code_initial_pos,
      std::vector<std::string> instructions_to_link);
};

#endif  // MONTADOR_H
