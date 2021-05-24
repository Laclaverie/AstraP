#include "captation.h"

captation::captation()
{

}
cv::Mat captation::background_substraction(cv::Mat frame){ // renvoi une image en NDG

    cv::Mat thresh,NDG,res;
    cv::absdiff(frame,background_,frame);
    /*  On converti en Niveau de gris*/
    cv::cvtColor(frame,NDG,cv::COLOR_BGR2GRAY);
    /*  On converti l'image en image binaire */
    cv::threshold(NDG,thresh,threshValue_,maxBinaryValue_,thresholdType_);
   // v1 cv::absdiff(NDG,background_,res);
    return res;
}
void captation::capterTraiter(){

    cv::Mat frame_sc,frame_s;       // frame_s : frame sans le fond (substraction) frame_sc : frame sans le fond et avec la convhull
    cv::VideoCapture cap(0);
    cv::namedWindow("Sortie Camera",1);

    while(cv::waitKey(5)<0){

        cv::Mat frame;
        // recup frame
        cap>>frame;
        // flip frame
        cv::flip(frame,frame,1);

        //cv::imshow("Sortie Camera",frame);

    }

}
cv::Mat captation::bwareaopen(cv::Mat &im, double size){
    // Find all contours
       std::vector<std::vector<cv::Point>> contours;
       std::vector<cv::Vec4i> hierarchy;        // chercher ce qu'est cette infamnie
       cv::findContours(im, contours,hierarchy,cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

       for (unsigned int i = 0; i < contours.size(); i++)
       {
           // Calculate contour area
           double area = cv::contourArea(contours[i]);

           // Remove small objects by drawing the contour with black color
           if ( area <= size){
               cv::drawContours(im, contours, i, CV_RGB(0, 0, 0), -1);
           }
       }
       return im;
}

// https://docs.opencv.org/3.4/d7/d1d/tutorial_hull.html
cv::Mat captation::convhull(cv::Mat &im){ // à utiliser aprèsbackground_substraction
    // etape 1 : flou
    cv::blur(im,im,cv::Size(9,9));
    // etape 2 :  contours : détecteur Canny
    cv:: Mat canny_output;
    cv::Canny(im,canny_output,threshValue_,threshValue_*2);
    // etape 3 : contours
    std::vector<std::vector <cv::Point>> contours;
    cv::findContours(canny_output,contours,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);
    // etape 4 : hull
    std::vector<std::vector <cv::Point>> hull(contours.size());
    for(size_t i=0;i<contours.size();i++){        //https://stackoverflow.com/questions/1181079/stringsize-type-instead-of-int/1181081#1181081
        cv::convexHull(contours[i],hull[i]);
    }

   // affichage
    cv::Mat drawing =cv::Mat::zeros(canny_output.size(),CV_8UC3);
    for (size_t i =0;i<contours.size();i++){
        cv::Scalar color = cv::Scalar(255,0,0);
        cv::drawContours(drawing,contours,(int)i,color);
        cv::drawContours(drawing,hull,(int)i,color);
    }

return drawing;
}

cv::Mat captation::imfill(cv::Mat &im){ //https://learnopencv.com/filling-holes-in-an-image-using-opencv-python-c/#:~:text=There%20is%20no%20imfill%20function,pixel%20(0%2C%200).
     std::vector<std::vector<cv::Point> > contours_vector;

   cv::findContours(im, contours_vector, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

   cv::Mat contourImage(im.size(), CV_8UC1, cv::Scalar(0));
   for ( ushort contour_index = 0; contour_index < contours_vector.size(); contour_index++) {
       cv::drawContours(contourImage, contours_vector, contour_index, cv::Scalar(255), -1);
   }
   return contourImage;
}


std::vector<cv::Mat> captation::makeMaskYcbCr(cv::Mat &im,int choix,bool hsv){
    /* ---Variables globales de la fonction--- */
    cv::Mat res, clone,canny_output,rectangle;
    std::vector<std::vector<cv::Point>> contours,cnts;
   // std::vector<cv::Point> cnts;
    cv::RNG rng(123456789);
    /* --- éléments structurant ---*/
    rectangle = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(15,15));
    /* --- conversion en YcbCr  ---*/

    if(hsv){
        cv::cvtColor(im,res,cv::COLOR_BGR2HSV);
    }
    else{
        cv::cvtColor(im,res,cv::COLOR_BGR2YCrCb);
    }


    clone= captation::splitThreshMerge(res,im,hsv);

    cv::cvtColor(clone,clone,cv::COLOR_BGR2GRAY);
    cv::Mat temps= clone.clone();
    //cv::imshow("TOOTOT nass",clone);
    /* --- fill les mains + bras ---*/

    cv::Canny(clone,canny_output,(double)threshValue_,(double)thresholdType_);
    cv::dilate(canny_output,canny_output,rectangle);


    cv::findContours(canny_output,contours,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);


    std::vector<cv::Point> approx;
    std::vector<std::vector<cv::Point>> hull(contours.size());
    std::vector<std::vector<int>> hullIndices(contours.size());
    std::vector<std::vector<cv::Vec4i>> defects(contours.size());
    /// fill convex hull
    cv::Mat drawing = cv::Mat::zeros(canny_output.size(),CV_8UC3);
    cv::Mat main_convexe_hull_ = cv::Mat::zeros(canny_output.size(),CV_8UC3);

    for (size_t i=0;i<contours.size();i++){
        cv::convexHull(contours[i],hull[i]);
        cv::convexHull(contours[i],hullIndices[i]);

       if(choix==1){
        if (hullIndices[i].size()>3){
            cv::convexityDefects(contours[i],hullIndices[i],defects[i]);
        }
       }
        //cv::Scalar color= cv::Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        cv::Scalar color(255,255,255);
        cv::drawContours(drawing,contours,(int)i,color,-1); // -1 pour fill les contours


        cv::drawContours(main_convexe_hull_,contours,(int)i,color,-1); // -1 pour fill les contours
        cv::drawContours(main_convexe_hull_,hull,(int)i,color,-1); // -1 pour fill toute l'envelloppe convexe
       }

    /* --- chercher les connexity Defects --- */

    cv::Canny(clone,canny_output,(double)threshValue_,(double)thresholdType_);
    cv::dilate(canny_output,canny_output,rectangle);
    cv::erode(canny_output,canny_output,rectangle);
    canny_output=captation::imfill(canny_output);
    cv::Mat tmp=canny_output;

    //cv::imshow("tmp",tmp);

    canny_output=~canny_output;
    canny_output=captation::bwareaopen(canny_output,90000);

    canny_output=~canny_output;

    //cv::imshow("canny output",canny_output);

    cv::findContours(canny_output,contours,cv::RETR_EXTERNAL,cv::CHAIN_APPROX_TC89_L1);
    /// fill convex hull

   // cv::GaussianBlur(drawing,drawing, cv::Size(21,21),5,5);

    //cv::threshold(drawThresh,drawThresh,100,256,0);
    if (choix==1){


    /// Draw convexityDefects
   for (unsigned int i = 0; i < defects.size(); ++i)
    {
        for(const cv::Vec4i& v : defects[i])
        {
            float depth = v[3] / 256;
            if (depth > 25) //  filter defects by depth, e.g more than 10
            {
                int startidx = v[0]; cv::Point ptStart(contours[i][startidx]);
                int endidx = v[1]; cv::Point ptEnd(contours[i][endidx]);
                int faridx = v[2]; cv::Point ptFar(contours[i][faridx]);

                line(drawing, ptStart, ptEnd, cv::Scalar(0, 255, 0), 1);
                line(drawing, ptStart, ptFar, cv::Scalar(0, 255, 0), 1);
                line(drawing, ptEnd, ptFar, cv::Scalar(0, 255, 0), 1);
                circle(drawing, ptFar, 4, cv::Scalar(0, 255, 0), 2);
            }
        }
    }

    //cv::imshow("defects",drawing);
}

    cv::cvtColor(main_convexe_hull_,main_convexe_hull_,cv::COLOR_BGR2GRAY);
    cv::threshold(main_convexe_hull_,main_convexe_hull_,threshValue_,255,0);
    std::vector<cv::Mat> resFinal;
    resFinal.push_back(hands_convexity_);
    resFinal.push_back(main_convexe_hull_);
    return resFinal ;
}
cv::Mat captation::splitThreshMerge(cv::Mat &res,cv::Mat &im,bool hsv){ // Utilisation du hsv
    cv::Mat channel[3],mask,ellipse;
    ellipse= cv::getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(5,5));

    /* --- Threshold sur chacun des canaux ---*/
    /* /!\ Ordre des channels inversés (BRG et non pas RGB)*/

    cv::split(res,channel); // récuperer les 3 channels

    if(!hsv){
    for(int i=0;i<3;i++){
        cv ::blur(channel[i],channel[i],cv::Size(5,5));

            //cv::equalizeHist(channel[i],channel[i]);
            channel[i] = (channel[i]>YCrCbValues_[i*2])&(channel[i]<YCrCbValues_[i*2+1]);
            cv::threshold(channel[i],channel[i],threshValue_,maxBinaryValue_,0);
    }
}
    else{
        for(int i=0;i<3;i++){
            cv ::blur(channel[i],channel[i],cv::Size(5,5));

                //cv::equalizeHist(channel[i],channel[i]);
                channel[i] = (channel[i]>HSVValues_[i*2])&(channel[i]<HSVValues_[i*2+1]);
                cv::threshold(channel[i],channel[i],threshValue_,maxBinaryValue_,0);
        }
    }
    /* ---- Suppression du fond genant ----*/
    mask=channel[1].mul(channel[2]).mul(channel[0]);

    //cv::imshow("Mask original",mask);
    mask=captation::bwareaopen(mask,5000);
    //cv::imshow("avant erosion", mask);
    cv::erode(mask,mask,ellipse);
    mask=captation::bwareaopen(mask,5000);
    cv::dilate(mask,mask,ellipse);
    //cv::imshow(" apres erosion",mask);
    mask=captation::imfill(mask);
    //cv::imshow("filled",mask);

    // corrections
    mask=~mask;
    mask=captation::bwareaopen(mask,50000);
    mask=~mask;
  //  cv::imshow("après bwwww", mask);
    /* --- image pour conv hull --- */
    hands_convexity_=mask;

    cv::Mat clone=im.clone();
    cv::Mat channel_image_origine [3];
    cv::Mat res_bitwise[3];
    /* --- split pour mask couleur ---*/
    cv::split(clone,channel_image_origine);
    for (int i=0;i<3;i++){
        cv::bitwise_and(channel_image_origine[i],mask,res_bitwise[i]);
    }
    /* --- merge pour reconstituer image ---*/
    cv::merge(res_bitwise,3,clone);

    return clone;
}
void captation::BRGBL_critere(cv::Mat input, cv::Mat output){

   std::vector<cv::Mat> res=captation::makeMaskYcbCr(input,0,true);
   cv::Mat labelImage,stats,centroids,stats_hull,centroids_hull,labelImage_hull,img_color;
   int nLabels = cv::connectedComponentsWithStats(res[0], labelImage, stats, centroids, 8, CV_32S);
   int nLabels_hull=cv::connectedComponentsWithStats(res[1], labelImage_hull, stats_hull, centroids_hull, 8, CV_32S);
   std::vector<int> areas_convex;
   std::vector<int> areas_hull;

       //remplir aires convexes
    for (int i =1;i<nLabels;i++){
        cv::Mat maskLabel=labelImage==i;
        qDebug() << " Aire label "<<i<<" : "<<cv::countNonZero(maskLabel);
        areas_convex.push_back(cv::countNonZero(maskLabel));
        //cv::imshow("Label convex "+std::to_string(i),maskLabel);

    }
    // remplir les hull
    for (int i =1;i<nLabels_hull;i++){
        cv::Mat maskLabel=labelImage_hull==i;
        qDebug() << " Aire label Hull "<<i<<" : "<<cv::countNonZero(maskLabel);
        areas_hull.push_back(cv::countNonZero(maskLabel));
        //cv::imshow("Label HULL "+std::to_string(i),maskLabel);}

    }

       // solidity
    int max_ITER=cv::min(nLabels,nLabels_hull);
    for (int i=0;i<max_ITER-1;i++){
        qDebug()<< " Solidity = "<<double(areas_convex.at(i))/double(areas_hull.at(i));
        solidity_.push_back(double(areas_convex.at(i))/double(areas_hull.at(i)));
    }

/*
TEST LABELS
       std:: vector<cv::Vec3b> colors(nLabels);
       colors[0]=cv::Vec3b(0,0,0);

       for(int i = 1; i < nLabels; i++ ) {
         colors[i] = cv::Vec3b(rand()%256, rand()%256, rand()%256);
       }
       img_color = cv::Mat::zeros(res[1].size(), CV_8UC3);
            for( int y = 0; y < img_color.rows; y++ )
                  for( int x = 0; x < img_color.cols; x++ )
                  {
                        int label = labelImage.at<int>(y, x);
                        CV_Assert(0 <= label && label <= nLabels);
                        img_color.at<cv::Vec3b>(y, x) = colors[label];
                  }


        cv::imshow("imgcolor",img_color);


*/

}
