//
// Created by Q on 2023/6/1.
//
#include "iostream"
#include "vector"

using namespace std;
class Shape{
public:virtual void display()=0;
};
class Rect:public Shape{
public:virtual void display(){cout<<"Rect";}
};
class Circle:public Shape{
public:virtual void display(){cout<<"Circle";}
};
class Square:public Rect{
public:virtual void display(){cout<<"Square";}
};
int main(){
    vector<Shape*>V;
    V.push_back(new Rect);
    V.push_back(new Circle);
    V.push_back(new Square);
    V.push_back(new Circle);
    V.push_back(new Rect);


    return 0;
}