//
// Created by Q on 2023/5/11.
//

#include "stack.h"
#include "../../my_config.h"
#include "../list_container/myList.h"
#include "vector"
using namespace std;
int main(){
    wen::stack<int,wen::myList<int>>istack;
    istack.push(1);
    istack.push(3);
    istack.push(5);
    istack.push(7);

    cout<<istack.size()<<endl;
    cout<<istack.top()<<endl;

    istack.pop();cout<<istack.top()<<endl;
    istack.pop();cout<<istack.top()<<endl;
    istack.pop();cout<<istack.top()<<endl;
    cout<<istack.size()<<endl;


    return 0;
}
