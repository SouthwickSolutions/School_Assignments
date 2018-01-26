#ifndef COLORTABLE_H_INCLUDED
#define COLORTABLE_H_INCLUDED

#include <vector>
#include <cstdlib>
#include <random>
#include <time.h>

class Color{
    public:
        int mChannelsArray[3];

        Color();
        Color(const int& red,
              const int& green,
              const int& blue);

        int getRed() const;
        int getGreen() const;
        int getBlue() const;
        int getChannel(const int& channel) const;

        void setRed(const int& value);
        void setGreen(const int& value);
        void setBlue(const int& value);
        void setChannel(const int& channel, const int& value);

        void invert(const int& max_color_value);
        bool operator==(const Color& rhs) const;
};

class ColorTable{
    public:
        Color mBadColor;
        std::vector<Color> mVectorOfColors;
        bool mFirstIter;

        ColorTable(const size_t& num_color);
        size_t getNumberOfColors() const;

        void setNumberOfColors(const size_t& num_color);

        const Color& operator[](const int& i) const;
        Color& operator[](const int& i);

        void setRandomColor(const int& max_color_value,
                            const size_t& position );
        void insertGradient(const Color& color1,
                            const Color& color2,
                            const size_t& position1,
                            const size_t& position2);
};

#endif // COLORTABLE_H_INCLUDED
