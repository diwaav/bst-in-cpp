/********************************************************************************* 
* Diwa Ashwini Vittala, dashwini
* 2022 Spring CSE101 PA7
* Dictionary.cpp
* Dictionary ADT
**********************************************************************************/

#include "Dictionary.h"
#include <iostream>
#include <string>

/*** Helper Functions ***/

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nullptr) {
        inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nullptr) {
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
    if (R != nullptr) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R) {
        int compare = k.compare(R->key);
        if (compare == 0) {
            return R;
        } else if (compare < 0) {
            return search(R->left, k);
        } else {
            return search(R->right, k);
        }
    }
    return nil;
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    Node *temp = R;
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    return temp;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
    Node *temp = R;
    while (temp->right != nullptr) {
        temp = temp->right;
    }
    return temp;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk. If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nullptr) {
        return nil;
    }
    if (N->right) {
        return findMin(N->right);
    } else if ((N->parent) && N->parent->left == N) {
        return N->parent;
    } else {
        Node *temp = N;
        while ((temp->parent != nil) &&  (temp == (temp->parent)->right)) {
            temp = temp->parent;
        }
        return temp->parent;
    }
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nullptr) {
        return nil;
    }
    if (N->left) {
        return findMax(N->left);
    } else if ((N->parent) && N->parent->right == N) {
        return N->parent;
    } else {
        Node *temp = N;
        while ((temp->parent != nil) &&  (temp == (temp->parent)->left)) {
            temp = temp->parent;
        }
        return temp->parent;
    }


}

/*** Constructors and Destructors ***/
// Node constructor
Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    nil = nullptr;
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    nil = nullptr;
    root = nullptr;
    current = nullptr;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
    return;
}

// Destructor
Dictionary::~Dictionary() {
    postOrderDelete(root);
    num_pairs = 0;
    root = current = nullptr;
    return;
}

/*** Access functions ***/

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    if (search(root, k) != nil) {
        return true;
    } else {
        return false;
    }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    Node *N = search(root, k);
    if (N == nil) {
        throw std::logic_error("Dictionary: getValue(): Value not in Dictionary.\n");
    } else {
        return N->val;
    }
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    if (current != nil) {
        return true;
    } else {
        return false;
    }
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey(): Key not in Dictionary.\n");
    } else {
        return current->key;
    }
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): Value not in Dictionary.\n");
    } else {
        return current->val;
    }
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    postOrderDelete(root);
    root = nil = current = nullptr;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    if (root == nullptr) {
        root = new Node(k, v);
        num_pairs = 1;
        return;
    }
    Node* N = search(root, k);
    if (N != nullptr) {
        N->val = v;
        return;
    } else {
        Node *y;
        Node *x = root;
        Node *z = new Node(k, v);
        int compare;
        while (x != nullptr) {
            y = x;
            compare = k.compare(x->key);
            if (compare < 0) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if(compare < 0) {
            y->left = z;
        } else {
            y->right = z;
        }
        num_pairs += 1;
    }
}

// transplant()
// Transplants a subtree - helper for remove()
void Dictionary::transplant(Node *u, Node *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != nullptr) {
        v->parent = u->parent;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    Node *z = search(root, k);
    if (z == nullptr) {
        throw std::logic_error("Dictionary: remove(): Key not in Dictionary.\n");
    }

    if (z->left == nullptr) {
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        transplant(z, z->left);
    } else {
        Node *y = findMin(z->right);
        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    num_pairs -= 1;
    if (z == current) {
        current = nil;
    }
    delete z;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    if (size() > 0) {
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    if (size() > 0) {
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): Value not in Dictionary.\n");
    } else {
        current = findNext(current);
    }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): Value not in Dictionary.\n");
    } else {
        current = findPrev(current);
    }
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    if (num_pairs != D.num_pairs) {
        return false;
    } else {
        keyType first, second;
        inOrderString(first, root);
        inOrderString(second, D.root);
        if (first == second) {
            return true;
        } else {
            return false;
        }
    }
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if(this != &D){ // not self assignment
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
     }
     return *this;
}
