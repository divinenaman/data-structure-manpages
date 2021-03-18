#include<iostream>
#define ll long long int
using namespace std;

template<typename T>
class Node {
    public:
        string key;
        T value;
        Node<T>* next;
        Node(string key,T value){
            this->key = key;
            this->value = value;
            this->next = NULL;
        }
};

template<typename T>
class HashTable{
    public:
        int cs; // current size
        int ts; // total size
        Node<T> **arr;
        HashTable(int ts = 2){
            this->ts = ts;
            this->cs = 0;
            this->arr = new Node<T>* [this->ts];
            for(int i=0; i<this->ts; i++){
                this->arr[i] = NULL;
            }
        }

        // hash function => the core logic behind hash tables
        int hashFunc(string key){
            ll sum = 0;
            ll factor = 1;
            for(int i=0; i<key.size(); i++){
                sum = (sum%this->ts) + ((int)key[i]*factor)%this->ts;
                sum = sum % this->ts;
                factor = (factor%this->ts) * ((37%this->ts)%this->ts);
            }
            return (int)sum;
        }
        void rehash(){
            int old_size = this->ts;
            this->ts = 2*old_size;
            Node<T>** old_table = this->arr;
            this->arr = new Node<T>* [this->ts];
            for(int i=0; i<this->ts; i++){
                this->arr[i] = NULL;
            }
            for(int i=0; i<old_size; i++){
                Node<T> *temp = old_table[i];
                while(temp != NULL){
                    insert(temp->key, temp->value);
                    temp = temp->next;
                }
            }
        }


        void insert(string key, T value){
            int index = hashFunc(key);
            T result = search(key);
            if(result != NULL){
                Node<T> *temp = this->arr[index];
                while(temp != NULL){
                    if(temp->key == key){
                        temp->value = value;
                        return;
                    }
                    temp = temp->next;
                }
            }
            else{
                Node<T>* new_node = new Node<T>(key,value);
                if(this->arr[index] == NULL){
                    this->arr[index] = new_node;
                }else{
                    new_node->next = this->arr[index];
                    this->arr[index] = new_node;
                }
                this->cs++; 
                double load_factor = (double)(this->cs)/(this->ts);
                if(load_factor > 0.5){
                    rehash();
                }
            }
        }
        T search(string key){
            int index = hashFunc(key);
            Node<T> *temp = this->arr[index];
            while(temp!=NULL){
                if(temp->key == key) return temp->value;
                temp = temp->next;
            }
            return NULL;
        }
        void display(){
            cout<<"\n\n\n"<<"********************************";
            for(int i=0; i<this->ts; i++){
                Node<T> *temp = this->arr[i];
                while(temp != NULL){
                    cout<<temp->key<<":"<<temp->value<<"  ";
                    temp = temp->next;
                }
                cout<<endl;                                
            }
            cout<<"********************************"<<endl;
        } 
};

int main(){
    int n = 5;
    string key;
    int value;
    HashTable<int> *table = new HashTable<int>;
    while(n--){
        cin>>key>>value;
        table->insert(key,value);
    }
    table->display();
    return 0;
}