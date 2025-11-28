#include <iostream>
#include <unordered_map>
using namespace std;

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class dlinklist {
public:
    dlinklist();
    ~dlinklist();
    void insertAtHead(Node* r);
    void remove(Node* r);
    void moveToHead(Node* r);
    Node* popTail();
    Node* head() const; 

private:
    Node* _head;
    Node* _tail;
};

dlinklist::dlinklist() : _head(nullptr), _tail(nullptr) {}
dlinklist::~dlinklist() {
    Node* cur = _head;
    while (cur) {
        Node* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
}
void dlinklist::insertAtHead(Node* r) {
    if (!r) return;
    r->prev = nullptr;
    r->next = _head;
    if (_head) _head->prev = r;
    _head = r;
    if (!_tail) _tail = r;
}
void dlinklist::remove(Node* r) {
    if (!r) return;
    if (r->prev) r->prev->next = r->next;
    else _head = r->next;
    if (r->next) r->next->prev = r->prev;
    else _tail = r->prev;
    r->prev = r->next = nullptr;
}
void dlinklist::moveToHead(Node* r) {
    if (!r || r == _head) return;
    remove(r);
    insertAtHead(r);
}
Node* dlinklist::popTail() {
    Node* t = _tail;
    if (!t) return nullptr;
    remove(t);
    return t;
}
Node* dlinklist::head() const { return _head; }

class LRUCacheFixed {
public:
    LRUCacheFixed(int capacity);
    ~LRUCacheFixed();
    bool get(int key, int &out);
    void put(int key, int value);
    void printCache();

private:
    int cap;
    unordered_map<int, Node*> mp;
    dlinklist list;
};

LRUCacheFixed::LRUCacheFixed(int capacity) : cap(capacity), list() {
    if (cap <= 0) throw "Capacity must be greater than 0";
}
LRUCacheFixed::~LRUCacheFixed() {
    for (auto& p : mp) delete p.second;
    mp.clear();
}

bool LRUCacheFixed::get(int key, int &out) {
    auto it = mp.find(key);
    if (it == mp.end()) return false;
    Node* n = it->second;
    list.moveToHead(n);
    out = n->value;
    return true;
}

void LRUCacheFixed::put(int key, int value) {
    auto it = mp.find(key);
    if (it != mp.end()) {
        Node* n = it->second;
        n->value = value;
        list.moveToHead(n);
        return;
    }
    Node* n = new Node(key, value);
    list.insertAtHead(n);
    mp[key] = n;
    if ((int)mp.size() > cap) {
        Node* t = list.popTail();
        if (t) {
            mp.erase(t->key);
            delete t;
        }
    }
}

void LRUCacheFixed::printCache() {
    cout << "Cache (most recent -> least recent): ";
    Node* cur = list.head();
    while (cur) {
        cout << "[" << cur->key << ":" << cur->value << "] ";
        cur = cur->next;
    }
    cout << "\n";
}

int main() {
    try {
        int cap;
        cout << "Enter cache capacity: ";
        if (!(cin >> cap)) { cout << "Invalid input\n"; return 0; }
        LRUCacheFixed cache(cap);

        while (true) {
            cout << "\n1) Put key/value\n2) Get key\n3) Print cache\n4) Exit\nChoose: ";
            int choice;
            if (!(cin >> choice)) { cout << "Invalid choice\n"; cin.clear(); cin.ignore(10000, '\n'); continue; }
            if (choice == 1) {
                int k, v;
                cout << "Key: "; if (!(cin >> k)) { cout << "bad key\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                cout << "Value: "; if (!(cin >> v)) { cout << "bad value\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                cache.put(k, v);
            } else if (choice == 2) {
                int k;
                cout << "Key: "; if (!(cin >> k)) { cout << "bad key\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                int val;
                if (cache.get(k, val)) cout << "Value: " << val << "\n";
                else cout << "Key not found\n";
            } else if (choice == 3) {
                cache.printCache();
            } else if (choice == 4) {
                cout << "Exiting\n";
                break;
            } else {
                cout << "Invalid option\n";
            }
        }
    } catch (const char* msg) {
        cout << msg << "\n";
    }
    return 0;
}
