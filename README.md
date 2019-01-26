# Primordial Particle System 

Based on this [article](https://www.nature.com/articles/srep37969)

### Dependencies
* [CImg](http://cimg.eu/)

### Compile
`g++ *.cpp -L/usr/X11R6/lib -lm -lpthread -lX11 -fopenmp -O2`

### Parameters


Parameter 			| Flag 	| Default
--------------------|-------|------------
Filed Width	| `-w`	| 960
Field Height	| `-h`	| 540
Particle Count	| `-c`	| 1984
Alpha angle (deg)		| `-a`	| 180
Beta angle (deg)		| `-b`	| 17