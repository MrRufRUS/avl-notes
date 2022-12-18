#include<iostream>
#include<string>

#define SPACE 10

using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;
    Node* next;
    Node() {
        value = 0;
        left = NULL;
        right = NULL;
        next = this;
    }
    Node(int v) {
        value = v;
        left = NULL;
        right = NULL;
        next = this;
    }
};

class AVLTree {
public:
    Node* root;
    AVLTree() {
        root = NULL;
    }
    bool isTreeEmpty() {
        if (root == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
    int height(Node* head) {
        if (head == NULL)
            return -1;
        else {
            int lheight = height(head->left);
            int rheight = height(head->right);

            if (lheight > rheight)
                return (lheight + 1);
            else return (rheight + 1);
        }
    }
    int getBalanceFactor(Node* n) {
        if (n == NULL)
            return -1;
        return height(n->left) - height(n->right);
    }
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        return x;
    }
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        return y;
    }
    void printList(Node* head) {

        if (head != NULL) {

            Node* temp = head;
            do
            {
                cout << temp->value << " ";
                temp = temp->next;
            } while (temp != head);
            cout << endl;
        }
    }
    int countOfRepeats(Node* head) {
        int count = 0;
        if (head != NULL) {

            Node* temp = head;
            do
            {
                count++;
                temp = temp->next;
            } while (temp != head);
        }
        return count;
    }
    void insertAtTail(Node*& head, int val) {
        Node* n = new Node(val);
        if (head == NULL) {
            n->next = n;
            head = n;
        }
        else {
            Node* temp = head;

            while (temp->next != head) {
                temp = temp->next;
            }

            temp->next = n;
            n->next = head;
        }
    }
    Node* insert(Node* head, int val) {

        Node* new_node = new Node(val);
        if (head == NULL) {
            head = new_node;
            return head;
        }

        if (new_node->value < head->value) {
            head->left = insert(head->left, val);
        }
        else if (new_node->value > head->value) {
            head->right = insert(head->right, val);
        }
        else if (new_node->value == head->value) {
            insertAtTail(head, val);
        }

        int bf = getBalanceFactor(head);
        if (bf > 1 && new_node->value < head->left->value)
            return rightRotate(head);

        if (bf < -1 && new_node->value > head->right->value)
            return leftRotate(head);

        if (bf > 1 && new_node->value > head->left->value) {
            head->left = leftRotate(head->left);
            return rightRotate(head);
        }

        if (bf < -1 && new_node->value < head->right->value) {
            head->right = rightRotate(head->right);
            return leftRotate(head);
        }

        return head;

    }
    Node* maxValueNode(Node* node) {
        Node* current = node;
        while (current->right != NULL) {
            current = current->right;
        }
        return current;
    }
    void deleteAtTail(Node* head) {
        Node* temp = head;
        while (temp->next->next != head) {
            temp = temp->next;
        }

        Node* todelete = temp->next;
        temp->next = head;
        
        delete todelete;
    }
    Node* deleteNode(Node* head, int v) {
        if (head == NULL) {
            return NULL;
        }
        else if (v < head->value) {
            head->left = deleteNode(head->left, v);
        }
        else if (v > head->value) {
            head->right = deleteNode(head->right, v);
        }
        else {
            if (countOfRepeats(head) - 1 != 0) {
                deleteAtTail(head);
            }
            else {
            if (head->left == NULL) {
                Node* temp = head->right;
                delete head;
                return temp;
            }
            else if (head->right == NULL) {
                Node* temp = head->left;
                delete head;
                return temp;
            }
            else {
                Node* temp = maxValueNode(head->left);
                head->value = temp->value;
                head->right = deleteNode(head->right, temp->value);
            }
            }
        }

        int bf = getBalanceFactor(head);
        if (bf == 2 && getBalanceFactor(head->left) >= 0)
            return rightRotate(head);
        else if (bf == 2 && getBalanceFactor(head->left) == -1) {
            head->left = leftRotate(head->left);
            return rightRotate(head);
        }
        else if (bf == -2 && getBalanceFactor(head->right) <= -0)
            return leftRotate(head);
        else if (bf == -2 && getBalanceFactor(head->right) == 1) {
            head->right = rightRotate(head->right);
            return leftRotate(head);
        }

        return head;
    }
    void printTree(Node* head, int space) {
        if (head == NULL)
            return;
        space += SPACE;
        printTree(head->right, space);
        cout << endl;
        for (int i = SPACE; i < space; i++)
            cout << " ";
        printList(head);
        printTree(head->left, space);
    }
    Node* recursiveSearch(Node* head, int val) {
        if (head == NULL || head->value == val)
            return head;

        else if (val < head->value)
            return recursiveSearch(head->left, val);

        else
            return recursiveSearch(head->right, val);
    }
    void dispose(Node* head)
    {
        if (head == NULL) {
            return;
        }

        dispose(head->left);
        dispose(head->right);
        delete head;
        head = NULL;
    }
    int count(Node* head) {
        if (head == NULL) {
            return 0;
        }
        return countOfRepeats(head) +  count(head->left) + count(head->right);
    }
};
void inputNumber(AVLTree& obj, string code, string number) {
    obj.root = obj.insert(obj.root, stoi(code));
    for (int i = 0; i < number.length(); i++) {
        obj.root = obj.insert(obj.root, number[i] - '0');
    }
}

int main() {
    AVLTree obj;
        Node* new_node = new Node();

            /*obj.root = obj.insert(obj.root, 10);
            obj.root = obj.insert(obj.root, 10);
            obj.root = obj.insert(obj.root, 10);
            obj.root = obj.insert(obj.root, 10);
            obj.root = obj.insert(obj.root, 10);
            obj.root = obj.insert(obj.root, 5);
            obj.root = obj.insert(obj.root, 3);

            new_node = obj.recursiveSearch(obj.root, 5);
            if (new_node != NULL) {
                cout << "Value found" << endl;
            }
            else {
                cout << "Value NOT found" << endl;
            }
            
            obj.root = obj.deleteNode(obj.root, 10);
            cout << "PRINT 2D: " << endl;
            */
            string code = "999";
            string number = "12334560000";
            inputNumber(obj, code, number);
            obj.printTree(obj.root, 5);
            cout << obj.count(obj.root) << endl;
            obj.root = obj.deleteNode(obj.root, 0);
            obj.root = obj.deleteNode(obj.root, 0);
            obj.root = obj.deleteNode(obj.root, 0);
            obj.root = obj.deleteNode(obj.root, 3);
            obj.printTree(obj.root, 5);
            cout << obj.count(obj.root) << endl;
            obj.root = obj.deleteNode(obj.root, 0);
            obj.printTree(obj.root, 5);
            cout << obj.count(obj.root) << endl;
            obj.dispose(obj.root);

    return 0;
}