#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>



int main() {
	
	std::cout << "Welcome to Ascii art gen. Yes, I Larry, made this" << "\n";
	std::cout << "Art will be outputted to the \"OUTPUT.TXT\" text file under the \"out\" folder" << "\n";
	std::cout << "Enter path of desired image (Enter x to use default image): ";
	
	std::string filePath;
	std::cin >> filePath;

	if (filePath == "x") {
		filePath = "Images/Simple.jpg";
	}
		
	


	//Shader Code
		//const char* shaders = " .:-=+*#%@";
	std::array<char, 10> shaders = {' ','.',':','-','=','+','*','#','%','@'};
	const int numOfShaders = shaders.size() - 1;  //This -1 made me waste an hour trying to find the problem
	

	//Text file to open
	std::ofstream file("out/OUTPUT.txt", std::ios_base::trunc);


	//Image Preprocessing
	cv::Mat img = cv::imread(filePath);

	if (img.empty()) {
		std::cout << "Failed to read image" << std::endl;
		return -1;
	}

	cv::cvtColor(img, img, cv::COLOR_RGB2GRAY);
	cv::resize(img, img, cv::Size(150, 200), cv::INTER_LINEAR);


	//Printing ascii art to text file
	double percentPixel = 0.0;
	int shaderPos = 0;	
	for (int x = 0; x < img.rows - 1; x++) {
		for (int y = 0; y < img.cols - 1; y++) {
			percentPixel = ((int)img.at<uint8_t>(x, y)) / 255.0; //Gets a double of how dark a pixel is
			shaderPos = numOfShaders * percentPixel;  //Uses the double and multiplies it to get a relative position in shader array
			file << shaders[shaderPos] << shaders[shaderPos];  //Puts character into file
		}
		file << "\n";
	}


	//Closing file
	file.close();


	return 0;
}