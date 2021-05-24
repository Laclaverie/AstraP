#include "leaveoneout.h"

LeaveOneOut2::LeaveOneOut2(std::vector<double> positiveData,std::vector<double> negativeData, unsigned int method)
{
    std::vector<double> completeData=negativeData;
    completeData.insert(completeData.end(),positiveData.begin(),positiveData.end());

    const unsigned int n1=negativeData.size();
    const unsigned int n=completeData.size();

    for(unsigned int i=0;i<n;i++){
        std::vector<double> learningData=completeData;
        learningData.erase(learningData.begin()+i);

        std::vector<double> kernels;

        switch(method){
        case m_kmeans2:
            kernels=kmeans2(learningData);
            break;
        default:
            return;
        }

        double frontier=(kernels[0]+kernels[1])/2.f;
        frontier_+=frontier;

        //std::cout<<"i="<<i<<", k0="<<kernels[0]<<", k1="<<kernels[1]<<", frontier="<<frontier<<std::endl;

        if(i<n1){
            // In first set
            if(completeData[i]<frontier) TN_++;//std::cout<<"Vrai negatif"<<std::endl;
            else FP_++;//std::cout<<"Faux positif"<<std::endl;
        }
        else{
            if(completeData[i]<frontier) FN_++;//std::cout<<"Faux negatif"<<std::endl;
            else TP_++;//std::cout<<"Vrai positif"<<std::endl;
        }
    }
    frontier_/=(double)completeData.size();
}
