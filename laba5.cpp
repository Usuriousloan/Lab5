#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class PhoneBookEntry {
protected:
    string last_name;
    string first_name;
    string middle_name;
    string home_address;
    string phone_number;

public:
    PhoneBookEntry(string last, string first, string middle, string address, string phone)
        : last_name(last), first_name(first), middle_name(middle), home_address(address), phone_number(phone) {}

    virtual void print() const {
        cout << "Прізвище: " << last_name << endl;
        cout << "Ім'я: " << first_name << endl;
        cout << "По батькові: " << middle_name << endl;
        cout << "Домашня адреса: " << home_address << endl;
        cout << "Телефонний номер: " << phone_number << endl;
    }

    string getPhoneNumber() const {
        return phone_number;
    }
};

class SpecialPhoneBookEntry : public PhoneBookEntry {
private:
    string email;
    string company;

public:
    SpecialPhoneBookEntry(string last, string first, string middle, string address, string phone, string email, string company)
        : PhoneBookEntry(last, first, middle, address, phone), email(email), company(company) {}

    void print() const override {
        PhoneBookEntry::print();
        cout << "Електронна пошта: " << email << endl;
        cout << "Компанія: " << company << endl;
    }
};

class PhoneDirectory {
private:
    vector<PhoneBookEntry*> entries;

public:
    ~PhoneDirectory() {
        for (auto entry : entries) {
            delete entry;
        }
    }

    void addEntry(PhoneBookEntry* entry) {
        entries.push_back(entry);
    }

    void removeEntry(const string& phone) {
        auto it = remove_if(entries.begin(), entries.end(), [&phone](PhoneBookEntry* entry) {
            return entry->getPhoneNumber() == phone;
        });
        if (it != entries.end()) {
            delete *it;
            entries.erase(it);
        }
    }

    void printDirectory() const {
        for (auto entry : entries) {
            entry->print();
            cout << endl;
        }
    }
};

int main() {
    PhoneDirectory directory;

    directory.addEntry(new PhoneBookEntry("Бандера", "Степан", "Андрійович", "123 вул. Степана Бандери", "+380 44 123 1488"));
    directory.addEntry(new SpecialPhoneBookEntry("Шевченко", "Тарас", "Григорович", "456 вул. Дубова", "+380 44 432 1841", "osvita@gmail.com", "M.E.S.U."));

    directory.printDirectory();

    return 0;
}
