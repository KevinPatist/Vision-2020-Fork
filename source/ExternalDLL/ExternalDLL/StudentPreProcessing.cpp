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
	cv::medianBlur(input_matrix, input_matrix, 3);	// We passen een median blur toe omdat we hier meer succes mee hadden dan een gaussian filter
	float middle = 2;	// Dit is in de kernel de middeldste waarde
	float hoek = 1;	// En dit zijn de hoek waarden van de kernels
	cv::Mat kernel_x = (cv::Mat_<float>(3, 3) << hoek, 0,-hoek,
		middle, 0, -middle,
		hoek, 0, -hoek
		);

	cv::Mat kernel_y = (cv::Mat_<float>(3, 3) << hoek, middle, hoek,
		0, 0, 0,
		-hoek, -middle, -hoek);

	cv::Mat kernel_x1 = (cv::Mat_<float>(3, 3) << -hoek, 0, hoek,
		-middle, 0, middle,
		-hoek, 0, hoek);

	cv::Mat kernel_y1 = (cv::Mat_<float>(3, 3) << hoek, 0, -hoek,
		middle, 0, -middle,
		hoek, 0, -hoek);
	// we hebben gekozen voor 2 kernels voor de x en y richting omdat we met 1 kernel die 1 kant op ging geen goede resulaten kregen
	// We hadden ook de kernel vergroot naar 6 bij 6 en 9 bij 9 maar daar werd het niet beter van, alleen de lijnen werden heel dik. Dat is niet wat we willen
	// Wij hebben voor de 2 kernels per x en y richting gekozen omdat als we de kernels maar 1 richt op laten gaan laten we nu zeggen van rechts naar links. Dan is de linkerkant van de kernel plus en de andere kant min. 
	// Als we deze draaide detecte hij aan de rechterkant amper lijnen en toen hebben wij gekozen om de kernel allebij de kanten op te laten draaien zodat we aan allebij de kanten een goede detectie hebben
	cv::Mat output_matrix;

	cv::Mat x;	// Dit is de x kernel als de 2 kernels zijn samen gevoegd
	cv::Mat y;	// Dit is de y kernel als de 2 kernels zijn samen gevoegd

	// Dit zijn de output martixes voor de aparte kernels
	cv::Mat output_matrix_x;
	cv::Mat output_matrix_y;
	cv::Mat output_matrix_x1;
	cv::Mat output_matrix_y1;

	filter2D(input_matrix, output_matrix_x, CV_8U, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);		// hier word de eerste x kernel toegepast
	filter2D(input_matrix, output_matrix_y, CV_8U, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);		// hier word de eerste y kernel toegepast
	filter2D(input_matrix, output_matrix_x1, CV_8U, kernel_x1, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);	// hier word de tweede x kernel toegepast
	filter2D(input_matrix, output_matrix_y1, CV_8U, kernel_y1, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);	// hier word de tweede y kernel toegepast

	addWeighted(output_matrix_x, 0.7, output_matrix_x1, 0.7, 0, x);		// hier worden de 2 x kernels samen gevoegd
	addWeighted(output_matrix_y, 0.7, output_matrix_y1, 0.7, 0, y);		// hier worden de 2 y kernels samen gevoegd
	addWeighted(x, 1.0, y, 1.0, 0, output_matrix);						// hier worden de x en y kernel samen gevoegd


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