//
// Created by Q on 2023/5/11.
//
#include "myqueue.h"
using namespace std;
int main(){
    wen::queue<int>isqueue;
    isqueue.push(1);
    isqueue.push(3);
    isqueue.push(5);
    isqueue.push(7);

    cout << isqueue.size() << endl;
    cout << isqueue.front() << endl;

    isqueue.pop();cout << isqueue.front() << endl;
    isqueue.pop();cout << isqueue.front() << endl;
    isqueue.pop();cout << isqueue.front() << endl;
    cout << isqueue.size() << endl;

    return 0;
}