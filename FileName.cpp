#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 61; // 素数，作为散列表大小
const int MAX_RECORDS = 30; // 最大记录数

struct Record {
    string name;
    string phone;
    string address;
    bool isEmpty;

    Record() : isEmpty(true) {}
};
 
class HashTable {
public:
    HashTable();
    void insert(const string& name, const string& phone, const string& address);
    bool search(const string& name, string& phone, string& address) const;
    void display() const;

private:
    int hashFunction(const string& key) const;
    vector<Record> table;
    int currentSize;

    int probeFunction(int index, int step) const;
};

HashTable::HashTable() : table(TABLE_SIZE), currentSize(0) {}

int HashTable::hashFunction(const string& key) const {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31 + ch) % TABLE_SIZE;
    }
    return hash;
}

int HashTable::probeFunction(int index, int step) const {
    return (index + step * step) % TABLE_SIZE;
}

void HashTable::insert(const string& name, const string& phone, const string& address) {
    int index = hashFunction(name);
    int step = 1;
    while (!table[index].isEmpty) {
        index = probeFunction(index, step);
        step++;
    }
    table[index].name = name;
    table[index].phone = phone;
    table[index].address = address;
    table[index].isEmpty = false;
    currentSize++;
}

bool HashTable::search(const string& name, string& phone, string& address) const {
    int index = hashFunction(name);
    int step = 1;
    while (!table[index].isEmpty) {
        if (table[index].name == name) {
            phone = table[index].phone;
            address = table[index].address;
            return true;
        }
        index = probeFunction(index, step);
        step++;
    }
    return false;
}

void HashTable::display() const {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (!table[i].isEmpty) {
            cout << "Name: " << table[i].name << ", Phone: " << table[i].phone << ", Address: " << table[i].address << endl;
        }
    }
}

void showMenu() {
    cout << "功能选项：" << endl;
    cout << "1: 创建联系人" << endl;
    cout << "2: 搜索联系人" << endl;
    cout << "3: 显示所有联系人" << endl;
    cout << "4: 退出" << endl;
    cout << "请输入选择: ";
}

int main() {
    HashTable hashTable;
    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // 清除换行符，避免影响后续输入

        switch (choice) {
        case 1: {
            string name, phone, address;
            char cont = 'y';
            while (cont == 'y' || cont == 'Y') {
                cout << "输入联系人姓名: ";
                getline(cin, name);
                cout << "电话号码: ";
                getline(cin, phone);
                cout << "地址: ";
                getline(cin, address);
                hashTable.insert(name, phone, address);

                cout << "要继续吗? (y/n): ";
                cin >> cont;
                cin.ignore(); // 清除换行符
            }
            break;
        }
        case 2: {
            string searchName, searchPhone, searchAddress;
            char cont = 'y';
            while (cont == 'y' || cont == 'Y') {
                cout << "输入要搜索的联系人姓名: ";
                getline(cin, searchName);
                if (hashTable.search(searchName, searchPhone, searchAddress)) {
                    cout << "Found! 电话号码：: " << searchPhone << ", 地址: " << searchAddress << endl;
                }
                else {
                    cout << "没有该联系人!" << endl;
                }

                cout << "要继续吗? (y/n): ";
                cin >> cont;
                cin.ignore(); // 清除换行符
            }
            break;
        }
        case 3:
            hashTable.display();
            break;
        case 4:
            cout << "成功退出" << endl;
            break;
        default:
            cout << "无效输入，请重新选择：" << endl;
        }
    } while (choice != 4);

    return 0;
}
