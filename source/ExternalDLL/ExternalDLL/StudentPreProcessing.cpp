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
	//cv::medianBlur(*image, *image, 3);
	//cv::GaussianBlur(*image, *image, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	cv::Mat kernel = (cv::Mat_<float>(9, 9) << 0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		1, 1, 1, -4, -4, -4, 1, 1, 1,
		1, 1, 1, -4, -4, -4, 1, 1, 1,
		1, 1, 1, -4, -4, -4, 1, 1, 1,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0);
	cv::Mat kernel_x = (cv::Mat_<float>(3, 3) << 1, 0, -1,
												 5, 0, -5,
												 1, 0, -1);
	cv::Mat kernel_y = (cv::Mat_<float>(3, 3) << 1, 5, 1,
												 0, 0, 0,
												 -1, -5, -1);

	cv::Mat output_matrix_x;
	cv::Mat output_matrix_y;
	filter2D(input_matrix, output_matrix_x, CV_8U, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	filter2D(input_matrix, output_matrix_y, CV_8U, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
	cv::Mat output_matrix = cv::Mat_<float>(output_matrix_x.cols, output_matrix_x.rows);
	for (int i = 0; i < output_matrix_x.rows; i++) {
		for (int j = 0; j < output_matrix_x.cols; j++) {
			output_matrix.at<float>(i, j, 0) = output_matrix_x.at<float>(i, j, 0); //+ output_matrix_y.at<float>(j, i, 0)) / 2;
		}
	}
	IntensityImage* new_image_output = ImageFactory::newIntensityImage();
	HereBeDragons::NoWantOfConscienceHoldItThatICall(output_matrix, *new_image_output);  // MatrixToImage
	return new_image_output;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	return nullptr;
}