#include "PPM.h"

//my functions and methods
void fileOpenTest(std::string filename){
    //preps the file to be read
    std::ifstream fin(filename, std::ios::binary);

    //checks if the file was opened correctly
    if(!fin){
        std::cout << std::endl << "Error "
        "encountered while opening " <<
        filename << ". File does not exist in "
        "this directory or you did not enter "
        "it correctly. Please restart the "
        "program." << std::endl;
    }else{
        std::cout << std::endl << filename <<
        " successfully opened." << std::endl <<
        std::endl;
    }

    fin.close();
}
int PPM::get_width(){

    unsigned int i;
    int word_count = 1;
    std::vector<char> word_two;

    //preps the file to be read
    std::ifstream fin(mFilename,
                      std::ios::binary);

    std::string line;
    std::string first_line;
    if (getline(fin, line)){
            first_line = line;
    }else{
        std::cout << "did not get first line";
    }

    //parses the first line and grabs the width
    for(i = 0; i < first_line.length(); i++){
        if(first_line[i] == ' '){
            if(first_line[i+1] != ' '){
                word_count++;
            }
        }
        if(word_count == 2){
            if(first_line[i] != ' '){
                word_two.push_back(first_line[i]);
            }
        }
    }

    fin.close();

    //casts the width to a string
    std::string width(word_two.begin(), word_two.end());

    //casts the width to an int
    mWidth = std::atoi(width.c_str());

    return mWidth;
}
int PPM::get_height(){

    unsigned int i;
    int word_count = 1;
    std::vector<char> word_three;

    //preps the file to be read
    std::ifstream fin(mFilename,
                      std::ios::binary);

    //grabs the first line
    std::string line;
    std::string first_line;
    if (getline(fin, line)) first_line = line;

    //parses the first line and grabs the height
    for(i = 0; i < first_line.length(); i++){
        if(first_line[i] == ' '){
            if(first_line[i+1] != ' '){
                word_count++;
            }
        }
        if(word_count == 3){
            if(first_line[i] != ' '){
                word_three.push_back(first_line[i]);
            }
        }
    }

    fin.close();

    //casts the height to a string
    std::string height(word_three.begin(), word_three.end());

    //casts the height to an int
    mHeight = std::atoi(height.c_str());

    return mHeight;
}
int PPM::get_maxcolor(){

    unsigned int i;
    int word_count = 1;
    std::vector<char> word_four;

    //preps the file to be read
    std::ifstream fin(mFilename,
                      std::ios::binary);

    //grabs the first line
    std::string line;
    std::string first_line;
    if (getline(fin, line)) first_line = line;

    //parses the first line and grabs the maxcolor
    for(i = 0; i < first_line.length(); i++){
        if(first_line[i] == ' '){
            if(first_line[i+1] != ' '){
                word_count++;
            }
        }
        if(word_count == 4){
            if(first_line[i] != ' '){
                word_four.push_back(first_line[i]);
            }
        }
    }

    fin.close();

    //casts the maxcolor to a string
    std::string maxcolor(word_four.begin(), word_four.end());

    //casts the maxcolor to an int
    mMaxColorValue = std::atoi(maxcolor.c_str());

    return mMaxColorValue;
}
std::string PPM::get_binary(){

    std::string line;

    std::ifstream fin(mFilename,
                      std::ios::binary);

    //getline() is called twice to start
    //reading from the second line
    getline(fin, line);
    getline(fin, line);
    char binary_part[line.size()+1];
    strcpy(binary_part, line.c_str());

    fin.close();

    mBinaryPart = line;

    return mBinaryPart;
}

//required methods
PPM::PPM(){
    mWidth = 0;
    mHeight = 0;
    mMaxColorValue = 0;
    mBinaryPart = "";
    std::cout << "Please enter a filename you "
    "would like to open or create (including "
    "extension):"
     " ";
    std::cin >> mFilename;
    std::cout << std::endl;
    //fileOpenTest(mFilename);
}
std::ostream& operator<<(std::ostream& oStream,
                         PPM& ppmObject){

    int width = ppmObject.get_width();
    int height = ppmObject.get_height();
    int maxColor = ppmObject.get_maxcolor();
    std::string binaryPart = ppmObject.get_binary();

    oStream << "P6" << ' ' << width << ' ' <<
    height << ' ' << maxColor << std::endl << binaryPart;

    return oStream;
}
std::istream& operator>>(std::istream& iStream,
                         PPM& ppmObject){

    char eorc;
    int acceptableAnswer = 0;

    //checks if user wants to use existing file
    //or create a new one.
    std::cout << "Are you writing to an "
    "[e]xisting file or [c]reating a new file "
    "(e/c): ";
    std::cin >> eorc;

    while(acceptableAnswer == 0){
        if(eorc =='c'){
            std::ofstream newFile(ppmObject.mFilename,
                                  std::ios::binary);
            std::cout << "File " << ppmObject.mFilename <<
            " has been created." << std::endl <<
            std::endl;
            newFile.close();
            acceptableAnswer = 1;
        }else if(eorc == 'e'){
            acceptableAnswer = 1;
            return iStream;
        }else{
            std::cout << "Please enter e or "
            "c: ";
            std::cin >> eorc;
        }
    }

    //preps file for input
    std::ofstream fout(ppmObject.mFilename,
                      std::ios::binary);

    fout << "P6 ";
    std::cout << "Enter width of image (in "
    "pixels): ";
    std::cin >> ppmObject.mWidth;
    fout << ppmObject.mWidth << ' ';
    std::cout << "Enter height of image (in "
    "pixels): ";
    std::cin >> ppmObject.mHeight;
    fout << ppmObject.mHeight << ' ';
    std::cout << "Enter max color value: ";
    std::cin >> ppmObject.mMaxColorValue;
    fout << ppmObject.mMaxColorValue;
    fout << "\r\n";
    std::cout << "Enter binary representation "
    "of image: ";
    std::cin >> ppmObject.mBinaryPart;
    fout << ppmObject.mBinaryPart;
    fout.close();

    return iStream;
}
bool PPM::operator==(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->get_width();
    ppm1Height = this->get_height();
    ppm2Width = rhs.get_width();
    ppm2Height = rhs.get_height();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total == ppm2Total;
}
bool PPM::operator!=(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->get_width();
    ppm1Height = this->get_height();
    ppm2Width = rhs.get_width();
    ppm2Height = rhs.get_height();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total != ppm2Total;
}
bool PPM::operator>(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->get_width();
    ppm1Height = this->get_height();
    ppm2Width = rhs.get_width();
    ppm2Height = rhs.get_height();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total > ppm2Total;
}
bool PPM::operator>=(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->get_width();
    ppm1Height = this->get_height();
    ppm2Width = rhs.get_width();
    ppm2Height = rhs.get_height();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total >= ppm2Total;
}
bool PPM::operator<(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->get_width();
    ppm1Height = this->get_height();
    ppm2Width = rhs.get_width();
    ppm2Height = rhs.get_height();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total < ppm2Total;
}
bool PPM::operator<=(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->get_width();
    ppm1Height = this->get_height();
    ppm2Width = rhs.get_width();
    ppm2Height = rhs.get_height();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total <= ppm2Total;
}
PPM PPM::operator+=(PPM& rhs){

    unsigned int i;
    std::string binaryString;

    //grabs the string representation of the
    //binary part of the images
    std::string binaryPart1 = this->get_binary();
    std::string binaryPart2 = rhs.get_binary();

    //this for loop does the following:
    //1.) parses through the binary strings by
    //    sets of 8 for both images,
    //2.) converts string representation of
    //    bytes to actual bytes,
    //3.) adds them together (taking into
    //    consideration max color val of
    //    Image 1),
    //4.) converts decimal back to binary,
    //5.) concatenates string of bytes
    for (i = 0; i < binaryPart1.size();
        i += 8){
            //1.)
            std::string sub1 =
            binaryPart1.substr(i, 8);
            std::string sub2 =
            binaryPart2.substr(i, 8);

            //2.)
            std::bitset<8> bitset1(sub1);
            std::bitset<8> bitset2(sub1);

            //3.)
            long maxColorValue =
            this->get_maxcolor();
            long sub1_long = bitset1.to_ulong();
            long sub2_long = bitset2.to_ulong();
            long total = sub1_long + sub2_long;

            if (total > maxColorValue){
                total = maxColorValue;
            }
            //4.)
            std::string backtobinary =
            std::bitset<8>(total).to_string();

            //5.)
            binaryString += backtobinary;
    }

    //ppm1 += ppm2
    this->mBinaryPart = binaryString;

    return *this;
}
PPM PPM::operator-=(PPM& rhs){

    unsigned int i;
    std::string binaryString;

    //grabs the string representation of the
    //binary part of the images
    std::string binaryPart1 = this->get_binary();
    std::string binaryPart2 = rhs.get_binary();

    //this for loop does the following:
    //1.) parses through the binary strings by
    //    sets of 8 for both images,
    //2.) converts string representation of
    //    bytes to actual bytes,
    //3.) subtracts them (taking into
    //    consideration min color val of
    //    0),
    //4.) converts decimal back to binary,
    //5.) concatenates string of bytes
    for (i = 0; i < binaryPart1.size();
        i += 8){
            //1.)
            std::string sub1 =
            binaryPart1.substr(i, 8);
            std::string sub2 =
            binaryPart2.substr(i, 8);

            //2.)
            std::bitset<8> bitset1(sub1);
            std::bitset<8> bitset2(sub1);

            //3.)
            long minColorValue = 0;
            long sub1_long = bitset1.to_ulong();
            long sub2_long = bitset2.to_ulong();
            long total = sub1_long - sub2_long;

            if (total < minColorValue){
                total = minColorValue;
            }
            //4.)
            std::string backtobinary =
            std::bitset<8>(total).to_string();

            //5.)
            binaryString += backtobinary;
    }

    //ppm1 += ppm2
    this->mBinaryPart = binaryString;

    return *this;
}
PPM PPM::operator+(PPM& rhs){

    unsigned int i;
    std::string binaryString;

    //creates the new PPM object to be returned
    PPM ppmObject;

    //grabs the mWidth of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    int width1 = this->mWidth;
    int width2 = rhs.mWidth;
    ppmObject.mWidth = width1 + width2;

    //grabs the mHeight of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    int height1 = this->mHeight;
    int height2 = rhs.mHeight;
    ppmObject.mHeight = height1 + height2;

    //grabs the max color value of both PPM
    //objects, adds them, then assigns them
    //to the new ppm object. If value is over
    //255, set it to 255
    int maxcolor1 = this->mMaxColorValue;
    int maxcolor2 = rhs.mMaxColorValue;
    int maxcolor = maxcolor1 + maxcolor2;
    if (maxcolor > 255){maxcolor = 255;}
    ppmObject.mMaxColorValue = maxcolor;

    //grabs the string representation of the
    //binary part of the images
    std::string binaryPart1 = this->get_binary();
    std::string binaryPart2 = rhs.get_binary();

    //this for loop does the following:
    //1.) parses through the binary strings by
    //    sets of 8 for both images,
    //2.) converts string representation of
    //    bytes to actual bytes,
    //3.) adds them together (taking into
    //    consideration max color val of
    //    Image 1),
    //4.) converts decimal back to binary,
    //5.) concatenates string of bytes
    for (i = 0; i < binaryPart1.size();
        i += 8){
            //1.)
            std::string sub1 =
            binaryPart1.substr(i, 8);
            std::string sub2 =
            binaryPart2.substr(i, 8);

            //2.)
            std::bitset<8> bitset1(sub1);
            std::bitset<8> bitset2(sub1);

            //3.)
            long maxColorValue =
            this->get_maxcolor();
            long sub1_long = bitset1.to_ulong();
            long sub2_long = bitset2.to_ulong();
            long total = sub1_long + sub2_long;

            if (total > maxColorValue){
                total = maxColorValue;
            }
            //4.)
            std::string backtobinary =
            std::bitset<8>(total).to_string();

            //5.)
            binaryString += backtobinary;
    }

    //ppm1 -= ppm2
    ppmObject.mBinaryPart = binaryString;

    return ppmObject;
}
PPM PPM::operator-(PPM& rhs){

    unsigned int i;
    std::string binaryString;

    //creates the new PPM object to be returned
    PPM ppmObject;

    //grabs the mWidth of both PPM objects,
    //subtracts them, then assigns them to the
    //new PPM object. If value is less than 0,
    //zero is assigned.
    int width1 = this->mWidth;
    int width2 = rhs.mWidth;
    int totalwidth = width1 - width2;
    if(totalwidth < 0){totalwidth = 0;}
    ppmObject.mWidth = totalwidth;

    //grabs the mHeight of both PPM objects,
    //subtracts them, then assigns them to the
    //new PPM object. If value is less than 0,
    //zero is assigned.
    int height1 = this->mHeight;
    int height2 = rhs.mHeight;
    int totalheight = height1 - height2;
    if(totalheight < 0){totalheight = 0;}
    ppmObject.mHeight = totalheight;

    //grabs the max color value of both PPM
    //objects, subtracts them, then assigns
    //them to the new ppm object. If value is
    //less than 0 255, set it to 0
    int maxcolor1 = this->mMaxColorValue;
    int maxcolor2 = rhs.mMaxColorValue;
    int maxcolor = maxcolor1 - maxcolor2;
    if (maxcolor < 0){maxcolor = 0;}
    ppmObject.mMaxColorValue = maxcolor;

    //grabs the string representation of the
    //binary part of the images
    std::string binaryPart1 = this->get_binary();
    std::string binaryPart2 = rhs.get_binary();

    //this for loop does the following:
    //1.) parses through the binary strings by
    //    sets of 8 for both images,
    //2.) converts string representation of
    //    bytes to actual bytes,
    //3.) subtracts them (taking into
    //    consideration min color val of
    //    0),
    //4.) converts decimal back to binary,
    //5.) concatenates string of bytes
    for (i = 0; i < binaryPart1.size();
        i += 8){
            //1.)
            std::string sub1 =
            binaryPart1.substr(i, 8);
            std::string sub2 =
            binaryPart2.substr(i, 8);

            //2.)
            std::bitset<8> bitset1(sub1);
            std::bitset<8> bitset2(sub1);

            //3.)
            long minColorValue = 0;
            long sub1_long = bitset1.to_ulong();
            long sub2_long = bitset2.to_ulong();
            long total = sub1_long - sub2_long;

            if (total < minColorValue){
                total = minColorValue;
            }
            //4.)
            std::string backtobinary =
            std::bitset<8>(total).to_string();

            //5.)
            binaryString += backtobinary;
    }

    //ppm3 = ppm1 - ppm2
    this->mBinaryPart = binaryString;

    return ppmObject;
}
PPM PPM::operator*=(const double& d){

    unsigned int i;
    std::string binaryString;

    //grabs the string representation of the
    //binary part of the image
    std::string binaryPart = this->get_binary();

    //this for loop does the following:
    //1.) parses through the binary strings by
    //    sets of 8 for both images,
    //2.) converts string representation of
    //    bytes to actual bytes,
    //3.) multiplies them together (taking into
    //    consideration max color val of
    //    Image 1),
    //4.) converts decimal back to binary,
    //5.) concatenates string of bytes
    for (i = 0; i < binaryPart.size();
        i += 8){
            //1.)
            std::string sub =
            binaryPart.substr(i, 8);

            //2.)
            std::bitset<8> bitset1(sub);

            //3.)
            long maxColorValue =
            this->get_maxcolor();
            long sub_long = bitset1.to_ulong();
            long total = sub_long * d;

            if (total > maxColorValue){
                total = maxColorValue;
            }else if(total < 0){
                total = 0;
            }
            //4.)
            std::string backtobinary =
            std::bitset<8>(total).to_string();

            //5.)
            binaryString += backtobinary;
    }

    //ppm1 *= ppm2
    this->mBinaryPart = binaryString;

    return *this;
}
PPM PPM::operator/=(const double& d){

    unsigned int i;
    std::string binaryString;

    //grabs the string representation of the
    //binary part of the image
    std::string binaryPart = this->get_binary();

    //this for loop does the following:
    //1.) parses through the binary strings by
    //    sets of 8 for both images,
    //2.) converts string representation of
    //    bytes to actual bytes,
    //3.) divides them together (taking into
    //    consideration max color val of
    //    Image 1 and 0),
    //4.) converts decimal back to binary,
    //5.) concatenates string of bytes
    for (i = 0; i < binaryPart.size();
        i += 8){
            //1.)
            std::string sub =
            binaryPart.substr(i, 8);

            //2.)
            std::bitset<8> bitset1(sub);

            //3.)
            long maxColorValue =
            this->get_maxcolor();
            long sub_long = bitset1.to_ulong();
            long total = sub_long / d;

            if (total > maxColorValue){
                total = maxColorValue;
            }else if(total < 0){
                total = 0;
            }
            //4.)
            std::string backtobinary =
            std::bitset<8>(total).to_string();

            //5.)
            binaryString += backtobinary;
    }

    //ppm1 /= ppm2
    this->mBinaryPart = binaryString;

    return *this;
}
PPM PPM::operator*(const double& d){

    unsigned int i;
    std::string binaryString;

    //creates the new PPM object to be returned
    PPM newPPM;

    //grabs the mWidth of the PPM object,
    //multiplies them, then assigns them to the
    //new PPM object
    int width = this->mWidth;
    newPPM.mWidth = width * d;

    //grabs the mHeight of the PPM object,
    //multiplies them, then assigns them to the
    //new PPM object
    int height = this->mHeight;
    newPPM.mHeight = height * d;

    //grabs the max color value of the PPM
    //object, multiplies them, then assigns
    //them to the new ppm object. If value is
    //over 255, set it to 255. If the value is
    //under 0, assign it to 0
    int maxcolorold = this->mMaxColorValue;
    int maxcolor = maxcolorold * d;
    if (maxcolor > 255){
            maxcolor = 255;
    }else if(maxcolor < 0){
        maxcolor = 0;
    }
    newPPM.mMaxColorValue = maxcolor;

    //grabs the string representation of the
    //binary part of the images
    std::string binaryPart =
    this->get_binary();

    //this for loop does the following:
    //1.) parses through the binary strings by
    //    sets of 8 for both images,
    //2.) converts string representation of
    //    bytes to actual bytes,
    //3.) multiplies them together (taking into
    //    consideration max color val of
    //    Image 1),
    //4.) converts decimal back to binary,
    //5.) concatenates string of bytes
    for (i = 0; i < binaryPart.size();
        i += 8){
            //1.)
            std::string sub =
            binaryPart.substr(i, 8);

            //2.)
            std::bitset<8> bitset1(sub);

            //3.)
            long maxColorValue =
            this->get_maxcolor();
            long sub_long = bitset1.to_ulong();
            long total = sub_long * d;

            if (total > maxColorValue){
                total = maxColorValue;
            }else if(total < 0){
                total = 0;
            }

            //4.)
            std::string backtobinary =
            std::bitset<8>(total).to_string();

            //5.)
            binaryString += backtobinary;
    }

    //ppm3 = ppm * double
    newPPM.mBinaryPart = binaryString;

    return newPPM;
}
PPM PPM::operator/(const double& d){

    unsigned int i;
    std::string binaryString;

    //creates the new PPM object to be returned
    PPM newPPM;

    //grabs the mWidth of the PPM object,
    //divides them, then assigns them to the
    //new PPM object
    int width = this->mWidth;
    newPPM.mWidth = width / d;

    //grabs the mHeight of the PPM object,
    //divides them, then assigns them to the
    //new PPM object
    int height = this->mHeight;
    newPPM.mHeight = height / d;

    //grabs the max color value of the PPM
    //object, divides them, then assigns
    //them to the new ppm object. If value is
    //over 255, set it to 255. If the value is
    //under 0, assign it to 0
    int maxcolorold = this->mMaxColorValue;
    int maxcolor = maxcolorold / d;
    if (maxcolor > 255){
            maxcolor = 255;
    }else if(maxcolor < 0){
        maxcolor = 0;
    }
    newPPM.mMaxColorValue = maxcolor;

    //grabs the string representation of the
    //binary part of the images
    std::string binaryPart =
    this->get_binary();

    //this for loop does the following:
    //1.) parses through the binary strings by
    //    sets of 8 for both images,
    //2.) converts string representation of
    //    bytes to actual bytes,
    //3.) divides them together (taking into
    //    consideration max color val of
    //    Image 1),
    //4.) converts decimal back to binary,
    //5.) concatenates string of bytes
    for (i = 0; i < binaryPart.size();
        i += 8){
            //1.)
            std::string sub =
            binaryPart.substr(i, 8);

            //2.)
            std::bitset<8> bitset1(sub);

            //3.)
            long maxColorValue =
            this->get_maxcolor();
            long sub_long = bitset1.to_ulong();
            long total = sub_long / d;

            if (total > maxColorValue){
                total = maxColorValue;
            }else if(total < 0){
                total = 0;
            }

            //4.)
            std::string backtobinary =
            std::bitset<8>(total).to_string();

            //5.)
            binaryString += backtobinary;
    }

    //ppm3 = ppm * double
    newPPM.mBinaryPart = binaryString;

    return newPPM;
}
