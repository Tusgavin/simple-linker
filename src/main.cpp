#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

#define error(msg) { std::cout << "eRRor: " << msg << std::endl; exit(EXIT_FAILURE); }

#include "ligador.h"

int main(int argc, char *argv[]) {

    for (int i=1; i<argc; i++) {
        const std::string fileName = std::string(argv[i]);
        std::string line;
        std::fstream myFile;


        myFile.open(fileName);

        if (myFile.is_open()) {
            while (getline (myFile,line) ) {
                std::stringstream ss(line);
                std::string item = "";

                std::cout << line << std::endl;

                for (size_t i=0; i<=line.size(); i++) {

                    if (i == line.size() && item.size()!=0) {
                        // this->fileInstructions.push_back(item);
                        std::cout << item << std::endl;
                        item = "";
                    }

                    if (line[i] == ';') {
                        
                        if (item.size() != 0) {
                            // this->fileInstructions.push_back(item);
                            std::cout << item << std::endl;
                            item = "";
                        }
                        break;
                    }

                    if ((!isalpha(line[i]) && !std::isdigit(line[i])) || line[i]==' ') {
                        if (item.size() != 0) {
                            // this->fileInstructions.push_back(item);
                            std::cout << item << std::endl;
                            item = "";
                        }
                    } else {
                        item += line[i];
                    }

                }
            }

            myFile.close();
        } else error("could not open file ! =x"); 

    }

    return 0;
}
