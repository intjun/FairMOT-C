#include <fstream>
#include "utils.h"
#include "detection.h"

FileDetector::FileDetector(FileDetectorConfig& config)
	:params_(config)
	, frame_idx_(-1)
{
	clear_2d_vector(vec_vec_det_);
}

FileDetector::~FileDetector()
{
}

bool FileDetector::read_from_list()
{
	if (params_.det_list_name == "")
		return false;
	read_filelist(params_.det_list_name, vec_det_filename_);
	return true;
}


bool FileDetector::init()
{
	if (params_.det_list_name != "")
	{
		std::cout << "please check  file exists, only one should be non-empty..." << std::endl;
		return false;
	}
	if (params_.det_list_name != "")
		return read_from_list();
}

void FileDetector::get_detection(cv::Mat& frame, std::vector<DetectionBox>& vec_db, std::vector<cv::Mat>& vec_features)
{
	int im_w = frame.cols;
	int im_h = frame.rows;
	vec_db.clear();
	vec_features.clear();
	frame_idx_++;

	std::ifstream infile(vec_det_filename_[frame_idx_]+".size");
	if (infile.fail())
	{
		std::cout << "read file fails: " << vec_det_filename_[frame_idx_] << ", cannot read annotation file." << std::endl;
		return;
	}
	int det_cnt, det_dim, fea_cnt, fea_dim;
	infile >> det_cnt >> det_dim >> fea_cnt >> fea_dim;
	infile.close();
	std::vector<float> dets(det_cnt*det_dim);
	std::ifstream in_det(vec_det_filename_[frame_idx_] + ".det", ios::in | ios::binary);
	if (det_cnt>0)
		in_det.read((char *)&dets[0], sizeof(float)*dets.size());
	in_det.close();
	for (int i=0;i<det_cnt;i++)
	{
		float x1 = dets[i*det_dim]; if (x1 < 0)x1 = 0; if (x1 > (im_w - 1)) x1 = im_w - 1;
		float y1 = dets[i*det_dim + 1]; if (y1 < 0)y1 = 0; if (y1 > (im_h - 1)) y1 = im_h - 1;
		float x2 = dets[i*det_dim + 2]; if (x2 < 0)x2 = 0; if (x2 > (im_w - 1)) x2 = im_w - 1;
		float y2 = dets[i*det_dim + 3]; if (y2 < 0)y2 = 0; if (y2 > (im_h - 1)) y2 = im_h - 1;
		vec_db.push_back(DetectionBox(frame_idx_,
			cv::Rect_<float>(cv::Point_<float>(x1, y1),
				cv::Point_<float>(x2, y2)), dets[i*det_dim + 4]));
	}
	std::vector<float> features(fea_cnt*fea_dim);
	std::ifstream in_fea(vec_det_filename_[frame_idx_] + ".feature", ios::in | ios::binary);
	if (fea_cnt > 0)
		in_fea.read((char *)&features[0], sizeof(float)*features.size());
	in_fea.close();
	for (int i = 0; i < fea_cnt; i++)
	{
		cv::Mat im(1, fea_dim, CV_32FC1, &features[0] + i * fea_dim);
		float*data = (float*)im.data;
		vec_features.push_back(im.clone());
	}
}
