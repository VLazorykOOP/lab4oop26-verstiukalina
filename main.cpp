#include <ctime>
#include <fstream>
#include <iostream>
#include <new>
#include <string>
#include <windows.h>

using namespace std;

class VectorShort {
private:
    short *data;
    int size;
    int codeError;
    static int countObjects;

    void vydilityPamiat(int n, short value = 0) {
        size = n > 0 ? n : 1;
        codeError = 0;
        data = new (nothrow) short[size];
        if (!data) {
            size = 1;
            codeError = 1;
            data = new short[1];
            data[0] = 0;
            return;
        }
        for (int i = 0; i < size; i++) {
            data[i] = value;
        }
    }

public:
    VectorShort() {
        vydilityPamiat(1, 0);
        countObjects++;
    }

    VectorShort(int n) {
        vydilityPamiat(n, 0);
        countObjects++;
    }

    VectorShort(int n, short value) {
        vydilityPamiat(n, value);
        countObjects++;
    }

    VectorShort(const VectorShort &other) {
        vydilityPamiat(other.size, 0);
        codeError = other.codeError;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        countObjects++;
    }

    ~VectorShort() {
        delete[] data;
        countObjects--;
    }

    static int otrymatyKilnistObiektiv() {
        return countObjects;
    }

    int otrymatyRozmir() const { return size; }
    int otrymatyKodPomylky() const { return codeError; }

    void vstanovytyKodPomylky(int value) {
        codeError = value;
    }

    void zapovnytyVypadkovo(short left, short right) {
        for (int i = 0; i < size; i++) {
            data[i] = left + rand() % (right - left + 1);
        }
    }
    
    VectorShort &operator=(const VectorShort &other) {
        if (this != &other) {
            delete[] data;
            vydilityPamiat(other.size, 0);
            codeError = other.codeError;
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    short &operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 2;
            return data[size - 1];
        }
        codeError = 0;
        return data[index];
    }
  
    const short &operator[](int index) const
    {
        if (index < 0 || index >= size) {
            return data[size - 1];
        }
        return data[index];
    } 

    VectorShort &operator++() {
        for (int i = 0; i < size; i++) {
            ++data[i];
        }
        return *this;
    }

    VectorShort operator++(int) {
        VectorShort temp(*this);
        for (int i = 0; i < size; i++) {
            data[i]++;
        }
        return temp;
    }

    VectorShort &operator--() {
        for (int i = 0; i < size; i++) {
            --data[i];
        }
        return *this;
    }

    VectorShort operator--(int) {
        VectorShort temp(*this);
        for (int i = 0; i < size; i++) {
            data[i]--;
        }
        return temp;
    }

    bool operator!() const { return size != 0; }

    VectorShort operator~() const 
    {
        VectorShort temp(*this);
        for (int i = 0; i < size; i++) {
            temp.data[i] = ~temp.data[i];
        }
        return temp;
    }

    VectorShort operator-() const
    {
        VectorShort temp(*this);
        for (int i = 0; i < size; i++) {
            temp.data[i] = -temp.data[i];
        }
        return temp;
    }

    VectorShort &operator+=(const VectorShort &other) {
        int n = size < other.size ? size : other.size;
        for (int i = 0; i < n; i++) {
            data[i] += other.data[i];
        }
        if (size != other.size) {
            codeError = 3;
        }
        return *this;
    }

    VectorShort &operator-=(const VectorShort &other) {
        int n = size < other.size ? size : other.size;
        for (int i = 0; i < n; i++) {
            data[i] -= other.data[i];
        }
        if (size != other.size) {
            codeError = 3;
        }
        return *this;
    }

    VectorShort &operator*=(short number) {
        for (int i = 0; i < size; i++) {
            data[i] *= number;
        }
        return *this;
    }

    VectorShort &operator/=(short number) {
        if (number == 0) {
            codeError = 4;
            return *this;
        }
        for (int i = 0; i < size; i++) {
            data[i] /= number;
        }
        return *this;
    }

    VectorShort &operator%=(short number) {
        if (number == 0) {
            codeError = 4;
            return *this;
        }
        for (int i = 0; i < size; i++) {
            data[i] %= number;
        }
        return *this;
    }

    VectorShort &operator|=(const VectorShort &other) {
        int n = size < other.size ? size : other.size;
        for (int i = 0; i < n; i++) {
            data[i] |= other.data[i];
        }
        if (size != other.size) {
            codeError = 3;
        }
        return *this;
    }

    VectorShort &operator^=(const VectorShort &other) {
        int n = size < other.size ? size : other.size;
        for (int i = 0; i < n; i++) {
            data[i] ^= other.data[i];
        }
        if (size != other.size) {
            codeError = 3;
        }
        return *this;
    }

    VectorShort &operator&=(const VectorShort &other) {
        int n = size < other.size ? size : other.size;
        for (int i = 0; i < n; i++) {
            data[i] &= other.data[i];
        }
        if (size != other.size) {
            codeError = 3;
        }
        return *this;
    }

    int operator()() const
    {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i];
        }
        return sum;
    }

    bool operator==(const VectorShort &other) const
    {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const VectorShort &other) const
    {
        return !(*this == other);
    }

    bool operator>(const VectorShort &other) const
    {
        int n = size < other.size ? size : other.size;
        for (int i = 0; i < n; i++) {
            if (data[i] <= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator>=(const VectorShort &other) const
    {
        int n = size < other.size ? size : other.size;
        for (int i = 0; i < n; i++) {
            if (data[i] < other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<(const VectorShort &other) const
    {
        int n = size < other.size ? size : other.size;
        for (int i = 0; i < n; i++) {
            if (data[i] >= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator<=(const VectorShort &other) const
    {
        int n = size < other.size ? size : other.size;
        for (int i = 0; i < n; i++) {
            if (data[i] > other.data[i]) {
                return false;
            }
        }
        return true;
    }

    friend VectorShort operator+(const VectorShort &a, const VectorShort &b);
    friend VectorShort operator-(const VectorShort &a, const VectorShort &b);
    friend VectorShort operator*(const VectorShort &a, short number);
    friend VectorShort operator/(const VectorShort &a, short number);
    friend VectorShort operator%(const VectorShort &a, short number);
    friend VectorShort operator|(const VectorShort &a, const VectorShort &b);
    friend VectorShort operator^(const VectorShort &a, const VectorShort &b);
    friend VectorShort operator&(const VectorShort &a, const VectorShort &b);
    friend istream &operator>>(istream &in, VectorShort &v);
    friend ostream &operator<<(ostream &out, const VectorShort &v);

    void *operator new(size_t sizeObject) {
        return ::operator new(sizeObject);
    }

    void operator delete(void *ptr) {
        ::operator delete(ptr);
    }
};

int VectorShort::countObjects = 0;

VectorShort operator+(const VectorShort &a, const VectorShort &b) {
    int n = a.otrymatyRozmir() < b.otrymatyRozmir() ? a.otrymatyRozmir() : b.otrymatyRozmir();
    VectorShort temp(n);
    for (int i = 0; i < n; i++) {
        temp[i] = a[i] + b[i];
    }
    if (a.otrymatyRozmir() != b.otrymatyRozmir()) {
        temp.vstanovytyKodPomylky(3);
    }
    return temp;
}

VectorShort operator-(const VectorShort &a, const VectorShort &b) {
    int n = a.otrymatyRozmir() < b.otrymatyRozmir() ? a.otrymatyRozmir() : b.otrymatyRozmir();
    VectorShort temp(n);
    for (int i = 0; i < n; i++) {
        temp[i] = a[i] - b[i];
    }
    if (a.otrymatyRozmir() != b.otrymatyRozmir()) {
        temp.vstanovytyKodPomylky(3);
    }
    return temp;
}

VectorShort operator*(const VectorShort &a, short number) {
    VectorShort temp(a);
    temp *= number;
    return temp;
}

VectorShort operator/(const VectorShort &a, short number) {
    VectorShort temp(a);
    temp /= number;
    return temp;
}

VectorShort operator%(const VectorShort &a, short number) {
    VectorShort temp(a);
    temp %= number;
    return temp;
}

VectorShort operator|(const VectorShort &a, const VectorShort &b) {
    int n = a.otrymatyRozmir() < b.otrymatyRozmir() ? a.otrymatyRozmir() : b.otrymatyRozmir();
    VectorShort temp(n);
    for (int i = 0; i < n; i++) {
        temp[i] = a[i] | b[i];
    }
    if (a.otrymatyRozmir() != b.otrymatyRozmir()) {
        temp.vstanovytyKodPomylky(3);
    }
    return temp;
}

VectorShort operator^(const VectorShort &a, const VectorShort &b) {
    int n = a.otrymatyRozmir() < b.otrymatyRozmir() ? a.otrymatyRozmir() : b.otrymatyRozmir();
    VectorShort temp(n);
    for (int i = 0; i < n; i++) {
        temp[i] = a[i] ^ b[i];
    }
    if (a.otrymatyRozmir() != b.otrymatyRozmir()) {
        temp.vstanovytyKodPomylky(3);
    }
    return temp;
}

VectorShort operator&(const VectorShort &a, const VectorShort &b) {
    int n = a.otrymatyRozmir() < b.otrymatyRozmir() ? a.otrymatyRozmir() : b.otrymatyRozmir();
    VectorShort temp(n);
    for (int i = 0; i < n; i++) {
        temp[i] = a[i] & b[i];
    }
    if (a.otrymatyRozmir() != b.otrymatyRozmir()) {
        temp.vstanovytyKodPomylky(3);
    }
    return temp;
}

istream &operator>>(istream &in, VectorShort &v) {
    for (int i = 0; i < v.size; i++) {
        in >> v.data[i];
    }
    return in;
}

ostream &operator<<(ostream &out, const VectorShort &v) {
    out << "[ ";
    for (int i = 0; i < v.size; i++) {
        out << v.data[i] << " ";
    }
    out << "]";
    return out;
}

struct Contact
{
    string email;
    string phone;
};

class EmailPhoneBook {
private:
    Contact *data;
    int size;
    int codeError;
    string emptyValue;

public:
    EmailPhoneBook(int n = 0) {
        size = n;
        codeError = 0;
        emptyValue = "";
        if (size > 0) {
            data = new Contact[size];
        }
        else {
            data = NULL;
        }
    }

    ~EmailPhoneBook() {
        delete[] data;
    }

    void stvorytyNabir() {
        for (int i = 0; i < size; i++) {
            data[i].email = "user" + to_string(i + 1) + "@mail.com";
            data[i].phone = "+38067" + to_string(1000000 + rand() % 9000000);
        }
    }

    string &operator[](const string &email) {
        for (int i = 0; i < size; i++) {
            if (data[i].email == email) {
                codeError = 0;
                return data[i].phone;
            }
        }
        codeError = 1;
        return emptyValue;
    }

    string operator()(const string &phone) {
        for (int i = 0; i < size; i++) {
            if (data[i].phone == phone) {
                codeError = 0;
                return data[i].email;
            }
        }
        codeError = 1;
        return "";
    }

    int otrymatyKodPomylky() const { return codeError; }

    friend istream &operator>>(istream &in, EmailPhoneBook &book);
    friend ostream &operator<<(ostream &out, const EmailPhoneBook &book);
};

istream &operator>>(istream &in, EmailPhoneBook &book) {
    for (int i = 0; i < book.size; i++) {
        in >> book.data[i].email >> book.data[i].phone;
    }
    return in;
}

ostream &operator<<(ostream &out, const EmailPhoneBook &book) {
    for (int i = 0; i < book.size; i++) {
        out << book.data[i].email << " - " << book.data[i].phone << "\n";
    }
    return out;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    srand((unsigned)time(0));

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1 - Завдання 1 VectorShort\n";
        cout << "2 - Завдання 2 EmailPhoneBook\n";
        cout << "3 - Завдання 3 Matrix3F\n";
        cout << "0 - Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        if (choice == 1) {
            // Task1();
        } else if (choice == 2) {
            // Task2();
        } else if (choice == 3) {
            // Task3();
        }
    } while (choice != 0);

    return 0;
}
