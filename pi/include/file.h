#ifndef FILE_H 
#define FILE_H 

#include <string>
#include <fstream>
#include <vector>

class File {
    public:
        void generate(std::vector<std::string> arguments, float value) {
            this->write(arguments, value); 
            this->close();
        }
        File(std::string fileName): fileName(fileName){}
    protected:
        std::string fileName; 
        virtual void write(std::vector<std::string> arguments, float value) = 0 ;
        virtual void close() = 0 ;    
};

class CsvFile : public File {
    std::ofstream stats; 
    void write(std::vector<std::string> arguments, float value);
    void close();   
    public: 
    CsvFile(std::string fileName): File(fileName){
        std::string path = "build/";
        path.append(fileName);
        path.append(".csv");
        stats.open(path, std::ios_base::app) ;
    }
    ~CsvFile(){}
};

#endif
