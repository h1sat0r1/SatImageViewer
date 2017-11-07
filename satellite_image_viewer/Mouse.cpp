/*=================================================================================================
    
    Mouse.cpp

    Created on 17th/Oct/2017
    @author: Toriya

    参考:
    https://docs.opencv.org/3.2.0/d7/dfc/group__highgui.html

    マウスイベントの種類は以下．
    EVENT_MOUSEMOVE     indicates that the mouse pointer has moved over the window.
    EVENT_LBUTTONDOWN   indicates that the left mouse button is pressed.
    EVENT_RBUTTONDOWN   indicates that the right mouse button is pressed.
    EVENT_MBUTTONDOWN   indicates that the middle mouse button is pressed.
    EVENT_LBUTTONUP     indicates that left mouse button is released.
    EVENT_RBUTTONUP     indicates that right mouse button is released.
    EVENT_MBUTTONUP     indicates that middle mouse button is released.
    EVENT_LBUTTONDBLCLK indicates that left mouse button is double clicked.
    EVENT_RBUTTONDBLCLK indicates that right mouse button is double clicked.
    EVENT_MBUTTONDBLCLK indicates that middle mouse button is double clicked.
    EVENT_MOUSEWHEEL    positive and negative values mean forward and backward scrolling, respectively.
    EVENT_MOUSEHWHEEL   positive and negative values mean right and left scrolling, respectively.

    フラグの種類は以下．マウスイベントが発生したときの『状態』を表す．
    EVENT_FLAG_LBUTTON  indicates that the left mouse button is down.
    EVENT_FLAG_RBUTTON  indicates that the right mouse button is down.
    EVENT_FLAG_MBUTTON  indicates that the middle mouse button is down.
    EVENT_FLAG_CTRLKEY  indicates that CTRL Key is pressed.
    EVENT_FLAG_SHIFTKEY indicates that SHIFT Key is pressed.
    EVENT_FLAG_ALTKEY   indicates that ALT Key is pressed.

=================================================================================================*/

#include "Mouse.h"

#define WINNAME_CLIPPING "Clipping"

cv::Point2i point_ul, point_br;

/*-----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/
void mouseCallBack(int _eventTp, int _x, int _y, int _flags, void* _userdata)
{

    Params *ptr = static_cast<Params*> (_userdata);

    ptr->x = _x;
    ptr->y = _y;
    ptr->event = _eventTp;
    ptr->flags = _flags;
    
    cv::Mat     tmp = ptr->img.clone();

    double aspect = static_cast<float>(tmp.rows) / static_cast<float>(tmp.cols);

    switch (ptr->event)
    {
    case cv::EVENT_LBUTTONDOWN:
        // Update the point_ul
        point_ul.x = ptr->x;
        point_ul.y = ptr->y;

#ifdef _DEBUG_
        cout << "ul :" << point_ul;
        cout << "\t\tbr :" << point_br << "\t\t*" << endl;
#endif
        break;

    case cv::EVENT_LBUTTONUP:
        // Update the point_br
        point_br.x = ptr->x;
        point_br.y = ptr->y;

#ifdef _DEBUG_
        cout << "ul: " << point_ul;
        cout << "\t\tbr: " << point_br << "\t\t*"<< endl;
#endif
        // End
        ptr->flags = 9999;
        ptr->ul = point_ul;
        ptr->br = point_br;
        break;

    default:
        break;
    }

    if (ptr->flags == cv::EVENT_FLAG_LBUTTON)
    {
        // Update the point_br
        point_br.x = ptr->x;
        point_br.y = ptr->y;
        
        if (point_ul.x < point_br.x &&
            point_ul.y < point_br.y
           )
        {

#ifdef _DEBUG_
            cout << "ul: " << point_ul;
            cout << "\t\tbr: " << point_br << endl;
#endif
            cv::rectangle(tmp, point_ul, point_br, cv::Scalar(255, 255, 255), 10, 4, 0);
        }
    }

    cv::imshow(WINNAME_CLIPPING, tmp);
    cv::resizeWindow(WINDOWNAME_IMAGE_WINDOW, WIN_WIDTH, (int)(WIN_WIDTH * aspect));

}


/*-----------------------------------------------------------------------------
  vector<cv::Point2i> clipImage(Params* _p)
    [Out] out.at(0): Position of Up-Left
          out.at(1): Position of Bottom-Right 
-----------------------------------------------------------------------------*/
vector<cv::Point2i> clipImage(Params* _p)
{
    // Valuables
    vector<cv::Point2i> vec_;
    //cv::Point2i posUL, posBR;

    // Flag to exit ("true" to exit)
    bool flag_exit = false;

    // Win name
    cv::namedWindow(WINNAME_CLIPPING, CV_WINDOW_FREERATIO);

    // Roop
    while (!flag_exit)
    {

        cv::setMouseCallback(WINNAME_CLIPPING, mouseCallBack, _p);

        cv::waitKey(1);

        // [Enter] to next
        if (_p->flags == 9999    &&
            _p->ul.x < _p->br.x  &&
            _p->ul.y < _p->br.y    )
        {
            cv::destroyAllWindows();
            break;
        }

    }// while

    vec_.push_back(_p->ul);
    vec_.push_back(_p->br);

#ifdef _DEBUG_
    cout << "UL: " << vec_.at(0);
    cout << "\t\tBR: " << vec_.at(1) << endl;
#endif


    return vec_;
}