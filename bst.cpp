
// Anuragh Sundar, Erin DeLong (5/5/2021)



#include <iostream>
using std::cout;

template<class T>
// constructor sets up empty tree
IntBST<T>::IntBST() : root(nullptr) { }

template<class T>
// destructor deletes all nodes
IntBST<T>::~IntBST() {
    clear(root);
}
template<class T>
// recursive helper for destructor
void IntBST<T>::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

// insert value in tree; return false if duplicate
template<class T>
bool IntBST<T>::insert(T value) {
    // handle special case of empty tree first
    if (!root) {
	root = new Node(value);
	return true;
    }
    // otherwise use recursive helper
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
template<class T>
bool IntBST<T>::insert(T value, Node *n) {
    if (value == n->info)
	return false;
    if (value < n->info) {
	if (n->left)
	    return insert(value, n->left);
	else {
	    n->left = new Node(value);
	    n->left->parent = n;
	    return true;
	}
    }
    else {
	if (n->right)
	    return insert(value, n->right);
	else {
	    n->right = new Node(value);
	    n->right->parent = n;
	    return true;
	}
    }
}

// print tree data pre-order
template<class T>
void IntBST<T>::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
template<class T>
void IntBST<T>::printPreOrder(Node *n) const {
    if (n) {
	cout << n->info << " ";
	printPreOrder(n->left);
	printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
template<class T>
void IntBST<T>::printInOrder() const {
    printInOrder(root);
}

template<class T>
void IntBST<T>::printInOrder(Node *n) const {
    if (n == nullptr) {
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
    
}

// prints tree data post-order, with helper
template<class T>
void IntBST<T>::printPostOrder() const {
    printPostOrder(root);
}

template<class T>
void IntBST<T>::printPostOrder(Node *n) const {
    if (n == nullptr) {
        return;
    }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
template<class T>
T IntBST<T>::sum() const {
    return sum(root);
}

// recursive helper for sum
template<class T>
T IntBST<T>::sum(Node *n) const {
    if (n == nullptr) {
        return 0;
    }
    return n->info + sum(n->left)+ sum(n->right);
    
}

// return count of values
template<class T>
int IntBST<T>::count() const {
    return count(root);
}

// recursive helper for count
template<class T>
int IntBST<T>::count(Node *n) const {
    if (n == nullptr) {
        return 0;
    }
    return 1 + count(n->left)+ count(n->right);
}




// returns true if value is in the tree; false if not
template<class T>
bool IntBST<T>::contains(T value) const {
    Node* current = root;
    while (current) {
        if (current->info == value) {
            return true;
        }
        else if (current->info > value) {
            current = current->left;
        }
        else if (current->info < value) {
            current = current->right;
        }
    }
    return false;
}

// returns the Node containing the predecessor of the given value
template<class T>
class IntBST<T>::Node* 
IntBST<T>::getPredecessorNode(T value) const{
    Node* current = root;
    while (current) {
        if (current->info == value) {
            if(current->left){
                if(current->left->right){
                    return current->left->right;
                }
                return current->left;
            }
            else{
                while (current->parent && current->parent->info > value) {
                    current = current->parent;
                }
                if (current->parent == nullptr){
                    return nullptr;
                }
                else{
                    return current->parent;
                }
            }
        }
        else if (current->info > value) {
            current = current->left;
        }
        else if (current->info < value) {
            current = current->right;
        }
    }
    return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
template<class T>
T IntBST<T>::getPredecessor(T value) const{
    if (getPredecessorNode(value) == nullptr) {
        return 0;
    }
    return getPredecessorNode(value)->info;
}

// returns the Node containing the successor of the given value
template<class T>
class IntBST<T>::Node* 
IntBST<T>::getSuccessorNode(T value) const{
    Node* current = root;
    while (current) {
        if (current->info == value) {
            if(current->right){
                if(current->right->left){
                    return current->right->left;
                }
                return current->right;
            }
            else{
                while (current->parent && current->parent->info < value) {
                    current = current->parent;
                }
                if (current->parent == nullptr){
                    return nullptr;
                }
                else{
                    return current->parent;
                }
            }
        }
        else if (current->info > value) {
            current = current->left;
        }
        else if (current->info < value) {
            current = current->right;
        }
    }
    return nullptr;
}


// returns the successor value of the given value or 0 if there is none
template<class T>
T IntBST<T>::getSuccessor(T value) const{
    if (getSuccessorNode(value) == nullptr) {
        return 0;
    }
    return getSuccessorNode(value)->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
template<class T>
bool IntBST<T>::remove(T value){
    Node* current = root;
     //check if node is a leaf
    while(current){
        if (current->info == value) {
            if (current->left == nullptr && current->right == nullptr) {
                
                if(current->parent == nullptr){ // checking if it is root
                    root = nullptr;
                }
                else if (current == current->parent->left) {
                    current->parent->left = nullptr;
                }
                else if (current == current->parent->right) {
                    current->parent->right = nullptr;
                }
                
                delete current;
                return true;
            }
        // check if node has right child and no left child
            else if (current->right && current->left == nullptr) {
                Node* rightChild = current->right; 
                if(current->parent == nullptr){ // checking if it is root
                    root = rightChild;
                    rightChild->parent = nullptr;
                }
                else if(current->parent->right == current){
                    current->parent->right = rightChild;
                    rightChild->parent = current->parent;
                }
                else if(current->parent->left == current){
                    current->parent->left = rightChild;
                    rightChild->parent = current->parent;
                }
                delete current;
                return true;
            }
        // check if node has left child and no right child
            else if (current->left && current->right == nullptr) {
                Node* leftChild = current->left; 
                if(current->parent == nullptr){ // checking if it is root
                    root = leftChild;
                    leftChild->parent = nullptr;
                }
                else if (current->parent->left == current) {
                    current->parent->left = leftChild;
                    leftChild->parent = current->parent;
                }
                else if (current->parent->right == current) {
                    current->parent->right = leftChild;
                    leftChild->parent = current->parent;
                }
                
                delete current;
                return true;
            }
        //check if node has 2 children
            Node* temp = current->right;
            if (current->right && current->left) {
                while (temp->left) {
                    temp = temp->left;
                }
                current->info = temp->info;
                current = current->right;
                value = temp->info;
            }
            
        }
        else if (current->info > value) {
            current = current->left;
        }
        else if (current->info < value) {
            current = current->right;
        }
    }
    return false;   
           
} 

