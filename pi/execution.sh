#! /bin/bash
#
#declare -a x=(1000000 100000000 10000000000 1000000000000)
declare -a x=(100 10000 100000 )
#Strong scaling 

for i in ${!x[@]} ;do for j in {1..4}; do echo ${x[$i]}; OMP_PLACES="cores(${j})" OMP_PROC_BIND="compact" ./build/sequential -N ${x[$i]} -C ${j} -f fileTest -s; ./build/critical -N ${x[$i]} -C ${j} -f fileTest -s; ./build/atomic -N ${x[$i]} -C ${j} -f fileTest -s ; done; done   
awk -F, '{
    if($3 == 1){
        ref[$1","$2] = $5
    }
}{
    $5 =  ref[$1","$2] / $5 
    print $1, $2, $3, $4, $5
}' build/fileTest_strong_scale.csv > build/speedup_strong_scale.dat


gnuplot -e "load 'src/graph/strong_scale.dem'"
open build/graph/strong_scale.png & 

# Weak scaling 
for i in ${!x[@]} ;do for j in {1..4}; do let y=x[$i]*${j}; echo "y is ${y}"; OMP_PLACES="cores(${j})" OMP_PROC_BIND="compact" ./build/sequential -N ${y} -C ${j} -f fileTest -w; ./build/critical -N ${y} -C ${j} -f fileTest -w; ./build/atomic -N ${y} -C ${j} -f fileTest -w ; done; done   
awk -F, '
FNR == NR {
    if($3 == 1){
        ref[$1","length($2)] = $5
    }
    next
}{
    $5 =  (ref[$1","length($2)]) / $5 
    print $1, $2, $3, $4, $5
}' build/fileTest_weak_scale.csv build/fileTest_weak_scale.csv> build/speedup_weak_scale.dat

gnuplot -e "load 'src/graph/weak_scale.dem'"
open build/graph/weak_scale.png & 
