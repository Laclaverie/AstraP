#ifndef DEMARRAGE_H
#define DEMARRAGE_H

#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<windows.h>
#include<string>

class demarrage
{
public:
    demarrage();
    bool start();
    void GetDesktopResolution(int& horizontal, int& vertical);
private:
    int time=5;
    std::string texte_="Press Enter to calibrate";
};

#endif // DEMARRAGE_H
