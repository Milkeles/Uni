#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <queue>

template <class T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node<T>* left;
        Node<T>* right;

        node(const & T data) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    node<T>* root;
    void destroy(Node* node);

public:
    BinaryTree();
    ~BinaryTree();
    void insert(Node*, const T&);
    bool search(Node*, const T&);
    void remove(Node*, const T&);
    void leftRootRightTraversal(Node*);
    void rightRootLeftTraversal(Node*);
    void rootLeftRightTraversal(Node*);
    void rootRightLeftTraversal(Node*);
    void leftRightRootTraversal(Node*);
    void rightLeftRootTraversal(Node*);
    void levelTraversal(Node*);
};

template <class T>
BinaryTree<T>::BinaryTree() {
    root = nullptr;
}

template <class T>
void BinaryTree<T>::destroy(Node* node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template <class T>
BinaryTree<T>::~BinaryTree() {
    destroy(root);
}


template <class T>
void BinaryTree<T>::insert(Node* node, const T& value) {
    if (node == nullptr) {
        node = new Node(value);
    } else if (node->data > value) {
        insert(node->left, value);
    } else if (node-> data < value) {
        insert(node->right, value);
    }
}

template <class T>
bool BinaryTree<T>::search(Node* node, const T& value) {
    if (node == nullptr) {
        return false;
    }
    else if (node->data == value) {
        return true;
    } else if (node->data < value) {
        search(node->left);
    } else {
        search(node->right)
    }
}

template <class T>
void BinaryTree<T>::remove(Node* node, const T& value) {
    if (node == nullptr) {
        return;
    } else if (node->data > value) {
        remove(node->left, value);
    } else if (node->data < value) {
        remove(node->right, value);
    } else if (node->data == value) {
        if (node->left != nullptr && node->right != nullptr) {
            Node<T>* min = node->right;

            while(min->left != nullptr) {
                min = min->left;
            }
            node->data = min->data;
            remove(node->right, min->data);
        } else {
            Node<T>* temp = node;
            if (node->left != nullptr) {
                node = node->left;
            } else {
                node = node->right;
            }
            delete temp;
        }
    }
}

template <class T>
void BinaryTree<T>::leftRootRightTraversal(Node* node = nullptr) {
    if (node == nullptr && root != nullptr) {
        node = root;
    } else {
        return;
    }

    if (node->left != nullptr) {
        leftRootRightTraversal(node->left);
    }

    std::cout << node->data << ' ';

    if (node->right != nullptr) {
        leftRootRightTraversal(node->right);
    }
}

template <class T>
void BinaryTree<T>::rightRootLeftTraversal(Node* node = nullptr) {
    if (node == nullptr && root != nullptr) {
        node = root;
    } else {
        return;
    }

    if (node->right != nullptr) {
        rightRootLeftTraversal(node->right);
    }

    std::cout << node->data << ' ';

    if (node->left != nullptr) {
        rightRootLeftTraversal(node->left);
    }
}

template <class T>
void BinaryTree<T>::rootLeftRightTraversal(Node* node = nullptr) {
    if (node == nullptr && root != nullptr) {
        node = root;
    } else {
        return;
    }

    std::cout << node->data << ' ';
    if (node->left != nullptr) {
        rootLeftRightTraversal(node->left);
    }

    if (node->right != nullptr) {
        rootLeftRightTraversal(node->right);
    }
}


template <class T>
void BinaryTree<T>::rootRightLeftTraversal(Node* node = nullptr) {
    if (node == nullptr && root != nullptr) {
        node = root;
    } else {
        return;
    }

    std::cout << node->data << ' ';
    if (node->right != nullptr) {
        rootRightLeftTraversal(node->right);
    }

    if (node->left != nullptr) {
        rootRightLeftTraversal(node->left);
    }
}

template <class T>
void BinaryTree<T>::leftRightRootTraversal(Node* node = nullptr) {
    if (node == nullptr && root != nullptr) {
        node = root;
    } else {
        return;
    }

    if (node->left != nullptr) {
        leftRightRootTraversal(node->left);
    }

    if (node->right != nullptr) {
        leftRightRootTraversal(node->right);
    }
    std::cout << node->data << ' ';
}

template <class T>
void BinaryTree<T>::rightLeftRootTraversal(Node* node = nullptr) {
    if (node == nullptr && root != nullptr) {
        node = root;
    } else {
        return;
    }

    if (node->right != nullptr) {
        rightLeftRootTraversal(node->right);
    }

    if (node->left != nullptr) {
        rightLeftRootTraversal(node->left);
    }
    std::cout << node->data << ' ';
}

template <class T>
void BinaryTree<T>::levelTraversal(Node * node = nullptr) {
    if (node == nullptr && root != nullptr) {
        node = root;
    } else {
        return;
    }

    std::queue<Node*> q;
    q.push(node);

    while(!q.empty()) {
        Node * current = q.pop();
        std::cout << current->data << ' ';
        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }

    std::cout << std::endl;
}

#endif
