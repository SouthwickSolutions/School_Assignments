#include <iostream>
#include "PPM.h"
#include "PPM.cpp" //take out when compiling on linux

int main(){

    PPM ppmObject1, ppmObject2;

    std::ifstream newFile("van-gogh-starry-night.ppm",
                          std::ios::binary);
    newFile >> ppmObject1;
    newFile.close();

    char choice = ppmObject1.setUserChoice();

    while(choice != 'n'){
        if(choice == 'c'){
            std::ofstream doneFile("vgppmC.ppm",
                                    std::ios::binary);

            ppmObject2.outputCopy(ppmObject1);
            doneFile << ppmObject2;
            doneFile.close();

            std::cout << std::endl <<
            "***COPY FINISHED***"
            << std::endl << std::endl;

            choice = 'n';
        }else if(choice == 'r'){
            std::ofstream doneFile("vgppmR.ppm",
                                    std::ios::binary);
            ppmObject1.outputRed();
            doneFile << ppmObject1;
            doneFile.close();

            std::cout << std::endl <<
             "***RED CONVERSION FINISHED***"
            << std::endl << std::endl;

            choice = 'n';
        }else if(choice == 'g'){
            std::ofstream doneFile("vgppmG.ppm",
                                    std::ios::binary);
            ppmObject1.outputGreen();
            doneFile << ppmObject1;
            doneFile.close();

            std::cout << std::endl <<
             "***GREEN CONVERSION FINISHED***"
            << std::endl << std::endl;

            choice = 'n';
        }else if(choice == 'b'){
             std::ofstream doneFile("vgppmB.ppm",
                                    std::ios::binary);
            ppmObject1.outputBlue();
            doneFile << ppmObject1;
            doneFile.close();

            std::cout << std::endl <<
             "***BLUE CONVERSION FINISHED***"
            << std::endl << std::endl;

            choice = 'n';
        }else if(choice == 'l'){
             std::ofstream doneFile("vgppmL.ppm",
                                    std::ios::binary);
            ppmObject1.outputLinear();
            doneFile << ppmObject1;
            doneFile.close();

            std::cout << std::endl <<
             "***LINEAR CONVERSION FINISHED***"
            << std::endl << std::endl;

            choice = 'n';
        }
    }
    return 0;
}
