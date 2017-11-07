/*=================================================================================================

    satellite_image_viewer.h

    Created on 21st/Sep./2017
    @author: h1sat0r1

=================================================================================================*/

#ifndef _SATELLITE_IMAGE_VIEWER_
#define _SATELLITE_IMAGE_VIEWER_

/* include */
#include <iostream>
#include <opencv2/core.hpp>		//OpenCV 3.2 or later
#include <opencv2/highgui.hpp>	//OpenCV 3.2 or later
#include "cvui.h"
#include "MainHeader.h"

/* Namespace */
using namespace std;


/* Def func */
#define ADJUST_BRIGHTNESS(i,m,s,e)	(uchar)CLIP3(0,255,255.0*(s)*powf((i),(e))/(m))


#endif

