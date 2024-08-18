#ifndef EXECUTION_H 
#define EXECUTION_H 
#include <string>

enum SCALING {
    STRONG = 0, 
    WEAK 
};
class Execution {
    public :
        long num_steps = 100000000;
        long num_cores = 4;
        long num_split = 1;
        double step;
        SCALING scaling = STRONG;
        std::string fileName; 
        Execution(int argc, char**argv);
        void run();
};
#endif
