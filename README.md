# Primordial Particle System 


<p align="center"><img alt="main gif" src="https://i.imgur.com/5MPUWTY.gif"></p>

Based on this [article](https://www.nature.com/articles/srep37969)

### Dependencies
* [CImg](http://cimg.eu/)

### Build
* get [CImg](http://cimg.eu/)
* put `Cimg.h` from the downloaded archive into the project folder
* compile with`g++ *.cpp -L/usr/X11R6/lib -lm -lpthread -lX11 -fopenmp -O2`

### Parameters


Parameter 			| Flag 	| Default
--------------------|-------|------------
Filed Width	| `-w`	| 960
Field Height	| `-h`	| 540
Particle Count	| `-c`	| 1984
Alpha angle (deg)		| `-a`	| 180
Beta angle (deg)		| `-b`	| 17
