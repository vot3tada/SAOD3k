void Swap(int& a, int& b)
{
    //��-�����������
   /*
   int c = b;
   int b = a;
   a = c;
   */

   //������ �� ��-�����������
    int* pa = &a, * pb = &b;
    int c = *pb;
    *pb = *pa;
    *pa = c;
}