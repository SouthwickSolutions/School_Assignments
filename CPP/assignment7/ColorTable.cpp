#include "ColorTable.h"

Color::Color(){
    mChannelsArray[0] = 0;
    mChannelsArray[1] = 0;
    mChannelsArray[2] = 0;
}

Color::Color(const int& red,
              const int& green,
              const int& blue){
    mChannelsArray[0] = red;
    mChannelsArray[1] = green;
    mChannelsArray[2] = blue;
}

int Color::getRed() const{
    return mChannelsArray[0];
}

int Color::getGreen() const{
    return mChannelsArray[1];
}

int Color::getBlue() const{
    return mChannelsArray[2];
}

int Color::getChannel(const int& channel) const{
    if(channel < 0 || channel > 2){return -1;}
    else{return mChannelsArray[channel];}
}

void Color::setRed(const int& value){
    mChannelsArray[0] = value;
}

void Color::setGreen(const int& value){
    mChannelsArray[1] = value;
}

void Color::setBlue(const int& value){
    mChannelsArray[2] = value;
}

void Color::setChannel(const int& channel, const int& value){
    if(channel < 0 || channel > 2){return;}
    else{mChannelsArray[channel] = value;}
}

void Color::invert( const int& max_color_value ){
    int r, g, b;

    if((getRed() < max_color_value) && (getGreen() < max_color_value) && (getBlue() < max_color_value)){
        r = max_color_value - getRed();
        g = max_color_value - getGreen();
        b = max_color_value - getBlue();

        setRed(r);
        setGreen(g);
        setBlue(b);
    }
}

bool Color::operator==(const Color& rhs) const{
    bool rValue;

    if(this->getRed() == rhs.getRed() &&
       this->getGreen() == rhs.getGreen() &&
       this->getBlue() == rhs.getBlue()){
        rValue = true;
    }else{
        rValue = false;
    }
    return rValue;
}










ColorTable::ColorTable(const size_t& num_color){
    mVectorOfColors.resize(num_color);
    mBadColor = Color(-1, -1, -1);
    mFirstIter = true;
}

size_t ColorTable::getNumberOfColors() const{
    return mVectorOfColors.size();
}

void ColorTable::setNumberOfColors(const size_t& num_color){
    mVectorOfColors.resize(num_color);
}

const Color& ColorTable::operator[](const int& i) const{
    size_t j = i;

    if(i < 0 || j >= getNumberOfColors()){
        return mBadColor;
    }else{
        return mVectorOfColors[i];
    }
}

Color& ColorTable::operator[](const int& i){
    size_t j = i;

    if(i < 0 || j >= getNumberOfColors()){
        return mBadColor;
    }else{
        return mVectorOfColors[i];
    }
}

void ColorTable::setRandomColor(const int& max_color_value,
                                const size_t& position){
    if(position > getNumberOfColors() ||
       max_color_value < 0){return;}

    if(mFirstIter){
        mFirstIter = false;
        srand(time(NULL));
    }

    int randNum;
    Color ColorObject= mVectorOfColors[position];

    randNum = rand()%(max_color_value+1);
    ColorObject.setRed(randNum);
    randNum = rand()%(max_color_value+1);
    ColorObject.setGreen(randNum);
    randNum = rand()%(max_color_value+1);
    ColorObject.setBlue(randNum);

    mVectorOfColors[position] = ColorObject;
}

void ColorTable::insertGradient(const Color& color1,
                                const Color& color2,
                                const size_t& position1,
                                const size_t& position2){
    int i;
    int deltaR = 0;
    int deltaG = 0;
    int deltaB = 0;
    int positionDiff = 0;
    int deltaIncreaseR = 0;
    int deltaIncreaseG = 0;
    int deltaIncreaseB = 0;

    if ( position2 <= position1 ){}
    else{
        positionDiff = (position2 - position1) + 1;
        deltaIncreaseR = (color2.getRed() - color1.getRed()) / (positionDiff - 1);
        deltaIncreaseG = (color2.getGreen() - color1.getGreen()) / (positionDiff - 1);
        deltaIncreaseB = (color2.getBlue() - color1.getBlue()) / (positionDiff - 1);

        for (i=0; i < positionDiff; i++){

            deltaR = (color1.getRed() + (i * deltaIncreaseR));
            mVectorOfColors[position1 + i].setRed(deltaR);

            deltaG = (color1.getGreen() + (i * deltaIncreaseG));
            mVectorOfColors[position1 + i].setGreen(deltaG);

            deltaB = (color1.getBlue() + (i * deltaIncreaseB));
            mVectorOfColors[position1 + i].setBlue(deltaB);
       }
    }
 }
