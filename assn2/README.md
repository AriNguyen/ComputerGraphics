# Assignment 2 - Clip and Draw Polygon

Language: C++ 11<br>
OS: macOS Catalina<br> 
Note: Test on tux with the same instruction in the section **Compile and Run** and it worked<br>

## Compile and Run
```shell
make
```
The makefile would run g++ with tag c++11:
```shell
g++ -std=c++11 -o CG_hw2.cpp utils.cpp PBMFile.cpp PSImage.cpp GeoObjects.cpp
```

## File Structure
```
├── assn2/
    ├── img/                 # hold all images 
    |   ...
    ├── output/              # hold output images
    |   ...
    ├── test/                # hold test cases
    |   ...
    ├── execute              # bash file    
    ├── makefile             # make file
    ├── CG_hw2.cpp           # hold main function 
    ├── utils.cpp            # hold utils functions for clipping and drawing Line
    ├── utils.h
    ├── GeoObjects.cpp       # hold Geometryobjects: Point, Line, Polygon, GeoObjects
    ├── GeoObjects.h  
    ├── PSImage.cpp          # hold PSImage object
    ├── PSImage.h
    ├── PBMFile.cpp          # hold PBM object format
    └── PBMFile.h
```

## Testing
```shell
chmod 700 execute
./execute
```

The bash file runs:
```shell
./CG_hw2 -f img/hw2_a.ps -s 1.5 > hw2_ex1.pbm 
./CG_hw2 -f img/hw2_a.ps -m -250 -n -200 > hw2_ex2.pbm
./CG_hw2 -f img/hw2_b.ps -a 170 -b 100 -c 270 -d 400 > hw2_ex3.pbm
./CG_hw2 -f img/hw2_b.ps -s 2 > hw2_ex4.pbm
./CG_hw2 -f img/hw2_c.ps -a 200 -b 100 -c 375 -d 400 > hw2_ex5.pbm
./CG_hw2 -f img/hw2_c.ps -a 275 -b 100 -c 550 -d 502 > hw2_ex6.pbm
./CG_hw2 -f img/hw2_b.ps -d 270 -c 435 -b 170 -a 100 -r 17 > hw2_ex7.pbm
./CG_hw2 -f img/hw2_b.ps -a -135 -b -53 -c 633 -d 442 > hw2_ex8.pbm
./CG_hw2 -f img/hw2_c.ps -a -150 -b -475 -c 123 -d -65 > hw2_ex9.pbm 
 ```






