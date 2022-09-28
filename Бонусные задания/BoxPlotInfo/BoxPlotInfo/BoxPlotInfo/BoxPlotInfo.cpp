#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <math.h>

void boxInfo(std::vector<double> array, int e)
{
    std::vector<double> arrayCopy;
    for (int i = 0; i < array.size(); i++)
        arrayCopy.push_back(array[i]);
    double min;
    double lq;
    double median;
    double mean;
    double stddev;
    double uq;
    double max;
    std::sort(arrayCopy.begin(), arrayCopy.end());
    std::cout.setf(std::ios::scientific);
    std::cout.precision(e);
    //for (auto i : arrayCopy) std::cout << i << "\t";
    //std::cout << std::endl;



    //min & max
    min = arrayCopy[1.5];
    max = arrayCopy[array.size() - 1.5];

    //квартили
    for (double i = 0; i < array.size() - 1; i++)
    {
        if (i / (array.size() - 1) <= 1.0 / 4 && (i + 1) / (array.size() - 1) >= 1.0/4)
        {
            lq = array[i] + ((1.0 / 4) - (i / (array.size() - 1))) / ((i + 1) / (array.size() - 1) - (i / (array.size() - 1))) * (array[i + 1] - array[i]);
        }
        if (i / (array.size() - 1) <= 3.0 / 4 && (i + 1) / (array.size() - 1) >= 3.0 / 4)
        {
            uq = array[i] + ((3.0 / 4) - (i / (array.size() - 1))) / ((i + 1) / (array.size() - 1) - (i / (array.size() - 1))) * (array[i + 1] - array[i]);
            break;
        }
    }
    
    
    //median
    if (arrayCopy.size() % 2) median = arrayCopy[arrayCopy.size() / 2];
    else median = (arrayCopy[arrayCopy.size() / 2] + arrayCopy[arrayCopy.size() / 2 + 1]) / 2;
    
    
    //mean
    mean = 0;
    for (auto i : array) mean += i;
    mean /= array.size();
    //std::cout << std::accumulate(array.begin(), array.end(), 0) << "\n"; фигню считает, возвращает целое.

    //stddev
    stddev = 0;
    for (auto i : array) stddev += (i - mean) * (i - mean);
    stddev /= array.size() - 1;
    stddev = sqrt(stddev);
    



    std::cout << "min:\t" << min << std::endl;
    std::cout << "lq:\t" << lq << std::endl;
    std::cout << "median:\t" << median << std::endl;
    std::cout << "mean:\t" << mean << std::endl;
    std::cout << "stddev:\t" << stddev << std::endl;
    std::cout << "uq:\t" << uq << std::endl;
    std::cout << "max:\t" << max << std::endl;

    //out
    std::cout << "out:\t";
    for (int i = 0; i < static_cast<int>(1.5); i++) std::cout << arrayCopy[i] << " " << arrayCopy[array.size() - 1 - i] << " ";
}


int main()
{
    std::vector<double> x = { 0.0855298042e+00, 1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00 };
    //for (auto i : x) std::cout << i << "\t";
    boxInfo(x, 2);
}
