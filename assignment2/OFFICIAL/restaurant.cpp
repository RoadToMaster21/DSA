#include "main.h"

// ----------- HUFFMAN CODE BELOW ------------//
bool compareChars(pair<char, int> p1, pair<char, int> p2) {
    if (p1.second != p2.second) {
        return p1.second < p2.second;
    } else {
        return p1.first < p2.first;
    }
}

void countChars(string str, deque<char>& charList, deque<int>& countList) {
    deque<pair<char, int>> charQueue;
    unordered_map<char, int> counts;
    for (char c : str) {
        counts[c]++;
        bool found = false;
        for (auto& p : charQueue) {
            if (p.first == c) {
                p.second++;
                found = true;
                break;
            }
        }
        if (!found) {
            charQueue.push_back(make_pair(c, 1));
        }
    }
    sort(charQueue.begin(), charQueue.end(), compareChars);
    for (auto& p : charQueue) {
        charList.push_back(p.first);
        countList.push_back(p.second);
    }
}
int findIndex(char data, deque<char> charList) {
    for (size_t i = 0; i < charList.size(); i++) {
        if (charList[i] == data) {
            return i;
        }
    }
    return -1;
}

struct hfMinHeapNode {
	char data;
	unsigned freq;
	hfMinHeapNode *left, *right;
	hfMinHeapNode(char data, unsigned freq) {
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

void printCodes(struct hfMinHeapNode* root, string str, deque<char> charList, string traverse[]) {
	if (!root) return;
	if (root->data != '~') {
	    traverse[findIndex(root->data, charList)] = str;
	}
	printCodes(root->left, str + "0", charList, traverse);
	printCodes(root->right, str + "1", charList, traverse);
}

void print(deque<hfMinHeapNode*> minHeap) {
    for (size_t i = 0; i < minHeap.size(); i++) {
        cout <<minHeap[i]->data << ": " << minHeap[i]->freq << "    ";
    }
    cout << endl;
}

void HuffmanCodes(deque<char> charList, deque<int> countList, string traverse[]) {
	hfMinHeapNode *left, *right, *top;
	deque<hfMinHeapNode*> minHeap;
	for (size_t i = 0; i < charList.size(); ++i) {
        minHeap.push_back(new hfMinHeapNode(charList[i], countList[i]));
	}
	//print(minHeap);
	while (minHeap.size() != 1) {
		left = minHeap.front();
		minHeap.pop_front();

		right = minHeap.front();
		minHeap.pop_front();
		top = new hfMinHeapNode('~', left->freq + right->freq);
		top->left = left;
		top->right = right;
		stack<hfMinHeapNode*> st;
		while (top->freq < minHeap.back()->freq) {
		    st.push(minHeap.back());
		    minHeap.pop_back();
		}
		minHeap.push_back(top);
		while (!st.empty()) {
		    minHeap.push_back(st.top());
		    st.pop();
		}
		//print(minHeap);
	}
	printCodes(minHeap.front(), "", charList, traverse);
}
// ----------- HUFFMAN CODE ABOVE ------------//

class Customer {
public:
    string name;
    int result;
    int id;
    int num;
    string table;
    Customer () {
        name = "";
        result = 0;
        id = 0;
        num = 0;
        table = "";
    }
    Customer(string name, int result, int id, int num, string table) {
        this->name = name;
        this->result = result;
        this->id = id;
        this->num = num;
        this->table = table;
    }
};

// ------------- HASHTABLE BELOW --------------//
class Hashtable {
public:
    Customer* hashtable = new Customer[MAXSIZE/2];
public:
    void insertCustomer(Customer customer) {
        int index = customer.result % (MAXSIZE/2);
        if (hashtable[index].name == customer.name) {
            return;
        }
        if (hashtable[index].name == "") {
            hashtable[index] = customer;
            return;
        }
        while (hashtable[index].name != "") {
            if (index == MAXSIZE/2 - 1){
                index = 0;
            } else index++;
        }
        hashtable[index] = customer;
    }

    bool isFull() {
        for (int i = 0; i < MAXSIZE / 2; i++) {
            if (hashtable[i].name == "") {
                return false;
            }
        }
        return true;
    }

    void updateHT(string name) {
        for (int i = 0; i < MAXSIZE / 2; i++) {
            if (hashtable[i].name == name) {
                hashtable[i].num++;
                return;
            }
        }
    }

    void printHT() {
        for (int i = 0; i < MAXSIZE / 2; i++) {
            if (hashtable[i].name != "") {
                cout << hashtable[i].id << "-" << hashtable[i].result << "-" << hashtable[i].num << endl;
            }
        }
    }

    void clearHT() {
        hashtable = new Customer[MAXSIZE/2];
    }

    void cleHT(int id) {
        for (int i = 0; i < MAXSIZE/2; i++) {
            if (hashtable[i].id == id) {
                Customer c("", 0, 0, 0, "");
                hashtable[i] = c;
                return;
            }
        }
    }

    ~Hashtable() {
        delete[] hashtable;
    }
};
// -------------- HASHTABLE ABOVE ----------------//

// ----------- AVLTree IMPLEMENT BELOW ------------//
struct Node {
	Customer customer;
	struct Node *left;
	struct Node *right;
	int height;
};

int height(struct Node *N) {
	if (N == NULL)
		return 0;
	return N->height;
}

struct Node* newNode(Customer customer) {
	struct Node* node = new Node;
	node->customer = customer;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}

struct Node *rightRotate(struct Node *root) {
	struct Node* newroot = root->left;
	struct Node* temp = newroot->right;
	newroot->right = root;
	root->left = temp;
	// Update heights
	root->height = max(height(root->left), height(root->right)) + 1;
	newroot->height = max(height(newroot->left), height(newroot->right)) + 1;

	return newroot;
}

struct Node *leftRotate(struct Node *root) {
	struct Node* newroot = root->right;
	struct Node* temp = newroot->left;
	newroot->left = root;
	root->right = temp;
	// Update heights
	root->height = max(height(root->left), height(root->right)) + 1;
	newroot->height = max(height(newroot->left), height(newroot->right)) + 1;

	return newroot;
}

int getBalance(Node *N) {
	if (N == NULL) return 0;
	return height(N->left) - height(N->right);
}

Node* insert(Node* node, Customer customer) {
	if (node == NULL)
		return(newNode(customer));

	if (customer.result < node->customer.result)
		node->left = insert(node->left, customer);
	else {
        node->right = insert(node->right, customer);
	}

	node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalance(node);
	// Left Left Case
	if (balance > 1 && customer.result < node->left->customer.result) {
        return rightRotate(node);
	}
	// Right Right Case
	if (balance < -1 && customer.result >= node->right->customer.result) {
        return leftRotate(node);
	}
	// Left Right Case
	if (balance > 1 && customer.result >= node->left->customer.result) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	// Right Left Case
	if (balance < -1 && customer.result < node->right->customer.result) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

Node* minValueNode(Node* node)
{
    Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, string name, int result) {
    if (root == NULL) return root;
    if (result < root->customer.result) {
        root->left = deleteNode(root->left, name, result);
    } else if (result > root->customer.result || name != root->customer.name) {
        root->right = deleteNode(root->right, name, result);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else *root = *temp;
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);
            root->customer = temp->customer;
            root->right = deleteNode(root->right, name, temp->customer.result);
        }
    }
    if (root == NULL) return root;
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void avlUpdateNum(Node* root, string name, int result) {
    if (root->customer.name == name) {
        root->customer.num++;
        return;
    } else if (result < root->customer.result) {
        avlUpdateNum(root->left, name, result);
    } else {
        avlUpdateNum(root->right, name, result);
    }
}

bool isAVLfull(deque <Customer> fifo) {
    int num = 0;
    for (size_t i = 0; i < fifo.size(); i++) {
        if (fifo[i].table == "AVL") {
            num++;
        }
    }
    if (num == MAXSIZE/2) return true;
    return false;
}

void printbfs(Node* root)
{
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        cout << node->customer.id << "-" << node->customer.result << "-" << node->customer.num << endl;
        q.pop();
        if (node->left != NULL)
            q.push(node->left);
        if (node->right != NULL)
            q.push(node->right);
    }
}
// ----------- AVLTree IMPLEMENT ABOVE ------------//

// ------------- HEAP for LFCO BELOW --------------//
class Heap {
public:
	deque<Customer> arr;

	Heap(){}

    int getLeftChild(int parent) {
	    return 2*parent + 1;
    }

    int getRightChild(int parent) {
	    return 2*parent + 2;
    }

    int getParent(int child) {
	    return (child - 1) / 2;
    }

    int getIndex(string name) {
        for (size_t i = 0; i < arr.size(); i++) {
            if (arr[i].name == name) return i;
        }
        return -1;
    }

    int getIndex(int customerId) {
        for (size_t i = 0; i < arr.size(); i++) {
            if (arr[i].id == customerId) return i;
        }
        return -1;
    }

    int getIndex(Customer customer, deque<Customer> fifo) {
        for (size_t i = 0; i < fifo.size(); i++) {
            if (fifo[i].name == customer.name) return i;
        }
        return -1;
    }

    bool isSooner(Customer c1, Customer c2, deque<Customer> fifo) {
        return getIndex(c1, fifo) < getIndex(c2, fifo);
    }

    void reHeapUp(int child, deque<Customer> fifo) {
	    if (child != 0) {
		    int parent = getParent(child);
		    if ((arr[child].num < arr[parent].num) || (arr[child].num == arr[parent].num && isSooner(arr[child], arr[parent], fifo))) {
			    swap(arr[child], arr[parent]);
			    reHeapUp(parent, fifo);
		    }
	    }
    }

    void reHeapDown(size_t parent, deque<Customer> fifo) {
	    size_t left = getLeftChild(parent);
	    size_t right = getRightChild(parent);
	    size_t smallest = parent;
	    if (left < arr.size()) {
	        if (arr[smallest].num > arr[left].num) {
	            smallest = left;
	        } else if (arr[smallest].num == arr[left].num) {
	            if (isSooner(arr[left], arr[smallest], fifo)) {
	                smallest = left;
	            }
	        }
	    }
	    if (right < arr.size()) {
	        if (arr[smallest].num > arr[right].num) {
	            smallest = right;
	        } else if (arr[smallest].num == arr[right].num) {
	            if (isSooner(arr[right], arr[smallest], fifo)) {
	                smallest = right;
	            }
	        }
	    }
	    if (smallest != parent) {
	        swap(arr[smallest], arr[parent]);
	        reHeapDown(smallest, fifo);
	    }
    }

    void insertKey(Customer customer, deque<Customer> fifo) {
	    arr.push_back(customer);
	    int child = arr.size() - 1;
	    reHeapUp(child, fifo);
    }

    void deleteKey(int customerId, deque<Customer> fifo) {
	    if (arr.size() == 0) {
		    return;
	    }
	    int index = getIndex(customerId);
	    if (index != -1) {
	        arr[index] = arr[arr.size()-1];
	        arr.pop_back();
	        reHeapDown(index, fifo);
	    }
    }

    void cleHT(deque<Customer> fifo) {
        deque<int> cle;
        for (size_t i = 0; i < fifo.size(); i++) {
            if (fifo[i].table == "HT") {
                cle.push_back(fifo[i].id);
            }
        }
        while (!cle.empty()) {
            int temp = cle.front();
            deleteKey(temp, fifo);
            cle.pop_front();
        }
    }

    void cleAVL(deque<Customer> fifo) {
        deque<int> cle;
        for (size_t i = 0; i < fifo.size(); i++) {
            if (fifo[i].table == "AVL") {
                cle.push_back(fifo[i].id);
            }
        }
        while (!cle.empty()) {
            int temp = cle.front();
            deleteKey(temp, fifo);
            cle.pop_front();
        }
    }

    Customer getCustomer(int index) {
        return arr[index];
    }

    void preOrder(size_t index) {
        if (index < arr.size()) {
            Customer temp = getCustomer(index);
            cout << temp.id << "-" << temp.num << endl;
            preOrder(getLeftChild(index));
            preOrder(getRightChild(index));
        }
    }

    void checkHeap() {
        for (size_t i = 0; i < arr.size(); i++) {
            cout << arr[i].id << "-" << arr[i].result << "-" << arr[i].num << "    ";
        }
        cout << endl;
    }
};
// ------------- HEAP for LFCO ABOVE --------------//

// ----------- STRING NORMALIZE BELOW ------------//
bool checkLine(string str) {
    // check space at head and tail of string
    if (str[0] == ' ' || str[str.length() - 1] == ' ') {
        return false;
    }
    int space = 0;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ' ') space++;
        // check special character
        if (str[i] == ' ' || str[i] == '-' || (str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            continue;
        } else return false;
    }
    // only 1 space
    if (space > 1) {
        return false;
    }
    return true;
}

bool checkNum(string str) {
    for (size_t i = 1; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') continue;
        else return false;
    }
    if ((str[0] == '-') || (str[0] >= '0' && str[0] <= '9')) return true;
        else return false;
    return true;
}

bool checkChar(string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')){
            continue;
        } else return false;
    }
    return true;
}
// ----------- STRING NORMALIZE ABOVE ------------//

bool contain(deque <Customer> fifo, string name) {
    for (size_t i = 0; i < fifo.size(); i++) {
        if (fifo[i].name == name) {
            return true;
        }
    }
    return false;
}

bool contain(deque <Customer> fifo, int id) {
    for (size_t i = 0; i < fifo.size(); i++) {
        if (fifo[i].id == id) {
            return true;
        }
    }
    return false;
}

void fifoUpdateNum(deque <Customer>& fifo, string name) {
    for (size_t i = 0; i < fifo.size(); i++) {
        if (fifo[i].name == name) {
            fifo[i].num++;
            return;
        }
    }
}

void printfifo(deque <Customer> fifo) {
    for (size_t i = 0; i < fifo.size(); i++) {
        cout << fifo[i].id << "-" << fifo[i].result << "-" << fifo[i].num << "-" << fifo[i].table << "   ";
    }
    cout << endl;
}

Customer getCustomer(deque <Customer> fifo, int id) {
    for (size_t i = 0; i < fifo.size(); i++) {
        if (fifo[i].id == id) {
            return fifo[i];
        }
    }
    Customer c("", 0, 0, 0, "");
    return c;
}

Customer getCustomer(deque <Customer> fifo, string name) {
    for (size_t i = 0; i < fifo.size(); i++) {
        if (fifo[i].name == name) {
            return fifo[i];
        }
    }
    Customer c("", 0, 0, 0, "");
    return c;
}

void pushTo(Customer customer, deque<Customer>& fifo, deque<Customer>& lrco, Heap& heap) {
    fifo.push_back(customer);
    lrco.push_back(customer);
    heap.insertKey(customer, fifo);
}

void cle(int id, Hashtable& hashtable, Node* &root, deque<Customer>& fifo, deque<Customer>& lrco, Heap& heap) {
    if (id < 1) {
        hashtable.clearHT();
        heap.cleHT(fifo);
        for(auto it = fifo.begin(); it != fifo.end(); ) {
            if ((*it).table == "HT") {
                it = fifo.erase(it);
            } else {
                ++it;
            }
        }
        for(auto it = lrco.begin(); it != lrco.end(); ) {
            if ((*it).table == "HT") {
                it = lrco.erase(it);
            } else {
                ++it;
            }
        }
    }

    if (id >= 1 && id <= MAXSIZE) {
        if (contain(fifo, id)) {
            Customer temp = getCustomer(fifo, id);
            for(auto it = fifo.begin(); it != fifo.end(); ) {
                if ((*it).id == id) {
                    it = fifo.erase(it);
                    break;
                } else {
                    ++it;
                }
            }
            for(auto it = lrco.begin(); it != lrco.end(); ) {
                if ((*it).id == id) {
                    it = lrco.erase(it);
                    break;
                } else {
                    ++it;
                }
            }
            heap.deleteKey(id, fifo);
            if (temp.table == "HT") {
                hashtable.cleHT(id);
            } else {
                root = deleteNode(root, temp.name, temp.result);
            }
        }
    }

    if (id > MAXSIZE) {
        root = NULL;
        heap.cleAVL(fifo);
        for(auto it = fifo.begin(); it != fifo.end(); ) {
            if ((*it).table == "AVL") {
                it = fifo.erase(it);
            } else {
                ++it;
            }
        }
        for(auto it = lrco.begin(); it != lrco.end(); ) {
            if ((*it).table == "AVL") {
                it = lrco.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void simulate(string filename)
{
    Hashtable hashtable;
    Node* root = NULL;
    deque <Customer> fifo;
    deque <Customer> lrco;
    Heap heap;

    ifstream file;
    file.open(filename);
    string line;
    while (getline(file, line)) {
        if (checkLine(line) == false) {
            continue;
        }
        //cout << "------" << line << "-----" << endl;
        int pos = line.find(" ", 0);
        string com = line.substr(0, pos);
        // REG Command
        if (com == "REG") {
            string name = line.substr(pos + 1, line.length() - (pos + 1));
            //cout << name << endl;
            int result;
            if (checkChar(name)) {
                // find the value of result
                //cout << "YES" << endl;
                deque<char> charList;
                deque<int> countList;
                countChars(name, charList, countList);
                string traverse[charList.size()];
                string temp = "";
                if (charList.size() == 1) {
                    // Name have only 1 character
                    traverse[0] = '1';
                    int index = name.length() - 1;
                    while (temp.length() <= 15 && index >= 0) {
                        temp = traverse[0] + temp;
                        index--;
                    }
                } else {
                    // HUFFMAN build
                    HuffmanCodes(charList, countList, traverse);
                    int index = name.length() - 1;
                    while (temp.length() <= 15 && index >= 0) {
                        temp = traverse[findIndex(name[index], charList)] + temp;
                        index--;
                    }
                }
                if (temp.length() > 15) {
                    temp = temp.substr(temp.length() - 15, 15);
                }
                result = stoi(temp, nullptr, 2);
                //cout << temp << " -> " << result << endl;
                if (contain(fifo, name)) {
                    //cout << "Branch1" << endl;
                    fifoUpdateNum(fifo, name);
                    Customer temp = getCustomer(fifo, name);
                    if (temp.table == "HT") {
                        hashtable.updateHT(temp.name);
                    } else {
                        avlUpdateNum(root, temp.name, temp.result);
                    }
                    for(auto it = lrco.begin(); it != lrco.end(); ) {
                        if ((*it).name == temp.name) {
                            it = lrco.erase(it);
                            break;
                        } else {
                            ++it;
                        }
                    }
                    lrco.push_back(temp);
                    // Update Heap
                    heap.deleteKey(temp.id, fifo);
                    heap.insertKey(temp, fifo);
                } else if (hashtable.isFull() && isAVLfull(fifo)) {
                    int opt = result % 3;
                    //cout << "Branch2" << " " << opt << endl;
                    // FIFO
                    if (opt == 0) {
                        Customer temp = fifo.front();
                        cle(temp.id, hashtable, root, fifo, lrco, heap);
                        // add new customer
                        if (temp.table == "HT") {
                            Customer customer(name, result, temp.id, 1, "HT");
                            hashtable.insertCustomer(customer);
                            pushTo(customer, fifo, lrco, heap);
                        } else {
                            Customer customer(name, result, temp.id, 1, "AVL");
                            root = insert(root, customer);
                            pushTo(customer, fifo, lrco, heap);
                        }
                    }
                    // LRCO
                    if (opt == 1) {
                        Customer temp = lrco.front();
                        cle(temp.id, hashtable, root, fifo, lrco, heap);
                        // add new customer
                        if (temp.table == "HT") {
                            Customer customer(name, result, temp.id, 1, "HT");
                            hashtable.insertCustomer(customer);
                            pushTo(customer, fifo, lrco, heap);
                        } else {
                            Customer customer(name, result, temp.id, 1, "AVL");
                            root = insert(root, customer);
                            pushTo(customer, fifo, lrco, heap);
                        }
                    }
                    // LFCO
                    if (opt == 2) {
                        Customer temp = heap.getCustomer(0);
                        cle(temp.id, hashtable, root, fifo, lrco, heap);
                        if (temp.table == "HT") {
                            Customer customer(name, result, temp.id, 1, "HT");
                            hashtable.insertCustomer(customer);
                            pushTo(customer, fifo, lrco, heap);
                        } else {
                            Customer customer(name, result, temp.id, 1, "AVL");
                            root = insert(root, customer);
                            pushTo(customer, fifo, lrco, heap);
                        }
                    }
                } else {
                    //cout << "Branch3" << endl;
                    int id = result % MAXSIZE + 1;
                    while (contain(fifo, id)) {
                        if (id == MAXSIZE){
                            id = 1;
                        } else id++;
                    }
                    if (result % 2 == 1) {
                        if (!hashtable.isFull()) {
                            Customer customer(name, result, id, 1, "HT");
                            hashtable.insertCustomer(customer);
                            pushTo(customer, fifo, lrco, heap);
                        } else {
                            //cout << id << endl;
                            Customer customer(name, result, id, 1, "AVL");
                            root = insert(root, customer);
                            pushTo(customer, fifo, lrco, heap);
                        }
                    }
                    if (result % 2 == 0) {
                        if (!isAVLfull(fifo)) {
                            Customer customer(name, result, id, 1, "AVL");
                            root = insert(root, customer);
                            pushTo(customer, fifo, lrco, heap);
                        } else {
                            Customer customer(name, result, id, 1, "HT");
                            hashtable.insertCustomer(customer);
                            pushTo(customer, fifo, lrco, heap);
                        }
                    }
                }
            }
        }
        // CLE command
        if (com == "CLE") {
            string temp = line.substr(pos + 1, line.length() - (pos + 1));
            if (checkNum(temp)) {
                int id = stoi(temp, nullptr, 10);
                cle(id, hashtable, root, fifo, lrco, heap);
            }
        }
        // Print HT command
        if (com == "PrintHT") {
            hashtable.printHT();
        }
        // PrintAVL command
        if (com == "PrintAVL") {
            printbfs(root);
        }
        // PrintMH command
        if (com == "PrintMH") {
            heap.preOrder(0);
        }
        // cout << "FIFO: " << endl;
        // printfifo(fifo);
        // cout << "LRCO: " << endl;
        // printfifo(lrco);
        // cout << "HT: " << endl;
        // hashtable.printHT();
        // cout << "AVL: " << endl;
        // printbfs(root);
        // cout << "Min heap: " << endl;
        // heap.checkHeap();
    }
	return;
}

