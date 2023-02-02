#include "Body.h"


Body::Body(vector<double> axis, vector<double> v, double m, vector<double> color, vector<int> image_size) {
	this->axis = { axis[0] + image_size[1] / 2, axis[1] + image_size[0] / 2 };
	this->v = v;
	this->m = m;
	this->color = color;
}