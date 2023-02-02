#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <random>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "Body.h"
#include "NBodySimulator.h"
#include "Drawer.h"

using namespace std;
using namespace cv;


int WinMain() {
	vector<int> image_size = { 728, 1024 };
	Mat image = Mat::zeros(image_size[0], image_size[1], CV_8UC3);
	long long int frame_num = 3200;

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> axis(-128, 128);
	uniform_real_distribution<> v(-32, 32);
	uniform_real_distribution<> color(0, 255);
	poisson_distribution<> mass(4);
	uniform_int_distribution<> nums(32, 32);

	vector<Body*> body_arr = {};
	for (int i = 0; i < nums(gen) + 1; i++) {
		double m = mass(gen);
		double posx = axis(gen);
		double posy = axis(gen);
		double d = pow(pow(posx, 2) + pow(posy, 2), 1 / 2);
		double vx = -posy / pow(2, m) / d;
		double vy = posx / pow(2, m) / d;
		body_arr.push_back(new Body({ posx, posy }, { vx,vy }, pow(2, m), { color(gen), color(gen), color(gen) }, image_size));
	}
	body_arr.push_back(new Body({ 0,0 }, { 0,0 }, pow(2, 12), { 0, 255, 255 }, image_size));

	vector<thread> threads = {};
	atomic<int> status{ 1 };
	atomic<int> counter{ 0 };
	mutex mtx;
	condition_variable cv;


	NBodySimulator* nbody = new NBodySimulator(image, frame_num);
	nbody->simulate(body_arr, threads, status, counter, mtx, cv);

	Drawer* drawer = new Drawer(image, body_arr);
	drawer->start(threads, status);

}