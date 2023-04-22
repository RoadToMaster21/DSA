#include<iostream>
#include<cmath>
#include<fstream>
#include<string>

using namespace std;
#define MAXSIZE 15

class table
{
public:
    int ID;
    string name;
    int age;
    table* next;
    table(int ID, string name, int age, table* next)
    {
        this->ID = ID;
        this->name = name;
        this->age = age;
        this->next = next;
    }
};

class restaurant
{
public:
    table *recentTable;
    restaurant()
    {
        recentTable = nullptr;
    }
    ~restaurant()
    {
        delete recentTable;
    }
    table* finsert(table *last, int ID, string name, int age)
    {
        if (last != nullptr)
            return last;
        table *temp = new table(ID, "", age, last);

        last = temp;
        last->next = last;
        return last;
    }
    table *insert(table *last, int ID, string name, int age)
    {
        if (last == NULL)
            return finsert(last, ID, name, age);
        table *temp = new table (ID, name, age, last->next);
        last -> next = temp;
        last = temp;
        return last;
    }
};
struct tableqs {
    int ID;
    string name;
    int age;
    tableqs* next;
    tableqs* pre;
};
struct QueueStack {
    tableqs* head;
    tableqs* tail;
};

int sizeOf(QueueStack* q) {
    if (q->head == NULL) {
        return 0;
    }
    tableqs* p = q->head;
    int sq = 1;
    while (p != q->tail) {
        p = p->next;
        sq++;
    }
    return sq;
}

QueueStack* pushto(QueueStack* q, int ID, string name, int age, int sizedefault){
    if (sizeOf(q) == sizedefault) {
        return q;
    }
    if (q->head == NULL) {
        tableqs* temp = new tableqs;
        temp->ID = ID;
        temp->age = age;
        temp->name = name;
        temp->next = NULL;
        temp->pre = NULL;
        q->head = temp;
        q->tail = temp;
        return q;
    }
    tableqs* temp = new tableqs;
    temp->ID = ID;
    temp->age = age;
    temp->name = name;
    temp->pre = NULL;
    temp->next = q->head;
    q->head->pre = temp;
    q->head = temp;
    return q;
}
tableqs* popfromqueue(QueueStack* q) {
    if (q->head != q->tail) {
        tableqs* temp = q->tail;
        q->tail = temp->pre;
        q->tail->next = NULL;
        temp->pre = NULL;
        return temp;
    }
    tableqs* temp = q->tail;
    q->head = NULL;
    q->tail = NULL;
    return temp;
}

QueueStack* popfromstack(QueueStack* st, int ID) {
    // pop guest at table ID out of stack
    // If stack has 1 element
    if (st->head == st->tail) {
        st->head = NULL;
        st->tail = NULL;
        return st;
    }
    // More than 1 element
    tableqs* temp = st->tail;
    while (temp->ID != ID) {
        temp = temp->pre;
    }
    if (temp == st->head) {
        st->head = temp->next;
        st->head->pre = NULL;
        delete temp;
        return st;
    }
    if (temp == st->tail) {
        st->tail = temp->pre;
        st->tail->next = NULL;
        delete temp;
        return st;
    }
    tableqs* t = temp->pre;
    temp->next->pre = t;
    t->next = temp->next;
    delete temp;
    return st;
}

void changeID(QueueStack* st, string name, int ID) {
    if (st->tail != NULL) {
        tableqs* temp = st->tail;
        while (temp->name != name) {
            temp = temp->pre;
        }
        temp->ID = ID;
    }
    return;
}

void printqueue(QueueStack* q, int num) {
    if (q->head == NULL) {
        cout << "Empty" << endl;
        return;
    }
    if (num > 0 && num <= sizeOf(q)) {
        tableqs* temp = q->tail;
        for (int i = 1; i <= num; i++) {
            cout << temp->name << endl;
            temp = temp->pre;
        }
        return;
    }
    if (num == 0 || num > sizeOf(q)) {
        tableqs* temp = q->tail;
        while (temp != NULL) {
            cout << temp->name << endl;
            temp = temp->pre;
        }
        return;
    }
}

void printstack(QueueStack* st, int num) {
    if (st->head == NULL) {
        cout << "Empty" << endl;
        return;
    }
    if (num > 0 && num <= sizeOf(st)) {
        tableqs* temp = st->head;
        for (int i = 1; i <= num; i++) {
            cout << temp->name << endl;
            temp = temp->next;
        }
        return;
    }
    if (num == 0 || num > sizeOf(st)) {
        tableqs* temp = st->head;
        while (temp != NULL) {
            cout << temp->name << endl;
            temp = temp->next;
        }
        return;
    }
}

void printTotal(table* save, int mergenum, table* headmerge, table* lastmerge) {
    table* p1 = save;
    bool checkEmpty = true;
    if (mergenum > 0) {
        table* tail = lastmerge->next;
        while (tail->next != lastmerge->next) {
            tail = tail->next;
        }
        table* head = lastmerge->next;
        tail->next = headmerge;
        while (p1->next != save) {
            if (p1->name != "") {
                cout << p1->ID << "-" << p1->name << endl;
                checkEmpty = false;
            }
            if (p1 != headmerge) {
                p1 = p1->next;
            } else {
                if (save != head) {
                    p1 = head;
                } else {
                    p1 = lastmerge;
                }
            }
        }
        tail->next = head;
    } else {
        while (p1->next != save) {
            if (p1->name != "") {
                cout << p1->ID << "-" << p1->name << endl;
                checkEmpty = false;
            }
            p1 = p1->next;
        }
    }

    if (checkEmpty) {
        cout << "Empty" << endl;
    }
}

void swapq(tableqs* a, tableqs* b) {
    tableqs* temp = a;
    a->ID = b->ID;
    a->age = b->age;
    a->name = b->name;
    b->ID = temp->ID;
    b->age = temp->age;
    b->name = temp->name;
    //delete temp;
}
QueueStack* sortqueue(QueueStack* que, int &num) {
    QueueStack* q = que;
    if (q->head == NULL || sizeOf(q) == 1) {
        return q;
    }
    if (num > sizeOf(q)) {
        num = sizeOf(q);
    }
    tableqs* temp = q->tail;
    for (int i = 1; i <= num; i++) {
        int maxAge = temp->age;
        tableqs* index = temp;
        tableqs* run = temp->pre;
        while (run != NULL) {
            if (run->age > maxAge) {
                maxAge = run->age;
                index = run;
            }
            run = run->pre;
        }
        swapq(index, temp);
        temp = temp->pre;
    }
    return q;
}

int convertTo(string str) {
    int sum = 0;
    for (int i = str.length() - 1; i >= 0; i--) {
        sum += (str[i] - 48) * pow(10, str.length() - 1 - i);
    }
    return sum;
}

void simulate(string filename, restaurant* r)
{
    table *head = r->recentTable; // index MAXSIZE
    QueueStack* q = new QueueStack();
    QueueStack* st = new QueueStack();
    //q->head = NULL;
    table* save = head->next; // store the most recent updated
    table* headmerge = head->next;
    table* lastmerge = NULL;
    int mergenum = 0;
    fstream file;
    file.open(filename);
    string line;
    while (getline(file, line)) {
        string com;
        int pos = line.find(" ", 0);
        if (pos != -1) {
            com = line.substr(0, pos);
        } else {
            com = line;
        }
        if (com == "REG") {
            // String normalization
            int ID = 0, age;
            string name;
            int next = line.find(" ", pos + 1);
            string temp = line.substr(pos + 1, next - (pos + 1));
            if (temp[0] >= '0' && temp[0] <= '9') {
                ID = convertTo(temp);
                pos = next + 1;
                next = line.find(" ", pos);
                name = line.substr(pos, next - pos);
                age = convertTo(line.substr(next + 1, line.length() -  next));
            } else {
                name = temp;
                age = convertTo(line.substr(next + 1, line.length() -  next));
            }
            //cout << com << " " << ID << " " << name << " " << age << endl;

            // Implement command
            // REG with ID
            if (ID > 0 && age >= 16) {
                // Have Merge table
                table* p = head->next;
                if (mergenum > 0) {
                    p = lastmerge->next;
                }
                bool isEqual = false;
                // Find the index if equal
                for (int i = 1; i <= MAXSIZE - mergenum -1; i++) {
                    if (p->ID == ID) {
                        isEqual = true;
                        break;
                    } else {
                        p = p->next;
                    }
                }
                // If empty -> add
                if (isEqual) {
                    if (p->name == "") {
                        p->name = name;
                        p->age = age;
                        st = pushto(st, ID, name, age, 2*MAXSIZE);
                        save = p;
                    } else {
                    // The ID is rented, find the next
                        table* p1 = p->next;
                        while (p1->name != "" && p1 != p) {
                            p1 = p1->next;
                        }
                        if (p1->name == "") {
                            p1->name = name;
                            p1->age = age;
                            st = pushto(st, ID, name, age, 2*MAXSIZE);
                            // Save the index
                            save = p1;
                        }
                    // There is no table is available -> push to queue
                        else {
                            q = pushto(q, 0, name, age, MAXSIZE);
                            st = pushto(q, 0, name, age, 2*MAXSIZE);
                        }
                    }
                }
            }
            // REG with no ID
            else if (age >= 16) {
                table* p1 = head->next;
                bool isFind = false;
                for (int i = 1; i <= MAXSIZE - mergenum - 1; i++) {
                    if (p1->name == "") {
                        p1->name = name;
                        p1->age = age;
                        st = pushto(st, p1->ID, name, age, 2*MAXSIZE);
                        isFind = true;
                        save = p1;
                        break;
                    } else {
                        p1 = p1->next;
                    }
                }
                if (isFind == false) {
                    q = pushto(q, 0, name, age, MAXSIZE);
                    st = pushto(st, 0, name, age, MAXSIZE);
                }
            }
            //cout << save->ID << " " << save->name << " " << save->age << endl;
            //printstack(st, 0);
        }

        if (com == "REGM") {
            // String normalization
            int next = line.find(" ", pos + 1);
            string name = line.substr(pos + 1, next - (pos + 1)); // get name
            pos = next + 1;
            next = line.find(" ", pos);
            int age = convertTo(line.substr(pos, next - pos));
            int num = convertTo(line.substr(next + 1, line.length() - next - 1));

            //cout << com << " " << name << " " << age << " " << num << endl;
            // Implement command
            // If now is merging, continue

            // Find num of tables are empty
            if (mergenum == 0 && age >= 16) {
                table* p1 = head->next;
                table* p2 = new table(0, "", 0, NULL);
                bool findtable = false;
                int counttable = 0;
                for (int i = 1; i <= MAXSIZE - 1; i++) {
                    p2 = p1;
                    for (int j = 1; j <= num; j++) {
                        if (p2->name == "") {
                            counttable++;
                            if (counttable < num) p2 = p2->next;
                        } else {
                            counttable = 0;
                            break;
                        }
                    }
                    if (counttable == num) {
                        if (p1->ID > headmerge->ID) {
                            headmerge = p1;
                            lastmerge = p2;
                        }
                        counttable = 0;
                        findtable = true;
                    }
                    p1 = p1->next;
                }
                if (findtable) {
                    headmerge->name = name;
                    headmerge->age = age;
                    mergenum = num;
                    st = pushto(st, headmerge->ID, name, age, 2*MAXSIZE);
                    // cut linked list
                    table* temp = lastmerge->next;
                    while (temp->next != headmerge) {
                        temp = temp->next;
                    }
                    temp->next = lastmerge->next;
                    save = headmerge; // store recent updated
                }
            }
        }

        if (com == "CLE") {
            // String normalization
            int ID = convertTo(line.substr(pos + 1, line.length() - pos - 1));
	        //cout << com << " " << ID << endl;

            // Implement command
            if (ID > 0 && ID <= MAXSIZE) {
                // No merging in list + merging with ID not in from headmerge to lastmerge
                if (mergenum == 0 || (mergenum > 0 && headmerge->ID != ID)) {
                    table* p1 = head->next;
                    if (mergenum == 0) {
                        while (p1->ID != ID) {
                            p1 = p1->next;
                        }
                    } else {
                        p1 = lastmerge->next;
                        while (p1->ID != ID && p1->next != lastmerge->next) {
                            p1 = p1->next;
                        }
                    }
                    if (p1->ID == ID) {
                        if (p1->name != "") { // check if there is a guest at ID to delete
                            p1->age = 0;
                            p1->name = "";
                            popfromstack(st, p1->ID);
                            // pop from queue and push to list
                            if (q->tail != NULL) {
                                tableqs* temp = popfromqueue(q);
                                p1->name = temp->name;
                                p1->age = temp->age;
                                changeID(st, temp->name, p1->ID);
                                //delete temp;
                            save = p1;
                            }
                        }
                    }
                } else {
                    // CLE at headmerge
                    if (headmerge->name != "") {
                        headmerge->age = 0;
                        headmerge->name = "";
                        popfromstack(st, headmerge->ID);
                        table* p1 = headmerge;
                        for (int i = 1; i <= mergenum; i++) {
                            if (q->tail == NULL) {
                                break;
                            } else {
                                tableqs* temp = popfromqueue(q);
                                p1->name = temp->name;
                                p1->age = temp->age;
                                changeID(st, temp->name, p1->ID);
                                //delete temp;
                            }
                            p1 = p1->next;
                        }
                        save = headmerge;
                        mergenum = 0;
                    }
                }
            }
        }

        if (com == "PS") {
            // String normalization
            int num = 0;
            if (pos != -1) {
                num = convertTo(line.substr(pos + 1, line.length() - pos - 1));
            }
            //cout << com << " " << num << endl;
            // Implement command
            printstack(st, num);
        }

        if (com == "PQ") {
            // String normalization
            int num = 0;
            if (pos != -1) {
                num = convertTo(line.substr(pos + 1, line.length() - pos - 1));
            }
            //cout << com << " " << num << endl;
            // Implement command
            printqueue(q, num);

        }

        if (com == "SQ") {
            // String normalization
            int num = convertTo(line.substr(pos + 1, line.length() - pos - 1));
            //cout << com << " " << num << endl;

            // Implement command
            q = sortqueue(q, num);
            printqueue(q ,0);

        }

        if (com == "PT") {
            //cout << com << endl;
            printTotal(save, mergenum, headmerge, lastmerge);
        }
    }
    //delete q;
    //delete st;
    //delete head;
    //delete save;
    //delete headmerge;
    //delete lastmerge;
    file.close();
}

int main(int argc, char* argv[]) {

    restaurant* r = new restaurant();
    string fileName = "test.txt";

    //initialize table with ID, name and age
    for (int i = 1; i <= MAXSIZE; i++)
    {
        r->recentTable = r->insert(r->recentTable,i,"",0);
    }
    simulate(fileName,r);
    delete r;

    return 0;
}