#include<iostream>
#include<vector>

using namespace std;

class FenwickTree{

    public:
        vector<int> fenTree;
        int size;
        FenwickTree(int n,vector<int> arr){
            this->size = n;
            this->fenTree.assign(n,0);

            for(int i=0; i<n; i++){
                this->add_element(i,arr[i]);
            }
        }

        void add_element(int idx, int ele){
            for(int j=idx; j<size; j=j|(j+1)){
                fenTree[j]+=ele;                
            }
        }

        int sum(int idx){
            int res = 0;
            for(int j=idx; j>=0; j=(j&(j+1))-1){
                res+=fenTree[j];
            }
            return res;
        }
        int sum(int l,int h){

            return sum(h) - sum(l-1);
        }
};

int main(){
    int n = 10;
    vector<int> arr(n,2);
    FenwickTree *tree = new FenwickTree(arr.size(),arr);

    cout<<tree->sum(1,2)<<endl;
    cout<<tree->sum(2,3)<<endl;
    cout<<tree->sum(1,4)<<endl;
    cout<<tree->sum(4,9)<<endl;
}