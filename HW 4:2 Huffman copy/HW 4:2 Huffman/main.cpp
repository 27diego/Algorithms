#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node
{
    char letter;
    int frequency;
    Node* left;
    Node* right;
    
public:
    Node(char letter, int frequency)
    {
        this->letter = letter;
        this->frequency = frequency;
        this->left = nullptr;
        this->right = nullptr;
    }
    
};


class priorityHeap
{
    vector<Node*> data;
    
private:
    void swap(int i, int j);
    void heapifyUp(int idx);
    void heapifyDown(int i);

    
public://declaring functions within class
    Node *extractMin();
    void insert(Node *val);
    int size();
    bool empty() { return size() == 0;}
    void print() {
        for (auto n : data) {
            cout << n->letter <<":"<< n->frequency<< endl;
        }
    }
    Node* pop() { return extractMin();}
    void push(Node* val) { insert(val);}
    vector<Node*> getData(){return data;}
};


void priorityHeap::swap(int x, int y)
{
    Node *temp = data[y];
    data[y] = data[x];
    data[x] = temp;
}
void priorityHeap::heapifyUp(int end)
{
    if(end>0)
    {
        int parent = (end-1)/2;
        if(data[parent]->frequency>data[end]->frequency)
        {
            swap(end, parent);
            heapifyUp(parent);
        }
    }
}

void priorityHeap::heapifyDown(int begining)
{
    int left = 2 * begining + 1;
    int right = 2 * begining + 2;
    int holder = begining;
    
    if(left<data.size() && data[left]->frequency<data[holder]->frequency)
    {
        holder = left;
    }
    if(right<data.size() && data[right]->frequency<data[holder]->frequency)
    {
        holder = right;
    }
    
    if(holder != begining)
    {
        swap(holder, begining);
        heapifyDown(holder);
    }
}

Node *priorityHeap::extractMin()
{
    swap(0, data.size()-1);
    Node *temp = data.back();
    data.pop_back();
    
    heapifyDown(0);
    
    return temp;
}

void priorityHeap::insert(Node* node)
{
    data.push_back(node);
    heapifyUp(data.size()-1);
}

int priorityHeap::size()
{
    return data.size();
}

struct node_cmp{
    bool operator() (Node* a, Node* b)
    {
        return a->frequency<b->frequency;
    }
};

class HuffTree{
    Node* root;
public:
    HuffTree()
    {
        root = nullptr;
    }
    void insert(vector<Node*> letters)
    {
        std::priority_queue<Node*, std::vector<Node*>, node_cmp()> q;

        for(int x=0;x<letters.size();x++)
        {
            q.push(letters[x]);
        }
        
    }
    
};



int main() {
    priorityHeap pq;
//    pq.insert(new Node('A', 4));
//    pq.insert(new Node('B', 2));
//    pq.insert(new Node('C', 1));
//    pq.insert(new Node('D', 7));
//    pq.insert(new Node('E', 7));
//    pq.insert(new Node('F', 3));
//    pq.insert(new Node('O', 1));
//    pq.insert(new Node('S', 2));
//    pq.insert(new Node('T', 1));
//    pq.insert(new Node('V', 1));
//    pq.insert(new Node(' ', 7));
    
    string sentence = "i love computer science";
    unordered_map<char,int> letters;
    unordered_map<char, int>::iterator crawler;

    for(int x=0;x<sentence.length();x++)
    {
        letters.insert(make_pair(sentence[x], 0));
    }
    for(int x=0;x<sentence.length();x++)
    {
        for(crawler = letters.begin();crawler!=letters.end();crawler++)
        {
            if(sentence[x]==crawler->first)
            {
                crawler->second++;
            }
        }
    }
    for(crawler = letters.begin();crawler!=letters.end();crawler++)
    {
        pq.insert(new Node(crawler->first,crawler->second));
    }
    
    
    
   pq.print();
}

/*
 1100101110101100110111111011100011010101101100100111
 */
