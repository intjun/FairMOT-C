// FairMOT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "tracker.h"
void draw_tracks(cv::Mat&img, std::vector<std::shared_ptr<STrack>>& tracks)
{
	for (auto& tr:tracks)
	{
		cv::Rect_<float> loc = tr->to_tlwh_rect();
		int color_idx = (tr->track_id) % kColorNum * 4;
		cv::Scalar_<int> color = cv::Scalar_<int>(kColorArray[color_idx], kColorArray[color_idx + 1], kColorArray[color_idx + 2], kColorArray[color_idx + 3]);
		cv::rectangle(img, loc, color, 3, cv::LINE_AA, 0);

		int fontCalibration = cv::FONT_HERSHEY_COMPLEX;
		float fontScale = 1; 
		int fontThickness = 2;
		char text[15];
		sprintf(text, "%d", tr->track_id);
		std::string buff = text;
		putText(img, buff, cv::Point(loc.x, loc.y), fontCalibration, fontScale, color, fontThickness);/**/

	}
}
int main()
{
	DetectorConfig detconfig;
	detconfig.method = DetectorMethod::FromFile;
	detconfig.fd.det_list_name = "list.txt";

	auto det = std::unique_ptr<Detection>(DetectorFactory::create_object(detconfig));
	det->init();

	JDETrackerConfig config;
	config.conf_thres = 0.4f;
	config.K = 500;
	config.track_buffer = 30;
	int frame_rate = 20;
	JDETracker jde(config, frame_rate);
	cv::VideoCapture capture;
	capture.open("test.avi");
	cv::Mat frame;
	std::vector<DetectionBox> vec_db;
	std::vector<cv::Mat> vec_features;
	int frame_index = 0;
	while (true)
	{
		capture >> frame;
		if (frame.empty()) break;
		det->get_detection(frame, vec_db, vec_features);
		std::vector<std::shared_ptr<STrack>> tracks = jde.update(vec_db, vec_features);
		int a = 10;
		draw_tracks(frame, tracks);
// 		char tmp[100] = { '\0'};
// 		sprintf(tmp, "tmp/%03d.jpg", frame_index);
// 		std::string save_name = tmp;
// 		cv::imwrite(save_name, frame);
		cv::imshow("tracking", frame);
		cv::waitKey(1);
		frame_index++;
	}
}
