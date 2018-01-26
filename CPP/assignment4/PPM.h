#ifndef PPM_H_INCLUDED
#define PPM_H_INCLUDED

#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <bitset>
#include <stdlib.h>

class PPM{
    public:
        PPM();
        std::string mMagicNumber;
        int mWidth;
        int mHeight;
        int mMaxColorValue;
        std::vector<unsigned char> binaryRepresentation;
        unsigned char* binRep;

        bool mEntered;

        int getWidth() const;
        int getHeight() const;
        int getMaxColorValue() const;
        int getChannel(const int& row, const int& column, const int& channel) const;

        void setWidth(const int& width);
        void setHeight(const int& height);
        void setMaxColorValue(const int& max_color_value);
        void setChannel(const int& row, const int& column, const int& channel, const int& value);

        bool operator==(PPM& rhs);
        bool operator!=(PPM& rhs);
        bool operator>(PPM& rhs);
        bool operator>=(PPM& rhs);
        bool operator<(PPM& rhs);
        bool operator<=(PPM& rhs);

        PPM operator+=(const PPM& rhs);
        PPM operator-=(const PPM& rhs);

        PPM operator+(const PPM& rhs) const;
        PPM operator-(const PPM& rhs) const;

        PPM operator*=(const double& d);
        PPM operator/=(const double& d);

        PPM operator*(const double& d) const;
        PPM operator/(const double& d) const;

};

std::istream& operator>>(std::istream& iStream, PPM& ppmObject);
std::ostream& operator<<(std::ostream& oStream, PPM& ppmObject);

#endif // PPM_H_INCLUDED
