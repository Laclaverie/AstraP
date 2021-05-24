#include "mainwindow.h"
#include "captation.h"
#include "demarrage.h"

#include <QApplication>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <ctime>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <filesystem>


#include <stdio.h>
#include <stdarg.h>


typedef std::vector<std::string> stringvec;
using namespace std::chrono;

using std::cout; using std::cin;
using std::endl; using std::string;
//using std::filesystem::directory_iterator;
#include <sys/types.h>
#include <dirent.h>

void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}




int main(int argc, char *argv[])
{
    /* --- Tests en cours, ne pas avoir peur du main --- */
    QApplication a(argc, argv);
    MainWindow w;
   // w.show();
    //return a.exec();
    captation maCap;
    demarrage dem;
    //dem.start();
    cv::Mat frame = cv::imread("../Base d_images/main_fermee/main_fermee028.jpg",3);
   // cv::imshow("fond",fond);
    cv::imshow("frame",frame);

    high_resolution_clock::time_point time1 = high_resolution_clock::now();
    maCap.BRGBL_critere(frame,frame);
    high_resolution_clock::time_point time2 = high_resolution_clock::now();
    milliseconds duration = duration_cast<milliseconds>(time2 - time1);
    qDebug()<< " Temps d'execution : "<< (long)duration.count();


       cv::waitKey();
     /*   stringvec v;
        read_directory("C:/Users/seaga/Documents/Pierre/Telecom/Fise2/S8/Image/reconnaissance de forme/Projet/git/astra-pioneers/librairie/base_images/", v);
        std::copy(v.begin(), v.end(),
        std::ostream_iterator<std::string>(std::cout, "\n"));

       */

  /*  string outpath = "C:/Users/seaga/Documents/Pierre/Telecom/Fise2/S8/Image/reconnaissance de forme/Projet/git/astra-pioneers/librairie/etiquettes/";
    string inpath = "C:/Users/seaga/Documents/Pierre/Telecom/Fise2/S8/Image/reconnaissance de forme/Projet/git/astra-pioneers/librairie/Base d_images/main_ouverte/";
    string nom = "main_ouverte0";
    int nb_fichier= 63;
    for (int i=0;i<nb_fichier;i++){

        string ii= std::to_string(i+1);
        if(i<9){
           ii= "0"+ii;
        }
        string Image_name =nom+ii;
        cv::Mat im=cv::imread(inpath+Image_name+".jpg");
        cv::Mat res=maCap.makeMaskYcbCr(im);
        cv::imwrite(outpath+Image_name+".png",res);

    }
*/


    return 0;

}

