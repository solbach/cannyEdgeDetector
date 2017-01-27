#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges, color_dst;

int lowThreshold = 35;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

/**
 * @function detectorCallback
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void detectorCallback(int, void*)
{
    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );

    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

    /// Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);

    src.copyTo( dst, detected_edges);

    /// Hough
    cvtColor( detected_edges, color_dst, CV_GRAY2BGR );

    std::vector<Vec4i> lines;
    HoughLinesP( detected_edges, lines, 1, CV_PI/180, 80, 30, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        line( color_dst, Point(lines[i][0], lines[i][1]),
              Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
    }

    imshow( window_name, color_dst );
}


/** @function main */
int main( int argc, char** argv )
{
    std::cout << argc << " arguments provided" << std::endl;
    std::cout << "Canny Edge Detector\n" << std::endl;
    /// Check input
    if(argc < 2){
        std::cout << "No Input defined!" << std::endl;
        return -1;
    }

    /// Load an image
    src = imread( argv[1] );

    if( !src.data )
    {
        std::cout << "Input wrong!" << std::endl;
        return -1;
    }

    /// Create a matrix of the same type and size as src (for dst)
    dst.create( src.size(), src.type() );

    /// Convert the image to grayscale
    cvtColor( src, src_gray, CV_BGR2GRAY );

    /// Create a window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Create a Trackbar for user to enter threshold
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, detectorCallback );

    /// Show the image
    detectorCallback(0, 0);

    /// Wait until user exit program by pressing a key
    waitKey(0);

    return 0;
}