#ifndef PPM_H_INCLUDED
#define PPM_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <bitset>

class PPM{

    public:
        PPM();
        std::string mFilename;
        int mWidth;
        int mHeight;
        int mMaxColorValue;
        std::string mBinaryPart;
        bool operator==(PPM& rhs);
        bool operator!=(PPM& rhs);
        bool operator>(PPM& rhs);
        bool operator>=(PPM& rhs);
        bool operator<(PPM& rhs);
        bool operator<=(PPM& rhs);
        PPM operator+=(PPM& rhs);
        PPM operator-=(PPM& rhs);
        PPM operator+(PPM& rhs);
        PPM operator-(PPM& rhs);
        PPM operator*=(const double& d);
        PPM operator/=(const double& d);
        PPM operator*(const double& d);
        PPM operator/(const double& d);
        int get_width();
        int get_height();
        int get_maxcolor();
        std::string get_binary();
};

std::ostream& operator<<(std::ostream& oStream,
                         PPM& ppmObject);
std::istream& operator>>(std::istream& iStream,
                         PPM& ppmObject);
void fileOpenTest(std::string filename);

#endif // PPM_H_INCLUDED
