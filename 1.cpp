#include <iostream>
using namespace std;

class LibraryItem {
private:
    string title;
    string author;
    string dueDate;

public:
    LibraryItem(string t, string a) : title(t), author(a), dueDate("") {}
    virtual ~LibraryItem() {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getDueDate() const { return dueDate; }
    void setDueDate(const string &d) { dueDate = d; }

    virtual void checkOut(const string &date) = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() const = 0;
};

class Book : public LibraryItem {
private:
    bool checked;

public:
    Book(string t, string a) : LibraryItem(t, a), checked(false) {}

    void checkOut(const string &date) override {
        if (!checked) {
            setDueDate(date);
            checked = true;
            cout << "Checked out \"" << getTitle() << "\", due " << getDueDate() << "\n";
        } else {
            cout << "Already checked out\n";
        }
    }

    void returnItem() override {
        if (checked) {
            checked = false;
            setDueDate("");
            cout << "Returned \"" << getTitle() << "\"\n";
        } else {
            cout << "Not checked out\n";
        }
    }

    void displayDetails() const override {
        cout << "Book: " << getTitle() << " by " << getAuthor()
             << " — Due: " << (getDueDate().empty() ? "None" : getDueDate()) << "\n";
    }
};

class DVD : public LibraryItem {
private:
    bool checked;

public:
    DVD(string t, string a) : LibraryItem(t, a), checked(false) {}

    void checkOut(const string &date) override {
        if (!checked) {
            setDueDate(date);
            checked = true;
            cout << "Checked out DVD \"" << getTitle() << "\", due " << getDueDate() << "\n";
        } else {
            cout << "Already checked out DVD\n";
        }
    }

    void returnItem() override {
        if (checked) {
            checked = false;
            setDueDate("");
            cout << "Returned DVD \"" << getTitle() << "\"\n";
        } else {
            cout << "DVD was not checked out\n";
        }
    }

    void displayDetails() const override {
        cout << "DVD: " << getTitle() << " by " << getAuthor()
             << " — Due: " << (getDueDate().empty() ? "None" : getDueDate()) << "\n";
    }
};

int main() {
    const int MAX = 3;
    LibraryItem* items[MAX];

    items[0] = new Book("The Hobbit", "Tolkien");
    items[1] = new DVD("Matrix", "Wachowski");
    items[2] = new Book("1984", "Orwell");

    for (int i = 0; i < MAX; i++) {
        items[i]->displayDetails();
    }

    items[0]->checkOut("2025-12-01");
    items[1]->checkOut("2025-12-05");
    items[0]->returnItem();

    for (int i = 0; i < MAX; i++) {
        delete items[i];
    }

    return 0;
}
