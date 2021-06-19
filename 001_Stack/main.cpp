#include <iostream>
using namespace std;

template<class T> class Stack {

public:
    static const int StackSize = 30;
    int Top;
    T *values;

    Stack(){
        cout << " Class Stack() Start " << endl;
        Top = -1;
    }
    ~Stack(){
        cout << " Class Stack() End" << endl;
        delete [] values;
    }

    void push(T input){
        cout << "input =" << input << endl;
    }

    void pop(){

    }

    void size(){

    }

};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
