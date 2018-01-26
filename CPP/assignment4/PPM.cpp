#include "PPM.h"

PPM::PPM(){
    mWidth = 0;
    mHeight = 0;
    mMaxColorValue = 0;
    mEntered = false;
}

int PPM::getWidth() const{
    return mWidth;
}

int PPM::getHeight() const{
    return mHeight;
}

int PPM::getMaxColorValue() const{
    return mMaxColorValue;
}

int PPM::getChannel(const int& row, const int& column, const int& channel) const{
    int rValue;

    if(mHeight <=0 || mWidth <= 0 || row < 0 || row >= mHeight || column < 0 || column >= mWidth || channel < 0 || channel > 2){
        rValue = -1;
    }else{
        int maxChannelsPerRow = mWidth * 3;
        int firstChannelOfRow = (maxChannelsPerRow * row);
        int chosenChannel = firstChannelOfRow + ((column*3) + channel);
        rValue = binRep[chosenChannel];
    }
    return rValue;
}

void PPM::setWidth(const int& width){
    if (width >= 0){
        mWidth = width;
      }
}

void PPM::setHeight(const int& height){
    if (height >= 0){
        mHeight = height;
    }
}

void PPM::setMaxColorValue(const int& max_color_value){
    if (max_color_value >= 0 && max_color_value <= 255){
        mMaxColorValue = max_color_value;
    }
}

void PPM::setChannel(const int& row, const int& column, const int& channel, const int& value){
    if( mHeight <=0 || mWidth <= 0 || row < 0 || row >= mHeight || column < 0 || column >= mWidth || channel < 0 || channel > 2 || value < 0 || value > 255){
        return;
    }else{
        if(mEntered != true){
            size_t size = mWidth * mHeight * 3;
            binRep = new unsigned char[size];
            mEntered = true;
        }
        int maxChannelsPerRow = mWidth * 3;
        int firstChannelOfRow = (maxChannelsPerRow * row);
        int chosenChannel = firstChannelOfRow + ((column*3) + channel);
        binRep[chosenChannel] = value;
    }
}

std::istream& operator>>(std::istream& iStream, PPM& ppmObject){
    iStream >> ppmObject.mMagicNumber;
    iStream >> ppmObject.mWidth >> ppmObject.mHeight >> ppmObject.mMaxColorValue;
    iStream.get(); //skips the trailing white space

    size_t size = ppmObject.mWidth * ppmObject.mHeight * 3;

        if(ppmObject.mEntered != true){
            size_t size = ppmObject.mWidth * ppmObject.mHeight * 3;
            ppmObject.binRep = new unsigned char[size];
            ppmObject.mEntered = true;
        }
    iStream.read((char *)ppmObject.binRep, size);

    unsigned int i;
    for(i = 0; i < size; i++){
        std::bitset<8> byte (ppmObject.binRep[i]);
        long long_byte = byte.to_ulong();
        ppmObject.binaryRepresentation.push_back(long_byte);
        //std::cout << long_byte << ' ';
        //std::cout << byte.to_string() << ' ';
    }

    return iStream;
}

std::ostream& operator<<(std::ostream& oStream, PPM& ppmObject){
    int width = ppmObject.getWidth();
    int height = ppmObject.getHeight();
    int maxColor = ppmObject.getMaxColorValue();

    oStream << "P6" << ' ' << width << ' ' << height << ' ' << maxColor << '\n';

    size_t size = width * height * 3;
    //ppmObject.binRep = new char[size];

    oStream.write((char *)ppmObject.binRep, size);
    return oStream;
}

bool PPM::operator==(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->getWidth();
    ppm1Height = this->getHeight();
    ppm2Width = rhs.getWidth();
    ppm2Height = rhs.getHeight();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total == ppm2Total;
}

bool PPM::operator!=(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->getWidth();
    ppm1Height = this->getHeight();
    ppm2Width = rhs.getWidth();
    ppm2Height = rhs.getHeight();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total != ppm2Total;
}

bool PPM::operator>(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->getWidth();
    ppm1Height = this->getHeight();
    ppm2Width = rhs.getWidth();
    ppm2Height = rhs.getHeight();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total > ppm2Total;
}

bool PPM::operator>=(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->getWidth();
    ppm1Height = this->getHeight();
    ppm2Width = rhs.getWidth();
    ppm2Height = rhs.getHeight();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total >= ppm2Total;
}

bool PPM::operator<(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->getWidth();
    ppm1Height = this->getHeight();
    ppm2Width = rhs.getWidth();
    ppm2Height = rhs.getHeight();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total < ppm2Total;
}

bool PPM::operator<=(PPM& rhs){
    int ppm1Width, ppm2Width;
    int ppm1Height, ppm2Height;
    int ppm1Total, ppm2Total;

    //grabs the total pixels
    ppm1Width = this->getWidth();
    ppm1Height = this->getHeight();
    ppm2Width = rhs.getWidth();
    ppm2Height = rhs.getHeight();

    ppm1Total = ppm1Width * ppm1Height;
    ppm2Total = ppm2Width * ppm2Height;

    return ppm1Total <= ppm2Total;
}

PPM PPM::operator+=(const PPM& rhs){
    unsigned char* lhsBin = this->binRep;
    unsigned char* rhsBin = rhs.binRep;

    unsigned int i;
    for(i = 0; i< sizeof(lhsBin); i++){
        long currentBin = lhsBin[i] + rhsBin[i];
        if(currentBin > this->getMaxColorValue()){
            currentBin = (int) this->getMaxColorValue();
        }
        lhsBin[i] = currentBin;
    }
    return *this;
}

PPM PPM::operator-=(const PPM& rhs){
    unsigned char* lhsBin = this->binRep;
    unsigned char* rhsBin = rhs.binRep;

    unsigned int i;
    for(i = 0; i< sizeof(lhsBin); i++){
        long currentBin = lhsBin[i] - rhsBin[i];
        if(currentBin < 0){
            currentBin = (int) 0;
        }
        lhsBin[i] = currentBin;
    }
    return *this;
}

PPM PPM::operator+(const PPM& rhs) const{

    //creates the new PPM object to be returned
    PPM ppmObject;

    //grabs the mWidth of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    int width1 = this->getWidth();
    int width2 = rhs.getWidth();
    ppmObject.setWidth(width1 + width2);

    //grabs the mHeight of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    int height1 = this->getHeight();
    int height2 = rhs.getHeight();
    ppmObject.setHeight(height1 + height2);

    //grabs the max color value of both PPM
    //objects, adds them, then assigns them
    //to the new ppm object. If value is over
    //255, set it to 255
    int maxcolor1 = this->getMaxColorValue();
    int maxcolor2 = rhs.getMaxColorValue();
    int maxcolor = maxcolor1 + maxcolor2;
    if (maxcolor > 255){maxcolor = 255;}
    ppmObject.setMaxColorValue(maxcolor);


    unsigned char* lhsBin = this->binRep;
    unsigned char* rhsBin = rhs.binRep;

    unsigned int i;
    for(i = 0; i< sizeof(lhsBin); i++){
        long currentBin = lhsBin[i] + rhsBin[i];
        if(currentBin > this->getMaxColorValue()){
            currentBin = (int) this->getMaxColorValue();
        }
        lhsBin[i] = currentBin;
    }
    ppmObject.binRep = lhsBin;

    return ppmObject;
}

PPM PPM::operator-(const PPM& rhs) const{

    //creates the new PPM object to be returned
    PPM ppmObject;

    //grabs the mWidth of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    int width1 = this->getWidth();
    int width2 = rhs.getWidth();
    int totalwidth = width1 - width2;
    if(totalwidth <= 0){totalwidth = 1;}
    ppmObject.setWidth(totalwidth);

    //grabs the mHeight of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    int height1 = this->getHeight();
    int height2 = rhs.getHeight();
    int totalheight = height1 - height2;
    if(totalheight <= 0){totalheight = 1;}
    ppmObject.setHeight(totalheight);

    //grabs the max color value of both PPM
    //objects, adds them, then assigns them
    //to the new ppm object. If value is over
    //255, set it to 255
    int maxcolor1 = this->getMaxColorValue();
    int maxcolor2 = rhs.getMaxColorValue();
    int maxcolor = maxcolor1 - maxcolor2;
    if (maxcolor <= 0){maxcolor = 255;}
    ppmObject.setMaxColorValue(maxcolor);


    unsigned char* lhsBin = this->binRep;
    unsigned char* rhsBin = rhs.binRep;

    unsigned int i;
    for(i = 0; i< sizeof(lhsBin); i++){
        long currentBin = lhsBin[i] - rhsBin[i];
        if(currentBin < 0){
            currentBin = (int) 0;
        }
        lhsBin[i] = currentBin;
    }
    ppmObject.binRep = lhsBin;

    return ppmObject;
}

PPM PPM::operator*=(const double& d){
    unsigned char* lhsBin = this->binRep;

    unsigned int i;
    for(i = 0; i< sizeof(lhsBin); i++){
        long currentBin = lhsBin[i] * d;
        if(currentBin > this->getMaxColorValue()){
            currentBin = (int) this->getMaxColorValue();
        }else if(currentBin < 0){currentBin = 0;}
        lhsBin[i] = (int) currentBin;
    }
    return *this;
}

PPM PPM::operator/=(const double& d){
    unsigned char* lhsBin = this->binRep;

    unsigned int i;
    for(i = 0; i< sizeof(lhsBin); i++){
        long currentBin = lhsBin[i] / d;
        if(currentBin > this->getMaxColorValue()){
            currentBin = (int) this->getMaxColorValue();
        }else if(currentBin < 0){currentBin = 0;}
        lhsBin[i] = (int)currentBin;
    }
    return *this;
}

PPM PPM::operator*(const double& d) const{

    //creates the new PPM object to be returned
    PPM ppmObject;

    //grabs the mWidth of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    int width1 = this->getWidth();
    int totalwidth = width1 * d;
    if(totalwidth <= 0){totalwidth = 1;}
    ppmObject.setWidth(totalwidth);

    //grabs the mHeight of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    int height1 = this->getHeight();
    int totalheight = height1 * d;
    if(totalheight <= 0){totalheight = 1;}
    ppmObject.setHeight(totalheight);

    //grabs the max color value of both PPM
    //objects, adds them, then assigns them
    //to the new ppm object. If value is over
    //255, set it to 255
    int maxcolor1 = this->getMaxColorValue();
    int maxcolor = maxcolor1 * d;
    if (maxcolor > 255){maxcolor = 255;}
    if (maxcolor <= 0){maxcolor = 0;}
    ppmObject.setMaxColorValue(maxcolor);

    unsigned char* lhsBin = this->binRep;

    unsigned int i;
    for(i = 0; i< sizeof(lhsBin); i++){
        long currentBin = lhsBin[i] * d;
        if(currentBin > this->getMaxColorValue()){
            currentBin = (int) this->getMaxColorValue();
        }else if(currentBin < 0){
            currentBin = 0;
        }
        lhsBin[i] = currentBin;
    }
    ppmObject.binRep = lhsBin;

    return ppmObject;
}

PPM PPM::operator/(const double& d) const{

    //creates the new PPM object to be returned
    PPM ppmObject;

    //grabs the mWidth of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    double width1 = this->getWidth();
    double totalwidth = width1 / d;
    if(totalwidth <= 0){totalwidth = 1;}
    if(totalwidth > width1){totalwidth = width1;}
    ppmObject.setWidth(totalwidth);

    //grabs the mHeight of both PPM objects,
    //adds them, then assigns them to the new
    //PPM object
    int height1 = this->getHeight();
    int totalheight = height1 / d;
    if(totalheight <= 0){totalheight = 1;}
    if(totalheight > width1){totalheight = height1;}
    ppmObject.setHeight(totalheight);

    //grabs the max color value of both PPM
    //objects, adds them, then assigns them
    //to the new ppm object. If value is over
    //255, set it to 255
    int maxcolor1 = this->getMaxColorValue();
    int maxcolor = maxcolor1 / d;
    if (maxcolor <= 0 || maxcolor > 255){maxcolor = 255;}
    ppmObject.setMaxColorValue(maxcolor);


    unsigned char* lhsBin = this->binRep;

    unsigned int i;
    for(i = 0; i< sizeof(lhsBin); i++){
        long currentBin = lhsBin[i] / d;
        if(currentBin < 0){
            currentBin = (int) 0;
        }
        if(currentBin > 255){
            currentBin = 255;
        }
        lhsBin[i] = currentBin;
    }
    ppmObject.binRep = lhsBin;

    return ppmObject;
}
