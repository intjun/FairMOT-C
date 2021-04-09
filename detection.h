#pragma once
#include "opencv2/opencv.hpp"

#include "config.h"
//template <typename T>
class Detection //should use boost::noncopyable //interface 
{
public:
	virtual ~Detection() {};

	virtual bool init() = 0;
	virtual void get_detection(cv::Mat& frame, std::vector<DetectionBox>& vec_db, std::vector<cv::Mat>& vec_features) = 0;
};

class FileDetector :public Detection
{
public:
	FileDetector() = delete;
	explicit FileDetector(FileDetectorConfig& config);
	virtual ~FileDetector();
	FileDetector(const FileDetector&) = delete;
	FileDetector& operator=(const FileDetector&) = delete;

	bool init();
	void get_detection(cv::Mat& frame, std::vector<DetectionBox>& vec_db, std::vector<cv::Mat>& vec_features);
private:
	bool read_from_list();
private:
	FileDetectorConfig& params_;
	int frame_idx_;
	std::vector<std::string> vec_det_filename_;
	std::vector<std::vector<DetectionBox>> vec_vec_det_;
};


//    -m 
//template <typename T>
class DetectorFactory
{
public:
	// 	FaceDetectionFactory();
	// 	virtual ~FaceDetectionFactory();
	static Detection* create_object(DetectorConfig& config)
	{
		switch (config.method)
		{
		case DetectorMethod::FromFile:
			return new FileDetector(config.fd);

		}
	}
};

