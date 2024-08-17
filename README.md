# Lab instructions 
## Preformance evaluation methodology: 
1 - Modify the performance metric part of the codes to store the vaule ( with the params ) 
into a file ( csv suggested by the prof). 
2 - test with different number of cores  when code is parallized with OpenMP. Added as arg
3 - automatize the multiple execution ( given a range for each parameter)
4 - reapeat each excution multiple times ( at least 10 times)
5 - figure contain aggregated value ( i.e. mean, median, and/or standard deviation )
6 - Free to use whatever scripting language. 
7 - same for the drawing. 
8 - all the experiments should be done and evaluated on the same computer. 
10 - compatibility 


## Computing pi 
### Before the computation 
- [X] create files with the appropriate format.  
- [X] specify all the needed args. (first version doesn't need any args, i mean the sequential one) 
- [X] run the code more than a 10 times. 
### what to do 
evaluatioon on 1000000, 100000000, 10000000000, 1000000000000.

draw the figurs and explain the performance. 
- [X] critical
- [X] atomic 
- [X] reduction 
- [ ] split array into N parts, each thread compute a part and compute a partial sum
- [X] add args to specify number of cors 
- [X] calculate  strong scaling  ( I just added the arg for it, i need split the save files depending on which scaling, so i have easier time 
in the postprocessing with the awk.)
- [X] calculate weak scaling  
- [ ] Median, avg, error margin ? (taking in consideration the result from the sequential part.) 

