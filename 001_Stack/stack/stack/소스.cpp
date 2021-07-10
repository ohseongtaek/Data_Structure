#include <iostream>
using namespace std;

template<class T> class Stack {

public:
    static const int StackSize = 30;
    int top;
    T* values = new T;

    Stack() {
        cout << "=========Class Stack() Start " << endl;
        top = -1;
    }
    ~Stack() {
        cout << "=========Class Stack() End" << endl;
        delete[] values;
    }

    void push(T input) {
        if (!isFull()) {
            values[++top] = input;
        }
        else {
            cout << "Stack is Full!!! " << endl;
        }
    }

    void pop() {
        if (!empty()) {
            top--;
        }
        else {
            cout << "Stack is Empty!!! " << endl;
        }
    }

    T Top() {
        if (!empty()) {
            return values[top];
        }
        else {
            return NULL;
        }
    }

    bool empty(){
        if (top < 0) {
            return true;
        }
        else {
            return false;
        }

    }

    int size() {
        return top + 1;
    }

    bool isFull() {
        if ((top + 1) == top) {
            return true;
        }
        else {
            return false;
        }
    }
};

int main()
{
    Stack<int> st;


    cout << "00. Stack Empty After Genertaion = " << st.empty() << endl;
    cout << "01. Stack Size AFter Genertaion = " << st.size() << endl;

    st.push(10);
    cout << "02. Stack Push After Push 10 = " << st.size() << endl;
    
    cout << "03. Stack Top After Push = " << st.Top() << endl;

    cout << "04. Stack Empty AFter Push = " << st.empty() << endl;

    st.pop();
    cout << "05. Stack Size After Pop = " << st.size() << endl;
    

    return 0;
}
