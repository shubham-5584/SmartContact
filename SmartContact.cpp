#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
    string address;
};

vector<Contact> contacts;

void loadContacts() {
    ifstream file("contacts.txt");
    Contact c;
    while (getline(file, c.name) && getline(file, c.phone) && getline(file, c.email) && getline(file, c.address)) {
        contacts.push_back(c);
    }
    file.close();
}

void saveContacts() {
    ofstream file("contacts.txt");
    for (size_t i = 0; i < contacts.size(); ++i) {
        file << contacts[i].name << endl;
        file << contacts[i].phone << endl;
        file << contacts[i].email << endl;
        file << contacts[i].address << endl;
    }
    file.close();
}

void addContact() {
    Contact c;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, c.name);
    cout << "Enter phone: ";
    getline(cin, c.phone);
    cout << "Enter email: ";
    getline(cin, c.email);
    cout << "Enter address: ";
    getline(cin, c.address);
    contacts.push_back(c);
    saveContacts();
    cout << "Contact added successfully.\n";
}

void viewContacts() {
    cout << "\n--- All Contacts ---\n";
    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". Name: " << contacts[i].name << endl;
        cout << "   Phone: " << contacts[i].phone << endl;
        cout << "   Email: " << contacts[i].email << endl;
        cout << "   Address: " << contacts[i].address << endl << endl;
    }
}

void searchContact() {
    string keyword;
    cout << "Enter name or phone to search: ";
    cin.ignore();
    getline(cin, keyword);
    bool found = false;
    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].name.find(keyword) != string::npos || contacts[i].phone.find(keyword) != string::npos) {
            cout << "\nName: " << contacts[i].name << endl;
            cout << "Phone: " << contacts[i].phone << endl;
            cout << "Email: " << contacts[i].email << endl;
            cout << "Address: " << contacts[i].address << endl;
            found = true;
        }
    }
    if (!found) cout << "No contact found.\n";
}

void deleteContact() {
    string name;
    cout << "Enter name of the contact to delete: ";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].name == name) {
            contacts.erase(contacts.begin() + i);
            saveContacts();
            cout << "Contact deleted.\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Contact not found.\n";
    }
}


void editContact() {
    string name;
    cout << "Enter name of the contact to edit: ";
    cin.ignore();
    getline(cin, name);
    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].name == name) {
            cout << "Enter new phone: ";
            getline(cin, contacts[i].phone);
            cout << "Enter new email: ";
            getline(cin, contacts[i].email);
            cout << "Enter new address: ";
            getline(cin, contacts[i].address);
            saveContacts();
            cout << "Contact updated.\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

int main() {
    loadContacts();
    int choice;
    do {
        cout << "\n==== Smart Contact Management System ====\n";
        cout << "1. Add Contact\n";
        cout << "2. View All Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Edit Contact\n";
        cout << "5. Delete Contact\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: editContact(); break;
            case 5: deleteContact(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

