# Assignment 2 - Clip and Draw Polygon
Language: C++ 11<br>
OS: macOS Catalina<br>
Note: Test on tux with the same instruction in the section **Compile and Run** and it worked for both assignment 1 and 2<br>

## Compile and Run
```shell
make
```
The makefile runs g++ with tag c++11:
```shell
g++ -std=c++11 -o bin/CG_hw2 CG_hw2.cpp utils.cpp pbm_file.cpp ps_image.cpp geometry_objects.cpp transformations.cpp drawing.cpp time.cpp
```

## Testing
Test assignment 2:
```shell
chmod 700 misc/execute
./misc/execute
```
When running the above command line, the bash file runs all command below. All output images is in folder **output/hw2**
```shell
./bin/CG_hw2 -f img/hw2_a.ps -s 1.5 > output/hw2/hw2_ex1.pbm 
./bin/CG_hw2 -f img/hw2_a.ps -m -250 -n -200 > output/hw2/hw2_ex2.pbm
./bin/CG_hw2 -f img/hw2_b.ps -a 170 -b 100 -c 270 -d 400 > output/hw2/hw2_ex3.pbm
./bin/CG_hw2 -f img/hw2_b.ps -s 2 > output/hw2/hw2_ex4.pbm
./bin/CG_hw2 -f img/hw2_c.ps -a 200 -b 100 -c 375 -d 400 > output/hw2/hw2_ex5.pbm
./bin/CG_hw2 -f img/hw2_c.ps -a 275 -b 100 -c 550 -d 502 > output/hw2/hw2_ex6.pbm
./bin/CG_hw2 -f img/hw2_b.ps -d 270 -c 435 -b 170 -a 100 -r 17 > output/hw2/hw2_ex7.pbm
./bin/CG_hw2 -f img/hw2_b.ps -a -135 -b -53 -c 633 -d 442 > output/hw2/hw2_ex8.pbm
./bin/CG_hw2 -f img/hw2_c.ps -a -150 -b -475 -c 123 -d -65 > output/hw2/hw2_ex9.pbm 
 ```

To test if the program works for assignment 1. All output images for hw1 is in folder **output/hw1**
```shell
chmod 700 misc/execute_hw1
./misc/execute_hw1
```


## File Structure
```
├── assn2/
    ├── img/                 # hold all images 
    |   ...
    ├── output/hw2/          # hold output images
    |   ...
    ├── test/                # hold test cases
    |   ...
    ├── output/              # hold output
    |   ...
    ├── misc/                # bash scripts
    |   ...
    ├── execute              # bash file    
    ├── makefile             # make file
    ├── CG_hw2.cpp           # hold main function 
    ├── drawing.cpp          # hold functions for drawing, clipping
    ├── drawing.hpp
    ├── transformations.cpp  # hold functions for transforming matrices
    ├── transformations.hpp
    ├── utils.cpp            # hold utils functions for tokenize string, handle arguments
    ├── utils.hpp
    ├── geometry_objects.cpp # hold Geometryobjects: Point, Line, Polygon, GeoObjects
    ├── geometry_objects.hpp  
    ├── ps_image.cpp         # hold PSImage object
    ├── ps_image.hpp
    ├── pbm_file.cpp         # hold PBM object format
    └── pbm_file.hpp
```

## Line Intersection
Source:<br>
https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#cite_note-Wolfram-1








