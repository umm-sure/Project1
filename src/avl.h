#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H

#include <string>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class avlTree
{
    struct node
    {
        node* left;
        node* right;
        int height;

        string id;
        string name;

        node(string id_, string name_)
        {
            id = id_;
            name = name_;
            height = 0;
            left = nullptr;
            right = nullptr;
        }
    };

public:
        avlTree();
        string insert(const string& name_, string id_);
        string remove(const string& id_);
        string search(const string& id_);
        string searchName(string name_);
        void printInorder();
        void printPreorder();
        void printPostorder();
        string removeInorder(int n);
        void printLevelCount();
        ~avlTree();

private:
    node* root;

    node* remove(const string& id_, node* n);
    int balanceFactor(node* n);
    node* insert(node* n, const string& name, const string& id_);
    void printInorder(node* n, vector<string>& names);
    void printPreorder(node* n, vector<string>& names);
    void printPostorder(node* n, vector<string>& names);
    string search(const string& id, node* n);
    void searchName(string name, node* n, vector<string>& ids);
    int calcHeights(node* n);
    pair<string, string> findRemoveSuccessor(node* subroot, node* n);
    void deletePostorder(node* n);
    int removeInorder(int n, int& curr, node* in);
    node* rotateLeft(node* n);
    node* rotateRight(node* n);
    node* rotateLeftRight(node* n);
    node* rotateRightLeft(node* n);

};

avlTree::avlTree()
{
    root = nullptr;
}

string avlTree::insert(const string& name_, string id_)
{
    if(root == nullptr) // if there is no root, no need to go into insert helper function
    {
        root = new node(id_, name_);
        root->height = 1;
        //should always be successful
        return "successful";
    }
    if (insert(root, name_, id_) == nullptr)
    {
        // insert helper returns nullptr when there is already matching ID
        return "unsuccessful";
    }
    calcHeights(root); // recalc heights just for verification
    return "successful";
}

avlTree::node* avlTree::insert(node* n, const string& name, const string& id_)
{
    if(n == nullptr)
    {
        //create new node when inserting and find nullptr
        node* temp =  new node(id_, name);
        temp->height = 1;
        return temp;
    }
    if(id_ < n->id)
    {
        //go to left subtree when id key is less than node id
        n->left = insert(n->left, name, id_);
        n->height++;
    }
    else if(id_ > n->id)
    {
        //go to right subtree when if key is greater than node id
        n->right = insert(n->right, name, id_);
        n->height++;
    }
    else if(n->id == id_)
    {
        //bad case (invalid insert id)
        return nullptr;
    }

    //checking balance (this checks at every level on call stack)
    int balance = balanceFactor(n);
    //cout << n->id << ": " << balance << endl;

    //if statements reflect table found at pg. 33 of balanced trees pdf
    if(balance == 2)
    {
        int balance_2 = balanceFactor(n->left);

        if(balance_2 == -1)
        {
            n = rotateLeftRight(n);
        }
        if(balance_2 == 1)
        {
            n = rotateRight(n);
        }
    }
    else if(balance == -2)
    {
        int balance_2 = balanceFactor(n->right);
        //cout << balance_2 << endl;
        if(balance_2 == -1)
        {
            n = rotateLeft(n);
        }
        if(balance_2 == 1)
        {
            n = rotateRightLeft(n);
        }
    }

    calcHeights(n);

    return n;
}

string avlTree::remove(const string& id_)
{
    if(search(id_) == "unsuccessful") //check if id key is found in tree
        return "unsuccessful";
    else
    {
        if(remove(id_, root) == nullptr) //only happens when tree is invalid
            return "unsuccessful";
        else
            return "successful";
    }
}

string avlTree::search(const string& id_)
{
    if(root == nullptr) //when root is nullptr there's nothing to search lol
        return "unsuccessful";

    string result = search(id_, root);
    if (result.empty()) // when result is empty, nothing was found
    {
        return "unsuccessful";
    }
    else
        return result;
}

string avlTree::searchName(string name_)
{
    if(root == nullptr)  //when root is nullptr there's nothing to search lol
        return "unsuccessful";

    vector<string> ids;
    searchName(name_, root, ids);
    if(ids.empty()) // if ids vector is empty, no matching name was found
        return "unsuccessful";
    else
    {
        //fill up string with ids of matched names
        //will always have at least one id at this point
        string l = "";
        for(int i = 0; i<ids.size(); i++)
        {
            if(i != 0) //newline after each name
                l+= "\n";
            l += ids[i];
        }
        return l;
    }
}

void avlTree::printInorder()
{
    if (root == nullptr) //if root is nullptr, nothing to print
        cout << endl;
    else
    {
        vector<string> names;
        printInorder(root, names); //updates names vector

        //print out each name
        for(int i = 0; i < names.size(); i++) {
            if (i != 0)
                cout << ", ";
            cout << names[i];
        }
    }
}

void avlTree::printPreorder()
{
    if (root == nullptr)  //if root is nullptr, nothing to print
        cout << endl;
    else
    {
        vector<string> names;
        printPreorder(root, names);//updates names vector

        //print out each name
        for(int i = 0; i < names.size(); i++)
        {
            if(i != 0)
                cout << ", ";
            cout << names[i];
        }
    }
}

void avlTree::printPostorder()
{
    if (root == nullptr)  //if root is nullptr, nothing to print
        cout << endl;
    else
    {
        vector<string> names;
        printPostorder(root, names);//updates names vector

        //print out each name
        for(int i = 0; i < names.size(); i++)
        {
            if(i != 0)
                cout << ", ";
            cout << names[i];
        }
    }
}

int avlTree::balanceFactor(avlTree::node *n)
{
    if(n->right == nullptr && n->left == nullptr)
    {
        return 0; //no subtrees to take height of
    }
    else if(n->right == nullptr && n->left != nullptr)
    {
        return calcHeights(n->left); //only left subtree
    }
    else if(n->right != nullptr && n->left == nullptr)
    {
        return (0 - calcHeights(n->right)); //only right subtree
    }
    else
    {
        return calcHeights(n->left) - calcHeights(n->right); //both subtree
    }
}

void avlTree::printInorder(avlTree::node *n, vector<string>& names)
{
    if(n == nullptr)
    {
        cout << ""; //essentially pass statement
    }
    else
    {
        //inorder = left -> current ->right

        printInorder(n->left, names);
        names.push_back(n->name);
        printInorder(n->right, names);
    }
}

void avlTree::printPreorder(avlTree::node *n, vector<string>& names)
{
    if(n == nullptr)
    {
        cout << "";//essentially pass statement
    }
    else
    {
        //preorder = current -> left -> right

        names.push_back(n->name);
        printPreorder(n->left, names);
        printPreorder(n->right, names);
    }
}

void avlTree::printPostorder(avlTree::node *n, vector<string>& names)
{
    if(n == nullptr)
    {
        cout << "";//essentially pass statement
    }
    else
    {
        //postorder = left -> right -> current

        printPostorder(n->left, names);
        printPostorder(n->right, names);
        names.push_back(n->name);
    }
}

string avlTree::removeInorder(int n)
{
    if(n < 0)
        return "unsuccessful"; //invalid n value
    else
    {
        int curr = 0;
        if(removeInorder(n, curr, root) == n) //returns correct value of n when successful
            return "successful";
        else
            return "unsuccessful";
    }
}

string avlTree::search(const string& id, avlTree::node *n)
{
    if(n == nullptr)
    {
        return ""; //if reach nullptr, missed id (DNE)
    }
    else
    {
        if(id < n->id) // go to left subtree
            return search(id, n->left);
        else if(id > n->id) // go to right subtree
            return search(id, n->right);
        else
            return n->name; //correct id found
    }
}

void avlTree::searchName(string name, avlTree::node *n, vector<string>& ids)
{
    if(n == nullptr)
    {
        return; //if node is null, nothing to pushback in ids vector
    }
    else
    {
        //needs to be preorder traversal (assignment instructions)

        if(name == n->name) //if current name is correct, pushback respective id
            ids.push_back(n->id);
        searchName(name, n->left, ids);
        searchName(name, n->right, ids);
    }
}

int avlTree::calcHeights(avlTree::node *n)
{
    if(n->left == nullptr && n->right == nullptr) //1-based height
        return 1; //node is already 1 height
    else if(n->left == nullptr) //only right subtree
        n->height = calcHeights(n->right)+1;
    else if(n->right == nullptr) //only left subtree
        n->height = calcHeights(n->left)+1;
    else //both subtrees exist
        n->height = max(calcHeights(n->left)+1, calcHeights(n->right)+1);
    return n->height;
}

avlTree::node* avlTree::remove(const string& id_, avlTree::node* n)
{
    if(n == nullptr) //return nullptr cause reached end of delete search
    {
        return n;
    }
    if(n->id > id_) //if id key is less than node id, go to left subtree
    {
        n->left = remove(id_, n->left);
    }
    else if(n->id < id_) //if id key is greater than node id, go to right subtree
    {
        n->right = remove(id_, n->right);
    }
    else //Correct node
    {
        if(n->left == nullptr && n->right == nullptr) // no children
        {
            free(n);
            return nullptr;
        }
        else if(n->left == nullptr && n->right != nullptr) //right child
        {
            avlTree::node* temp = n->right;
            free(n);
            return temp;
        }
        else if(n->left != nullptr && n->right == nullptr) // left child
        {
            avlTree::node* temp = n->left;
            free(n);
            return temp;
        }
        else //both childs
        {
            pair<string, string> info = findRemoveSuccessor(n,n);
            n->id = info.first;
            n->name = info.second;
            return n;
        }
    }
    return n;
}


pair<string, string> avlTree::findRemoveSuccessor(avlTree::node *subroot, avlTree::node* n)
{
    if(n == nullptr) //returns empty pair (checked) in traversal
    {
        return make_pair("", "");
    }
    else
    {
        //inorder = left -> current -> right

        pair<string, string> l = findRemoveSuccessor(subroot, n->left);

        if(!l.first.empty() && !l.second.empty())
            return l;

        if(n->id > subroot->id) //first id greater than subtree, return non-empty pair and delete node
        {
            pair<string, string> info = make_pair(n->id, n->name);
            remove(n->id);
            return info;
        }

        pair<string, string> r = findRemoveSuccessor(subroot, n->right);
        if(!r.first.empty() && !r.second.empty())
            return r;
    }
    return make_pair("", "");
}

void avlTree::printLevelCount()
{
    if(root == nullptr)//level is zero when root is nullptr
        cout << '0' << endl;
    else
    {
        calcHeights(root); //calc heights for verification
        cout << root->height << endl;//height of root is num levels
    }
}

avlTree::~avlTree()
{
    if(root == nullptr) //nothing to delete when root is null
        return;
    else
        deletePostorder(root);
}

void avlTree::deletePostorder(avlTree::node *n)
{
    if(n == nullptr)
        return;
    else
    {
        //post order makes sure nodes deleted have no children
        deletePostorder(n->left);
        deletePostorder(n->right);
        remove(n->id, n);
    }
}

int avlTree::removeInorder(int n, int &curr, avlTree::node *in)
{
    if(in == nullptr)
    {
        return -1;
    }
    else
    {
        int x = removeInorder(n, curr, in->left);
        if(x == n)
            return x;
        if(curr == n)
        {
            remove(in->id);
            return curr;
        }
        else
        {
            curr++;
        }
        int y = removeInorder(n, curr, in->right);
        if(y == n)
            return y;
    }
    return 0;
}

avlTree::node *avlTree::rotateLeft(avlTree::node *n)
{
    //Solution from Module 5 stepik solutions
    bool isRoot = root->id == n->id;
    node* rightTemp = n->right;
    n->right = rightTemp->left;
    rightTemp->left = n;
    if(isRoot)
        root = rightTemp;
    return rightTemp;
}

avlTree::node *avlTree::rotateRight(avlTree::node *n)
{
    //Solution from Module 5 stepik solutions
    bool isRoot = root->id == n->id;
    node* leftTemp = n->left;
    n->left = leftTemp->right;
    leftTemp->right = n;
    if (isRoot)
        root = leftTemp;
    return leftTemp;
}

avlTree::node *avlTree::rotateLeftRight(avlTree::node *n)
{
    //Solution from Module 5 stepik solutions
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

avlTree::node *avlTree::rotateRightLeft(avlTree::node *n)
{
    //Solution from Module 5 stepik solutions
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}



#endif //PROJECT1_AVL_H
