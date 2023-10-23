#include "polyndrom.h"
#include <iostream>
using namespace std;
int main()
{
    Polyndrom p1;
    p1.add_element(3, 100);
    p1.add_element(4,5);
    p1.add_element(5,8);
    p1.echo();
    Polyndrom p2(p1);
    p2.echo();
    p1.add_element(0, 0);
    p1.echo();
    cout<<p1.getsum(1) << endl;
    Polyndrom p3;
    p3.add_element(1,2);
    p3.add_element(4,1);
    p3.echo();
    cout << p3.getsum(2) << endl;
    Polyndrom p5;
    p5 = p1 + p2;
    p5.echo();

}
