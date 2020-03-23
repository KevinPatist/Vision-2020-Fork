#include "StudentPreProcessing.h"
#include "ImageIO.h"
#include "ImageFactory.h"
#include "HereBeDragons.h"


IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	cv::Mat input_matrix;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(image, input_matrix); // ImageToMatrix
	//cv::GaussianBlur(input_matrix, input_matrix, cv::Size(3, 3), 1, 1, cv::BORDER_DEFAULT);
	//cv::medianBlur(*image, *image, 3);
	float middle = 2;
	float top = 1;
	cv::Mat kernel_x = (cv::Mat_<float>(9, 9) << top, top, top, 0, 0, 0, -top, -top, -top,
		top, top, top, 0, 0, 0, -top, -top, -top,
		top, top, top, 0, 0, 0, -top, -top, -top,
												 middle, middle, middle, 0, 0, 0, -middle, -middle, -middle,
		middle, middle, middle, 0, 0, 0, -middle, -middle, -middle,
		middle, middle, middle, 0, 0, 0, -middle, -middle, -middle,
												 top, top, top, 0, 0, 0, -top, -top, -top,
		top, top, top, 0, 0, 0, -top, -top, -top,
		top, top, top, 0, 0, 0, -top, -top, -top
);

	cv::Mat kernel_y = (cv::Mat_<float>(9, 9) << top, top, top, middle, middle, middle, top, top, top,
		top, top, top, middle, middle, middle, top, top, top,
		top, top, top, middle, middle, middle, top, top, top,
												  0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
												 -top, -top, -top, -middle, -middle, -middle, -top, -top, -top,
		- top, -top, -top, -middle, -middle, -middle, -top, -top, -top,
		- top, -top, -top, -middle, -middle, -middle, -top, -top, -top);

	cv::Mat kernel_x1 = (cv::Mat_<float>(9,9) << -top, -top, -top, 0, 0, 0, top, top, top,
		-top, -top, -top, 0, 0, 0, top, top, top,
		-top, -top, -top, 0, 0, 0, top, top, top,
												  -middle, -middle, -middle, 0, 0, 0, middle, middle, middle,
		-middle, -middle, -middle, 0, 0, 0, middle, middle, middle,
		-middle, -middle, -middle, 0, 0, 0, middle, middle, middle,
		-top, -top, -top, 0, 0, 0, top, top, top,
		- top, -top, -top, 0, 0, 0, top, top, top,
		-top, -top, -top, 0, 0, 0, top, top, top);

	cv::Mat kernel_y1 = (cv::Mat_<float>(9, 9) << top, top, top, 0, 0, 0, -top, -top, -top,
		top, top, top, 0, 0, 0, -top, -top, -top,
		top, top, top, 0, 0, 0, -top, -top, -top,
												  middle, middle, middle, 0, 0, 0, -middle, -middle, -middle,
		middle, middle, middle, 0, 0, 0, -middle, -middle, -middle,
		middle, middle, middle, 0, 0, 0, -middle, -middle, -middle,
												  top, top, top, 0, 0, 0, -top, -top, -top,
		top, top, top, 0, 0, 0, -top, -top, -top,
		top, top, top, 0, 0, 0, -top, -top, -top);
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

	//addWeighted(output_matrix_x, 0.7, output_matrix_x1, 0.7, 0, x); //0.7
	//addWeighted(output_matrix_y, 0.7, output_matrix_y1, 0.7, 0, y);
	addWeighted(output_matrix_x, 1.0, output_matrix_y, 1.0, 0, output_matrix);

	//cv::Sobel(input_matrix, output_matrix_x, CV_16S, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
	//cv::convertScaleAbs(output_matrix_x, output_matrix_x1);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	//cv::Sobel(input_matrix, output_matrix_y, CV_16S, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT);
	//cv::convertScaleAbs(output_matrix_y, output_matrix_y1);

	/// Total Gradient (approximate)
	//addWeighted(output_matrix_x1, 0.5, output_matrix_y1, 0.5, 0, output_matrix);

	IntensityImage* new_image_output = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(output_matrix, *new_image_output);  // MatrixToImage
	return new_image_output;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	cv::Mat OverHillOverDale;
	HereBeDragons::HerLoveForWhoseDearLoveIRiseAndFall(image, OverHillOverDale);
	cv::threshold(OverHillOverDale, OverHillOverDale, 254, 255, cv::THRESH_BINARY_INV);
	IntensityImage* ThoroughBushThoroughBrier = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(OverHillOverDale, *ThoroughBushThoroughBrier);
	return ThoroughBushThoroughBrier;
}