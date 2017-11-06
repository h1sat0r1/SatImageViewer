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


/*-----------------------------------------------------------------------------
int main()
-----------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
    // Valuables
    char* fname;
    int c, x1, y1, x2, y2;
    cv::Mat_<Type> image;

    // Arguments
    fname = argv[1];
    c = atoi(argv[2]);
	//fname = "A:\\Hisa\\Pictures\\Dataset\\Optical\\ALOS AVNIR-2\\GEOTIFF_RPC_AV2\\GeoTIFF_RPC_AV2\\IMG-01-ALAV2A134782730_O1B2R_U.tif";
	//c = 1;

	if (argc == 7)
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
	else
	{
		// Read
		image = satellite_image_reader(fname, 1);

		// Show
		satellite_image_viewer(image);
	}

	//const int r = 10;
	//cv::namedWindow("test", cv::WINDOW_KEEPRATIO);
	//cv::imshow("test", image);
	//cv::resizeWindow("test", image.cols / r, image.rows / r);
	//cv::waitKey(0);
	//cv::destroyAllWindows();


    return 0;
}

//EOF