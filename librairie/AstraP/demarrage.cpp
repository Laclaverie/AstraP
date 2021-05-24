#include "demarrage.h"

demarrage::demarrage()
{

}
/* --- Fonction à paufiner pour plus tard :: adaptabilité de l'application en fonction de l'écran de l'utilisateur --
void demarrage::GetDesktopResolution(int &horizontal, int &vertical){

       RECT desktop;

       // Get a handle to the desktop window
       const HWND hDesktop = GetDesktopWindow();
       // Get the size of screen to the variable desktop
       GetWindowRect(hDesktop, &desktop);
       // The top left corner will have coordinates (0,0)
       // and the bottom right corner will have coordinates
       // (horizontal, vertical)
       horizontal = desktop.right;
       vertical = desktop.bottom;

}
*/
bool demarrage::start(){
    bool ok=false;
    cv::Mat frame;
    cv::VideoCapture cap(0);
  //  cv::resize(frame,frame,cv::Size(),0.75,0.75);

   /* int horizontal = 0;
    int vertical = 0;

    GetDesktopResolution(horizontal,vertical);

    cv::Point origine= cv::Point(horizontal/12,vertical/25);
Pour plus tard : faire une fonction qui s'adapte à l'écran de l'utilisateur
*/

    while (ok==false) {//fonction non finie
        cap>>frame;
        cv::resize(frame,frame,cv::Size(800,600));
        cv::flip(frame,frame,1);// retourner
        cv::namedWindow("Calibration",cv::WINDOW_FULLSCREEN);

        cv::putText(frame,texte_,
                    cv::Point(100,300),
                    cv::FONT_HERSHEY_SIMPLEX, //mit au pif, à changer si jamais : Font
                    1.5,    // taille ( 2.0 : 2fois plus grand)
                    cv::Scalar(0,0,255)// couleur
                    ,2
                   , cv::LINE_AA);
        //cv::imshow("Calibration",frame);

        if (cv::waitKey(30)==13)//entrée
        {
            ok = true; // sortir de la boucle d'attente et lancer la suite
        }


    }






    return ok;
}

