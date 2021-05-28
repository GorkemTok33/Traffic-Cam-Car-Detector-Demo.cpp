/*
______________________________________________________________________________
_____________________________________________________________________________ |
Author: GÖRKEM TOK							                                 ||
Email: ceng.gorkem.tok@gmail.com					                         ||
Linkedin: https://www.linkedin.com/in/gorkem-tok33/                          ||
Language: C++                                                                ||
Libraries: OpenCv 3.4                                                        ||
_____________________________________________________________________________||
______________________________________________________________________________|
*/

#ifdef DEBUG
#pragma comment (lib,”user32.lib”)
#pragma comment(lib, "opencv_core340d.lib")
#pragma comment(lib, "opencv_highgui340d.lib")
#pragma comment(lib, "opencv_imgcodecs340d.lib")
#pragma comment(lib, "opencv_videoio340d.lib")
#pragma comment(lib, "opencv_imgproc340d.lib")
#pragma comment(lib, "opencv_text340d.lib")
#pragma comment(lib, "opencv_video340d.lib")
#pragma comment(lib, "opencv_bgsegm340d.lib")

#else
#pragma comment(lib, "opencv_core340.lib")
#pragma comment(lib, "opencv_highgui340.lib")
#pragma comment(lib, "opencv_imgcodecs340.lib")
#pragma comment(lib, "opencv_videoio340.lib")
#pragma comment(lib, "opencv_imgproc340.lib")
#pragma comment(lib, "opencv_text340.lib")
#pragma comment(lib, "opencv_video340.lib")
#pragma comment(lib, "opencv_bgsegm340.lib")

#endif // DEBUG


#include <iostream>
#include <cstdio>
#include <vector>
#include "opencv2\highgui\highgui.hpp"
#include <opencv2\core\core.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\core.hpp>
#include <opencv2\video\video.hpp>
#include <opencv2\bgsegm\bgsegm.hpp>

using namespace std;

void TrafficCamCarDetector(string videofilepath, int segmtype, bool detectShadows = false, double learningRate = -1.0)
{
	char *methotsString[] = { "MOG", "MOG2", "KNN", "GMG"};

	if (segmtype < 0 || segmtype > 3)
	{
		cout << "TrafficCamCarDetector Exception: invalid method value" << endl;
		return;
	}

	cv::VideoCapture vc;
	cv::Ptr<cv::BackgroundSubtractor> bsmet;

	if (vc.open(videofilepath))
	{
		switch (segmtype)
		{

		case 0:
			bsmet = cv::bgsegm::createBackgroundSubtractorMOG();
			break;
		case 1:
			bsmet = cv::createBackgroundSubtractorMOG2(500,100.0, detectShadows);
			break;
		case 2:
			bsmet = cv::createBackgroundSubtractorKNN(500, 400.0, detectShadows);
			break;
		case 3:
			bsmet = cv::bgsegm::createBackgroundSubtractorGMG(10);
			break;
		default:
			cout << "backgroundsegmTest Exception: invalid method value" << endl;
			break;
		}

		auto count = [](cv::Mat diffFrame, cv::Mat originalFrame)
		{
			vector<vector<cv::Point>> contours;
			cv::RotatedRect rrect;
			cv::findContours(diffFrame, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
			for (int i = 0; i < contours.size(); i++)
			{
				rrect = cv::minAreaRect(contours[i]);
				cv::drawContours(originalFrame, contours, i, cv::Scalar(0, 0, 255), 2);
				cv::Point2f center;
				float radius;
				cv::minEnclosingCircle(contours[i], center, radius);
				if (radius >= 20)
					cv::circle(originalFrame, center, radius, cv::Scalar(0, 255, 0), 2);
			}
		};

		cv::Mat frame;
		cv::Mat originalFrame;
		cv::Mat bgsegmImage;
		cv::Mat morphImage;
		string winFrame = "Main Frame";
		string winBsmet = methotsString[segmtype];
		string winMorph = "After Morphology";
		string winCount = "Function Count Result";
		cv::namedWindow(winFrame, CV_WINDOW_NORMAL);
		cv::namedWindow(winBsmet, CV_WINDOW_NORMAL);
		cv::namedWindow(winMorph, CV_WINDOW_NORMAL);
		cv::namedWindow(winCount, CV_WINDOW_NORMAL);
		double fps = vc.get(CV_CAP_PROP_FPS);
		if (fps < 23.0)
			fps = 23.0;

		for (;;)
		{
			if (vc.grab())
			{
				vc.retrieve(frame);
				cv::imshow(winFrame, frame);
				frame.copyTo(originalFrame);
				cv::GaussianBlur(frame, frame, cv::Size(5, 5), 7);
				bsmet->apply(frame, bgsegmImage, learningRate);
				cv::imshow(winBsmet, bgsegmImage);
				cv::Mat kernel = cv::getStructuringElement(CV_SHAPE_RECT, cv::Size(3, 3), cv::Point(-1, -1));
				cv::morphologyEx(bgsegmImage, morphImage, CV_MOP_ERODE, kernel, cv::Point(-1,-1), 1);
				cv::morphologyEx(bgsegmImage, morphImage, CV_MOP_CLOSE, kernel, cv::Point(-1, -1), 5);
				cv::imshow(winMorph, morphImage);
				count(morphImage, originalFrame);
				cv::imshow(winCount, originalFrame);
			}

			if (cv::waitKey(1000 / fps) == 27)
			{
				cout << "Pressed ESC ! End Of Run" << endl;
				break;
			}
		}

		vc.release();
		cv::destroyAllWindows();

		return;
	}

	cout << "backgroundsegmTest Exception: Couldn't read videofile from path: " + videofilepath<<endl;

	return;
}

int main()
{
    string filepath = ""; //your file path
    TrafficCamCarDetector(filepath, 1);
    return;
}
