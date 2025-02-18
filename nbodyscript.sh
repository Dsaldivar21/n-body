#!/bin/bash
#SBATCH --job-name=nbody_simulation
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G

TEST_CASES=(
    "100 1 10000 100"       
    "1000 1 10000 100"      
    "2 200 5000000 1000"    
)

mkdir -p results

for test in "${TEST_CASES[@]}"; do    
    PARAMS=($test)
    NUM_PARTICLES=${PARAMS[0]}
    DT=${PARAMS[1]}
    NUM_ITER=${PARAMS[2]}

    OUTPUT_FILE="results/output_${NUM_PARTICLES}p_${DT}dt_${NUM_ITER}steps.tsv"

    ./nbody $test

    cp output.tsv $OUTPUT_FILE

    > output.tsv

   
done


