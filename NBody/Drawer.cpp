#include "Drawer.h"

Drawer::Drawer(Mat& image, vector<Body*>& body_arr) {
	this->image = image;
	this->body_arr = body_arr;
	this->n = body_arr.size();
	vector<vector<double>>n_axis(n, vector<double>(2, 0));
	this->n_axis = n_axis;
	this->offset = { 0,0 };
	Size s = image.size();
	this->height = s.height;
	this->width = s.width;
}

void Drawer::update_image(vector<Body*>& body_arr, atomic<int>& status) {
	for (int i = 0; i < n; i++) {
		n_axis[i][0] = body_arr[i]->axis[0] + offset[0];
		n_axis[i][1] = body_arr[i]->axis[1] + offset[1];
		circle(image, Point(n_axis[i][0], n_axis[i][1]), log(body_arr[i]->m), Scalar(body_arr[i]->color[0], body_arr[i]->color[1], body_arr[i]->color[2]), -1);
	}
	imshow("NBody, ¡ü¡ý¡û¡ú, H(to middle), T(track), Esc(quit)", image);
	if (status.load() == 1) {
		for (int i = 0; i < n; i++) {
			circle(image, Point(n_axis[i][0], n_axis[i][1]), log(body_arr[i]->m), Scalar(0, 0, 0), -1);
		}
	}
}

void Drawer::wait_key_action(atomic<int>& status) {
	int buttom = waitKeyEx(1);
	if (buttom == 27) {
		status.store(-1);
	}
	else if (buttom == 2490368) {
		offset[1] += 10;
	}
	else if (buttom == 2621440) {
		offset[1] -= 10;
	}
	else if (buttom == 2424832) {
		offset[0] += 10;
	}
	else if (buttom == 2555904) {
		offset[0] -= 10;
	}
	else if (buttom == 'H') {
		offset[0] = 0;
		offset[1] = 0;
	}
	else if (buttom == 'T') {
		if (status.load() == 1) {
			status.store(2);
		}
		else if (status.load() == 2) {
			status.store(1);
		}
	}
	if (buttom == 'T' || buttom == 2490368 || buttom == 2621440 || buttom == 2424832 || buttom == 2555904) {
		Drawer::refresh_image();
	}
}

void Drawer::refresh_image() {
	rectangle(image, Point(0, 0), Point(width, height), Scalar(0, 0, 0), -1);
}

void Drawer::start(vector<thread>& threads, atomic<int>& status) {
	while (status.load() > 0) {
		update_image(body_arr, status);
		wait_key_action(status);
	}
	for (auto& t : threads) {
		t.join();
	}
}
