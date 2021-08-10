#include <fstream>
#include <regex>

#include "ligador.h"




void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


int main(int argc, char *argv[]) {

    std::vector<File *> assembly_files;

    for (int i=1; i<argc; i++) {

        std::vector<std::pair<std::string, int>> labels_in_file;
        std::string assembly_code;
        int assembly_code_size;
        int assembly_code_start;
        int file_index = i-1;

        const std::string fileName = std::string(argv[i]);
        std::string line;
        std::fstream myFile;


        myFile.open(fileName);

        if (myFile.is_open()) {

            int line_index = 0;

            while (getline (myFile,line) ) {
                std::stringstream ss(line);
                std::string item = "";

                if (line == "MV-EXE") continue;

                const char label_detector = ':';

                if (line[0] == label_detector && line_index==0) {
                    line.erase(remove(line.begin(), line.end(), label_detector), line.end());
                    
                    std::vector<std::string> elems = split(line, ' ');
                    // std::cout << "primeiro split" << std::endl;
                    // for(auto k=0; k<elems.size(); k++){
                    //     std::cout << elems[k] << std::endl;
                    // }
                    std::pair<std::string, int> label;
                    label.first = elems[0];
                    label.second = std::stoi(elems[1]);
                    labels_in_file.push_back(label);
                } else if (line_index == 0 && std::isdigit(line[0])) {
                    line_index = 1;

                    std::vector<std::string> elems = split(line, ' ');
                    // std::cout << "segundo split" << std::endl;
                    // for(auto k=0; k<elems.size(); k++){
                    //     std::cout << elems[k] << std::endl;
                    // }
                    
                    assembly_code_size = std::stoi(elems[0]);
                    assembly_code_start = std::stoi(elems[3]);
                } else if (line_index == 1 && (std::isdigit(line[0]) || line[0] == label_detector)) {
                    line_index = -1;
                    assembly_code = line;
                }
                

            }

            myFile.close();
        } else error("could not open file ! =x"); 

        // for(auto k=0; k<labels_in_file.size(); k++){
        //     std::cout << labels_in_file[k].first << " e " << labels_in_file[k].second << std::endl;
        // }
        // std::cout << assembly_code << std::endl;
        // std::cout << assembly_code_size << std::endl;
        // std::cout << assembly_code_start << std::endl;
        // std::cout << file_index << std::endl;
        

        File* file = new File(labels_in_file, assembly_code, assembly_code_size, assembly_code_start, file_index);
        assembly_files.push_back(file);

    }

    Linker* linker = new Linker(assembly_files);
    linker->concatenate_modules_in_code();
    linker->output();

    return 0;
}
