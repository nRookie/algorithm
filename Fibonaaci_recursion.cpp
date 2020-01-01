#include<stdio.h>

int Fibonacci(int n)
{
    if(n==1||n==2)
      return 1;
    else
      return Fibonacci(n-1)+Fibonacci(n-2);
}

int main()
{
  int n = 0;

  scanf("%d",&n);
  int result = Fibonacci(n);
  printf("F%d:%d\n",n,result);
  return 0;
}
