#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <math.h>

void boxInfo(const std::vector<double>& array, int e)
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
    std::cout << "min:\t" << min << std::endl;
    std::cout << "lq:\t" << Q1 << std::endl;
    std::cout << "median:\t" << median << std::endl;
    std::cout << "mean:\t" << mean << std::endl;
    std::cout << "stddev:\t" << stddev << std::endl;
    std::cout << "uq:\t" << Q3 << std::endl;
    std::cout << "max:\t" << max << std::endl;
    std::cout << "out:\t";
    for (int i = 0; i < out.size(); std::cout << out[i++] << " ");
    std::cout << std::endl;
}


int main()
{
    //std::vector<double> x = { 0.0855298042e+00, 1.4513241053e+00,1.3237277269e+00,1.0128350258e+00,1.4122089148e+00,6.5826654434e-01,2.0795986652e+00,1.0230206251e+00,1.4231411219e+00,1.1091691256e+00,1.7714337111e+00,1.3986129761e+00,1.0640757084e+00,1.4216910601e+00,1.2402026653e+00 };
    std::vector<double> x = { 71.4543, 
        70.8654,
        70.8306,
        71.143,
        73.9102,
        73.1449,
        70.8669,
        72.6236,
        72.9664,
        72.1965 };
    //for (auto i : x) std::cout << i << "\t";
    boxInfo(x, 2);
}
