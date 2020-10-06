
# HW1 - Clip and draw line
Language: C++ 11
OS: macOS Catalina (test on tux and worked)

## File Structure
```
├── assn1
    ├── test            
    ├── data
    ├── CG_hw1.cpp           # hold main function for
    ├── utils.cpp            # hold utils functions for clipping and drawing Line
    ├── utils.h  
    ├── PBMFile.cpp          # hold PBM object format
    └── PBMFile.h
```

## Compile the program
```shell
make
```
The makefile would run g++ with tag c++11:
```shell
g++ -std=c++11 -o CG_hw1 CG_hw1.cpp PBMFile.cpp
```

## Test the program
```shell
./CG_hw1 -f hw1.ps -a 0 -b 0 -c 499 -d 499 -s 1.0 -m 0 -n 0 -r 0 > out.pbm
./CG_hw1 -f hw1.ps -a 0 -b 0 -c 499 -d 499 -s 0.8 -m 85 -n 25 -r 10 > out.pbm
./CG_hw1 -f hw1.ps -s 0.5 > out.pbm 
./CG_hw1 -f hw1.ps -r -30 > out.pbm
./CG_hw1 -f hw1.ps -m 100 -n 100 > out.pbm
./CG_hw1 -f hw1.ps -a 25 -b 50 -c 399 -d 399 > out.pbm
./CG_hw1 -f hw1.ps -a 25 -b 50 -c 399 -d 399 -r 30 -m 100 -n 100 -s 0.5 > out.pbm
```


