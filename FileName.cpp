#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 61; // ��������Ϊɢ�б��С
const int MAX_RECORDS = 30; // ����¼��

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
    cout << "����ѡ�" << endl;
    cout << "1: ������ϵ��" << endl;
    cout << "2: ������ϵ��" << endl;
    cout << "3: ��ʾ������ϵ��" << endl;
    cout << "4: �˳�" << endl;
    cout << "������ѡ��: ";
}

int main() {
    HashTable hashTable;
    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // ������з�������Ӱ���������

        switch (choice) {
        case 1: {
            string name, phone, address;
            char cont = 'y';
            while (cont == 'y' || cont == 'Y') {
                cout << "������ϵ������: ";
                getline(cin, name);
                cout << "�绰����: ";
                getline(cin, phone);
                cout << "��ַ: ";
                getline(cin, address);
                hashTable.insert(name, phone, address);

                cout << "Ҫ������? (y/n): ";
                cin >> cont;
                cin.ignore(); // ������з�
            }
            break;
        }
        case 2: {
            string searchName, searchPhone, searchAddress;
            char cont = 'y';
            while (cont == 'y' || cont == 'Y') {
                cout << "����Ҫ��������ϵ������: ";
                getline(cin, searchName);
                if (hashTable.search(searchName, searchPhone, searchAddress)) {
                    cout << "Found! �绰���룺: " << searchPhone << ", ��ַ: " << searchAddress << endl;
                }
                else {
                    cout << "û�и���ϵ��!" << endl;
                }

                cout << "Ҫ������? (y/n): ";
                cin >> cont;
                cin.ignore(); // ������з�
            }
            break;
        }
        case 3:
            hashTable.display();
            break;
        case 4:
            cout << "�ɹ��˳�" << endl;
            break;
        default:
            cout << "��Ч���룬������ѡ��" << endl;
        }
    } while (choice != 4);

    return 0;
}
