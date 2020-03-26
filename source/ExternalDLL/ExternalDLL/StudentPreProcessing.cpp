#include "StudentPreProcessing.h"
#include "ImageIO.h"
#include "ImageFactory.h"
#include "HereBeDragons.h"


IntensityImage* StudentPreProcessing::stepToIntensityImage(const RGBImage& image) const {
	return nullptr;
}

IntensityImage* StudentPreProcessing::stepScaleImage(const IntensityImage& image) const {
	return nullptr;
}

IntensityImage* StudentPreProcessing::stepEdgeDetection(const IntensityImage& image) const {
	cv::Mat input_matrix;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(image, input_matrix); // ImageToMatrix
	//cv::GaussianBlur(input_matrix, input_matrix, cv::Size(3, 3), 1, 1, cv::BORDER_DEFAULT);
	cv::medianBlur(input_matrix, input_matrix, 3);
	float middle = 2;
	float top = 1;
	cv::Mat kernel_x = (cv::Mat_<float>(3, 3) << top, 0,-top,
		middle, 0, -middle,
		top, 0, -top
		);

	cv::Mat kernel_y = (cv::Mat_<float>(3, 3) << top, middle, top,
		0, 0, 0,
		-top, -middle, -top);

	cv::Mat kernel_x1 = (cv::Mat_<float>(3, 3) << -top, 0, top,
		-middle, 0, middle,
		-top, 0, top);

	cv::Mat kernel_y1 = (cv::Mat_<float>(3, 3) << top, 0, -top,
		middle, 0, -middle,
		top, 0, -top);
	cv::Mat output_matrix;
	cv::Mat x;
	cv::Mat y;
	cv::Mat output_matrix_x;
	cv::Mat output_matrix_y;
	cv::Mat output_matrix_x1;
	cv::Mat output_matrix_y1;
	filter2D(input_matrix, output_matrix_x, CV_8U, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	filter2D(input_matrix, output_matrix_y, CV_8U, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	filter2D(input_matrix, output_matrix_x1, CV_8U, kernel_x1, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	filter2D(input_matrix, output_matrix_y1, CV_8U, kernel_y1, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

	addWeighted(output_matrix_x, 0.7, output_matrix_x1, 0.7, 0, x); //0.7
	addWeighted(output_matrix_y, 0.7, output_matrix_y1, 0.7, 0, y);
	addWeighted(x, 1.0, y, 1.0, 0, output_matrix);


	IntensityImage* new_image_output = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(output_matrix, *new_image_output);  // MatrixToImage
	return new_image_output;
}

IntensityImage* StudentPreProcessing::stepThresholding(const IntensityImage& image) const {
	cv::Mat OverHillOverDale;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(image, OverHillOverDale);
	cv::threshold(OverHillOverDale, OverHillOverDale, 98, 255, cv::THRESH_BINARY_INV);
	IntensityImage* ThoroughBushThoroughBrier = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(OverHillOverDale, *ThoroughBushThoroughBrier);
	return ThoroughBushThoroughBrier;
}