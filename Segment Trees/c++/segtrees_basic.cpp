#include <iostream>
#include <vector>
using namespace std;

// vector implementation
// segment tree of sum of vector elemets

template <typename T>
class SegmentTrees
{
private:
    vector<T> segment;

public:
    int size, start, end, vertex;
    SegmentTrees(T *arr, int size)
    {
        this->size = 4 * size; // max size : 4*size
        this->start = 0;
        this->end = size - 1;
        this->vertex = 1;                     // Index of root vertex = 1
        this->segment.resize(this->size + 1); // start indexing from 1 => size+1
        build(1, arr, 0, size - 1);
    }

    // O(n)
    void build(int v, T *arr, int l, int h)
    {
        if (l == h)
        {
            this->segment[v] = *(arr + l);
        }
        else
        {
            int mid = (l + h) / 2;
            build(v * 2, arr, l, mid);
            build(v * 2 + 1, arr, mid + 1, h);
            this->segment[v] = this->segment[2 * v] + this->segment[2 * v + 1];
        }
    }

    // O(log(n))
    T find(int start, int end, int v, int l, int h)
    {
        if (l > h)
            return 0;
        if (l == start && h == end)
            return this->segment[v];
        int mid = (start + end) / 2;
        return find(start, mid, v * 2, l, min(h, mid)) + find(mid + 1, end, v * 2 + 1, max(l, mid + 1), h);
    }

    // O(log(n))
    void update(int start, int end, int v, int pos, T val)
    {
        if (start == end && start == pos)
            this->segment[v] = val;
        else
        {
            int mid = (start + end) / 2;
            if (pos <= mid)
                update(start, mid, v * 2, pos, val);
            else
                update(mid + 1, end, v * 2 + 1, pos, val);
            this->segment[v] = this->segment[v * 2] + this->segment[v * 2 + 1];
        }
    }

    void display()
    {
        for (T i : this->segment)
        {
            cout << i << endl;
        }
    }
};

int main()
{
    int arr[] = {1, 2, 7, 8, 9, 5};
    SegmentTrees<int> *tree = new SegmentTrees<int>(arr, 6);
    tree->update(tree->start, tree->end, tree->vertex, 2, 10);
    tree->display();
    cout << "SUM: " << tree->find(tree->start, tree->end, tree->vertex, 1, 2) << endl;
}