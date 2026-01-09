#include <iostream>
using namespace std;


template <typename T>
class Stack {
private:
    T* arr;        
    int top;       
    int size;      

public:
 
    Stack(int s) {
        size = s;
        arr = new T[size];
        top = -1;  
    }


    void push(T value) {
        if (top == size - 1) {
            cout << "Stack Overflow" << endl;
            return;
        }
        arr[++top] = value;
    }


    T pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return T();   
        }
        return arr[top--];
    }

    
    bool isEmpty() {
        return (top == -1);
    }

    
    ~Stack() {
        delete[] arr;
    }
};

int main() {

    
    Stack<int> intStack(5);
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    cout << "Popping elements from int stack:" << endl;
    while (!intStack.isEmpty()) {
        cout << intStack.pop() << endl;
    }


    Stack<double> doubleStack(5);
    doubleStack.push(1.5);
    doubleStack.push(2.5);
    doubleStack.push(3.5);

    cout << "\nPopping elements from double stack:" << endl;
    while (!doubleStack.isEmpty()) {
        cout << doubleStack.pop() << endl;
    }

    return 0;
}
