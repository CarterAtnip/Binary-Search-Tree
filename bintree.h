/*********************
* Name: Carter Atnip
* Programming III: Data structures
* header file for binary search tree class
**********************/

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H

#include <iostream>
#include <data.h>
#include <string>

using std::string;

class BinTree {
public:
    BinTree(); //constrcutor
    ~BinTree(); // destructor

    bool isEmpty();

    int getCount() const;

    bool getRootData(Data*);

    bool addNode(int, const string*);

    bool removeNode(int);

    void displayTree();

    void displayPreOrder();

    void displayPostOrder();

    void displayInOrder();

    bool contains(int);

    void clear();

    bool getNode(Data*, int);

    int getHeight();

private:
    DataNode *root;
    int count;


    void clear(DataNode*);

    bool addNode(DataNode*, DataNode**);

    DataNode* removeNode(int, DataNode*);

    DataNode* minValueNode(DataNode*);

    bool getNode(Data*, int, DataNode*);

    bool contains(int, DataNode*);

    int getHeight(DataNode*);

    void displayPreOrder(DataNode*);

    void displayPostOrder(DataNode*);

    void displayInOrder(DataNode*);
};


#endif /* BINTREE_BINTREE_H */

