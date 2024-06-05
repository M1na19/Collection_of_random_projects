#include "data.h"
#include <ctime>   

const int nrRows=50;
const int nrSeats=6;

const int maxMutations=10;

void GenteticAlgorithm(int nrGenerations,int nrTopPerformers,int generationSize){
    smartstore<Airplane> generation,topPerformers;
    for(int i=0;i<generationSize;i++){
        Airplane randomA=GenerateRandomAirplane(nrRows,nrSeats);
        generation.pushBack(randomA);
    }

    smartstore<int>performance;
    for(int g=0;g<nrGenerations;g++){
        performance.clear();
        for(int i=0;i<generationSize;i++){
            int perf=generation[i].Performance();
            performance.pushBack(perf);
        }

        topPerformers.clear();
        for(int i=0;i<nrTopPerformers;i++){
            int indexBiggest=performance.findSmallest();
            int perf=performance.cutout(indexBiggest);

            topPerformers.pushBack(generation[indexBiggest]);

            if(g==nrGenerations-1){
                cout<<i-1<<": "<<perf<<"\n";
                generation[indexBiggest].Print();
            }
        }
        
        generation.clear();
        for(int i=0;i<nrTopPerformers;i++){
            int mutationDegree=rand()%100+1;
            smartstore<Airplane> mutations=topPerformers[i].Mutate(maxMutations,mutationDegree,generationSize/nrTopPerformers);
            for(int j=0;j<generationSize/nrTopPerformers;j++){
                Airplane edited=changePassangerInfo(mutations[j]);
                generation.pushBack(edited);
            }
        }
    }

    
}

int main(){
    srand(static_cast<unsigned int>(std::time(nullptr)));
    GenteticAlgorithm(100,10,100);
}