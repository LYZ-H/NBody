#include "NBodySimulator.h"

NBodySimulator::NBodySimulator(Mat& image, long long int frame_num) {
	this->image = image;
	this->frame_num = frame_num;
	this->G = 1;
}

void NBodySimulator::update_acc_each(vector<Body*>& body_arr, vector<double>& acc, int n, int i) {
	for (int j = 0; j < n; j++) {
		if (i != j) {
			double d = max(sqrt(pow(body_arr[i]->axis[0] - body_arr[j]->axis[0], 2) + pow(body_arr[i]->axis[1] - body_arr[j]->axis[1], 2)), 1.0);
			acc[0] += G * body_arr[j]->m / pow(d, 3) * (body_arr[j]->axis[0] - body_arr[i]->axis[0]);
			acc[1] += G * body_arr[j]->m / pow(d, 3) * (body_arr[j]->axis[1] - body_arr[i]->axis[1]);
		}
	}
}

void NBodySimulator::update_body_each(Body* body, vector<double>& acc) {
	double dt = 1.0 / frame_num;
	body->v[0] += acc[0] * dt;
	body->v[1] += acc[1] * dt;
	body->axis[0] += body->v[0] * dt;
	body->axis[1] += body->v[1] * dt;
}

void NBodySimulator::update(vector<Body*>& body_arr, int n, int i, atomic<int>& status, atomic<int>& counter, mutex& mtx, condition_variable& cv) {
	vector<double> acc = { 0,0 };
	while (status.load() > 0) {
		acc[0] = 0;
		acc[1] = 0;
		update_acc_each(body_arr, acc, n, i);
		update_body_each(body_arr[i], acc);

		unique_lock<mutex> lck(mtx);
		if (counter.fetch_add(1, memory_order_relaxed) >= n - 1) {
			counter.store(0);
			cv.notify_all();
		}
		else if (status.load() > 0) {
			cv.wait_for(lck, 500ms);
		}
	}
}

void NBodySimulator::simulate(vector<Body*>& body_arr, vector<thread>& threads, atomic<int>& status, atomic<int>& counter, mutex& mtx, condition_variable& cv) {
	int n = body_arr.size();
	for (int i = 0; i < n; i++) {
		threads.push_back(thread(&NBodySimulator::update, this, ref(body_arr), n, i, ref(status), ref(counter), ref(mtx), ref(cv)));
	}
}