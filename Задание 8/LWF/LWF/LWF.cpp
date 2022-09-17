#include <iostream>
#include "WF.h"
#include "RWF.h"

int Distance(const WF& wf, const RWF& rwf)
{
    if (!(wf.Rows() - rwf.Rows())) throw std::logic_error("");
    return 0;
}

int main()
{
    char s[] = "on";
    char t[] = "ono";
    char s1[] = "";
    char s2[] = "";
    for (int i = 0; i < strlen(s)/2; i++)
    {
        s1[i] = s[i];
    }
    for (int i = strlen(s) / 2; i < strlen(s); i++)
    {
        s2[i - strlen(s) / 2] = s[i];
    }
    WF wf(4,3,s1,t);
    wf.Show();
    std::cout << "-----------------------" << std::endl;
    RWF rwf(4, 3, s2, t);
    rwf.Show();
}

