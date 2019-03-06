//
//  FAsTMatch.h
//  FAsT-Match
//
//  Created by Saburo Okita on 23/05/14.
//  Copyright (c) 2014 Saburo Okita. All rights reserved.
//

#ifndef __FAsT_Match__FAsTMatch__
#define __FAsT_Match__FAsTMatch__

#include <iostream>
#include <opencv2/opencv.hpp>
//edit by bodom
#include <iterator>

#include "MatchNet.h"
#include "MatchConfig.h"

using namespace std;
//using namespace cv;

namespace fast_match {
    class FAsTMatch{
    public:
        FAsTMatch();
        
        void init( float epsilon = 0.15f, float delta = 0.25f, bool photometric_invariance = false,
                   float min_scale = 0.5f, float max_scale = 2.0f );
        
        vector<cv::Point2f> apply(cv::Mat& image, cv::Mat& templ);
        
    protected:
		cv::Mat image, templ;
        
		cv::RNG rng;
        float epsilon;
        float delta;
        bool photometricInvariance;
        float minScale;
        float maxScale;
		cv::Size halfTempl;
		cv::Size halfImage;

        
        
        vector<MatchConfig> createListOfConfigs( MatchNet& net, cv::Size templ_size, cv::Size image_size );
        vector<cv::Mat> configsToAffine( vector<MatchConfig>& configs, vector<bool>& insiders );
        
        vector<MatchConfig> getGoodConfigsByDistance( vector<MatchConfig>& configs, float best_dist, float new_delta,
                                                      vector<double>& distances, float& thresh, bool& too_high_percentage );
        
        vector<MatchConfig> randomExpandConfigs( vector<MatchConfig>& configs, MatchNet& net,
                                                 int level, int no_of_points, float delta_factor );
        
        float getThresholdPerDelta( float delta );
        
        vector<double> evaluateConfigs(cv::Mat& image, cv::Mat& templ, vector<cv::Mat>& affine_matrices,
			cv::Mat& xs, cv::Mat& ys, bool photometric_invariance );
        
        
		cv::Mat preprocessImage(cv::Mat& image);
		cv::Mat makeOdd(cv::Mat& image);
        vector<cv::Point2f> calcCorners(cv::Size image_size, cv::Size templ_size, cv::Mat& affine );
        
    };
}

template<typename type>
ostream &operator <<( ostream& os, const std::pair<type, type> & vec ) {
    os << "[";
    os << vec.first << " " << vec.second;
    os << "]";
    return os;
}

template<typename type>
ostream &operator <<( ostream& os, const vector<type> & vec ) {
    os << "[";
    std::copy( vec.begin(), vec.end(), ostream_iterator<type>(os, ", ") );
    os << "]";
    return os;
}

#endif /* defined(__FAsT_Match__FAsTMatch__) */
