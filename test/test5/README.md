# Assignment 5: Z-Buffering


## Running Program
```shell
chmod 700 runall  
./runall  # bash file to execute all commands in testing 
```

```shell
make
```

## Testing
```shell
./CG_hw5 -f img/bound-sprellpsd.smf -j 0 -k 0 -o 500 -p 500 -x 0.0 -y 0.0 -z 1.0 -X 0.0 -Y 0.0 -Z 0.0 -q 0.0 -r 0.0 -w -1.0 -Q 0.0 -R 1.0 -W 0.0 -u -0.7 -v -0.7 -U 0.7 -V 0.7 -F 0.6 -B -0.6 > output/out.ppm 2> error

./CG_hw5 -f img/bound-cow.smf -F 0.1 > output/hw5_b.ppm 2> error

./CG_hw5 -f img/bound-cow.smf -F 0.1 -B -0.18 > output/hw5_c.ppm 2> error

./CG_hw5 -f img/bound-bunny_1k.smf -g bound-cow.smf -i bound-sprtrd.smf -u -.8 -U .8 -v -.8 -V .8 > output/hw5_d.ppm 2> error

./CG_hw5 -f img/bound-bunny_1k.smf -g bound-cow.smf -i bound-sprtrd.smf -q .4 -r .2 -w 1 -u -.6 -v -.6 -U .6 -V .6 -P > output/hw5_e.ppm 2> error

./CG_hw5 -j 334 -k 24 -o 449 -p 402 -f img/bound-sprellpsd.smf > output/hw5_f.ppm 2> error

./CG_hw5 -u -1.0 -U 0.8 -v -0.9 -V 1.0 -g bound-bunny_1k.smf -f img/bound-sprtrd.smf -j 34 -k 104 -o 149 -p 472 > output/hw5_g.ppm 2> error

./CG_hw5 -u -1.0 -U 0.8 -v -0.9 -V 1.0 -g bound-bunny_1k.smf -f img/bound-sprtrd.smf -j 34 -k 104 -o 149 -p 472 -Q -1.1 -R 0.9 -W 0.6 > output/hw5_h.ppm 2> error
```