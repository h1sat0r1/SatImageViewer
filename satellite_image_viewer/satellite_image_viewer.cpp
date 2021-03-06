/*=================================================================================================

    stereo_test.cpp

    Created on JUN/30/2017
    @author: h1sat0r1

=================================================================================================*/

/* include */
#include "satellite_image_viewer.h"

/*-----------------------------------------------------------------------------
	cv::Mat_<uchar>
	generateUCharImage(cv::Mat_<Type>& _m)
-----------------------------------------------------------------------------*/
cv::Mat_<uchar> generateUCharImage(cv::Mat_<Type>& _m)
{
	// Output
	cv::Mat_<uchar> m_(_m.size(), 0);

	// Row-Col
	int col = _m.cols;
	int row = _m.rows;

	// Ptr
	Type*	ps;
	uchar*	pd;

	// Mean
	cv::Scalar mean = cv::mean(_m);

	for (int j = 0; j < row; j++)
	{
		// Ptr
		ps = _m.ptr<Type>(j);
		pd = m_.ptr<uchar>(j);

		for (int i = 0; i < col; i++)
		{
			pd[i] = ADJUST_BRIGHTNESS(ps[i], mean[0], 0.25, 1.0);
		}
	}

	return m_;
}

/*-----------------------------------------------------------------------------
	stretch(cv::Mat& _img, cv::Mat& _disp, double _m, double _s, double _e)
-----------------------------------------------------------------------------*/
void stretch(cv::Mat& _img, cv::Mat& _disp, double _m, double _s, double _e)
{
	const int img_cols = _img.cols;
	const int img_rows = _img.rows;

	#ifdef _OPENMP
	#pragma omp parallel for
	#endif
	for (int j = 0; j < img_rows; j++)
	{
		Type*	ps = _img.ptr<Type>(j);
		uchar*	pd = _disp.ptr<uchar>(j);

		#ifdef _OPENMP
		#pragma omp parallel for
		#endif
		for (int i = 0; i < img_cols; i++)
		{
			pd[i] = ADJUST_BRIGHTNESS((double)ps[i], _m, _s, _e);
		}
		//i
	}
	//j
}



/*-----------------------------------------------------------------------------
    satellite_image_viewer(cv::Mat& _img, cv::Mat& _frame)
-----------------------------------------------------------------------------*/
int satellite_image_viewer(cv::Mat& _img)
{
    // Images
    cv::Mat	frame(300, 300, 0);
    cv::Mat	img_disp(_img.size(), CV_8U);
	
	// Image size
	const int	img_cols = _img.cols;
	const int	img_rows = _img.rows;

    // Valuables
	double		scale = 0.30;
	double		exponent = 1.0;
	cv::Scalar	mean, std;
	cv::Scalar	mean_disp, std_disp;
	double		min = -1.0, max = -1.0;
	bool		button_Apply = false;
	bool		button_ImageSave = false;

	// Static values
	cv::meanStdDev(_img, mean, std);
	cv::minMaxLoc(_img, &min, &max);
	mean_disp	= mean;
	std_disp	= std;

    // For CVUI
    cv::namedWindow(WINDOWNAME_IMAGE_WINDOW, cv::WINDOW_KEEPRATIO);
    cv::namedWindow(WINDOWNAME_OPERATIONPANEL);
    cvui::init(WINDOWNAME_IMAGE_WINDOW);
    cvui::init(WINDOWNAME_OPERATIONPANEL);

    // Window size
    float ratio = (float)_img.rows / (float)_img.cols;
    int win_width = WIN_WIDTH;
    
    // Roop count
    unsigned int count = 0;

    // Flag for the roop
    bool flag = true;

	// For image save
	time_t t;
	tm* lt;
	stringstream s;

	// Initialize Apply
	stretch(_img, img_disp, mean[0], scale, exponent);

	// Initialize Show 
	cv::imshow(WINDOWNAME_IMAGE_WINDOW, img_disp);
	cv::imshow(WINDOWNAME_OPERATIONPANEL, frame);
	cv::resizeWindow(WINDOWNAME_IMAGE_WINDOW, win_width, (int)(win_width*ratio));

    // Roop
    while (flag)
    {
        // Initialize frame
        frame = cv::Scalar(30, 30, 0);
        
        // Clip
        scale = CLIP3(-1000.0, 1000.0, scale);
		exponent = CLIP3(-1000.0, 1000.0, exponent);

        // Show texts
		cvui::text(frame,  20,  29, "SCALE");
		cvui::text(frame,  20,  89, "EXPONENT");
		cvui::text(frame, 150,  30, "Min: " + to_string((uchar)min));
		cvui::text(frame, 150,  60, "Max: " + to_string((uchar)max));
		cvui::text(frame, 150,  90, "Mean: " + to_string(mean_disp[0]));
		cvui::text(frame, 150, 120, "StdDev: " + to_string(std_disp[0]));

		// Show counters at position
		cvui::counter(frame, 20, 40, &scale, 0.05);
		cvui::counter(frame, 20, 100, &exponent, 0.01);

		// Button
		button_Apply = cvui::button(frame, 5, 150, 290, 100, "Apply");
		button_ImageSave = cvui::button(frame, 5, 255, 290, 40, "Save Image");
		// Update cvui internal stuff
		cvui::update();

        if (button_Apply)
        {
			// Apply
			stretch(_img, img_disp, mean(0), scale, exponent);

			// Show 
			cv::imshow(WINDOWNAME_IMAGE_WINDOW, img_disp);
			cv::resizeWindow(WINDOWNAME_IMAGE_WINDOW, win_width, (int)(win_width*ratio));

			// Update
			button_Apply = false;
			cv::meanStdDev(img_disp, mean_disp, std_disp);
			cv::minMaxLoc(img_disp, &min, &max);
		}
		else if (button_ImageSave)
		{
			// Initialize
			s.str("");
			s.clear(stringstream::goodbit);

			// Get the time
			t = time(nullptr);

			// Convert
			lt = localtime(&t);

			// String
			s << 1900 + lt->tm_year << "-";
			s << lt->tm_mon + 1 << "-";
			s << lt->tm_mday << "_";
			s << lt->tm_hour << "-";
			s << lt->tm_min << "-";
			s << lt->tm_sec;
			s << ".png";

			cv::imwrite(s.str(), img_disp);
			cout << "Saved: " + s.str() << endl;
		}
		else
		{
			// Decide the value with cursor keys
			//   [Top] or [Bottom] : adjust the "win_width"
			//   [Space] : move windows at default position
			//   [Esc] : exit
			switch (cv::waitKeyEx(1))
			{
			case CV_WAITKEY_CURSORKEY_LEFT:
				break;

			case CV_WAITKEY_CURSORKEY_RIGHT:
				break;

			case CV_WAITKEY_CURSORKEY_UP:
				win_width += 40;
				cv::imshow(WINDOWNAME_IMAGE_WINDOW, img_disp);
				cv::resizeWindow(WINDOWNAME_IMAGE_WINDOW, win_width, (int)(win_width*ratio));
				break;

			case CV_WAITKEY_CURSORKEY_DOWN:
				win_width -= 40;
				cv::imshow(WINDOWNAME_IMAGE_WINDOW, img_disp);
				cv::resizeWindow(WINDOWNAME_IMAGE_WINDOW, win_width, (int)(win_width*ratio));

				break;

			case CV_WAITKEY_SPACE:
				cv::moveWindow(WINDOWNAME_IMAGE_WINDOW, 120, 0);
				cv::moveWindow(WINDOWNAME_OPERATIONPANEL, 120, 0);
				break;

			case CV_WAITKEY_TAB:
				scale = 0.30;
				exponent = 1.0;
				break;

			case CV_WAITKEY_ESC:
				flag = false;
				break;

			case 's':
				// Initialize
				s.str("");
				s.clear(stringstream::goodbit);

				// Get the time
				t = time(nullptr);

				// Convert
				lt = localtime(&t);

				// String
				s << 1900 + lt->tm_year << "-";
				s << lt->tm_mon + 1 << "-";
				s << lt->tm_mday << "_";
				s << lt->tm_hour << "-";
				s << lt->tm_min << "-";
				s << lt->tm_sec;
				s << ".png";

				cv::imwrite(s.str(), img_disp);
				cout << "Saved: " + s.str() << endl;
				break;

			default:
				break;
			}
		}

        // Show them on the screen
        cv::imshow(WINDOWNAME_OPERATIONPANEL, frame);

		// Roop counter
		count++;

	}
	//while�����

    return 0;
}


/* EOF */