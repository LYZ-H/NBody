#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <thread>
#include "Body.h"
using namespace std;
using namespace cv;

class NBodySimulator {
public:
	NBodySimulator(Mat& image, long long int frame_num);
	void simulate(vector<Body*>& body_arr, vector<thread>& threads, atomic<int>& status, atomic<int>& counter, mutex& mtx, condition_variable& cv);
private:
	Mat image;
	long long int frame_num;
	double G;

	void update_acc_each(vector<Body*>& body_arr, vector<double>& acc, int n, int i);

	void update_body_each(Body* body, vector<double>& acc);

	void update(vector<Body*>& body_arr, int n, int i, atomic<int>& status, atomic<int>& counter, mutex& mtx, condition_variable& cv);
};