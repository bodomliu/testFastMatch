//
//  main.cpp
//  FAsT-Match
//
//  Created by Saburo Okita on 22/05/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#include "FAsTMatch.h"
#include "MatchConfig.h"

using namespace std;
//using namespace cv;

int main(int argc, const char * argv[])
{

 	cv::Mat image = cv::imread( "C:/Users/boss/Desktop/testFastMatch/image.png" );
	cv::Mat templ = cv::imread( "C:/Users/boss/Desktop/testFastMatch/template.png" );
    
    fast_match::FAsTMatch fast_match;
    fast_match.init( 0.15f, 0.85f, false, 0.5f, 2.0f );
    vector<cv::Point2f> corners = fast_match.apply( image, templ );

    
	cv::namedWindow("");
	cv::moveWindow("", 0, 0);
    
    line( image, corners[0], corners[1], cv::Scalar(0, 0, 255), 2);
    line( image, corners[1], corners[2], cv::Scalar(0, 0, 255), 2);
    line( image, corners[2], corners[3], cv::Scalar(0, 0, 255), 2);
    line( image, corners[3], corners[0], cv::Scalar(0, 0, 255), 2);
    
	cv::Mat appended( image.rows, 2 * image.cols, CV_8UC3, cv::Scalar(0, 0, 0) );
    
	//cv::QtFont font = cv::fontQt("Calibri");
	//cv::addText( appended, "Template: ", cv::Point( 50, 50 ),font );
	//cv::putText(appended, "Template: ", cv::Point(50, 50), cv::HersheyFonts::FONT_HERSHEY_SIMPLEX, 14.0, cv::Scalar(0, 0, 255));
	templ.copyTo(cv::Mat(appended, cv::Rect((image.cols - templ.cols) / 2, (image.rows - templ.cols) / 2, templ.cols, templ.rows)) );
    image.copyTo(cv::Mat(appended, cv::Rect( image.cols, 0, image.cols, image.rows)) );
    
    imshow("", appended );
	cv::waitKey(0);
    
    return 0;
}

