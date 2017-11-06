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
using	Type = uchar;       /* uchar, ushort, float */
#define	DataDepth CV_8U  /* uchar:CV_8U, ushort:CV_16U, float:CV_32F */
#define	DataType(n) CV_MAKETYPE((DataDepth),(n))


#endif

