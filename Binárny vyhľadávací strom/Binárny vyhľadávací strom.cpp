#include "pch.h"
#include <iostream>
#include <string>
#include <functional>
using namespace std;


// BST je datova struktura umoznujuca rychle vyhladavanie uzlov.
//
// Vlastnost BST:
//  * pre lubovolny uzol U v BST plati:
//      a) uzly v lavom podstrome su mensie ako U
//      b) uzly v pravom podstrome su vacsie ako U
//  * vsetky uzly v BST su unikatne

struct Node
{
	
	int data;      
	Node* parent;   
	Node *left;     
	Node *right;    


	Node(int data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) :
		data(data),
		parent(parent),
		left(left),
		right(right)
	{
	}
};

// TODO: Doprogramujte vyznacene metody


class BST
{
public:
	
	BST(Node* root = nullptr) :
		root(root)
	{
	}

	~BST() {
		this->removeTree();
	}

	// TODO 1: dokoncite funkciu na vlozenie uzla s hodnotou 'data' do BST
	bool insert(int data) {
		return insert(this->root, data);
	}

	// TODO 2: dokoncite kopirovaci konstruktor, ktory vytvori BST ako 
	// kopiu ineho BST
	BST(const BST& otherBST) {
		copyTree(otherBST.root);
	}

	// TODO 3: dokoncite funkciu na vyhladanie uzla s hodnotou 'data'
	Node* search(int data) {
		return search(this->root, data);
	}

	// TODO 4: dokoncite funkciu na vymazanie uzla s hodnotou 'data'
	bool remove(int data) {
		return remove(this->root, data);
	}

	// TODO 5: dokoncite funkciu na vymazanie celeho BST
	void removeTree() {
		removeTree(this->root);
		this->root = nullptr;
	}

	// TODO 6: dokoncite funkciu na vypis stromu stylom pre-order
	void printPreOrder() {
		printPreOrder(this->root);
	}

	// TODO 7: dokoncite funkciu na vypis stromu stylom in-order
	void printInOrder() {
		printInOrder(this->root);
	}

	// TODO 8: dokoncite funkciu na vypis stromu stylom post-order
	void printPostOrder() {
		printPostOrder(this->root);
	}

	// TODO 9: dokoncite funkciu na vypis stromu stylom level-order (do sirky)
	void printLevelOrder() {
		int i = 0;
		while (printLevel(this->root, i)) {
			i++;
		}
	}

	// TODO 10: dokoncite funkciu na zistenie hlbky uzla s hodnotou 'data'
	int depth(int data) {
		return depth(this->root, data, 0);
	}

	// TODO 11: dokoncite funkciu na zistenie maximalnej hlbky stromu
	// Poznamka: koren ma hlbku 0.
	int treeDepth() {
		return treeDepth(this->root);
	}

	// TODO 12: dokoncite funkciu na zistenie poctu prvkov v strome
	int count() {
		return count(this->root);
	}

	// TODO 13: dokoncite funkciu 'applyFunction', ktora aplikuje
	//
	// vami definovanu funkciu 'fn' na kazdy uzol v BST.
	//
	// Funkcia 'fn' musi byt typu void fn(Node*), kde parametrom je povodny uzol.
	// Definujte si lubovolnu funkciu 'fn', ktora splna hore uvedene kriteria.
	//
	// Priklad definicie funkcie 'fn', ktora vypise potomkov zadaneho uzla:
	//
	// void fn(Node* node){
	//    if(node){
	//      cout << "Node: [" << node->data << "]" << endl;
	//      cout << " ---> Left child: " << ((node->left) ? to_string(node->left->data) : "n/a") << endl;
	//      cout << " ---> Right child: " << ((node->right) ? to_string(node->right->data) : "n/a") << endl;
	//    }
	// }
	// 
	// Namiesto definicie funkcie 'fn' mozete pouzit lambda vyraz.

	void applyFunctionToEachNode(const function<void(Node*)>& fn) {
		applyFunctionToEachNode(this->root, fn);
	}

private:
	Node* root;  


	bool insert(Node* current, int data) {

	
		if (!current) {
			this->root = new Node(data);
			return true;
		}
		
		if (data == current->data) {
			return false;
		}
		
		else if (data < current->data) {
			if (current->left) {
				return insert(current->left, data);
			}
			else {
				current->left = new Node(data, current);
			}
		}
		
		else {
			if (current->right) {
				return insert(current->right, data);
			}
			else {
				current->right = new Node(data, current);
			}
		}
		return true;
	}

	
	void copyTree(Node* current) {
		if (current) {
			this->insert(current->data);
			copyTree(current->left);
			copyTree(current->right);
		}
	}

	Node* search(Node* current, int data) {
		if (!current) {
			return nullptr;
		}
		if (current->data == data) {
			return current;
		}
		else if (data < current->data) {
			return search(current->left, data);
		}
		else {
			return search(current->right, data);
		}
	}

	bool remove(Node* current, int data) {
		if (!current) {
			return false;
		}
		if (current->data == data) {
			if (!current->right) {
				if (this->root == current) {
					this->root = current->left;
				}
				else {
					if (current == current->parent->left) {
						current->parent->left = current->left;
					}
					else {
						current->parent->right = current->left;
					}
				}
				if (current->left) {
					current->left->parent = current->parent;
				}
				delete current;
			}
			else if (!current->left) {
				if (this->root == current) {
					this->root = current->right;
				}
				else {
					if (current == current->parent->left) {
						current->parent->left = current->right;
					}
					else {
						current->parent->right = current->right;
					}
				}
				if (current->right) {
					current->right->parent = current->parent;
				}
				delete current;
			}
			
			else {
				Node* rightTreeMin = findMin(current->right); 
				current->data = rightTreeMin->data; 
				remove(current->right, rightTreeMin->data);
			}
			return true;
		}
		
		else if (current->data > data) {
			return remove(current->left, data);
		}
		else {
			return remove(current->right, data);
		}
	}

	
	void removeTree(Node* current) {
		if (current) {
			removeTree(current->left);
			removeTree(current->right);
			delete current;
		}
	}

	
	void printPreOrder(Node* current) {
		if (current) {
			cout << current->data << " ";
			printPreOrder(current->left);
			printPreOrder(current->right);
		}
	}

	void printInOrder(Node* current) {
		if (current) {
			printInOrder(current->left);
			cout << current->data << " ";
			printInOrder(current->right);
		}
	}

	void printPostOrder(Node* current) {
		if (current) {
			printPostOrder(current->left);
			printPostOrder(current->right);
			cout << current->data << " ";
		}
	}

	bool printLevel(Node* current, int level) {
		if (current) {
			if (level == 0) {
				cout << current->data << " ";
				return true;
			}
			bool isLevelLeft = printLevel(current->left, level - 1);
			bool isLevelRight = printLevel(current->right, level - 1);
			if (isLevelLeft || isLevelRight) {
				return true;
			}
			return false;
		}
		return false;
	}

	int depth(Node* current, int data, int d) {
		if (current) {
			if (current->data == data) {
				return d;
			}
			else if (data < current->data) {
				return depth(current->left, data, d + 1);
			}
			else {
				return depth(current->right, data, d + 1);
			}
		}
		return -1;
	}

	int treeDepth(Node* current) {
		if (current) {
			int ld = 1 + treeDepth(current->left);
			int rd = 1 + treeDepth(current->right);
			if (ld > rd) {
				return ld;
			}
			return rd;
		}
		return -1;
	}

	int count(Node* current) {
		if (current) {
			return 1 + count(current->left) + count(current->right);
		}
		return 0;
	}

	void applyFunctionToEachNode(Node* current, const function<void(Node*)>& fn) {
		if (!current) return;
		applyFunctionToEachNode(current->left, fn);
		fn(current);
		applyFunctionToEachNode(current->right, fn);
	}

	Node* findMin(Node* current) {
		if (current) {
			while (current->left) {
				current = current->left;
			}
		}
		return current;
	}
};

void fn(Node* node) {
	if (node) {
		cout << "Node: [" << node->data << "]" << endl;
		cout << " ---> Left child: " << ((node->left) ? to_string(node->left->data) : "n/a") << endl;
		cout << " ---> Right child: " << ((node->right) ? to_string(node->right->data) : "n/a") << endl;
	}
}

int main() {
	BST tree;

	// TODO: riadne otestujte vsetky operacie v triede BST

	// 1. insert
	cout << "Insert: " << endl;
	int values[]{ 4,2,1,3,6,5,7 };
	for (int v : values) {
		cout << v << ": " << (tree.insert(v) ? "inserted" : "not inserted (duplicate)") << endl;
	}

	cout << endl;

	// 2. copy constructor
	cout << "Copy constructor: " << endl;
	BST tree2(tree);
	cout << "Copy of BST created" << endl;

	cout << endl;

	// 3. search
	cout << "Search: " << endl;
	int to_search[]{ 5,1,9,4,11,3,8,50 };
	for (int t : to_search) {
		cout << t << ": " << (tree.search(t) ? "found" : "not found") << endl;
	}

	cout << endl;

	// 4. remove
	cout << "Remove: " << endl;
	int to_delete[]{ 4,2,3,10 };
	for (int r : to_delete) {
		// cout << r << ": " << (tree.remove(r) ? "removed" : "not removed (not found)") << endl; // odkomentujte pre otestovanie
	}

	cout << endl;

	// 5. remove tree
	cout << "Remove tree: " << endl;
	// tree.removeTree(); // odkomentujte pre otestovanie
	// cout << "Tree removed" << endl;

	cout << endl;

	// 6. pre-order print
	cout << "Pre-Order print: " << endl;
	tree.printPreOrder();

	cout << endl << endl;

	// 7. in-order print
	cout << "In-Order print: " << endl;
	tree.printInOrder();

	cout << endl << endl;

	// 8. post-order print
	cout << "Post-Order print: " << endl;
	tree.printPostOrder();

	cout << endl << endl;

	// 9. level-order print
	cout << "Level-Order print: " << endl;
	tree.printLevelOrder();

	cout << endl << endl;

	// 10. depth of node
	cout << "Depth of node:" << endl;
	for (int i : values) {
		cout << i << ": " << tree.depth(i) << endl;
	}

	cout << endl;

	// 11. max depth of tree
	cout << "Max depth of tree:" << endl;
	cout << tree.treeDepth() << endl;

	cout << endl;

	// 12. number of nodes in tree
	cout << "Number of nodes in tree:" << endl;
	cout << tree.count() << endl;

	cout << endl;

	// 13. apply function to each node
	cout << "Apply function to each node:" << endl;
	tree.applyFunctionToEachNode(fn);

	// string label{ "[Node]" };
	// tree.applyFunctionToEachNode([label](Node* node) { cout << label << ": " << node->data << endl; });

	cout << endl;

	return 0;
}