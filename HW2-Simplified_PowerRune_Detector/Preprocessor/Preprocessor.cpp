//
// Created by 李喆昊 on 2021/9/23.
//

#include "Preprocessor.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
Preprocessor::Preprocessor() {
    morphElement = getStructuringElement(
            MORPH_RECT,
            Size(2 * morphSize + 1,
                 2 * morphSize + 1),
            Point(morphSize, morphSize));
}

Mat Preprocessor::denoise(const Mat &inputImg, const int binaryFilterThresh, const int binaryFilterMaxVal) {
    // TODO: 你要实现的部分
    vector<Mat> channels;
    split( inputImg, channels);
    Mat R=channels.at(2);
    Mat B=channels.at(0);
    Mat dif= R-B;
    Mat BinaryImage;
    threshold(dif, BinaryImage, 100, 255, THRESH_BINARY);
    imshow("ezt",BinaryImage);
}


Mat Preprocessor::morphologyProcess(const Mat &inputImg) {
    // TODO: 你要实现的部分：形态学变换

}

Mat Preprocessor::operator()(const Mat &inputImg) {
    // binary filter
    auto midImg = denoise(inputImg);
    Mat close;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3), Point(-1, -1));
	morphologyEx(midImg, close, MORPH_CLOSE, kernel);
    // Use morphologyProcess to connect separated part
    return morphologyProcess(midImg);
}
