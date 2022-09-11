void Swap(int& a, int& b)
{
    //По-человечески
   /*
   int c = b;
   b = a;
   a = c;
   */

   //Сташно не по-человечески
    int* pa = &a, * pb = &b;
    int c = *pb;
    *pb = *pa;
    *pa = c;
}