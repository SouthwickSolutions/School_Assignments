#include "PPM.h"
#include "PPM.cpp" //take this out when compiling
//with G++

int main()
{
    std::cout << "Welcome. Please follow the "
    "prompt and make sure to enter file names "
    "exactly if you are using existing "
    "files. You will be creating/opening eight "
    "ppm"
    " files for the testing." << std::endl
    << std::endl;

    //sets up first object
    PPM picture1;
    std::cin >> picture1;
    std::cout << std::endl << "Representation "
    "of first object:" << std::endl;
    std::cout << picture1 << std::endl <<
    std::endl << "----------" << std::endl
    << std::endl;

    //sets up second object
    PPM picture2;
    std::cin >> picture2;
    std::cout << std::endl << "Representation "
    "of second object:" << std::endl;
    std::cout << picture2 << std::endl <<
    std::endl << "----------" << std::endl
    << std::endl;

    //sets up third object
    PPM picture3;
    std::cin >> picture3;
    std::cout << std::endl << "Representation "
    "of third object:" << std::endl;
    std::cout << picture3 << std::endl <<
    std::endl << "----------" << std::endl
    << std::endl;

    //sets up fourth object
    std::cout << std::endl << "Use [c] for this "
    "file. ";
    PPM picture4;
    std::cin >> picture4;
    std::cout << std::endl << "Representation "
    "of fourth object:" << std::endl;
    std::cout << picture4 << std::endl <<
    std::endl << "----------" << std::endl
    << std::endl;

    //sets up fifth object
    PPM picture5;
    std::cin >> picture5;
    std::cout << std::endl << "Representation "
    "of fifth object:" << std::endl;
    std::cout << picture5 << std::endl <<
    std::endl << "----------" << std::endl
    << std::endl;

    //sets up sixth object
    std::cout << std::endl << "Use [c] for this "
    "file. ";
    PPM picture6;
    std::cin >> picture6;
    std::cout << std::endl << "Representation "
    "of sixth object:" << std::endl;
    std::cout << picture6 << std::endl <<
    std::endl << "----------" << std::endl
    << std::endl;

    //sets up seventh object
    std::cout << std::endl << "Use [c] for this "
    "file. ";
    PPM picture7;
    std::cin >> picture7;
    std::cout << std::endl << "Representation "
    "of seventh object:" << std::endl;
    std::cout << picture7 << std::endl <<
    std::endl << "----------" << std::endl
    << std::endl;

    //sets up eighth object
    std::cout << std::endl << "Use [c] for this "
    "file. ";
    PPM picture8;
    std::cin >> picture8;
    std::cout << std::endl << "Representation "
    "of eigth object:" << std::endl;
    std::cout << picture8 << std::endl <<
    std::endl << "----------" << std::endl
    << std::endl;

    //comparison of sizes. Else-if is used
    //instead of else to test the operator
    //being overloaded
    std::cout << "Comparison between first and "
    "second objects:" << std::endl;
    if(picture1 == picture2){
        std::cout << "The images match in "
        "size." << std::endl;
    }else if(picture1 != picture2){
        std::cout << "The images do not match "
        "in size." << std::endl;
    }
    if(picture1 < picture2){
        std::cout << "Image 1 is smaller than "
        "Image 2." << std::endl;
    }else if(picture1 > picture2){
        std::cout << "Image 1 is larger than "
        "Image 2." << std::endl;
    }else{
        std::cout << "Image 1 is neither "
        "larger nor smaller than Image 2."
         << std::endl;
    }
    if(picture1 <= picture2){
        std::cout << "Image 1 is smaller than "
        "or equal to Image 2." << std::endl;
    }else if(picture1 >= picture2){
        std::cout << "Image 1 is larger than "
        "or equal to Image 2." << std::endl;
    }

    // += test
    std::cout << "picture1 += picture 2 test:"
    << std::endl;
    picture1 += picture2;

    // -= test
    std::cout << "picture2 -= picture3 test:"
    << std::endl;
    picture2 -= picture3;

    //ppm4 = ppm1 + ppm5 test
    std::cout << "picture4 = picture1 + "
    "picture5 test:" << std::endl;
    picture4 = picture1 + picture5;

    //ppm6 = ppm1 - ppm5 test
    std::cout << "picture6 = picture1 + "
    "picture5 test:" << std::endl;
    picture6 = picture1 - picture5;

    //ppm *= double test
    std::cout << "picture1 *= .67 test: "
    << std::endl;
    picture1 *= .67;

    //ppm /= double test
    std::cout << "picture4 /= .33 test: "
    << std::endl;
    picture4 /= .33;

    //ppmNew = ppm * double test
    picture7 = picture1 * .67;

    //ppmNew = ppm / double test
    picture8 = picture1 / .67;
}
