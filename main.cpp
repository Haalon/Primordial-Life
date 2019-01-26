#include "field.h"
#include "CImg.h"
#include <ctime>
#include <iostream>
#include <omp.h>

using namespace std;
using namespace cimg_library;

#define PI 3.14159265358979323846

double alpha = PI;
double beta = PI/180*17;
double radius = 25;

int width = 1920/2;
int height = 1080/2;
int p_count = 1984;

void parseArgs(int argc, char const *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		string arg = argv[i];

		if((arg == "-c") || (arg == "--count"))
		{
			if(i + 1 >= argc)
			{
				 cerr << "--count option requires one argument." << endl;
				 exit(EXIT_FAILURE);
			}
			p_count = stoi(argv[++i]);
			continue;
		}

		if((arg == "-w") || (arg == "--width"))
		{
			if(i + 1 >= argc)
			{
				 cerr << "--width option requires one argument." << endl;
				 exit(EXIT_FAILURE);
			}
			width = stoi(argv[++i]);
			continue;
		}

		if((arg == "-h") || (arg == "--height"))
		{
			if(i + 1 >= argc)
			{
				 cerr << "--height option requires one argument." << endl;
				 exit(EXIT_FAILURE);
			}
			height = stoi(argv[++i]);
			continue;
		}

		if((arg == "-a") || (arg == "--alpha"))
		{
			if(i + 1 >= argc)
			{
				 cerr << "--alpha option requires one argument." << endl;
				 exit(EXIT_FAILURE);
			}
			alpha = PI * stod(argv[++i]) / 180;
			continue;
		}


		if((arg == "-b") || (arg == "--beta"))
		{
			if(i + 1 >= argc)
			{
				 cerr << "--beta option requires one argument." << endl;
				 exit(EXIT_FAILURE);
			}
			beta = PI * stod(argv[++i]) / 180;
			continue;
		}

	}
}

int main(int argc, char const *argv[])
{
	parseArgs(argc,argv);
	Field fld(width, height, p_count, alpha, beta);
	auto img = fld.show();

	CImgDisplay main_disp(img,"PPS");
	double time = 0;
	while (!main_disp.is_closed() )
    {
    	// main_disp.wait(20);
    	double start = omp_get_wtime();
    	fld.update();
    	time +=  (omp_get_wtime() - start)*1000;
    	cout << fld.step << ": " << (time/fld.step) <<"\n";


    	// if(fld.step % 2 == 1)
    	{
	    	img = fld.show();
	    	// img.save("img/b.png", fld.step, 6);
	    	main_disp.display(img);

	    }
	    

    }
	return 0;
}