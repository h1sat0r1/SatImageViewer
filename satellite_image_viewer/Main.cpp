/*=================================================================================================

    Main.cpp

    Created on Jun/30/2017
    @author: h1sat0r1

=================================================================================================*/

/* include */
#include "MainHeader.h"

/* Prototype */
cv::Mat_<Type> satellite_image_reader(char* _fname, int _c);
cv::Mat_<Type> satellite_image_reader(char* _fname, int _c, int _x1, int _y1, int _x2, int _y2);
int satellite_image_viewer(cv::Mat& _img);
vector<cv::Point2i> clipImage(Params* _p);


/*-----------------------------------------------------------------------------
int main()
-----------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
    // Valuables
    char* fname;
    int c, x1, y1, x2, y2;
    cv::Mat_<Type> image;

	cout
		<< "\n*** USAGE ***\n"
		<< "Case1:\n"
		<< "  $ satellite_image_viewer.exe [filename] [Band num]\n"
		<< "Case2: ROI is given\n"
		<< "  $ satellite_image_viewer.exe [filename] [Band num] [x1] [y1] [x2] [y2]\n\n"
		<< "*[Band num] starts at 1, not 0.\n\n";

    // Arguments
    fname = argv[1];
    c = atoi(argv[2]);

	if (argc == 7)	/* ROI is given */
	{
		x1 = atoi(argv[3]);
		y1 = atoi(argv[4]);
		x2 = atoi(argv[5]);
		y2 = atoi(argv[6]);

        // Read
        image = satellite_image_reader(fname, c, x1, y1, x2, y2);

		// Show
		satellite_image_viewer(image);
    }
	else /* Specify ROI by mouse */
	{
		// Read
		cv::Mat_<Type> prev = satellite_image_reader(fname, c);

		// Mouse parameters
		Params param;
		param.img = prev.clone();
		prev.release();

		// Clipping
		vector<cv::Point2i> roi = clipImage(&param);

		// Read
		image = satellite_image_reader(fname, c, roi.at(0).x, roi.at(0).y, roi.at(1).x, roi.at(1).y);

		// Show
		satellite_image_viewer(image);
	}

    return 0;
}

//EOF