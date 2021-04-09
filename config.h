#pragma once
#include "opencv2/opencv.hpp"
struct STrackConfig
{
	float tlwh[4];
	float score;
	cv::Mat temp_feat;
	int buffer_size;
};

// Table for the 0.95 quantile of the chi - square distribution with N degrees of
// freedom(contains values for N = 1, ..., 9).Taken from MATLAB / Octave's chi2inv
// function and used as Mahalanobis gating threshold.

const std::map<int, float>chi2inv95 = {
	{1, 3.8415},
    {2 , 5.9915},
	{3 , 7.8147},
	{4 , 9.4877},
	{5 , 11.070},
	{6 , 12.592},
	{7 , 14.067},
	{8 , 15.507},
	{9 , 16.919} };

typedef struct DetectionBox
{
	int frame;
	cv::Rect_<float> box;
	float score;
	cv::Mat mask;
	std::vector<int> points;
	DetectionBox()
	{
		frame = -1; score = 0; box = cv::Rect_<float>(cv::Point_<float>(-1, -1), cv::Point_<float>(-1, -1));
	}
	DetectionBox(int frame_, const cv::Rect_<float>& box_, float score_)
	{
		frame = frame_; box = box_; score = score_;
	}
}DetectionBox;

struct FileDetectorConfig
{
	std::string det_list_name;
	float threshold;
	int start_x;
	int start_y;
	int min_size;
	int max_size;
};
enum struct DetectorMethod :unsigned char {
	FromFile
};
struct DetectorConfig
{
	DetectorMethod method;
	FileDetectorConfig fd;
};

struct JDETrackerConfig
{
	DetectorConfig det_config;
	float conf_thres;
	int K;
	int track_buffer;
};

const int kColorNum = 40;
const int kColorArray[kColorNum * 4] =
{ 246, 156, 192, 7,
165, 166, 2, 179,
25, 147, 24, 67,
31, 132, 123, 250,
111, 208, 249, 149,
234, 37, 55, 147,
143, 29, 214, 169,
215, 84, 190, 204,
110, 239, 216, 103,
221, 142, 83, 166,
251, 222, 243, 67,
115, 91, 244, 128,
151, 254, 47, 13,
132, 253, 137, 127,
236, 246, 66, 169,
131, 63, 5, 237,
28, 12, 58, 99,
6, 49, 196, 195,
163, 9, 82, 197,
157, 103, 213, 44,
227, 86, 106, 79,
30, 72, 46, 152,
204, 9, 223, 80,
25, 202, 70, 6,
141, 195, 106, 193,
166, 178, 228, 113,
105, 208, 175, 243,
193, 105, 28, 96,
251, 108, 207, 168,
110, 165, 55, 38, 
58, 190, 234, 236,
48, 225, 141, 239,
251, 163, 161, 73,
140, 59, 204, 205,
118, 19, 202, 34,
81, 104, 215, 42,
109, 175, 221, 223,
64, 0, 104, 10,
156, 242, 254, 136,
245, 33, 67, 208
};
