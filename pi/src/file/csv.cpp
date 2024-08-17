#include <file.h>

void CsvFile::write(std::vector<std::string> arguments,  float value){
    for(size_t i = 0 ; i < arguments.size(); i++){
        this->stats << arguments[i] << ", " ; 
    }
    this->stats << value << std::endl; 
}
void CsvFile::close(){
    this->stats.close(); 
}    

