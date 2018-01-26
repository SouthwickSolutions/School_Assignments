#ifndef JULIASET_H_INCLUDED
#define JULIASET_H_INCLUDED

#include <vector>

class JuliaSet{
    public:
        int    mWidth;
        int    mHeight;
        double mXMin;
        double mXMax;
        double mYMin;
        double mYMax;
        double mA;
        double mB;
        int    mMaxEscCount;

        std::vector<int> mEscapeValues;

        JuliaSet();

        int    getWidth()          const;
        int    getHeight()         const;
        double getMinX()           const;
        double getMaxX()           const;
        double getMinY()           const;
        double getMaxY()           const;
        double getA()              const;
        double getB()              const;
        int    getMaxEscapeCount() const;

        void setPixelSize(const int& width, const int& height);
        void setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y);
        void setParameters(const double& a, const double& b);
        void setMaxEscapeCount(const int& count );

        double calculateDeltaX() const;
        double calculateDeltaY() const;
        double calculatePlaneXFromPixelColumn(const int& column) const;
        double calculatePlaneYFromPixelRow(const int& row) const;
        void   calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const;

        void calculateNextPoint(const double x0, const double y0, double &x1, double &y1) const;
        int  calculatePlaneEscapeCount(const double& x0, const double& y0) const;
        int  calculatePixelEscapeCount(const int& row, const int& column) const;
        void calculateAllEscapeCounts();
        int  getPixelEscapeCount(const int& row, const int& column) const;

};

double pythagoreanTheorum(double x, double y);
#endif // JULIASET_H_INCLUDED
