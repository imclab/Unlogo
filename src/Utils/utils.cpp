/*
 *  utils.cpp
 *  structure
 *
 *  Created by Jeffrey Crouse on 2/7/11.
 *  Copyright 2011 Eyebeam. All rights reserved.
 *
 */

#include "utils.h"


//Takes a descriptor and turns it into an xy point
void keypoints2points(const vector<KeyPoint>& in, vector<Point2f>& out)
{
	out.clear();
	out.reserve(in.size());
	for (size_t i = 0; i < in.size(); ++i)
	{
		out.push_back(in[i].pt);
	}
}

//Takes an xy point and appends that to a keypoint structure
void points2keypoints(const vector<Point2f>& in, vector<KeyPoint>& out)
{
	out.clear();
	out.reserve(in.size());
	for (size_t i = 0; i < in.size(); ++i)
	{
		out.push_back(KeyPoint(in[i], 1));
	}
}


void crossCheckMatching( cv::Ptr<DescriptorMatcher>& descriptorMatcher,
						const Mat& descriptors1, const Mat& descriptors2,
						vector<DMatch>& filteredMatches12, int knn )
{
	filteredMatches12.clear();
	vector<vector<DMatch> > matches12, matches21;
	descriptorMatcher->knnMatch( descriptors1, descriptors2, matches12, knn );
	descriptorMatcher->knnMatch( descriptors2, descriptors1, matches21, knn );
	for( size_t m = 0; m < matches12.size(); m++ )
	{
		bool findCrossCheck = false;
		for( size_t fk = 0; fk < matches12[m].size(); fk++ )
		{
			DMatch forward = matches12[m][fk];
			
			for( size_t bk = 0; bk < matches21[forward.trainIdx].size(); bk++ )
			{
				DMatch backward = matches21[forward.trainIdx][bk];
				if( backward.trainIdx == forward.queryIdx )
				{
					filteredMatches12.push_back(forward);
					findCrossCheck = true;
					break;
				}
			}
			if( findCrossCheck ) break;
		}
	}
}


//--------------------------------------------------------------
vector<Point> warpCorners( double* h, vector<Point> src )
{
	vector<Point> dst(4);
	// from find_object.cpp  There is probably a "better" way to do this.
	for(int i = 0; i < 4; i++ )
	{
		double x = src[i].x, y = src[i].y;
		double Z = 1./(h[6]*x + h[7]*y + h[8]);
		double X = (h[0]*x + h[1]*y + h[2])*Z;
		double Y = (h[3]*x + h[4]*y + h[5])*Z;
		dst[i] = Point(cvRound(X), cvRound(Y));
	}
	return dst;
}
