
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
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sys/time.h>
#include <omp.h>
#include <file.h>
#include <execution.h>
#include <sstream>

double step;
int main (int argc, char** argv)
{
    Execution exec(argc, argv); 
    // Read command line arguments.
    
    int i;
    double x, pi, sum = 0.0, localSum = 0.0;
    std::vector<std::string> arguments; 
    std::stringstream ss1; 
    CsvFile file(exec.fileName); 

    step = 1.0/(double) exec.num_steps;

    // Timer products.
    struct timeval begin, end;

    gettimeofday( &begin, NULL );
    // I should have 2 loops, the first loop taking the number of jobs
    // to assignate the threads.
    // the second loop is the size of the array that we gave to each thread. 
    // in the seocond loop we make a local summation and we do a reduction on the 
    // results of each thread.
    // TODO make also the number N configurable and test on it.
        for(int r=0 ; r< 100; r++){
            sum = 0.0 ;
            // this should be the loop that we will try to parallelize
            // sum should be a global variable ? 
            // vary the chunck size too ? i think in schedule dynamic by default is 4. 
            #pragma omp parallel for reduction(+:sum) num_threads(exec.num_cores) private(localSum)
            for (i=0;i< exec.num_steps/exec.num_split; i++){
                localSum = 0.0;
                for(int k=1; k <= exec.num_split; k++){
                    x = (i*exec.num_split + k+0.5)*step;
                    localSum = localSum + 4.0/(1.0+x*x);
                }
                sum = sum + localSum;

            }
            pi = step * sum;
        }
    gettimeofday( &end, NULL );

    // Calculate time.
    double time = 1.0 * ( end.tv_sec - begin.tv_sec ) +
        1.0e-6 * ( end.tv_usec - begin.tv_usec );
    arguments.push_back("splitN");
    arguments.push_back(std::to_string(exec.num_steps));
    arguments.push_back(std::to_string(exec.num_cores));
    arguments.push_back(std::to_string(exec.num_split));
    arguments.push_back(std::to_string(pi));
    ss1 << std::abs(pi - exec.piExpec);
    arguments.push_back(ss1.str());
    file.generate(arguments, time);
    printf("\n impl: (%s), pi with %ld steps is %lf in %lf seconds \n ", "splitN", exec.num_steps,pi,time);

}
