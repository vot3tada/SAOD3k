#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <math.h>
#include <tuple>

std::tuple<double, double, double, double, double, double, double, std::vector<double>> boxInfo(const std::vector<double>& array, int e)
{
    std::vector<double> arrayCopy(array);
    double k = 1.5,
        min,
        Q1,
        median,
        mean,
        stddev,
        Q3,
        max;
    std::vector<double> out;
    std::sort(arrayCopy.begin(), arrayCopy.end());
    std::cout.setf(std::ios::scientific);
    std::cout.precision(e);
    //Квартили
    Q1 = arrayCopy[0.25 * arrayCopy.size()];
    Q3 = arrayCopy[0.75 * arrayCopy.size()];
    //Границы
    min = Q1 - k * (Q3 - Q1);
    max = Q3 + k * (Q3 - Q1);
    //Медиана
    if (arrayCopy.size() % 2) median = arrayCopy[arrayCopy.size() / 2];
    else median = (arrayCopy[arrayCopy.size() / 2] + arrayCopy[arrayCopy.size() / 2 + 1]) / 2;
    //Среднее
    mean = std::accumulate(array.begin(), array.end(), 0.0) / array.size();
    //Среднее квадратичное
    stddev = 0;
    for (auto i : array) stddev += (i - mean) * (i - mean);
    stddev /= array.size() - 1;
    stddev = sqrt(stddev);
    //out и границы
    for (auto i : arrayCopy)
    {
        if (i > min)
        {
            min = i;
            break;
        }
        out.push_back(i);
    }
    for (int i = array.size() - 1; i >= 0 ; i--)
    {
        if (arrayCopy[i] < max)
        {
            max = arrayCopy[i];
            break;
        }
        out.push_back(arrayCopy[i]);
    }
    std::tuple<double, double, double, double, double, double, double, std::vector<double>> tuple(min,Q1,median,mean,stddev,Q3,max,out);
    return tuple;
}


int main()
{
    //std::vector<double> x = { 0.0855298042e+00, 1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00 };
    std::vector<double> x = { 
        6.51706,
        6.62028,
        6.64584,
        6.64686,
        6.66331,
        6.71154,
        6.66711,
        6.69527,
        6.7197,
        6.736 };
    //for (auto i : x) std::cout << i << "\t";
    auto a = boxInfo(x, 2);
    std::cout << "min:\t" << std::get<0>(a) << std::endl;
    std::cout << "lq:\t" << std::get<1>(a) << std::endl;
    std::cout << "median:\t" << std::get<2>(a) << std::endl;
    std::cout << "mean:\t" << std::get<3>(a) << std::endl;
    std::cout << "stddev:\t" << std::get<4>(a) << std::endl;
    std::cout << "uq:\t" << std::get<5>(a) << std::endl;
    std::cout << "max:\t" << std::get<6>(a) << std::endl;
    std::cout << "out:\t";
    auto out = std::get<7>(a);
    for (int i = 0; i < out.size(); std::cout << out[i++] << " ");
    std::cout << std::endl;
}
