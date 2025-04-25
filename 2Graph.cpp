#include <iostream>
#include <cstring>
#define MAX 100
using namespace std;

class node
{
    int id;
    char name[20];
    node *next;
    friend class graph;
};

class graph
{
    node *head[20];
    int n;

public:
    graph(int n1)
    {
        n = n1;
        for (int i = 0; i < n; i++)
        {
            head[i] = nullptr;
        }
    }
    void create();
    void display();
    void non_dft(int vertex);
    void non_bft(int vertex);
    void rec_dft(int vertex);
};
class mystack
{
public:
    int top;
    int stack[MAX];

public:
    mystack()
    {
        top = -1;
    }
    friend class graph;
    int isfull()
    {
        if (top == MAX - 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int isempty()
    {
        if (top == -1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void push(int x)
    {
        if (isfull())
        {
            cout << "Stack is full" << endl;
        }
        else
        {
            top++;
            stack[top] = x;
        }
    }
    int pop()
    {
        if (isempty())
        {
            cout << "stack is empty" << endl;
            return -1;
        }
        else
        {
            int s = stack[top];
            top--;
            return s;
        }
    }
};

class myqueue
{
    int front, rear;
    int queue[MAX];

public:
    myqueue()
    {
        front = -1;
        rear = -1;
    }
    friend class graph;
    int isfull()
    {
        if (rear == MAX - 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int isempty()
    {
        if (front == -1 || rear == -1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void insert(int x)
    {
        if (isfull())
        {
            cout << "queue is full" << endl;
        }
        else
        {
            if (front == -1)
            {
                front = 0;
            }
            rear++;
            queue[rear] = x;
        }
    }
    int Delete()
    {
        if (isempty())
        {
            cout << "queue is already empty" << endl;
            return -1;
        }
        else
        {
            int q = queue[front];
            front++;
            return q;
        }
    }
};

void graph ::create()
{
    char ch;
    for (int i = 0; i < n; i++)
    {
        head[i] = new node();
        cout << "enter the name at " << i << " : " << endl;
        cin >> head[i]->name;
        head[i]->id = i;
        head[i]->next = NULL;
    }
    for (int i = 0; i < n; i++)
    {
        node *temp = head[i];
        cout << "does user " << i << " have any friend (y-yes/n-no) : " << endl;
        cin >> ch;
        while (ch == 'y')
        {
            node *curr = new node();
            cout << "accept friend id " << endl;
            cin >> curr->id;
            if (curr->id < 0 && curr->id >= n)
            {
                cout << "invalid id ! " << endl;
                delete curr;
                continue;
            }
            strcpy(curr->name, head[curr->id]->name);
            curr->next = NULL;
            temp->next = curr;
            temp = curr;
            cout << "if more friend press y(yes) otherwise n(no) : " << endl;
            cin >> ch;
        }
    }
}

void graph ::display()
{
    node *temp;
    for (int i = 0; i < n; i++)
    {
        temp = head[i];
        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                cout << temp->id << " " << temp->name << endl;
            }
            else
            {
                cout << temp->id << " " << temp->name << " -> ";
            }
            temp = temp->next;
        }
    }
}

void graph::non_dft(int vertex)
{
    int visited[100] = {0};
    node *temp;
    mystack s;
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    s.push(vertex);
    while (s.isempty() == 0)
    {
        int v = s.pop();
        if (visited[v] == 0)
        {
            cout << head[v]->id << " -> " << head[v]->name << endl;
            visited[v] = 1;
        }
        temp = head[v]->next;
        while (temp != NULL)
        {
            if (visited[temp->id] == 0)
            {
                s.push(temp->id);
            }

            temp = temp->next;
        }
    }
}
void graph ::non_bft(int vertex)
{
    int visited[100] = {0};
    node *temp;
    myqueue q;
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    q.insert(vertex);
    while (q.isempty() == 0)
    {
        int v = q.Delete();
        if (visited[v] == 0)
        {
            cout << head[v]->id << " -> " << head[v]->name << endl;
            visited[v] = 1;
        }
        temp = head[v]->next;
        while (temp != NULL)
        {
            if (visited[temp->id] == 0)
            {
                q.insert(temp->id);
            }
            temp = temp->next;
        }
    }
}
void graph :: rec_dft(int vertex){
    static int visited[100]={0};
    visited[vertex]= 1;
    cout<<head[vertex]->id<<" -> "<<head[vertex]->name<<endl;
    node *temp = head[vertex]->next;
    while(temp != NULL){
        if(visited[temp->id]==0){
            rec_dft(temp->id);
        }
        temp =   temp->next;
    }

}
int main()
{
    int n;
    int vertex;
    int choice;
    cout << "enter the number : " << endl;
    cin >> n;
    graph g(n);
    g.create();
    cout << "Normal Traversal : " << endl;
    g.display();
    cout<<endl;
    cout << "Enter what you want to see " << endl;
    cout << " 1.Non Recursive DFT \n 2.Non Recursive BFT \n 3.Recursive DFT" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "enter the vertex you want to see DFT : ";
        cin >> vertex;
        g.non_dft(vertex);
        break;
    case 2:
        cout << "enter the vertex you want to see BFT : ";
        cin >> vertex;
        g.non_bft(vertex);
    case 3:
        cout << "enter the vertex you want to see Recursive DFT : ";
        cin >> vertex;
        g.rec_dft(vertex);
    default:
        break;
    }

    return 0;
}