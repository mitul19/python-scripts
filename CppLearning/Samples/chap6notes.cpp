#include <iostream>
using namespace std;
/*
User defined data types:
	Struct 
		Mix of multiple datatype 
		we cant print entire struct 
    class 
        have functions 
        have access specifiers like private, public and protected.
    pointers
        (*) to declare to pointer with datatype like (int *p1) [this is integer datatype pointer ]
        Pointer points to references in memory 
        (&) used to reference the data location for by pointer 
    Linked List
        list of struct or classes that include a pointer 
        this pointer points to the next struct or class
        (->) arrow operator when you're using pointers in reference to population data


*/
struct student
{
    string name;
    float GPA;
};

// class examples and constructors 
class bankact 
{
    private: 
    float balance;
    
    public: 
    void BankAccount(); 
    void Deposit(float);
    void WithDrawl(float);
    float getBalance();

};
void bankact::BankAccount() 
{
    balance = 0.00;
}
float bankact::getBalance() 
{
    return balance;
}
void bankact::Deposit(float dep) 
{
    balance = balance + dep;
}
void bankact::WithDrawl(float wit) 
{
    balance = balance - wit;
}

// linked list struct 
struct Node
{
    int data;
    Node *link;
};
//dont use Typedef unless its required 
typedef Node* nodePtr;

//fun prototype
void insert(nodePtr& head, int data);


int main ()
{   
    student Teacher;
    Teacher.name = "Mr Mitul";
    Teacher.GPA = 3.6;
    cout << Teacher.GPA << endl << Teacher.name << endl;

    // we can assign array of struct as well 
    student firstPeriod[10];
    firstPeriod[0].name = "Tom";
    firstPeriod[0].GPA = 4.0;
    cout << firstPeriod[0].name << ": GPA --> " << firstPeriod[0].GPA << endl;
    
    bankact savings;
    bankact current;

    cout << "Savings Balance: " << savings.getBalance()<< endl;
    cout << "Current Balance: " << current.getBalance()<< endl;
    
    savings.Deposit(100);
    current.Deposit(100);
   
    cout << "Savings Balance: " << savings.getBalance()<< endl;
    cout << "Current Balance: " << current.getBalance()<< endl;
    
    savings.WithDrawl(24.3);
    current.WithDrawl(0.5);

    cout << "Savings Balance: " << savings.getBalance()<< endl;
    cout << "Current Balance: " << current.getBalance()<< endl;
    
    cout << "Pointer examples" << endl;

    int v1 =0;
    int *p1;
    p1 = &v1;
    cout << v1 << " and pointer is  " << *p1 << endl; 
    *p1 = 42;
    cout << v1 << " and pointer is  " << *p1 << endl; 

    cout << "Linked List Example: " << endl;

    nodePtr head;
    head = new Node;
    head->data = 20;
    head->link = NULL;

    // just printing one node 
    cout << head->data << endl;

    //now insert few items 
    insert(head, 30);
    insert(head, 40);
    insert(head, 50);

    //creating new tem node pointer assign it to head so we can refer.
    nodePtr tmp;
    tmp = head;

    while(tmp != NULL) 
    {
        cout << tmp->data << endl; //print 
        tmp = tmp->link; // move pointer to next node
    }

    return 0;
}

void insert(nodePtr& head, int data)
{
   nodePtr tempPtr;  // new node pointer 
   tempPtr = new Node;  // create new Node 
   tempPtr->data = data;
   tempPtr->link = head;  // linking it to Head
   head = tempPtr;  // moving head to start at the list 
}