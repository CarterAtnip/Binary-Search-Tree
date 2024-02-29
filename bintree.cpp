/*********************
* Name: Carter Atnip
* Programming III: Data structures
* logic for binary search tree class
**********************/
#include "bintree.h"

// default constructor
BinTree::BinTree() {
 root = NULL;
 count = 0;
}

/*********************
* Name: isEmpty
* Parameters: None
* Returns: bool
* checks if there are any nodes in the tree and returns true or false accordingly
**********************/
bool BinTree::isEmpty() {
    return root == NULL;
}

/*********************
* Name: getCount
* Parameters: None
* Returns: int
* returns how many nodes there are in the tree
**********************/
int BinTree::getCount() const {
    return count;
}

/*********************
* Name: getRootData
* Parameters: Data (data ptr)
* Returns: bool
* fills the passed struct with the base root's data if there is ne and returns t/f accordingly
**********************/
bool BinTree::getRootData(Data *data) {
    bool success = false;

    if (root == NULL) {
        data->id = -1;
        data->information = "";

    } else {
        data->id = root->data.id;
        data->information = root->data.information;
        success = true;
    }

    return success;
}

/*********************
* Name: displayTree
* Parameters: None
* Returns: None
* displays the stats of the binary search tree
**********************/
void BinTree::displayTree() {
    std::cout << "DISPLAY TREE\n";
    std::cout << "==============================================\n";
    if(isEmpty()) {std::cout << "Tree is empty\n";}
    else {std::cout << "Tree is not empty\n";}
    std::cout << "Node count: " << getCount() << std::endl;
    std::cout << std::endl;
    displayPreOrder();
    std::cout << std::endl;
    displayInOrder();
    std::cout << std::endl;
    displayPostOrder();
    std::cout << "==============================================\n";
}


/*********************
* Name: displayPreOrder
* Parameters: None
* Returns: None
* calls private method to do traversal
**********************/
void BinTree::displayPreOrder() {
    std::cout << "Pre-Order Traversal\n";
    displayPreOrder(root);
}

/*********************
* Name: displayPreOrder
* Parameters: DataNode (node ptr)
* Returns: None
* recursively does a preorder traversal through the tree and prints as it goes
**********************/
void BinTree::displayPreOrder(DataNode *node) {
    if (node != NULL) {

        std::cout << node->data.id << " " << node->data.information << std::endl;

        displayPreOrder(node->left);

        displayPreOrder(node->right);
    }
}

/*********************
* Name: displayPostOrder
* Parameters: None
* Returns: None
* calls private method to do traversal
**********************/
void BinTree::displayPostOrder() {
    std::cout << "Post-Order Traversal\n";
    displayPostOrder(root);
}

/*********************
* Name: displayPreOrder
* Parameters: node (DataNode ptr)
* Returns: None
* recursively does a postorder traversal through the tree and prints as it goes
**********************/
void BinTree::displayPostOrder(DataNode *node) {
    if (node != NULL) {

        displayPostOrder(node->left);

        displayPostOrder(node->right);

        std::cout << node->data.id << " " << node->data.information << std::endl;
    }
}

/*********************
* Name: displayInOrder
* Parameters: None
* Returns: None
* calls private method to do traversal
**********************/
void BinTree::displayInOrder() {
    std::cout << "In-Order Traversal\n";
    displayInOrder(root);
}

/*********************
* Name: displayinOrder
* Parameters: node (DataNode ptr)
* Returns: None
* recursively does an in order traversal through the tree and prints as it goes
**********************/
void BinTree::displayInOrder(DataNode *node) {
    if (node != NULL) {
        displayInOrder(node->left);

        std::cout << node->data.id << " " << node->data.information << std::endl;

        displayInOrder(node->right);
    }
}

/*********************
* Name: clear
* Parameters: None
* Returns: None
* calls private method, sets count to 0 and nulls root
**********************/
void BinTree::clear() {
 clear(root);
 count = 0;
 root = NULL;
}

/*********************
* Name: clear
* Parameters: current (DataNode ptr)
* Returns: void
* recurisvely goes through left and right branches, nulls and deletes them
**********************/
void BinTree::clear(DataNode *current) {
    if (current != NULL) {
        clear(current->left);
        clear(current->right);

        current->left = NULL;
        current->right = NULL;
        delete current;
    }

}

/*********************
* Name: addNode
* Parameters: id (int) data (constr string ptr)
* Returns: bool
* public addNode method that validates id is non negative and then calls a private method
* to add the nodes recursively left to right
**********************/
bool BinTree::addNode(int id, const string *data) {
    bool success = false;

    if (id > -1 && !data->empty()) {
        DataNode *new_element = new DataNode;
        new_element->data.information = *data;
        new_element->data.id = id;
        new_element->left = NULL;
        new_element->right = NULL;

        success = addNode(new_element, &root);
    }

    if (success) {count++;}

    return success;
}

/*********************
* Name: addNode
* Parameters: new_element (DataNode ptr) current (PBR DataNode ptr)
* Returns: bool
* recurisvely calls itself until it finds a spot for the ID in the tree and returns a bool to indicate success
**********************/
bool BinTree::addNode(DataNode *new_element, DataNode **current) {
    bool success = false;

    if (*current == NULL) {
        *current = new_element;
        success = true;

    } else if (new_element->data.id <= (*current)->data.id) {
        success = addNode(new_element, &(*current)->left);

    } else {
        success = addNode(new_element, &(*current)->right);
    }

    return success;
}

/*********************
* Name: removeNode
* Parameters: id (int)
* Returns: bool
* public remove node method that calls a private method to recurisvely remove based on id
**********************/
bool BinTree::removeNode(int id) {
    int temp_count = count;

    root = removeNode(id, root);

    return temp_count > count;
}

/*********************
* Name: removeNode
* Parameters: id (int) current (DataNode ptr)
* Returns: DataNode ptr
* recursively navigates tree to find corresponding ID. Deletes the ID if found and rebuilds the tree accordingly
**********************/
DataNode *BinTree::removeNode(int id, DataNode *current) {
    if (current != NULL) {
        if (current->data.id > id) {current->left = removeNode(id, current->left);}

        else if (current->data.id < id) {current->right = removeNode(id, current->right);}

        else {
            DataNode* temp;

            if (current->left == NULL) {
                temp = current->right;
                delete current;
                current = temp;
                count--;


            } else if (current->right == NULL) {
                temp = current->left;
                delete current;
                current = temp;
                count--;


            } else {
                temp = minValueNode(current->right);
                current->data.id = temp->data.id;
                current->data.information = temp->data.information;

                current->right = removeNode(temp->data.id, current->right);
            }
        }
    }

    return current;
}

/*********************
* Name: minValueNode
* Parameters: node (DataNode ptr)
* Returns: DataNode ptr
* uses a while loop to traverse the tree from the passed root to find the lowest value node
**********************/
DataNode *BinTree::minValueNode(DataNode *node) {
    DataNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

/*********************
* Name: getNode
* Parameters: data (Data ptr), id (int)
* Returns: bool
* determines if the id passed is valid and then calls the private varient
**********************/
bool BinTree::getNode(Data *data, int id) {
    bool success = false;

    if (id > -1) {success = getNode(data, id, root);}

    return success;
}

/*********************
* Name: getNode
* Parameters: data (Data ptr), id (int),
* Returns: bool
* returns true and fills the empty struct if the id is found using binary search
**********************/
bool BinTree::getNode(Data *data, int id, DataNode *current) {
    bool success = false;

    if (current == NULL) {success = false;}

    else if(id > current->data.id) {success = getNode(data, id, current->right);}

    else if(id < current->data.id) {success = getNode(data, id, current->left);}

    else {
        data->id = current->data.id;
        data->information = current->data.information;

        success = true;
    }

    return success;
}

/*********************
* Name: contains
* Parameters: id (int)
* Returns: bool
* determines if the id passed is valid then calls the private method
**********************/
bool BinTree::contains(int id) {
    bool success = false;

    if (id > -1) {success = contains(id, root);}

    return success;
}

/*********************
* Name: contains
* Parameters: current (DataNode ptr), id (int),
* Returns: bool
* using binary search determines if the ID passed is in the tree returns bool accordingly
**********************/
bool BinTree::contains(int id, DataNode *current) {
    bool success = true;

    if (current == NULL) {success = false;}

    else if(id > current->data.id) {success = contains(id, current->right);}

    else if(id < current->data.id) {success = contains(id, current->left);}

    return success;
}

/*********************
* Name: getHeight
* Parameters: None
* Returns: int
* calls private version of this method
**********************/
int BinTree::getHeight() {return getHeight(root);}

/*********************
* Name: getHeight
* Parameters: current (dataNode ptr)
* Returns: int
* recurisvely counts the height of the tree
**********************/
int BinTree::getHeight(DataNode *current) {
    int lh = 0;
    int rh = 0;

    if (current != NULL) {
        lh = getHeight(current->left) + 1;
        rh = getHeight(current->right) + 1;
    }
    return lh > rh ? lh : rh;
}

// destructor
BinTree::~BinTree() {
    clear();
}
