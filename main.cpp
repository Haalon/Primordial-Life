#include "field.h"
#include "CImg.h"
#include <ctime>
#include <iostream>
#include <omp.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char const *argv[])
{
	Field fld(1920/2,1080/2, 1024+512+256+128+64);
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