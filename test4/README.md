# Assignment 4 
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

When running the above command line, the bash file runs all command below. All output images is in folder **out/**
```shell
./CG_hw4 -f img/bound-lo-sphere.smf -j 0 -k 0 -o 500 -p 500 -x 0.0 -y 0.0 -z 1.0 -X 0.0 -Y 0.0 -Z 0.0 -q 0.0 -r 0.0 -w -1.0 -Q 0.0 -R 1.0 -W 0.0 -u -0.7 -v -0.7 -U 0.7 -V 0.7 > > out/bound_lo/out1.pbm 2> error

./CG_hw4 -f img/bound-lo-sphere.smf -x -1.0 -z 0.5 -q 1.0 -w -0.5 > > out/bound_lo/out2.pbm 2> error

./CG_hw4 -f img/bound-lo-sphere.smf -q 1.0 -w -1.0 > > out/bound_lo/out3.pbm 2> error

./CG_hw4 -f img/bound-lo-sphere.smf -x -4.0 -z 5.0 -q 1.0 -w -0.5 > > out/bound_lo/out4.pbm 2> error

./CG_hw4 -f img/bound-lo-sphere.smf -k 125 -p 375 -q 1.0 -u -1.4 -U 1.4 > > out/bound_lo/out5.pbm 2> error
 ```

**Bunny Example Parallel Projection**
 ```shell
./CG_hw4 -f img/bound-bunny_200.smf -j 100 -k 50 -o 400 -p 450 -x 0.5 -y 0.2 -z 1.0 -X 0.2 -Y -0.2 -Z 0.3 -q -3.0 -r -2.0 -w 1.0 -Q 3.0 -R -2 -W -4.0 -u -.5 -v -.9 -U 1.2 -V .8 -P > out/bunny/hw4_f.pbm 2> error

./CG_hw4 -f img/bound-bunny_200.smf -j 100 -k 50 -o 400 -p 450 -x 0.5 -y 0.2 -z 1.0 -X 0.2 -Y -0.2 -Z 0.3 -q -3.0 -r -2.0 -w 1.0 -Q 3.0 -R -2 -W -4.0 -u -.5 -v -.9 -U 1.2 -V .8 > out/bunny/hw4_g.pbm 2> error
 ```

 **Cow Example**
 ```shell
./CG_hw4 -f img/bound-cow.smf > out/cow/cow_default.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -P > out/cow/cow_parallel.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -j 0 -k 30 -o 275 -p 305 -P > out/cow/cow_jkopP.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -x 1.5 > out/cow/cow_x1.5.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -x 4.75 -y -3.25 -z 3.3 -P > out/cow/cow_xyzPar.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -X 0.25 -Y -0.15 -Z 0.3 > out/cow/cow_XYZ.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -X 0.35 -Y -0.3 -Z 0.3 -u -0.35 -v -0.35 -P > out/cow/cow_XYZuvP.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -X 0.25 -Y -0.15 -Z 0.3 -j 103 -k 143 -o 421 -p 379 > out/cow/cow_XYZjkop.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -X 0.35 -Y -0.3 -Z 0.3 -u -0.35 -v -0.35 -j 43 -k 71 -o 201 -p 402 -P > out/cow/cow_XYZuvjkopP.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -q -1 -r 1.5 -w -2.0 > out/cow/cow_q_r_w.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -Q 1.5 -R 1 -W .4 > out/cow/cow_QRW.pbm 2> error

./CG_hw4 -f img/bound-cow.smf -u -1.5 -v -0.9 -U 1.2 -V 0.7 > out/cow/cow_uvUV.pbm 2> error
 ```

**Debug:**
```shell
./CG_hw4 -f img/cube.smf -u -1.5 -v -1.5 -U 1.5 -V 1.5 -F 1 -B -5 > out/ex1.pbm 2> error

./CG_hw4 -f img/cube.smf -q 1.5 -r 2 -w 5 -u -1 -v -1 -U 1 -V 1 -z 6 -F 1 -B -5 > out/ex2.pbm 2> error

./CG_hw4 -f img/cube.smf -x -4.0 -z 5.0 -q 1.0 -w -0.5 -u -1.0 -v -1.0 -U 1.0 -V 1.0 -F 1 -B -5 > out/ex3.pbm 2> error

# Parallel
./CG_hw4 -f img/cube.smf -u -1.5 -v -1.5 -U 1.5 -V 1.5 -F 1 -B -5 -P > out/ex1_P.pbm 2> error

./CG_hw4 -f img/cube.smf -q 1.5 -r 2 -w 5 -u -1 -v -1 -U 1 -V 1 -z 6 -F 1 -B -5 -P > out/ex2_P.pbm 2> error

./CG_hw4 -f img/cube.smf -x -4.0 -z 5.0 -q 1.0 -w -0.5 -u -1.0 -v -1.0 -U 1.0 -V 1.0 -F 1 -B -5 -P > out/ex3_P.pbm 2> error
```

## Automate testing
To test if the program works for assignment 1. All output images for hw1 is in folder **output/hw3/hw1**
```shell
chmod 700 misc/execute_hw1
./misc/execute
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








