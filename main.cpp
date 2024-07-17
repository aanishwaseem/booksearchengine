#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
using namespace std;


template <class type>
class tree {
private:
	class Node {
	public:
		type data;
		Node* left;
		Node* right;
		Node(type d = 0) {
			data = d;
			left = NULL;
			right = NULL;
		}

	};

	Node* root;

public:
	tree() { root = NULL; }
	void insertR(type d, Node*& node) {

		if (node == NULL) {

			node = new Node(d);

		}
		else if (node->data > d)

			insertR(d, node->left);

		else if (node->data < d)

			insertR(d, node->right);
	}
	void insertR(type d) {
		insertR(d, root);

	}
	void visit(Node* ptr) { cout << ptr->data << ""; }
	bool searchR(Node* node, type d)
	{
		if (node) {
			if (node->data > d)

				return searchR(node->left, d);

			else if (node->data < d)

				return searchR(node->right, d);

			else
			{
				return true;
			}
		}
		else
			return false;

	}
	bool searchR(type d) {

		return searchR(root, d);

	}
	void deleteR(type d, Node*& node)
	{

		if (node) {

			if (d > node->data)

				deleteR(d, node->right);

			else if (d < node->data)

				deleteR(d, node->left);

			else

				deleteNode(node);

		}

	}
	void deleteNode(Node*& node) {

		Node* temp = node;

		if (node->left == NULL) {

			node = node->right;

			delete temp;

		}

		else if (node->right == NULL) {

			node = node->left;

			delete temp;

		}

		else {

			type d = getPredecessor(node->left);

			node->data = d;

			deleteR(d, node->left);

		}

	}
	type getPredecessor(Node* n)

	{

		while (n->right != NULL)

			n = n->right;

		return n->data;

	}
	void InOrder(Node* t)

	{

		if (t) {

			InOrder(t->left);

			visit(t);

			InOrder(t->right);

		}

	}

	void Destroy(Node*& node) {

		if (node) {

			Destroy(node->left);

			Destroy(node->right);

			delete node;

		}

	}
	~tree() { Destroy(root); }
};

struct wordDetails {
	int chapter;
	int page;
	int line;
	wordDetails() { chapter = -1, page = -1, line = -1; }
	wordDetails(int chap, int pg, int line) : chapter(chap), page(pg), line(line) {}

	bool operator>(wordDetails obj) {
		return (chapter > obj.chapter);
	}
	bool operator<(wordDetails obj) {
		return (chapter < obj.chapter);
	}
	friend ostream& operator << (ostream&, wordDetails);
};

ostream& operator << (ostream& COUT, wordDetails details) {
	COUT << "Chapter: " << details.chapter << ", Page: "<<details.page<<", Line: "<<details.line << endl;
	//COUT << "Page: " << details.page << endl;
	//COUT << "Line: " << details.line << endl;
	return COUT;
}

class occurance {
public:
	occurance() {}

	occurance(string word) : word(word) {}
	void addInList(wordDetails detail) {
		dll.insert(dll.end(), detail);
	}
	bool operator>(string obj) {
		return (word > obj);
	}
	bool operator<(string obj) {
		return (word < obj);
	}
	bool operator>(occurance obj) {
		return (word > obj.word);
	}
	bool operator==(occurance obj) {
		return (word == obj.word);
	}
	string getWord() {
		return word;
	}
	void print() {
		cout << "- " << word << endl << endl;
		int i = 1;
		for (list<wordDetails>::iterator it = dll.begin(); it != dll.end(); it++, i++) {
			cout << "> " << i << ":" << endl;
			cout << *it << endl;
		}
		cout << "------------------------------------------------------------------------" << endl;
	}
	friend class tree<occurance>;
private:
	string word;
	list<wordDetails> dll;
};


template <>
class tree<occurance> {
private:
	class Node {
	public:
		occurance data;
		Node* left;
		Node* right;
		Node(occurance d) {
			data = d;
			left = NULL;
			right = NULL;
		}
	};

	Node* root;
public:
	tree() { root = NULL; }
	void insertR(string d, wordDetails detail, Node*& node) {

		if (node == NULL) {
			occurance word(d);
			word.addInList(detail);
			node = new Node(word);
		}
		else if (node->data > d)

			insertR(d, detail, node->left);

		else if (node->data < d)

			insertR(d, detail, node->right);
		else
			node->data.addInList(detail);
	}
	bool search(string word, Node* node) {
		if (node == NULL)
			return false;
		else if (node->data < word)
			return search(word, node->right);
		else if (node->data > word)
			return search(word, node->left);
		else {
			node->data.print();
			return true;
		}
	}
	void store(Node* node, vector<occurance>& arr) {
		if (node != NULL) {
			store(node->left, arr);
			arr.push_back(node->data);
			store(node->right, arr);
		}
	}
	vector<occurance> getArrayFromBST() {
		vector<occurance> res;
		store(root, res);
		return res;
	}
	void mergeR(vector<occurance> arr, vector<occurance> arr2, vector<occurance>& res, int i1, int& i2) {
		if (i2 >= arr2.size())
			return;
		if (i1 < arr.size()) {
			if (arr2[i2].word > arr[i1].word)
				return;
		}
		res.push_back(arr2[i2]);
		i2++;
		mergeR(arr, arr2, res, i1, i2);
	}
	void merge(vector<occurance> arr, vector<occurance> arr2, vector<occurance>& res, int i1, int i2) {
		if (i1 < arr.size()) {
			mergeR(arr, arr2, res, i1, i2);
			res.push_back(arr[i1]);
			i1++;
			merge(arr, arr2, res, i1, i2);
		}
		else
			mergeR(arr, arr2, res, i1, i2);
	}
	vector<occurance> merge(vector<occurance> arr, vector<occurance> arr2) {
		vector<occurance> res;
		merge(arr, arr2, res, 0, 0);
		return res;
	}
	void constructBSTFromArray(tree<occurance>& bst, vector<occurance> arr, int first, int last) {
		if (first > last)
			return;
		int mid = (first + last) / 2;
		bst.insert(arr[mid]);
		constructBSTFromArray(bst, arr, first, mid - 1);
		constructBSTFromArray(bst, arr, mid + 1, last);
	}
	void constructMergedBST(tree<occurance>& tree2, tree<occurance> &mergedBST) {
		vector<occurance> arr = getArrayFromBST();
		vector<occurance> arr2 = tree2.getArrayFromBST();
		vector<occurance> res = merge(arr, arr2);
		constructBSTFromArray(mergedBST, res, 0, res.size() - 1);
	}
	bool search(string word) {
		bool ret = search(word, root);
		if (!ret)
			cout << ">> NOT FOUND" << endl;
		return ret;
	}
	void insertR(string d, wordDetails details) {
		insertR(d, details, root);

	}
	void insert(occurance d, Node*& node) {

		if (node == NULL) {

			node = new Node(d);
		}
		else if (node->data.word > d.word)

			insert(d, node->left);

		else if (node->data.word < d.word)

			insert(d, node->right);
		else {
			node->data.dll.merge(d.dll);
		}
	}
	void insert(occurance data) {
		insert(data, root);
	}
	void inorderPrint(Node* node) {
		if (node != NULL) {
			inorderPrint(node->left);
			node->data.print();
			inorderPrint(node->right);
		}
	}
	void inorderPrint() {
		inorderPrint(root);
	}
	occurance getPredecessor(Node* n) {
		while (n->right != NULL)
			n = n->right;
		return n->data;
	}

	void deleteI(string d) {
		Node* parent = root;
		Node* child = root;
		bool flag = false;
		while (child && child->data.word != d) {
			parent = child;
			if (parent->data > d)
				child = child->left;
			else if (parent->data < d)
				child = child->right;
		}
		if (child) { //if data is found
			flag = true;
			if (child == root) {
				deleteNode(root);
			}
			else if (parent->left == child) {
				deleteNode(parent->left);
			}
			else {
				deleteNode(parent->right);
			}
		}
		if (!flag)
			cout << "Word " << d << " not found" << endl;
	}
	void deleteNode(Node*& node) {
		Node* temp = node;
		if (node->left == NULL) {
			node = node->right;
			delete temp;
		}
		else if (node->right == NULL) {
			node = node->left;
			delete temp;
		}
		else {
			occurance predecessor = getPredecessor(node->left);
			deleteI(predecessor.word);
			node->data.word = predecessor.word;
			node->data.dll.swap(predecessor.dll);
			cout << ">> Word deleted successfully" << endl;
		}
	}
	void Destroy(Node*& node) {

		if (node) {

			Destroy(node->left);

			Destroy(node->right);

			delete node;

		}

	}
	~tree() { Destroy(root); }
};

void populateStopwordBST(tree<string>& bst) {
	ifstream fr("stopwords.txt");
	string buffer;
	while (fr >> buffer) {
		bst.insertR(buffer);
	}
	fr.close();
}


// Function to convert a string to lowercase
std::string ToLower(const std::string& str) {
	std::string result = str;
	for (char& c : result) {
		if (c == ',' || c == '(' || c == ')' || c == '.' || c == '-')
			c = ' ';
		c = std::tolower(static_cast<unsigned char>(c));
	}
	return result;
}

void populateSpecializedBST(string filename, tree<string>& stopwords, tree<occurance>& searchtree) {
	// Open the text file for reading
	std::ifstream inputFile(filename);
	if (!inputFile) {
		std::cerr << "Error opening the file." << std::endl;
		return;
	}

	std::string line, word;
	int lineNumber = 0;
	int chapter = 0;
	int page = 0;
	bool found = false;

	while (std::getline(inputFile, line)) {
		size_t pos = 0;
		std::string lineLower = ToLower(line); // Convert line to lowercase for case-insensitive search
		stringstream ss(lineLower);

		if (line.substr(0, 9) == "# Chapter") {
			ss >> word;
			ss >> word;
			ss >> word;
			chapter = std::stoi(word);
		}
		else if (line.substr(0, 6) == "# Page") {
			ss >> word;
			ss >> word;
			ss >> word;
			page = std::stoi(word);
			lineNumber = 0;
		}
		else {
			wordDetails detail(chapter, page, lineNumber);
			while (ss >> word) {

				if (!stopwords.searchR(word))
					searchtree.insertR(word, detail);
			}
		}
		lineNumber++;
	}
	inputFile.close();

}

void findcommon2(vector<occurance> arr1, vector<occurance> arr2, int i1, int& i2) {
	if (i2 >= arr2.size())
		return;
	if (arr2[i2] > arr1[i1])
		return;
	else if (arr2[i2] == arr1[i1]) {
		cout << "> " << arr2[i2].getWord() << endl;
		i2++;
		return;
	}
	i2++;
	findcommon2(arr1, arr2, i1, i2);
}

void findcommon(vector<occurance> arr1, vector<occurance> arr2, int i1, int i2) {
	if (i1 < arr1.size() && i2 < arr2.size()) {
		findcommon2(arr1, arr2, i1, i2);
		i1++;
		findcommon(arr1, arr2, i1, i2);
	}
}

void findcommon(tree<occurance>& bst, tree<occurance>& bst2) {
	vector<occurance> arr1 = bst.getArrayFromBST();
	vector<occurance> arr2 = bst2.getArrayFromBST();
	cout << "\t\t------------------------\n";
	cout << "\t\t\tCOMMON WORDS\n";
	cout << "\t\t------------------------\n";
	findcommon(arr1, arr2, 0, 0);
}


void clear() {
	int choice;
	cout << "GO back" << endl;
	cin >> choice;
	system("cls");  
}


int main() {
	tree<string> stopwordBST;
	populateStopwordBST(stopwordBST);
	tree<occurance> bst, bst2, merged;
	populateSpecializedBST("input.txt", stopwordBST, bst);
	populateSpecializedBST("input2.txt", stopwordBST, bst2);
	bst.constructMergedBST(bst2, merged);
	int choice;
	std::string word;

	while (true) {
		std::cout << "Menu:" << std::endl;
		std::cout << "1. Print all Words in Book" << std::endl;
		std::cout << "2. Search the Book" << std::endl;
		std::cout << "3. Delete a word" << std::endl;
		std::cout << "4. Merge two Books" << std::endl;
		std::cout << "5. Find common words in two Books" << std::endl;
		std::cout << "6. Exit" << std::endl;
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1: {
			int c1;

			cout << "Enter Book you want to print" << endl;
			cin >> c1;
			if (c1 == 1)
				bst.inorderPrint();
			if (c1 == 2)
				bst2.inorderPrint();
			clear();
			break;
		}
		case 2: {
			int c1;
			cout << "Enter BST you want to search from" << endl;
			cin >> c1;
			std::cout << "Enter the word to search for: ";
			std::cin >> word;

			if (c1 == 1)
				bst.search(word);
			if (c1 == 2)
				bst2.search(word);
			if (c1 == 3)
				merged.search(word);
			clear();
			break;
		}
		case 3: {

			int c1;
			cout << "Enter BST you want to delete word from" << endl;
			cin >> c1;
			std::cout << "Enter the word to delete: ";
			std::cin >> word;

			if (c1 == 1)
				bst.deleteI(word);
			if (c1 == 2)
				bst2.deleteI(word);
			if (c1 == 3)
				merged.deleteI(word);
			clear();
			break;
		}
		case 4:
			cout << "\n\n\n/////////////////////////////////////\n//////////////////////////////////////////\n\n\n";
			cout << "\t\tMERGED BST" << endl;
			cout << "\n\n\n/////////////////////////////////////\n//////////////////////////////////////////\n\n\n";
			merged.inorderPrint();
			clear();
			break;

		case 5:
			findcommon(bst, bst2);
			clear();
			break;

		case 6:
			std::cout << "Exiting the program." << std::endl;
			return 0;

		default:
			std::cout << "Invalid choice. Please enter a valid option." << std::endl;
		}
	}

	return 0;
}
