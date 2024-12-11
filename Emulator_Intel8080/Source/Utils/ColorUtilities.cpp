#include "ColorUtilities.h"



void rgbToXyz(const RGB& rgb, double& x, double& y, double& z) {
    double r = rgb.r / 255.0;
    double g = rgb.g / 255.0;
    double b = rgb.b / 255.0;

    r = (r > 0.04045) ? std::pow((r + 0.055) / 1.055, 2.4) : (r / 12.92);
    g = (g > 0.04045) ? std::pow((g + 0.055) / 1.055, 2.4) : (g / 12.92);
    b = (b > 0.04045) ? std::pow((b + 0.055) / 1.055, 2.4) : (b / 12.92);

    x = r * 0.4124564 + g * 0.3575761 + b * 0.1804375;
    y = r * 0.2126729 + g * 0.7151522 + b * 0.0721750;
    z = r * 0.0193339 + g * 0.1191920 + b * 0.9503041;
}
LAB xyzToLab(double x, double y, double z) {
    double refX = 95.047;
    double refY = 100.000;
    double refZ = 108.883;

    x /= refX;
    y /= refY;
    z /= refZ;

    x = (x > 0.008856) ? std::pow(x, 1.0 / 3.0) : (7.787 * x) + (16.0 / 116.0);
    y = (y > 0.008856) ? std::pow(y, 1.0 / 3.0) : (7.787 * y) + (16.0 / 116.0);
    z = (z > 0.008856) ? std::pow(z, 1.0 / 3.0) : (7.787 * z) + (16.0 / 116.0);

    LAB lab;
    lab.L = (116.0 * y) - 16.0;
    lab.a = 500.0 * (x - y);
    lab.b = 200.0 * (y - z);

    return lab;
}
LAB rgbToLab(const RGB& rgb) {
    double x, y, z;
    rgbToXyz(rgb, x, y, z);
    return xyzToLab(x, y, z);
}

double deltaE_CIE76(const RGB& rgb1, const RGB& rgb2) {
    LAB lab1 = rgbToLab(rgb1);
    LAB lab2 = rgbToLab(rgb2);

    return std::sqrt(std::pow(lab1.L - lab2.L, 2) + std::pow(lab1.a - lab2.a, 2) + std::pow(lab1.b - lab2.b, 2));
}
double deltaE_CIE94(const RGB& rgb1, const RGB& rgb2) {

    LAB lab1 = rgbToLab(rgb1);
    LAB lab2 = rgbToLab(rgb2);


    double kL = 1.0, kC = 1.0, kH = 1.0;
    double K1 = 0.045, K2 = 0.015;

    double deltaL = lab1.L - lab2.L;
    double L_bar = (lab1.L + lab2.L) / 2.0;

    double C1 = std::sqrt(std::pow(lab1.a, 2) + std::pow(lab1.b, 2));
    double C2 = std::sqrt(std::pow(lab2.a, 2) + std::pow(lab2.b, 2));
    double C_bar = (C1 + C2) / 2.0;

    double deltaC = C1 - C2;

    double deltaA = lab1.a - lab2.a;
    double deltaB = lab1.b - lab2.b;
    double deltaH = std::sqrt(std::pow(deltaA, 2) + std::pow(deltaB, 2) - std::pow(deltaC, 2));

    double SL = 1.0;
    double SC = 1.0 + K1 * C_bar;
    double SH = 1.0 + K2 * C_bar;

    double deltaE94 = std::sqrt(std::pow(deltaL / (kL * SL), 2) +
        std::pow(deltaC / (kC * SC), 2) +
        std::pow(deltaH / (kH * SH), 2));

    return deltaE94;
}
double deltaEuler(const RGB& rgb1, const RGB& rgb2) {
    return std::sqrt(std::pow(rgb1.r - rgb2.r, 2) + std::pow(rgb1.g - rgb2.g, 2) + std::pow(rgb1.b - rgb2.b, 2));
}


std::vector<RGB> GetSortedByDeltaColors(const std::vector<RGB>& Colors, RGB Source, double(*function_delta)(const RGB&, const RGB&)) {

    std::vector<std::pair<double, RGB>> delta_and_colors;

    for (int i = 0; i < Colors.size(); i++) {
        delta_and_colors.push_back({ function_delta(Colors[i], Source), Colors[i] });
    }

    std::sort(delta_and_colors.begin(), delta_and_colors.end(), [](std::pair<double, RGB> a, std::pair<double, RGB> b)
        {
            return a.first < b.first;
        });

    std::vector<RGB>result(delta_and_colors.size());
    for (int i = 0; i < delta_and_colors.size(); i++) {
        result[i] = (delta_and_colors[i].second);
    }
    return result;
}

std::vector<RGB> GetSortedByDeltaColors_Eucledean(const std::vector<RGB>& Colors, RGB Source) {
    return GetSortedByDeltaColors(Colors, Source, deltaEuler);
}
std::vector<RGB> GetSortedByDeltaColors_CIE76(const std::vector<RGB>& Colors, RGB Source) {
    return GetSortedByDeltaColors(Colors, Source, deltaE_CIE76);
}
std::vector<RGB> GetSortedByDeltaColors_CIE94(const std::vector<RGB>& Colors, RGB Source) {
    return GetSortedByDeltaColors(Colors, Source, deltaE_CIE94);
}

