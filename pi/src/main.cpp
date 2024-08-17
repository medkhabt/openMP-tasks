/*
 * This program will numerically compute the integral of

 4/(1+x*x) 

 from 0 to 1.  The value of this integral is pi -- which 
 is great since it gives us an easy way to check the answer.

History: Written by Tim Mattson, 11/1999.
Modified/extended by Jonathan Rouzaud-Cornabas, 10/2022
Modified/extended by Khalil Loukhnati, 18/2024
*/

#include <limits>
#include <cstdio>
#include <sys/time.h>
#include <file.h>
#include <execution.h>


int main (int argc, char** argv)
{
    Execution exec(argc, argv); 

    CsvFile file(exec.fileName); 
    double step = 1.0/(double) exec.num_steps;
    int i;
    double x, pi, sum = 0.0;
    std::vector<std::string> arguments; 
    struct timeval begin, end;

    gettimeofday( &begin, NULL );
    for(int r=0 ; r< 100; r++){
        sum = 0.0 ;
        for (i=1;i<= exec.num_steps; i++){
            x = (i-0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
        pi = step * sum;
    }
    gettimeofday( &end, NULL );

    // Calculate time.
    double time = 1.0 * ( end.tv_sec - begin.tv_sec ) +
        1.0e-6 * ( end.tv_usec - begin.tv_usec );
    arguments.push_back("sequential");
    arguments.push_back(std::to_string(exec.num_steps));
    arguments.push_back(std::to_string(exec.num_cores));
    arguments.push_back(std::to_string(pi));

    file.generate(arguments, time);
    printf("\n pi with %ld steps is %lf in %lf seconds\n ",exec.num_steps,pi,time);
}
