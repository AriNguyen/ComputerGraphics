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
When running the above command line, the bash file runs all command below. All output images is in folder **output/hw3/hw2**
```shell
./CG_hw3 -f img/hw3_split.ps > output/hw3/hw3_a.pbm 2> error
./CG_hw3 -f img/hw3_split.ps -a 0 -b 0 -c 500 -d 500 -j 0 -k 0 -o 500 -p 500 -s 1.0 -m 0 -n 0 -r 0 > output/hw3/hw3_b.pbm 2> error
./CG_hw3 -f img/hw3_split.ps -a 50 -b 0 -c 325 -d 500 -j 0 -k 110 -o 480 -p 410 -s 1 -m 0 -n 0 -r 0 > output/hw3/hw3_c.pbm 2> error
./CG_hw3 -f img/hw3_split.ps -a 10 -b 10 -c 550 -d 400 -j 10 -k 10 -o 500 -p 400 -s 1.2 -m 6 -n 25 -r 8 > output/hw3/hw3_d.pbm 2> error
./CG_hw3 -f img/hw3_split.ps -b 62 -c 500 -d 479 -r 75 -j 139 -o 404 -p 461 -s .85 -m 300 > output/hw3/hw3_e.pbm 2> error
./CG_hw3 -f img/hw3_split.ps -a 275 -b 81 -c 550 -d 502 -r -37 -j 123 -k 217 -o 373 -p 467 > output/hw3/hw3_f.pbm 2> error
./CG_hw3 -f img/hw3_split.ps -d 301 -c 435 -b 170 -a -100 -r -23 > output/hw3/hw3_g.pbm 2> error
./CG_hw3 -f img/hw3_split.ps -a -135 -b -53 -c 633 -d 842 -m -23 -j 101 -p 415 -s 3.6 > output/hw3/hw3_h.pbm 2> error
 ```

To test if the program works for assignment 1. All output images for hw1 is in folder **output/hw3/hw1**
```shell
chmod 700 misc/execute_hw1
./misc/execute_hw1
```


## File Structure
```
├── assn2/
    ├── img/                 # hold all images 
    |   ...
    ├── output/hw3/hw2/          # hold output images
    |   ...
    ├── test/                # hold test cases
    |   ...
    ├── output/hw3/              # hold output
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








