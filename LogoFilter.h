/*
 *  LogoFilter.h
 *  unlogo
 *
 *  Created by Jeffrey Crouse on 8/18/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 */
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <highgui.h>
#include <cvaux.h>
#include "MatImage.h"
#include "ulUtils.h"


using namespace cv;
using namespace std;

typedef struct Logo {
	string search;
	string replace;
	Mat img;
	Mat replace_img;
	Scalar replace_color;
	vector<KeyPoint> keypoints;	
	Mat descriptors;
	vector<Point2f> points;
};

class LogoFilter {
public:
	LogoFilter();
	int init( string detector_type, string descriptor_extractor_type, string descriptor_matcher_type );
	int filter(Mat &in_image, Mat &out_img, bool draw_matches=false);
	int addLogo(string search, string replace);

protected:

	Ptr<FeatureDetector> detector;
	Ptr<DescriptorExtractor> descriptorExtractor;
	Ptr<DescriptorMatcher> descriptorMatcher;
	
	int ransacReprojThreshold;
	int ransacMethod;
	vector<Logo> logos;
	int framenum;
	
};