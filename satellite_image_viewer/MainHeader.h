/*=================================================================================================

    MainHeader.h

    Created on Jun/27/2017
    @author: h1sat0r1

=================================================================================================*/

#ifndef _MAIN_H_
#define _MAIN_H_

/* include */
#include <iostream>
#include <opencv2/core.hpp>		//OpenCV must be 3.2 or later
#include <opencv2/highgui.hpp>	//OpenCV must be 3.2 or later


/* Namespace */
using namespace std;


/* Def */
#define PMAX 255
#define PMIN 0


/* Data Type Definition (追々入力ファイルにしたがって型を自動決定できるようにしたい) */
using	Type = ushort;       /* uchar, ushort, float */
#define	DataDepth CV_16U  /* uchar:CV_8U, ushort:CV_16U, float:CV_32F */
#define	DataType(n) CV_MAKETYPE((DataDepth),(n))

/* Window names */
#define WINDOWNAME_IMAGE_WINDOW     "Viewer ([ESC] to exit)"
#define WINDOWNAME_OPERATIONPANEL   "Opration ([ESC] to exit)"
#define WIN_WIDTH 640

/* Arrow keys for cv::waitKeyEx() */
#define CV_WAITKEY_CURSORKEY_UP     2490368
#define CV_WAITKEY_CURSORKEY_DOWN   2621440
#define CV_WAITKEY_CURSORKEY_LEFT   2424832
#define CV_WAITKEY_CURSORKEY_RIGHT  2555904

/* Other prime keys for cv::waitKeyEx() */
#define CV_WAITKEY_ENTER    10
#define CV_WAITKEY_ESC      27
#define CV_WAITKEY_SPACE    32
#define CV_WAITKEY_TAB      9

//-------------------------------------------------------------------------------
//  Def funcs
//-------------------------------------------------------------------------------
#define CLIP3(min,max,a)	(((a)<(min))?(min):(((a)>(max))?(max):(a)))
#define ADJUST_BRIGHTNESS(i,m,s,e)	(uchar)CLIP3(0,255,255.0*(s)*powf((i),(e))/(m))


//-------------------------------------------------------------------------------
//  struct
//-------------------------------------------------------------------------------
struct Params
{
	int         x;
	int         y;
	int         event;
	int         flags;
	cv::Mat     img;
	cv::Point2i ul;
	cv::Point2i br;
};

#endif

/* EOF */

