#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;
struct Stack
{
    char number;
    Stack* prev;
    Stack* next;
};
struct Num
{
    string number;
    Num* prev;
    Num* next;
};
int prior(char a)
{
    switch (a)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case ')':
        return 4;
    case '(':
        return 0;
    default:
        return -1;
    }
}
class N
{
public:
    Stack* head = 0;
    Stack* tail = 0;
    Num* headN = 0;
    Num* tailN = 0;
    Num* str(string num)
    {
        Num* str = new Num();
        str->number = num;
        str->prev = nullptr;
        str->next = nullptr;

        if (tailN == nullptr) {
            headN = str;
            tailN = str;
        }
        else {
            tailN->next = str;
            str->prev = tailN;
            tailN = str;
        }
        return headN;
    }
    Stack* stack1(char num)
    {
        Stack* stack1 = new Stack();
        stack1->number = num;
        stack1->prev = nullptr;
        stack1->next = nullptr;

        if (head == nullptr) {
            head = stack1;
            tail = stack1;
        }
        else {
            tail->next = stack1;
            stack1->prev = tail;
            tail = stack1;
        }
        return head;
    }
    void del() {
        while (head != NULL)
        {
            if (head == NULL) return;

            Stack* ptr = head->next;
            if (ptr != NULL)
                ptr->prev = NULL;
            else
                tail = NULL;

            delete head;
            head = ptr;
        }
    }

    void delNum() {
        while (headN != NULL)
        {
            if (headN == NULL) return;

            Num* ptr = headN->next;
            if (ptr != NULL)
                ptr->prev = NULL;
            else
                tailN = NULL;

            delete headN;
            headN = ptr;
        }
    }
    void check(char a) {
        string sy;
        Stack* curr = tail;

        if (a == '(') {
            stack1(a);  // Push '(' to the stack
        }
        else if (a == ')') {
            while (curr != nullptr && curr->number != '(') {
                sy += curr->number;
                str(sy);
                sy.clear();
                Stack* nodeToDelete = curr;
                curr = curr->prev;

                // Deleting node
                if (nodeToDelete->prev != nullptr) {
                    nodeToDelete->prev->next = nodeToDelete->next;
                }
                else {
                    head = nodeToDelete->next;
                }
                if (nodeToDelete->next != nullptr) {
                    nodeToDelete->next->prev = nodeToDelete->prev;
                }
                else {
                    tail = nodeToDelete->prev;
                }
                delete nodeToDelete;
            }
            // Remove the '(' from the stack
            if (curr != nullptr && curr->number == '(') {
                Stack* nodeToDelete = curr;
                curr = curr->prev;
                if (nodeToDelete->prev != nullptr) {
                    nodeToDelete->prev->next = nodeToDelete->next;
                }
                else {
                    head = nodeToDelete->next;
                }
                if (nodeToDelete->next != nullptr) {
                    nodeToDelete->next->prev = nodeToDelete->prev;
                }
                else {
                    tail = nodeToDelete->prev;
                }
                delete nodeToDelete;
            }
        }
        else if (getLastValue(curr) == 0 || prior(a) > getLastValue(curr)) {
            stack1(a);
        }
        else {
            while (curr != nullptr && prior(a) <= getLastValue(curr)) {
                sy += curr->number;
                str(sy);
                sy.clear();
                Stack* nodeToDelete = curr;
                curr = curr->prev;

                // Deleting node
                if (nodeToDelete->prev != nullptr) {
                    nodeToDelete->prev->next = nodeToDelete->next;
                }
                else {
                    head = nodeToDelete->next;
                }
                if (nodeToDelete->next != nullptr) {
                    nodeToDelete->next->prev = nodeToDelete->prev;
                }
                else {
                    tail = nodeToDelete->prev;
                }
                delete nodeToDelete;
            }
            stack1(a);
        }
    }
    void empty1()
    {
        string sy1;
        Stack* curr = tail;
        while (curr != nullptr)
        {
            sy1 += curr->number;
            str(sy1);
            sy1.clear();
            curr = curr->prev;
        }
        del();
        return;
    }

    int getLastValue(Stack* curr) {
        if (curr == nullptr) {
            return 0;
        }
        return prior(curr->number);
    }
    double operate(double a, double b, const string& op) {
        if (op == "+") {
            return a + b;
        }
        else if (op == "-") {
            return a - b;
        }
        else if (op == "*") {
            return a * b;
        }
        else if (op == "/") {

            return a / b;
        }
        else if (op == "^")
            return pow(a, b);
        return 0;
    }
    void deleteNode(Num*& head, Num* node) {
        if (node->prev) {
            node->prev->next = node->next;
        }
        else {
            head = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        }
        delete node;
    }
    void cal()
    {
        Num* curr = headN;

        while (curr != nullptr) {
            if (curr->number == "+" || curr->number == "-" || curr->number == "*" || curr->number == "/" || curr->number == "^") {
                if (curr->prev != nullptr && curr->prev->prev != nullptr) {
                    double a = stod(curr->prev->prev->number);
                    double b = stod(curr->prev->number);
                    double result = operate(a, b, curr->number);
                    curr->number = to_string(result);
                    deleteNode(headN, curr->prev);
                    deleteNode(headN, curr->prev);
                }
            }
            curr = curr->next;
        }
        cout << "Decision:\t";
        coutInfoN();
        cout << endl;
        delNum();
    }
    void coutInfoN() {
        for (Num* curr = headN; curr != 0; curr = curr->next)
        {
            if (headN == 0)
                cout << "enpty";
            cout << curr->number << " ";
        }
    }

};
void transfomationPost(string a, int lenthString)
{
    N tr;
    string numbers;
    cout << a << "\n";
    for (int i = 0; i <= lenthString; i++)
    {
        if (isdigit(a[i]) || a[i] == '.')
        {
            numbers += a[i];
        }
        if ((a[i]) == '/' || a[i] == '*' || a[i] == '-' || a[i] == '+' || a[i] == '^' || i == lenthString)
        {
            if (!numbers.empty()) {
                tr.str(numbers);
                numbers.clear();
            }
            if (i != lenthString) {
                tr.check(a[i]);
            }
        }
    }
    tr.empty1();
    tr.coutInfoN();
    tr.del();
    tr.cal();
    tr.delNum();
}
void dArray()
{
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    int* array = new int[size];

    cout << "Enter " << size << " numbers:\n";
    for (int i = 0; i < size; ++i) {
        cout << "Element " << i + 1 << ": ";
        cin >> array[i];
    }

    cout << "You entered: ";
    for (int i = 0; i < size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
    delete[] array;
}
int menue()
{
    N tr;
    string a;
    cout << "Please, enter your example : \t";
    cin >> a;
    if (a.find("/0") != string::npos) {
        cout << "Error. - \"/0\" try again\n";
        menue();
    }
    const string ops = "+-*/";
    for (size_t i = 0; i < a.size() - 1; ++i) {
        if (ops.find(a[i]) != string::npos && ops.find(a[i + 1]) != string::npos) {
            cout << "Error. - The sing repeats! try again\n";
            menue();
        }
    }
    // далее мы избавляемся от косинусов и синусов, ПЕРЕВОДЯ ИХ В ЧИСЛО
    string action;
    string expression;
    string convert;
    double result;
    double pi = 3.14159265358979323846;
    for (int i = 0; i < a.size(); i++)
    {
        if (isdigit(a[i]))
        {
            convert += a[i];
        }
        if ((a[i]) == '/' || a[i] == '*' || a[i] == '-' || a[i] == '+' || a[i] == '^')
        {
            convert += a[i];
        }
        if (isalpha(a[i]))
        {
            while (a[i] != '(')
            {
                action += a[i];
                i++;
            }
            i++;
            while (a[i] != ')')
            {
                expression += a[i];
                i++;
            }
            double number = stod(expression);
            number = number * pi / 180;

            if (action == "sin")
            {
                result = sin(number);
            }
            else if (action == "cos")
            {
                result = cos(number);
            }
            action.clear();
            expression.clear();
            convert += to_string(result);
        }
    }
    int lenthString = convert.size();
    bool exite = true;
    int points;
    int b;
    do
    {
        system("cls");
        cout << "1 - Convrt OPZ\n" << "2 - dynamic array\n" << "3 - Exit\n" << "Please choose a point of menue:\t";
        cin >> points;
        switch (points) {
        case 1:
            cout << a << endl;
            transfomationPost(convert, lenthString);
            system("pause");
            break;
        case 2:
            system("cls");
            dArray();
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "If you want exite please enter \"0\"\nIf you want continue please enter \"1\"\n";
            cin >> b;
            if (b == 0)
                exit(0);
            if (b == 1)
            {
                a.clear();
                menue();
            }
            break;
        }
    } while (exite);
}
int main() {
    menue();
    return 0;
}