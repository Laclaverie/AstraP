#ifndef CAPTATION_H
#define CAPTATION_H

#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/core/types_c.h>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/hal/interface.h>
#include<QDebug>

#include <math.h>

#include<iostream>

#include <opencv2/objdetect.hpp>


class captation
{
public:
    captation();
    /* ---- boite à outils -- */
    cv::Mat background_substraction(cv::Mat frame);
    cv::Mat bwareaopen(cv::Mat &im,double size);
    cv::Mat convhull(cv::Mat &im);
    cv::Mat imfill(cv::Mat &im);
    std::vector<cv::Mat>makeMaskYcbCr(cv::Mat &im,int choix,bool hsv); // choix =0 : solidty =1: defects+solidy hsv or not hsv that is the question

    void capterTraiter();
    cv::Mat splitThreshMerge(cv::Mat &res, cv::Mat &im,bool hsv);
    void BRGBL_critere(cv::Mat input,cv::Mat output); // Critère B--RGBL
    std::vector<double> getBRGBL(){return solidity_;}

    /* ---- Inline fonction ----*/
    void setBackground(cv::Mat background){background_=background;}
    void setThreshold(int thresholdType,int threshValue){thresholdType_=thresholdType;threshValue_=threshValue;}
    void setMaxBinaryValue(int mbv){maxBinaryValue_=mbv;}




private:
    int thresholdType_= 0;              // https://docs.opencv.org/master/db/d8e/tutorial_threshold.html
    int threshValue_=200;            // fixé arbitairement
    int maxBinaryValue_=255;            //images en NDG
    cv::Mat background_;
    std::vector<double> solidity_;
    cv::Mat hands_convexity_;


    /* --- Channels YCbCr === YCrCb sur opencv ---*/
    float YCrCbValues_[6]= {0.0*255,1*255,0.525*255,0.6*255,0.4*255,0.55*255}; //ymin,ymax,crmin,crmax,cbmin,cbmax
    float HSVValues_[6]= {0.0013*255,0.099*255,0*255,1*255,0*255,1*255}; //Hmin,Hmax,Smin,Smax,Vmin,Vmax


};

#endif // CAPTATION_H
