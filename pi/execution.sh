#! /bin/bash
#
#declare -a x=(1000000 100000000 10000000000 1000000000000)
declare -a x=(100 10000 100000 )
#Strong scaling 

for i in ${!x[@]} ;
    do for j in {1..4}; 
        do echo ${x[$i]}; 
            OMP_PLACES="cores(${j})" OMP_PROC_BIND="compact" ./build/sequential -N ${x[$i]} -C ${j} -f fileTest -s;
            ./build/critical -N ${x[$i]} -C ${j} -f fileTest -s;
            ./build/atomic -N ${x[$i]} -C ${j} -f fileTest -s ;
            ./build/reduction -N ${x[$i]} -C ${j} -f fileTest -s ;
            ./build/splitN -N ${x[$i]} -C ${j} -D 10 -f fileTest -s ;
        done; done   
awk -F, '{
    if($3 == 1){
        ref[$1","$2] = $6
    }
}{
    $6 =  ref[$1","$2] / $6 
    print $1, $2, $3, $4, $5, $6
}' build/fileTest_strong_scale.csv > build/speedup_strong_scale.dat


gnuplot -e "load 'src/graph/strong_scale.dem'"
open build/graph/strong_scale.png & 

# Weak scaling 
for i in ${!x[@]} ;
    do for j in {1..4}; 
          do let y=x[$i]*${j}; echo "y is ${y}"; 
              OMP_PLACES="cores(${j})" OMP_PROC_BIND="compact" ./build/sequential -N ${y} -C ${j} -f fileTest -w;
              ./build/critical -N ${y} -C ${j} -f fileTest -w; 
              ./build/atomic -N ${y} -C ${j} -f fileTest -w ;
              ./build/reduction -N ${y} -C ${j} -f fileTest -w ;
              ./build/splitN -N ${y} -C ${j}-D 10 -f fileTest -w ;
          done; done   
awk -F, '
FNR == NR {
    if($3 == 1){
        ref[$1","length($2)] = $6
    }
    next
}{
    $6 =  (ref[$1","length($2)]) / $6 
    print $1, $2, $3, $4, $5, $6
}' build/fileTest_weak_scale.csv build/fileTest_weak_scale.csv> build/speedup_weak_scale.dat

gnuplot -e "load 'src/graph/weak_scale.dem'"
open build/graph/weak_scale.png & 

# Checking the best N split 
# It should be for each n_occurance. 
# for each one we multiple by 10 until we have one left. 
#
#
for i in ${!x[@]} ;
   do echo "x[i] = ${x[$i]}"; 
       for j in {1..4}; 
       do echo "j is $j" ;
           for ((k=1; k < ${x[$i]} ; k*=10)); do echo "i = $i, j = $j, k = $k";
            ./build/splitN -N ${x[$i]} -C ${j} -D ${k} -f compareSplit -s;
            #./build/splitN -N ${x[$i]} -C ${j} -D 100 -f compareSplit -s;
       done;
   done;
done
# do it again just for splitN
awk -F, '{
    if($3 == 1 && $4 == 1){
        ref[$1","$2] = $6
    }
}{
    $6 =  ref[$1","$2] / $6 
    print $1, $2, $3, $4, $5, $6
}' build/compareSplit_strong_scale.csv > build/speedup_strong_compare_split.dat


gnuplot -e "load 'src/graph/strong_scale_splitN.dem'"
open build/graph/strong_scale_splitN.png & 

for i in ${!x[@]} ;
    do for j in {1..4}; 
          do let y=x[$i]*${j}; echo "y is ${y}"; 
           for ((k=1; k < ${x[$i]} ; k*=10)); do echo "i = $i, j = $j, k = $k"; 
              ./build/splitN -N ${y} -C ${j} -D ${k} -f compareSplit -w ;
          done; done; done   
awk -F, '
FNR == NR {
    if($3 == 1 && $4 == 1){
        ref[$1","length($2)] = $6
    }
    next
}{
    $6 =  (ref[$1","length($2)]) / $6 
    print $1, $2, $3, $4, $5, $6
}' build/compareSplit_weak_scale.csv build/compareSplit_weak_scale.csv> build/speedup_weak_compare_split.dat

gnuplot -e "load 'src/graph/weak_scale_splitN.dem'"
open build/graph/weak_scale_splitN.png & 
