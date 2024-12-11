#ifndef COLORUTILITIES_H
#define COLORUTILITIES_H

#include <cmath>
#include <vector>
#include <string>
#include <algorithm>


struct RGB {
    double r;
    double g;
    double b;
};


// CIELAB
struct LAB {
    double L;
    double a;
    double b;
};


void rgbToXyz(const RGB& rgb, double& x, double& y, double& z);
LAB xyzToLab(double x, double y, double z);
LAB rgbToLab(const RGB& rgb);

double deltaE_CIE76(const RGB& rgb1, const RGB& rgb2);
double deltaE_CIE94(const RGB& rgb1, const RGB& rgb2);
double deltaEuler(const RGB& rgb1, const RGB& rgb2);
std::vector<RGB> GetSortedByDeltaColors(const std::vector<RGB>& Colors, RGB Source, double(*function_delta)(const RGB&, const RGB&));
std::vector<RGB> GetSortedByDeltaColors_Eucledean(const std::vector<RGB>& Colors, RGB Source);
std::vector<RGB> GetSortedByDeltaColors_CIE76(const std::vector<RGB>& Colors, RGB Source);
std::vector<RGB> GetSortedByDeltaColors_CIE94(const std::vector<RGB>& Colors, RGB Source);


#endif