#include "main.h"

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
    if (mergenum > 0) {
        // connect all table
        //cout << headmerge->ID << " " << lastmerge->ID << " " << save->ID << endl;
        table* tail = lastmerge->next;
        while (tail->next != lastmerge->next) {
            tail = tail->next;
        }
        tail->next = headmerge;
        for (int i = 1; i <= MAXSIZE; i++) {
            if (p1->name != "") {
                cout << p1->ID << "-" << p1->name << endl;
            }
            p1 = p1->next;
            // if (p1 != headmerge) {
            //     p1 = p1->next;
            // } else {
            //     if (save != head) {
            //         p1 = head;
            //     } else {
            //         p1 = lastmerge; // stop condition when run completely a circle if save = lastmerge->next
            //     }
            // }
        }
        // split
        tail->next = lastmerge->next;
    } else {
        for (int i = 1; i <= MAXSIZE; i++) {
            if (p1->name != "") {
                cout << p1->ID << "-" << p1->name << endl;
            }
            p1 = p1->next;
        }
    }

}

void swapq(tableqs* a, tableqs* b) {
    int ID = a->ID;
    string name = a->name;
    int age = a->age;
    a->ID = b->ID;
    a->age = b->age;
    a->name = b->name;
    b->ID = ID;
    b->age = age;
    b->name = name;
    //delete temp;
}
QueueStack* sortqueue(QueueStack* que, int &num) {
    QueueStack* q = que;
    if (q->head == NULL || sizeOf(q) == 1 || num < 1) {
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
        if (index != temp) {
            swapq(index, temp);
        }
        temp = temp->pre;
    }
    return q;
}

bool isExistInStack(QueueStack* st, string name) {
    if (st->head == NULL) {
        return false;
    }
    tableqs* temp = st->tail;
    while (temp != NULL) {
        if (temp->name == name) {
            return true;
        }
        temp = temp->pre;
    }
    return false;
}

// void view(QueueStack* st, string com) {
//     cout << com << ": ";
//     if (st->tail == NULL) {
//         cout << "Empty" << endl;
//         return;
//     }
//     tableqs* temp = st->head;
//     while (temp != NULL) {
//         cout << temp->ID << "-" << temp->name << " ";
//         temp = temp->next;
//     }
//     cout << " " << endl;
//     return;
// }

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

void reg(table* head, table* headmerge, table* lastmerge, int ID, string name, int age, int mergenum, QueueStack *q, QueueStack *st, table* &save) {
    // to count size of stack and queue
    int lostvalue = 0;
    if (mergenum > 0) {
        lostvalue = mergenum - 1;
    }
    //REG with ID
    if (ID > 0 && ID <= MAXSIZE && age >= 16) {
        table* p = head->next;
        
        // If restaurant has Merge table
        if (mergenum > 0) {
            p = lastmerge->next;
        } 
        // Find the index if equal
        bool isEqual = false;
        for (int i = 1; i <= MAXSIZE - mergenum; i++) {
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
                if (isExistInStack(st, name) == false) {
                    st = pushto(st, ID, name, age, 2*MAXSIZE - lostvalue);
                }
                save = p;
            } else {
            // The ID table is rented, find the next from ID+1 -> maxsize and return 1 -> ID
                table* p1 = p->next;
                while (p1->name != "" && p1 != p) {
                    p1 = p1->next;
                }
                if (p1->name == "") {
                    p1->name = name;
                    p1->age = age;
                    if (isExistInStack(st, name) == false) {
                        st = pushto(st, p1->ID, name, age, 2*MAXSIZE - lostvalue);
                    }
                    // Save the index
                    save = p1;
                }
                // There is no table is available -> push to queue
                else {
                    q = pushto(q, ID, name, age, MAXSIZE);
                    st = pushto(q, ID, name, age, 2*MAXSIZE - lostvalue);
                }
            }
        } 
        // ID in arange from headmerge to lastmerge
        else {
            table* p1 = lastmerge->next;
            bool isFind = false;
            for (int i = 1; i <= MAXSIZE - mergenum; i++) {
                if (p1->name == "") {
                    p1->name = name;
                    p1->age = age;
                    if (isExistInStack(st, name) == false) {
                        st = pushto(st, p1->ID, name, age, 2*MAXSIZE - lostvalue);
                    }
                    save = p1;
                    isFind = true;
                    break;
                } else {
                    p1 = p1->next;
                }
            }
            if (isFind == false) {
                q = pushto(q, ID, name, age, MAXSIZE);
                st = pushto(st, ID, name, age, 2*MAXSIZE - lostvalue);
            }
        }
    }
    // REG with no ID (ID = 0)
    else if (age >= 16 && ID == 0) {
        table* p1 = head->next;
        if (mergenum > 0) {
            p1 = lastmerge->next;
        }
        bool isFind = false;
        for (int i = 1; i <= MAXSIZE - mergenum; i++) {
            if (p1->name == "") {
                p1->name = name;
                p1->age = age;
                if (isExistInStack(st, name) == false) {
                    st = pushto(st, p1->ID, name, age, 2*MAXSIZE - lostvalue);
                } else {
                    changeID(st, name, p1->ID);
                }
                isFind = true;
                save = p1;
                break;
            } else {
                if (p1 == headmerge && mergenum > 0) {
                    p1 = lastmerge->next;
                } else {
                    p1 = p1->next;
                }
            }
        }
        if (isFind == false) {
            q = pushto(q, ID, name, age, MAXSIZE);
            st = pushto(st, ID, name, age, 2*MAXSIZE - lostvalue);
        }
    }
    //cout << save->ID << " " << save->name << " " << save->age << endl;
    //printstack(st, 0);
    // view(st, "stack");
    // view(q, "queue");
}

void simulate(string filename, restaurant* r)
{
    table *head = r->recentTable; // index MAXSIZE
    QueueStack* q = new QueueStack();
    QueueStack* st = new QueueStack();
    table* save = head->next; // store the most recent updated
    table* headmerge = head->next;
    table* lastmerge = NULL;
    int mergenum = 0;
    ifstream file;
    file.open(filename);
    string line;
    //int run = 1;
    while (getline(file, line)) {
        //
        // cout << run << ": " << endl;
        // run++;
        //
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
            //
            int posspace = line.find(" ", next + 1);
            //
            if (posspace != -1) {
                ID = stoll(temp);
                pos = next + 1;
                next = line.find(" ", pos);
                name = line.substr(pos, next - pos);
                age = stoll(line.substr(next + 1, line.length() -  next));
            } else {
                name = temp;
                age = stoll(line.substr(next + 1, line.length() -  next));
            }
            //cout << com << " " << ID << " " << name << " " << age << endl;
            // Implement command
            reg(head, headmerge, lastmerge, ID, name, age, mergenum, q, st, save);
        }

        if (com == "REGM") {
            // String normalization
            int next = line.find(" ", pos + 1);
            string name = line.substr(pos + 1, next - (pos + 1)); // get name
            pos = next + 1;
            next = line.find(" ", pos);
            int age = stoll(line.substr(pos, next - pos));
            int num = stoll(line.substr(next + 1, line.length() - next - 1));

            //cout << com << " " << name << " " << age << " " << num << endl;
            // Implement command

            // Find num of tables are empty
            if (mergenum == 0 && age >= 16) {
                table* p1 = head->next;
                table* p2 = new table(0, "", 0, NULL);
                bool findtable = false;
                int counttable = 0;
                for (int i = 1; i <= MAXSIZE; i++) {
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
            // view(st, "stack");
            // view(q, "queue");
        }

        if (com == "CLE") {
            // String normalization
            int ID = stoll(line.substr(pos + 1, line.length() - pos - 1));
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
                        p1 = lastmerge->next->next;
                        while (p1->ID != ID && p1 != lastmerge->next) {
                            p1 = p1->next;
                        }
                    }
                    if (p1->ID == ID) { // check case: CLE ID with ID from headmerge to lasmerge
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
                            }
                            save = p1;
                        }
                    }
                } else {
                    // CLE at headmerge
                    if (headmerge->name != "") {
                        headmerge->age = 0;
                        headmerge->name = "";
                        popfromstack(st, headmerge->ID);
                        int savemergenum = mergenum;
                        mergenum = 0;
                        save = headmerge;
                        table* tail = lastmerge->next;
                        while (tail->next != lastmerge->next) {
                            tail = tail->next;
                        }
                        tail->next = headmerge;
                        for (int i = 1; i <= savemergenum; i++) {
                            if (q->tail == NULL) {
                                break;
                            } else {
                                tableqs* temp = popfromqueue(q);
                                reg(head, headmerge, lastmerge, temp->ID, temp->name, temp->age, mergenum, q, st, save);
                                //delete temp;
                            }
                        }
                        
                    }
                }
            }
            // view(st, "stack");
            // view(q, "queue");
        }

        if (com == "PS") {
            // String normalization
            int num = 0;
            if (pos != -1) {
                num = stoll(line.substr(pos + 1, line.length() - pos - 1));
            }
            //cout << com << " " << num << endl;
            // Implement command
            printstack(st, num);
            
        }

        if (com == "PQ") {
            // String normalization
            int num = 0;
            if (pos != -1) {
                num = stoll(line.substr(pos + 1, line.length() - pos - 1));
            }
            //cout << com << " " << num << endl;
            // Implement command
            printqueue(q, num);
            
        }

        if (com == "SQ") {
            // String normalization
            int num = stoll(line.substr(pos + 1, line.length() - pos - 1));
            //cout << com << " " << num << endl;

            // Implement command
            if (num != 0) {
                q = sortqueue(q, num);
                printqueue(q ,0);
            }
            //view(q, "queue");

        }

        if (com == "PT") {
            //cout << com << endl;
            printTotal(save, mergenum, headmerge, lastmerge);
        }
    }
    delete q;
    delete st;
    file.close();
}
