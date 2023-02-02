#pragma once

#include <vector>
using namespace std;

class Body {
public:
	vector<double> axis;
	vector<double> v;
	double m;
	vector<double> color;
	Body(vector<double> axis, vector<double> v, double m, vector<double> color, vector<int> image_size);
};
