# README: Running N-Body Simulation
*DISCLAIMER THIS WAS AI GENERATED OpenAI. (2025). ChatGPT [Large language model]. https://chatgpt.com*

## Prerequisites
Ensure you have the following installed:
- A Linux-based system with SLURM workload manager
- GCC compiler
- Bash shell
- Python 3 with matplotlib libraries
- Access to UNCC's Centaurus node cluster

## Connecting to Centaurus
Open the terminal and enter:
```sh
ssh unccuser@hpc-student.uncc.edu
```
You will be prompted to enter your password and sign in via Duo. 

## Cloning the Repository
Once in the terminal enter:
```sh
git clone https://github.com/Dsaldivar21/n-body.git
cd n-body
```
## Compilation
Before running nbody, compile the C++ code:
```sh
g++ -o nbody nbody.cpp
```

## Running the Nbody Benchmark
To submit the Nbody job to the SLURM scheduler, use the provided script:
```sh
sbatch nbodyscript.sh
```
This script runs nbody.cpp on different input parameters and records execution times and creates the output.tsv files as unique files.

## Notes
- Modify `nbodyscript.sh` if using a different SLURM partition.
- Ensure the script has execute permissions: `chmod +x nbodyscript.sh`.
- Adjust memory/time limits in the SLURM script as needed.

## Troubleshooting
- If MergeSort does not execute, ensure `nbody` is compiled and executable (`chmod +x nbody.cpp`).
- If Python script fails, install dependencies with:
  ```sh
  pip install matplotlib
