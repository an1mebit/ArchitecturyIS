#include "camera.h"

Camera::Camera() : camera(cv::VideoCapture(0))
{}

cv::Mat Camera::getCoordinate()
{
	cv::Mat frame;
	camera >> frame;
	
	return frame;
}