#include<stdio.h>

int Fib[1000000] = {0};

void Fibonacci(int n)
{
  for (int i=0;i<n;i++)
  {
      if(i==0||i==1)
      Fib[i] = i;
      else
      {
        Fib[i] = Fib[i-1]+Fib[i-2];
      }
  }

}

int main()
{
  int n = 0;

  scanf("%d",&n);

  printf("F%d:%d",n,Fib[n]);
  return 0;
}


