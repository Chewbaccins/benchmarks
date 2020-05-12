#! /bin/bash
size=1024
step=1024
Maxsize=20480
nstart=4
nstep=4
nmax=1024 
while [ $nstart -le $nmax ]
do
    #echo $nstart
    nstart=$[$nstart+$nstep]
    while [ $size -le $Maxsize ]
    do 
        #echo $size
        size=$[$size+$step]
        cleo-submit -np $nstart -as intel ./runchol $size
    done
done