#!/bin/bash
#SBATCH --job-name=nbody_simulation
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G


./nbody 100 1 10000 100
./nbody 1000 1 10000 100
./nbody 2 200 5000000 1000
TEST_CASES=(
    "100 1 10000 100"       
    "1000 1 10000 100"      
    "2 200 5000000 1000"    
)

mkdir -p logs

for test in "${TEST_CASES[@]}"; do    
    PARAMS=($test)
    NUM_PARTICLES=${PARAMS[0]}
    DT=${PARAMS[1]}
    NUM_ITER=${PARAMS[2]}

    LOG_FILE="logs/output_${NUM_PARTICLES}p_${DT}dt_${NUM_ITER}steps.tsv"
    
    ./nbody $test > "$LOG_FILE"
done

