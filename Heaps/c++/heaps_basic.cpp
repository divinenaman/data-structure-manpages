#include<iostream>
#include<vector>
using namespace std;

template <typename T>
class Heaps {

private:	
	vector<T> heaps;
	int size;
	bool isMaxHeap;
public:
	Heaps(T arr[],int n,bool isMaxHeap) {
		this->size = n;
        this->heaps.resize(this->size);
        this->isMaxHeap = isMaxHeap;

        for(int i=0; i<n; i++) this->heaps[i]=arr[i];
        
        for(T i: this->heaps) cout<<i<<" ";	
        cout<<endl;
        	
        if(isMaxHeap) build_min_heap();
        else build_min_heap();
	}

	void build_min_heap() {
		int n = this->size;
		for(int i=n/2-1; i>=0; i--){
			min_heapify(i,n);
		}
	} 

	void build_max_heap() {
		int n = this->size;
		for(int i=n/2-1; i>=0; i--){
			max_heapify(i,n);
		}
	}

	void min_heapify(int idx,int n) { 
		int min = idx;
		int left = 2*idx;
		int right = 2*idx+1;
		if(left<n && this->heaps[min]>this->heaps[left]) min = left;
		if(right<n && this->heaps[min]>this->heaps[right]) min = right;

		if(min != idx){
			T temp = this->heaps[idx];
			this->heaps[idx] = this->heaps[min];
			this->heaps[min] = temp;
			min_heapify(min,n);
		}
	}

	void max_heapify(int idx,int n) {
		int max = idx;
		int left = 2*idx;
		int right	 = 2*idx+1;
		if(left<n && this->heaps[max]<this->heaps[left]) max = left;
		if(right<n && this->heaps[max]<this->heaps[right]) max = right;

		if(max != idx){
			T temp = this->heaps[idx];
			this->heaps[idx] = this->heaps[max];
			this->heaps[max] = temp;
			max_heapify(max,n);
		}
	}

	void display() {
		for(int i=this->size-1; i>=0; i--) {
			cout<<this->heaps[0]<<"\t";
			this->heaps[0] = this->heaps[i];
			if(this->isMaxHeap) max_heapify(0,i);
			else min_heapify(0,i);
		}
		cout<<endl;
	}
};

int main() {
	int a[] = {100,3,4,1,0,9,14,11,8,3};
	int n = 10;

	Heaps<int> max_heap = Heaps<int>(a,n,true);
	Heaps<int> min_heap = Heaps<int>(a,n,false);

	cout<<"MAX HEAP: ";
	max_heap.display();
	cout<<"MIN HEAP: ";
	min_heap.display();
}