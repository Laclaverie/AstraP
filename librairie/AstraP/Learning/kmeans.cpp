#include "kmeans.h"

std::vector<double> kmeans2(std::vector<double> hands){

    const unsigned int n = hands.size();
    unsigned int k = 2;

    std::vector<double> kernels={0.f,1.f};
    std::vector<double> newKernels;

    std::vector<unsigned int> classes[2],oldClasses[2];
    std::vector<unsigned int> classesLengths;

    bool endLoop=false;

    while (!endLoop){
        std::vector<double>(k,0.f).swap(newKernels);
        std::vector<unsigned int>(k,0).swap(classesLengths);
        float average=(kernels[0]+kernels[1])/2.f;
        for(unsigned int i=0; i<n; i++){
            if(hands[i]<average){
                classes[0].push_back(i);
                newKernels[0]+=hands[i];
                classesLengths[0]++;
            }
            else {
                classes[1].push_back(i);
                newKernels[1]+=hands[i];
                classesLengths[1]++;
            }
        }

        endLoop=classes[0]==oldClasses[0] && classes[1]==oldClasses[1];

        for(unsigned int i=0; i<k; i++){
            if(classesLengths[i]==0){
                k--;
                kernels.erase(kernels.begin()+i);
                oldClasses[i].erase(oldClasses[i].begin()+i);
                classes[i].erase(classes[i].begin()+i);
                i--;
            }
            else{
                kernels[i]=newKernels[i]/classesLengths[i];
                oldClasses[i].swap(classes[i]);
                std::vector<unsigned int>().swap(classes[i]);
            }
        }
    }
    return(kernels);
}
