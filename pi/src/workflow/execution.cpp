#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

#include <execution.h>
#include <file.h>

Execution::Execution(int argc, char** argv){
    for ( int i = 0; i < argc; i++ ) {
        if ( ( strcmp( argv[ i ], "-N" ) == 0 ) || ( strcmp( argv[ i ], "-num_steps" ) == 0 ) ) {
            this->num_steps = atol( argv[ ++i ] );
            printf( "  User num_steps is %ld\n", num_steps );
        } else if( (strcmp(argv[i], "-C") == 0) || (strcmp(argv[i], "-num_cores") == 0) ){
            this->num_cores = atol( argv[ ++i ]); 
            printf( "  User num_cores is %ld\n", num_cores );
        } else if( (strcmp(argv[i], "-s") == 0)){
            if(strcmp(argv[i], "-w") == 0){
                printf("Please choose between -s or -w (strong scaling or weak sclaing), can't do both ");
                exit( 1 ); 
            }else {
                this->scaling = STRONG;  
            }
        } else if ( strcmp(argv[i], "-f") == 0 ){
            this->fileName = argv[++i] ;
            printf( "  User fileName is %s\n", fileName.c_str() );
        } else if( (strcmp(argv[i], "-w") == 0)){
            if(strcmp(argv[i], "-s") == 0){
                printf("Please choose between -s or -w (strong scaling or weak sclaing), can't do both ");
                exit( 1 ); 
            }else {
                this->scaling = WEAK;  
            }
        } else if( (strcmp(argv[i], "-D") == 0)){
                this->num_split = atol(argv[++i]);  
            printf( "  User num_split is %ld\n", num_cores );
       
        } else if ( ( strcmp( argv[ i ], "-h" ) == 0 ) || ( strcmp( argv[ i ], "-help" ) == 0 ) ) {
            printf( "  Pi Options:\n" );
            printf( "  -num_steps (-N) <int>:      Number of steps to compute Pi (by default 100000000)\n" );
            printf( "  -help (-h):            print this message\n\n" );
            exit( 1 );
        }
    }

    if(this->scaling == STRONG){
        this->fileName.append("_strong_scale");
    } else {
        this->fileName.append("_weak_scale");
    }
}

void Execution::run(){
}
