#pragma once
#include <vector>;
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Body.h"
using namespace std;
using namespace cv;

class Drawer {
public:
	Drawer(Mat& image, vector<Body*>& body_arr);
	void start(vector<thread>& threads, atomic<int>& status);
private:
	long long int frame;
	long long int n;
	long long int width;
	long long int height;
	vector<double> offset;
	vector<vector<double>> n_axis;
	vector<Body*> body_arr;
	Mat image;

	void update_image(vector<Body*>& body_arr, atomic<int>& status);

	void wait_key_action(atomic<int>& status);

	void refresh_image();

};

