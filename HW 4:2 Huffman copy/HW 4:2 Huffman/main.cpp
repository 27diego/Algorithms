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

struct tieBreaker
{
    bool operator() (Node* a, Node* b)
    {
        if(a->frequency==b->frequency)
        {
            if(a->letter=='$'&&b->letter=='$')
            {
                return a->frequency<b->frequency;
            }
            else if(a->letter=='$')
            {
                return b<a;
            }
            else if(b->letter=='$')
            {
                return a<b;
            }
            return a->letter<b->letter;
        }
        return a->frequency<b->frequency;
    }
};



class HuffTree{
    Node* root;
    priorityHeap pq;
public:
    HuffTree()
    {
        root = nullptr;
    }
    void build(string sentence)
    {
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
        
        vector<Node*>priorityletters;
        
        while(pq.size()!=0)
        {
            priorityletters.push_back(pq.extractMin());
        }
        
        queue<Node*>q;
        
        sort(priorityletters.begin(), priorityletters.end(), tieBreaker());
        
        Node* temp = new Node('$',0);
        while(!priorityletters.empty())//trying to push $ to end to push to final queue
        {
            if(priorityletters.size()==1)
            {
                break;
            }
            temp=new Node('$',0);
            temp->left = priorityletters[0];
            priorityletters.erase(priorityletters.begin());
            if(priorityletters[0]!=nullptr)
            {
                temp->right = priorityletters[0];
                priorityletters.erase(priorityletters.begin());
            }
            temp->frequency = temp->right->frequency + temp->left->frequency;
            priorityletters.push_back(temp);
            sort(priorityletters.begin(), priorityletters.end(), tieBreaker());
            
            //            cout<<"Size: "<<priorityletters.size()<<endl;
            //            for(int x=0;x<priorityletters.size();x++)
            //            {
            //                cout<<"char: "<<priorityletters[x]->letter<<":"<<priorityletters[x]->frequency<<endl;
            //            }
            //            cout<<endl<<endl;
        }
        
        root = priorityletters[0];
        priorityletters.erase(priorityletters.begin());
        
        //        cout<<"root: "<<root->letter<<":"<<root->frequency<<endl;
        
    }
    
    void createMap()
    {
        
    }
    
};



int main() {
    HuffTree tree;
    
    string sentence = "i love computer science";
    
    tree.build(sentence);
    
}

/*
 1100101110101100110111111011100011010101101100100111
 */



/*
 void printPostHelp()
 {
 postOrder(root);
 }
 
 
 void postOrder(Node* root) //finished
 {
 if (root) {
 postOrder(root->left);
 printNode(root);
 postOrder(root->right);
 }
 }
 
 void printNode(Node* root)//finished
 {
 cout << root->data<<" ";
 
 */
