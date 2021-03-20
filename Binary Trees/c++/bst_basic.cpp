#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Node
{
public:
    T key;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    Node(T key, Node<T> *parent)
    {
        this->key = key;
        this->parent = parent;
        this->left = NULL;
        this->right = NULL;
    }
};

template <typename T>
class BST
{
private:
    Node<T> *root;

public:
    Node<T> *temp;

    BST()
    {
        this->root = NULL;
    }

    Node<T> *insert(T key, Node<T> *node = NULL, Node<T> *parent = NULL)
    {
        if (node == NULL)
        {
            Node<T> *newNode = new Node<T>(key, parent);
            node = newNode;
            //cout << node->key <<endl;
            return node;
        }
        else
        {
            if (key < node->key)
            {
                node->left = insert(key, node->left, node);
            }
            else
            {
                node->right = insert(key, node->right, node);
            }
        }
    }

    void deleteNode(T key, Node<T> *node)
    {
        if (node->key == key)
        {
            if (node->left == NULL && node->right == NULL)
            {
                if (node->parent->left != NULL && node->parent->left->key == key)
                {
                    node->parent->left = NULL;
                }
                else
                {
                    node->parent->right = NULL;
                }
            }
            else if (node->left != NULL && node->right == NULL)
                *node = *(node->left);
            else if (node->right != NULL && node->left == NULL)
                *node = *(node->right);
            else
            {
                Node<T> *succ = inorderSuccessor(node->right);
                node->key = succ->key;
                succ->key = key;
                deleteNode(key, succ);
            }
        }
        else if (node != NULL)
        {
            if (node->key > key)
                deleteNode(key, node->left);
            else
                deleteNode(key, node->right);
        }
    }

    Node<T> *inorderSuccessor(Node<T> *temp)
    {
        if (temp->left == NULL)
            return temp;
        return inorderSuccessor(temp->left);
    }

    void displayInorder(Node<T> *temp)
    {
        if (temp != NULL)
        {
            displayInorder(temp->left);
            cout << temp->key << " ";
            displayInorder(temp->right);
        }
    }
};

int main()
{
    BST<int> *tree = new BST<int>;
    Node<int> *root = tree->insert(90);
    tree->insert(40, root);
    tree->insert(20, root);
    tree->insert(10, root);
    tree->insert(100, root);
    tree->insert(97, root);
    tree->insert(49, root);
    tree->insert(15, root);

    tree->displayInorder(root);
    cout << endl;
    tree->deleteNode(10, root);
    tree->displayInorder(root);
    cout << endl;
    tree->deleteNode(100, root);
    tree->displayInorder(root);
    cout << endl;
    tree->deleteNode(40, root);
    tree->displayInorder(root);
    cout << endl;
}