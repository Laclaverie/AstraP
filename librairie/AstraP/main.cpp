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

#include "Learning/leaveoneout.h"


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
    demarrage dem;
    //dem.start();

    std::string path;
    int nbFiles=0;
    std::vector<double> fistsData;
    std::vector<double> nonFistsData;

    for(short i=0;i<2;i++){

        switch(i){
        case 0:
            path="../Base d_images/main_fermee/main_fermee0";
            nbFiles=42;
            break;
        case 1:
            path="../Base d_images/main_ouverte/main_ouverte0";
            nbFiles=64;
            break;
        default:
            break;
        }

        captation maCap;

        for(short j=1;j<nbFiles+1;j++){

            std::cout<<(i ? "Ferme" : "Ouvert") <<", "<<j<<std::endl;

            std::string id;
            if(j<10){
                id="0"+std::to_string(j);
            }
            else{
                id=std::to_string(j);
            }
            cv::Mat frame = cv::imread(path+id+".jpg",3);
            //cv::imshow("Frame",frame);

            try{
                maCap.BRGBL_critere(frame,frame);
            }  catch (...) {

            }
        }

        switch(i){
        case 0:
            fistsData=maCap.getBRGBL();
            break;
        case 1:
            nonFistsData=maCap.getBRGBL();
            break;
        default:
            break;
        }

    }

    std::cout<<"fistsDataLength : "<<fistsData.size()<<std::endl;
    std::cout<<"nonFistsDataLength : "<<nonFistsData.size()<<std::endl;

    LeaveOneOut2 confMat(fistsData,nonFistsData,LeaveOneOut2::Methods::m_kmeans2);

    std::cout<<"Nb echantillons : "<<confMat.nbEchantillons()<<std::endl;
    std::cout<<"TP : "<<confMat.TP_<<", FN : "<<confMat.FN_<<std::endl;
    std::cout<<"FP : "<<confMat.FP_<<", TN : "<<confMat.TN_<<std::endl;
    std::cout<<"Frontier : "<<confMat.getFrontier()<<std::endl;

    int wait;
    std::cin>>wait;
    std::cout<<wait<<std::endl;
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

