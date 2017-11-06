/*=================================================================================================

	satellite_image_reader.cpp

	Created on 21st/Sep./2017
	@author: h1sat0r1

=================================================================================================*/

/* include */
#include "satellite_image_reader.h"


/*-----------------------------------------------------------------------------
cv::Mat_<Type>
satellite_image_reader(char* _fname, int _c)
-----------------------------------------------------------------------------*/
void dispInfo(GDALDataset* _g)
{
	/* Display information about the raster file */
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  Information of the geospatial raster image                               \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	printf(
		"Driver     : %s/%s\n",
		_g->GetDriver()->GetDescription(),
		_g->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME));

	printf(
		"Size       : x%d * y%d * c%d\n",
		_g->GetRasterXSize(),
		_g->GetRasterYSize(),
		_g->GetRasterCount());

	printf(
		"Datatype   : %s\n",
		GDALGetDataTypeName(_g->GetRasterBand(1)->GetRasterDataType()));


	if (_g->GetProjectionRef() != NULL)
	{
		std::cout
			<< "Projection : "
			<< _g->GetProjectionRef()
			<< std::endl;// << std::endl;
	}

	double adfGeoTransform[6];
	if (_g->GetGeoTransform(adfGeoTransform) == CE_None)
	{
		printf(
			"Origin     = (%20.20f, %20.20f)\n",
			adfGeoTransform[0],
			adfGeoTransform[3]);

		printf(
			"Pixel Size = (%20.20f, %20.20f)\n",
			adfGeoTransform[1],
			adfGeoTransform[5]);
	}

	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");


	return;
}

/*-----------------------------------------------------------------------------
cv::Mat_<Type>
satellite_image_reader(char* _fname, int _c)
-----------------------------------------------------------------------------*/
cv::Mat_<Type>  satellite_image_reader(char* _fname, int _c)
{
    GDALAllRegister();

    // Open
    GDALDataset* g = (GDALDataset*)GDALOpen(_fname, GA_ReadOnly);

    // Exception
    if (g == NULL)
    {
        printf("[ERROR] Cannot read %s.\n", _fname);
        exit(-1);
    }

	// File name
	cout << _fname << endl;

	// Display georaster info
	dispInfo(g);

    // Size
    const int x = g->GetRasterXSize();
    const int y = g->GetRasterYSize();
    const int c = g->GetRasterCount();

    // Mat
    cv::Mat_<Type> m_ = cv::Mat_<Type>(y, x);

    // To RasterIO
    GDALRasterBand* poBand;
    Type* pafScan;
    int   nSize = x*y;

    // Malloc 
    poBand = g->GetRasterBand(_c);
    pafScan = (Type *)CPLMalloc(sizeof(Type)*nSize);

    // Reading
    poBand->RasterIO(
        GF_Read,
        0, 0,
        x, y,
        pafScan,
        x, y,
        poBand->GetRasterDataType(),
        0, 0);

    // Write to mat using pointer
    for (int j = 0; j < y; j++)
    {
        Type* p = m_.ptr<Type>(j);
        for (int i = 0; i < x; i++)
        {
            p[i] = pafScan[i + j*x];
        }
        //i
    }
    //j

    return m_;
}


/*-----------------------------------------------------------------------------
cv::Mat_<Type>
satellite_image_reader(char* _fname, int _c, int _x1, int _y1, int _x2, int _y2)
 
AOI version
-----------------------------------------------------------------------------*/
cv::Mat_<Type>  satellite_image_reader(char* _fname, int _c, int _x1, int _y1, int _x2, int _y2)
{
    GDALAllRegister();

    // Open
    GDALDataset* g = (GDALDataset*)GDALOpen(_fname, GA_ReadOnly);

    // Exception
    if (g == NULL)
    {
        printf("[ERROR] Cannot read %s.\n", _fname);
        exit(-1);
    }

	// File name
	cout << _fname << endl;

	// Display georaster info
	dispInfo(g);


    // Size
    const int org_x = g->GetRasterXSize();
    const int org_y = g->GetRasterYSize();
	const int x = _x2 - _x1;
	const int y = _y2 - _y1;
	const int c = g->GetRasterCount();

    // Mat
    cv::Mat_<Type> m_ = cv::Mat_<Type>(y, x);

    // To RasterIO
    GDALRasterBand* poBand;
    Type* pafScan;
    int   nSize = x*y;

    // Malloc 
    poBand = g->GetRasterBand(_c);
    pafScan = (Type *)CPLMalloc(sizeof(Type)*nSize);

    // Reading
    poBand->RasterIO( //•sˆÀ
        GF_Read,
        _x1, _y1,
        x, y,
        pafScan,
        x, y,
        poBand->GetRasterDataType(),
        0, 0);

    // Write to mat using pointer
    for (int j = 0; j < y; j++)
    {
        Type* p = m_.ptr<Type>(j);
        for (int i = 0; i < x; i++)
        {
            p[i] = pafScan[i + j*x];
        }
        //i
    }
    //j

    return m_;
}

//EOF