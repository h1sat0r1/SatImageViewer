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


/* Def */
#define WINDOWNAME_IMAGE_WINDOW     "SatImageViewer ([ESC] to close)"
#define WINDOWNAME_OPERATIONPANEL   "Operation Panel"
#define WIN_WIDTH 640

/* Arrow keys */
#define CV_WAITKEY_CURSORKEY_TOP        2490368
#define CV_WAITKEY_CURSORKEY_BOTTOM     2621440
#define CV_WAITKEY_CURSORKEY_RIGHT      2555904
#define CV_WAITKEY_CURSORKEY_LEFT       2424832

/* Primiteive keys */
#define CV_WAITKEY_ENTER    10
#define CV_WAITKEY_ESC      27
#define CV_WAITKEY_SPACE    32
#define CV_WAITKEY_TAB      9

/* Def func */
#define CLIP3(min,max,a)			(((a)<(min))?(min):(((a)>(max))?(max):(a)))
#define ADJUST_BRIGHTNESS(i,m,s,e)	(uchar)CLIP3(0,255,255.0*(s)*powf((i),(e))/(m))


#endif

