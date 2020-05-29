#include<iostream>
#include<sstream>
#include<cstdlib>
using namespace std ; 

template <class > class LinkedList ; 
template <class T>
class Node
{
    private:
        T elem ; 
        Node<T>* next ; 
    public:
        Node(T x) : next(NULL) , elem(x) {}
        friend class LinkedList<T>; 

};

template<class T> 
class LinkedList
{
    private:
    Node<T> * head ; 

    public:
        LinkedList() { head = NULL ; }
        ~LinkedList() { 
            delete head; 
            head= NULL; }
        void removefront() ; 
        void addfront(T x) ; 
        int size() ; 
        T front()  ; 
        bool empty() ; 
};

template<class T> //having a template class is better than having a stack class for int(to store values) and another stack for char
class Stack
{
    LinkedList<T> s ;
    public:
        void push(T x) { s.addfront(x); } 
        void pop() {s.removefront(); } 
        T top() {s.front(); }  
        bool empty() { s.empty(); } 
        int size() { s.size(); } 
};


bool isBoolOperator(char input) //to check if it is one of these operatorsStack
{ 
    return (input=='!' || input=='=' || input=='<' || input=='>' || input=='|' || input=='&' ); 
}

int transformWholeInteger(string input) 
{
    int a ; 
    string nb ; 

    for(int i=0; i<input.size(); i++)
    {
        if(isdigit(input[i])) nb+=input[i] ; 
        else break; 
    }
    stringstream(nb)>>a ;
    return a; 
}


template<class T>
void LinkedList<T>::addfront(T x) 
{
    Node<T>*v = new Node<T>(x) ; 
    v->next = head ; 
    head = v ; 
}
template<class T>
void LinkedList<T>::removefront() 
{
    Node<T>* v = head ; 
    head = head->next ; 
    delete v ; 
    v = NULL ; 
}
template<class T>
T LinkedList<T>::front()  { return head->elem; }

template<class T>
int LinkedList<T>::size()
{
    Node<T>*tmp = head ; 
    int nb = 0 ; 
    while(tmp!=NULL)
    {
        nb++ ; 
        tmp = tmp->next ; 
    }
    return nb ; 
}

template<class T>
bool LinkedList<T>::empty() { return head==NULL; }



void BooelanCheck() 
{
    cout<<"This program will evaluate boolean expressions and return a value of 'true' if the expression is true or 'false' if if false." ;
    cout<<" Your boolean expressions must be fully Parenthesized. Enter a blank line at the prompt to quit the program" <<endl<<endl ;
    cout<<"Enter the boolean expression to evaluate now: "<<endl ; 

    Stack<int> valuesStack;
    Stack<char> operatorsStack; 
    Stack<char> ParenthStack ;

    string line;

    while (getline(cin,line)) 
    {
        if (line==" ") break;

        else
        {
            for(int i = 0 ; i<line.size() ; i++)
            {
                if(line[i]=='(' ) 
                {
                ParenthStack.push((line[i]) )  ; 
                }
                else if(isdigit(line[i]) ) 
                {
                    int size=0 ;

                    for (int j=i; j<line.size(); j++)
                    {
                    if (isdigit(line[j])) size++;
                    else break ; 
                    }
                    
                    string s = line.substr(i, size) ; 
                    // cout<<"this is s:"<<s<<endl;
                    valuesStack.push(transformWholeInteger(s)) ; 
                    // cout<<"size: "<<size1 ;
                    i = i+ size - 1  ;  //-1 bcz Size starts from 1 and we want the index so we write -1
                }
                
                else if(isBoolOperator(line[i]))
                {
                    if(isBoolOperator(line[i+1])) // to check if it is &&, ||, ==
                    {
                        continue; 
                    }
                    operatorsStack.push(line[i]) ; //it will push only one &, or one |, or one = (= stands for equality not assignment operator bcz we are pushing 2nd = only)
                }   
                else if (line[i]==')' )
                {
                    if(ParenthStack.empty() )
                    {
                    cout<<"Error: no opening paranthesis"<<endl ; 
                    exit(1) ; 
                    }
                    else if(ParenthStack.top()=='(') //if we have open paranthesis before
                    { 
                        ParenthStack.pop() ; 
                        if(operatorsStack.empty()) 
                        {
                            if(valuesStack.empty()) 
                            {
                            cout<<"Error: no values in the stack"<<endl ; // error for something like () 
                            exit(1) ; 
                            }
                            
                        }
                        else if (!operatorsStack.empty()) 
                            {
                                char operator1 = operatorsStack.top() ; 
                                operatorsStack.pop() ; 
                                if(operator1=='!') 
                                {
                                    if(valuesStack.empty() )
                                    {
                                        cout<<"Error: No values are entered" ; //error for something like (!)
                                        exit(1) ; 
                                    }
                                    int val ; 
                                    val = valuesStack.top() ; 
                                    valuesStack.pop() ;
                                    if(val==0) 
                                    {
                                        valuesStack.push(1) ; 
                                    }

                                    else // for any number different than zero (!999)
                                    {
                                        valuesStack.push(0) ; 
                                    }
                                    
                                }
                                else if (operator1=='&') //if it is && (weonly pushed the second & so I didnot write  else if (operator1=='&&'))
                                {
                                    if(valuesStack.empty() || valuesStack.size()<2 ) //it is a binary operator, so size should be 2 and more
                                    {
                                        cout<<"Error: No entered values" ; 
                                        exit(1) ; 
                                    }
                                    int a = valuesStack.top(); 
                                    valuesStack.pop();

                                    int b = valuesStack.top(); 
                                    valuesStack.pop(); 
                                    
                                    if (a!=0 && b!=0 ) valuesStack.push(1) ; 
                                    else valuesStack.push(0) ; 
                                    
                                }
                                else if(operator1=='|') //for or operator
                                {
                                    if(valuesStack.empty() || valuesStack.size()<2 )
                                    {
                                        cout<<"Error: No entered values" ; 
                                        exit(1) ; 
                                    }
                                    int a = valuesStack.top(); 
                                    valuesStack.pop() ; 

                                    int b = valuesStack.top(); 
                                    valuesStack.pop() ; 

                                    if (a!=0 || b!=0) valuesStack.push(1) ; 
                                    else valuesStack.push(0) ; 
                                }
                                
                                else if (operator1=='=') //for == (equal operator)
                                {
                                    if(valuesStack.empty() || valuesStack.size()<2 )
                                    {
                                        cout<<"Error: No entered values" ; 
                                        exit(1) ; 
                                    }
                                    int a = valuesStack.top(); 
                                    valuesStack.pop() ; 
                                    int b = valuesStack.top(); 
                                    valuesStack.pop() ;

                                    if (a==b) valuesStack.push(1) ; 
                                    else valuesStack.push(0) ; 
                                }
                                else if (operator1=='>')
                                {
                                    if(valuesStack.empty() || valuesStack.size()<2 )
                                    {
                                        cout<<"Error: No entered values" ; 
                                        exit(1) ; 
                                    }
                                    int a = valuesStack.top(); 
                                    valuesStack.pop(); 

                                    int b = valuesStack.top();
                                    valuesStack.pop() ; 
                                    
                                    if ( b > a) valuesStack.push(1) ; 
                                    else valuesStack.push(0) ; 

                                }
                                else if (operator1=='<')
                                {
                                    if(valuesStack.empty() || valuesStack.size()<2 )
                                    {
                                        cout<<"Error: No entered values" ; 
                                        exit(1) ; 
                                    }
                                    int a = valuesStack.top(); 
                                    valuesStack.pop();
                                    
                                    int b = valuesStack.top(); 
                                    valuesStack.pop(); 

                                    if (b < a) valuesStack.push(1) ; 
                                    else valuesStack.push(0) ; 
                                }
                                
                            }
                            
                        }
                    }
                } //for loop exitted
        }
        
        if (valuesStack.size()!=1 || !operatorsStack.empty() || !ParenthStack.empty() )   
        {
            cout<<"Input is wrong, plz try again"<<endl ; 
             exit(1) ; 
        }

        if( (valuesStack.top())==0 ) cout<<"Your expression is FALSE"<<endl<<endl  ; 
        else if ((valuesStack.top())!=0) cout<<"Your expression is TRUE" <<endl<<endl ; 
        valuesStack.pop() ; 
        cout<<"Enter the boolean expression to evaluate now: "<<endl ; 
    } //while loop exitted
    
}


int main()
{
    BooelanCheck(); }
