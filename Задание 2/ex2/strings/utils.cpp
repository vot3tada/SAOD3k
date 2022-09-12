void Copy(char* d, char* s)
{
    for (char* pd = d, *ps = s; *pd++ = *ps++;);
}

int Len(const char* s)
{
    int i = 0;
    while (*(s + i))
        i++;
    return i;
}

int Compare(const char* s, const char* t)
{
    const char* p, *d;
    for (p = s, d = t; (*d == *p) && *p; d++, p++);
    return *p - *d;
}