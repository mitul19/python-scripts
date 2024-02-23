#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cjson/cJSON.h>

#include <gif_lib.h>
#include <opencv4/opencv2/opencv.hpp>
#define HAAR_CASCADE_PATH "resources/haarcascade_frontalface_alt2.xml"

using namespace std;

class FaceDetector
{
public:
    int loadCascade();
    int loadImage(string imagePath);
    int detectFaces();
    void displayImage();
    void saveJSON();

private:
    string imagePath_;
    cv::Mat image_;
    cv::CascadeClassifier faceHaarCascade_;
    std::vector<cv::Rect> faces_;

    void shrinkImage(int maxWidth, int maxHeight);
};

int FaceDetector::loadCascade()
{
    if (faceHaarCascade_.load(HAAR_CASCADE_PATH))
    {
        cerr << "ERROR: failed to load haar cascade from " << HAAR_CASCADE_PATH << endl;
        return -1; // failure
    }
    return 0; // success
}

int FaceDetector::loadImage(string imagePath)
{
    imagePath_ = imagePath;
    string fileExt;
    fileExt = imagePath.substr(imagePath.find_last_of(".") + 1);
    if ((fileExt == "jpeg") || (fileExt == "jpg"))
    {
        image_ = cv::imread(imagePath);
    }
    else if (fileExt == "png")
    {
        image_ = cv::imread(imagePath);
    }
    else
    {
        cerr << "ERROR: unrecognized file extension on " << imagePath << endl;
        return -1; // Failure
    }

    if (image_.empty())
    {
        cerr << "ERROR: Failed to load image file " << imagePath << endl;
        return -2; // Failure
    }
    return 0; // success
}

int FaceDetector::detectFaces()
{
    if (image_.empty())
    {
        cerr << "ERROR: Failed to load image file " << imagePath << endl;
        return -1; // Failure
    }

    // convert to grey scale
    cv::Mat imageGrayScale;
    cv::cvtColor(image_, imageGrayScale, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(imageGrayScale, imageGrayScale);

    // use haar cascade to detect faces
    faceHaarCascade_.detectMultiScale(imageGrayScale, faces_, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(250, 250));

    return faces_.size(); // number of faces detected
}

void FaceDetector::displayImage()
{
    if (image_.empty())
    {
        cerr << "ERROR: Cannot display image_; image_ not loaded" << endl;
        return; // failure
    }

    for (int i = 0; i < faces_.size(); i++)
    {
        cv::Point center(faces_[i].x + faces_[i].width / 2, faces_[i].y + faces_[i].height / 2);
        cv::ellipse(image_, center, cv::Size(faces_[i].width / 2, faces_[i].height / 2), 0, 0, 360, cv::Scalar(0, 255, 0), 10, 8, 0);
    }

    // scale image to fit within 1280x720 window
    shrinkImage(1280, 720);

    // create a window for display
    cv::namedWindow("Face Detector", cv::WINDOW_AUTOSIZE);
    cv::imshow("Face Detector", image_);
    cv::waitKey(0);
}

void FaceDetector::shrinkImage(int maxWidth, int maxHeight)
{
    if (image_.empty())
    {
        std::cerr << "ERROR: Cannot scale image_; image_ not loaded" << std::endl;
        return; // failure
    }

    // scale image_ to fit within maxWidth x maxHeight
    cv::Size s = image_.size();
    if ((s.width / s.height) > (maxWidth / maxHeight)) // scale based on width
    {
        cv::resize(image_, image_,
                   cv::Size(maxWidth, (s.height * maxWidth / s.width)));
    }
    else // scale based on height
    {
        cv::resize(image_, image_,
                   cv::Size((s.width * maxHeight / s.height), maxHeight));
    }
}

void FaceDetector::saveJSON()
{
    if (imagePath_.empty())
    {
        cerr << "ERROR: Can't save JSON: " << imagePath_ << " not available" << endl;
        return; // Failure
    }

    // populate JSON fields
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "countFaces", faces_.size());
    cJSON_AddStringToObject(json, "imageLocation", imagePath_.c_str());

    // create output file in same directory
    string outfilename = imagePath_ + ".json";
    FILE *fp = fopen(outfilename.c_str(), "w");
    if (fp == NULL)
    {
        cerr << "ERROR: unable to opens json file: " << outfilename << endl;
        return; // Failure
    }
    fputs(cJSON_Print(json), fp);
    fclose(fp);
    cJSON_Delete(json);
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cerr << "ERROR: Missing argument - path to image" << endl;
        return 1;
    }
}