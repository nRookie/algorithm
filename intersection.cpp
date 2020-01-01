#include<iostream>

using namespace std;

class Line
{
public:

Line(double a, double b, double c) { this->a =a; this->b = b; this->c = c;}
double a;
double b;
double c;
};

class Point
{
public:

Point(double x,double y)
{
this->x = x;
this->y = y;
}
double x;
double y;
};

Point intersection(Line l1,Line l2)
{
 double det1 = -(l1.b*l2.c-l2.b*l1.c);
 double det2 = (l1.a*l2.c-l2.a*l1.c);
 double det3 = (l1.a*l2.b-l1.b*l2.a);
 double x = det1/det3;
 double y = det2/det3;
 
 Point p(x,y);
 return p;
}

int main()
{
   double a1,b1,c1;
   cin>>a1>>b1>>c1;

   Line l1(a1,b1,c1);
   double a2,b2,c2;
   cin>>a2>>b2>>c2;
   Line l2(a2,b2,c2);

   Point p = intersection(l1,l2);
   cout<<p.x<<" "<<p.y<<endl;
   return 0;
}
