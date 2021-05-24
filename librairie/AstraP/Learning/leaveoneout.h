#ifndef LEAVEONEOUT_H
#define LEAVEONEOUT_H

#include "kmeans.h"

class LeaveOneOut2
{
public:
    enum Methods : unsigned int{
        m_kmeans2=0
    };

    LeaveOneOut2(std::vector<double> firstData,std::vector<double> secondData, unsigned int=LeaveOneOut2::Methods::m_kmeans2);
    unsigned int TP_=0, FP_=0, TN_=0, FN_=0;

    unsigned int nbEchantillons(){return(TP_+FP_+TN_+FN_);}

    double getFrontier(){return frontier_;}
private:
    double frontier_;
};

#endif // LEAVEONEOUT_H
