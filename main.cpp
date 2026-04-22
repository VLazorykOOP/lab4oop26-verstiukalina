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

class Vector3F {
private:
    int a;
    int b;
    int c;

public:
    Vector3F(int x = 0, int y = 0, int z = 0) {
        a = x;
        b = y;
        c = z;
    }

    Vector3F(const Vector3F &other) {
        a = other.a;
        b = other.b;
        c = other.c;
    }

    Vector3F &operator=(const Vector3F &other) {
        if (this != &other) {
            a = other.a;
            b = other.b;
            c = other.c;
        }
        return *this;
    }

    Vector3F &operator++() { a++; b++; c++; return *this; }

    Vector3F operator++(int) {
        Vector3F temp(*this);
        a++; b++; c++;
        return temp;
    }

    Vector3F &operator--() { a--; b--; c--; return *this; }

    Vector3F operator--(int) {
        Vector3F temp(*this);
        a--; b--; c--;
        return temp;
    }

    Vector3F operator-() const
    {
        return Vector3F(-a, -b, -c);
    }

    Vector3F operator+(const Vector3F &other) const
    {
        return Vector3F(a + other.a, b + other.b, c + other.c);
    }

    Vector3F operator-(const Vector3F &other) const
    {
        return Vector3F(a - other.a, b - other.b, c - other.c);
    }

    Vector3F operator*(const Vector3F &other) const
    {
        return Vector3F(a * other.a, b * other.b, c * other.c);
    }

    Vector3F operator*(int value) const
    {
        return Vector3F(a * value, b * value, c * value);
    }

    Vector3F operator/(int value) const
    {
        if (value == 0) {
            return *this;
        }
        return Vector3F(a / value, b / value, c / value);
    }

    Vector3F operator%(int value) const
    {
        if (value == 0) {
            return *this;
        }
        return Vector3F(a % value, b % value, c % value);
    }

    bool operator==(const Vector3F &other) const
    {
        return a == other.a && b == other.b && c == other.c;
    }

    bool operator!=(const Vector3F &other) const
    {
        return !(*this == other);
    }

    bool operator>(const Vector3F &other) const
    {
        return a > other.a && b > other.b && c > other.c;
    }

    bool operator>=(const Vector3F &other) const
    {
        return a >= other.a && b >= other.b && c >= other.c;
    }

    bool operator<(const Vector3F &other) const
    {
        return a < other.a && b < other.b && c < other.c;
    }

    bool operator<=(const Vector3F &other) const
    {
        return a <= other.a && b <= other.b && c <= other.c;
    }

    int suma() const { return a + b + c; }

    friend istream &operator>>(istream &in, Vector3F &v);
    friend ostream &operator<<(ostream &out, const Vector3F &v);
};

istream &operator>>(istream &in, Vector3F &v) {
    in >> v.a >> v.b >> v.c;
    return in;
}

ostream &operator<<(ostream &out, const Vector3F &v) {
    out << "(" << v.a << ", " << v.b << ", " << v.c << ")";
    return out;
}

class Matrix3F {
protected:
    Vector3F *data;
    int n;
    int codeError;
    static int count_matrix;

    void stvoryty(int size, int x = 0, int y = 0, int z = 0) {
        n = size;
        codeError = 0;
        if (n <= 0) {
            data = NULL;
            n = 0;
            return;
        }
        data = new (nothrow) Vector3F[n];
        if (!data) {
            n = 0;
            codeError = 1;
            return;
        }
        for (int i = 0; i < n; i++) {
            data[i] = Vector3F(x, y, z);
        }
    }

public:
    Matrix3F() {
        data = NULL;
        n = 0;
        codeError = 0;
        count_matrix++;
    }

    Matrix3F(int size) {
        stvoryty(size, 0, 0, 0);
        count_matrix++;
    }

    Matrix3F(int size, int value) {
        stvoryty(size, value, value, value);
        count_matrix++;
    }

    Matrix3F(int size, int x, int y, int z) {
        stvoryty(size, x, y, z);
        count_matrix++;
    }

    Matrix3F(const Matrix3F &other) {
        stvoryty(other.n, 0, 0, 0);
        codeError = other.codeError;
        for (int i = 0; i < n; i++) {
            data[i] = other.data[i];
        }
        count_matrix++;
    }

    ~Matrix3F() {
        delete[] data;
        count_matrix--;
    }

    int otrymatyRozmir() const { return n; }
    int otrymatyKodPomylky() const { return codeError; }
    static int otrymatyKilnistMatryts() { return count_matrix; }

    void zapovnytyVypadkovo(int left, int right) {
        for (int i = 0; i < n; i++) {
            data[i] = Vector3F(
                left + rand() % (right - left + 1),
                left + rand() % (right - left + 1),
                left + rand() % (right - left + 1));
        }
    }

    Matrix3F &operator=(const Matrix3F &other) {
        if (this != &other) {
            delete[] data;
            stvoryty(other.n, 0, 0, 0);
            codeError = other.codeError;
            for (int i = 0; i < n; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Matrix3F &operator++() {
        for (int i = 0; i < n; i++) {
            ++data[i];
        }
        return *this;
    }

    Matrix3F operator++(int) {
        Matrix3F temp(*this);
        for (int i = 0; i < n; i++) {
            data[i]++;
        }
        return temp;
    }

    Matrix3F &operator--() {
        for (int i = 0; i < n; i++) {
            --data[i];
        }
        return *this;
    }

    Matrix3F operator--(int) {
        Matrix3F temp(*this);
        for (int i = 0; i < n; i++) {
            data[i]--;
        }
        return temp;
    }

    bool operator!() const { return n != 0; }

    Matrix3F operator-() const
    {
        Matrix3F temp(*this);
        for (int i = 0; i < n; i++) {
            temp.data[i] = -temp.data[i];
        }
        return temp;
    }

    Vector3F &operator[](int index) {
        if (index < 0 || index >= n) {
            codeError = 2;
            return data[n - 1];
        }
        codeError = 0;
        return data[index];
    }

    const Vector3F &operator[](int index) const
    {
        if (index < 0 || index >= n) {
            return data[n - 1];
        }
        return data[index];
    }

    int operator()() const
    {
        int s = 0;
        for (int i = 0; i < n; i++) {
            s += data[i].suma();
        }
        return s;
    }

    Matrix3F &operator+=(const Matrix3F &other) {
        int m = n < other.n ? n : other.n;
        for (int i = 0; i < m; i++) {
            data[i] = data[i] + other.data[i];
        }
        return *this;
    }

    Matrix3F &operator+=(double value) {
        int x = (int)value;
        for (int i = 0; i < n; i++) {
            data[i] = data[i] + Vector3F(x, x, x);
        }
        return *this;
    }

    Matrix3F &operator+=(float value) {
        return (*this += (double)value);
    }

    Matrix3F &operator-=(const Matrix3F &other) {
        int m = n < other.n ? n : other.n;
        for (int i = 0; i < m; i++) {
            data[i] = data[i] - other.data[i];
        }
        return *this;
    }

    Matrix3F &operator-=(double value) {
        int x = (int)value;
        for (int i = 0; i < n; i++) {
            data[i] = data[i] - Vector3F(x, x, x);
        }
        return *this;
    }

    Matrix3F &operator-=(float value) {
        return (*this -= (double)value);
    }

    Matrix3F &operator*=(const Matrix3F &other) {
        int m = n < other.n ? n : other.n;
        for (int i = 0; i < m; i++) {
            data[i] = data[i] * other.data[i];
        }
        return *this;
    }

    Matrix3F &operator*=(const Vector3F &v) {
        for (int i = 0; i < n; i++) {
            data[i] = data[i] * v;
        }
        return *this;
    }

    Matrix3F &operator*=(double value) {
        int x = (int)value;
        for (int i = 0; i < n; i++) {
            data[i] = data[i] * x;
        }
        return *this;
    }

    Matrix3F &operator*=(float value) {
        return (*this *= (double)value);
    }

    Matrix3F &operator/=(int value) {
        if (value == 0) {
            codeError = 3;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            data[i] = data[i] / value;
        }
        return *this;
    }

    Matrix3F &operator/=(double value) {
        return (*this /= (int)value);
    }

    Matrix3F &operator/=(float value) {
        return (*this /= (int)value);
    }

    Matrix3F &operator%=(int value) {
        if (value == 0) {
            codeError = 3;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            data[i] = data[i] % value;
        }
        return *this;
    }

    bool operator==(const Matrix3F &other) const
    {
        if (n != other.n) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix3F &other) const
    {
        return !(*this == other);
    }

    bool operator>(const Matrix3F &other) const
    {
        int m = n < other.n ? n : other.n;
        for (int i = 0; i < m; i++) {
            if (!(data[i] > other.data[i])) {
                return false;
            }
        }
        return true;
    }

    bool operator>=(const Matrix3F &other) const
    {
        int m = n < other.n ? n : other.n;
        for (int i = 0; i < m; i++) {
            if (!(data[i] >= other.data[i])) {
                return false;
            }
        }
        return true;
    }

    bool operator<(const Matrix3F &other) const
    {
        int m = n < other.n ? n : other.n;
        for (int i = 0; i < m; i++) {
            if (!(data[i] < other.data[i])) {
                return false;
            }
        }
        return true;
    }

    bool operator<=(const Matrix3F &other) const
    {
        int m = n < other.n ? n : other.n;
        for (int i = 0; i < m; i++) {
            if (!(data[i] <= other.data[i])) {
                return false;
            }
        }
        return true;
    }

    friend Matrix3F operator+(const Matrix3F &a, const Matrix3F &b);
    friend Matrix3F operator+(const Matrix3F &a, int value);
    friend Matrix3F operator+(const Matrix3F &a, double value);
    friend Matrix3F operator+(const Matrix3F &a, float value);
    friend Matrix3F operator-(const Matrix3F &a, const Matrix3F &b);
    friend Matrix3F operator-(const Matrix3F &a, int value);
    friend Matrix3F operator-(const Matrix3F &a, double value);
    friend Matrix3F operator-(const Matrix3F &a, float value);
    friend Matrix3F operator*(const Matrix3F &a, const Matrix3F &b);
    friend Matrix3F operator*(const Matrix3F &a, const Vector3F &v);
    friend Matrix3F operator*(const Matrix3F &a, double value);
    friend Matrix3F operator*(const Matrix3F &a, float value);
    friend Matrix3F operator/(const Matrix3F &a, const Matrix3F &b);
    friend Matrix3F operator/(const Matrix3F &a, int value);
    friend Matrix3F operator/(const Matrix3F &a, float value);
    friend Matrix3F operator%(const Matrix3F &a, int value);
    friend istream &operator>>(istream &in, Matrix3F &m);
    friend ostream &operator<<(ostream &out, const Matrix3F &m);

    void *operator new(size_t sizeObject) {
        return ::operator new(sizeObject);
    }

    void operator delete(void *ptr) {
        ::operator delete(ptr);
    }
};

int Matrix3F::count_matrix = 0;

Matrix3F operator+(const Matrix3F &a, const Matrix3F &b) {
    Matrix3F temp(a);
    temp += b;
    return temp;
}

Matrix3F operator+(const Matrix3F &a, int value) {
    Matrix3F temp(a);
    temp += (double)value;
    return temp;
}

Matrix3F operator+(const Matrix3F &a, double value) {
    Matrix3F temp(a);
    temp += value;
    return temp;
}

Matrix3F operator+(const Matrix3F &a, float value) {
    Matrix3F temp(a);
    temp += value;
    return temp;
}

Matrix3F operator-(const Matrix3F &a, const Matrix3F &b) {
    Matrix3F temp(a);
    temp -= b;
    return temp;
}

Matrix3F operator-(const Matrix3F &a, int value) {
    Matrix3F temp(a);
    temp -= (double)value;
    return temp;
}

Matrix3F operator-(const Matrix3F &a, double value) {
    Matrix3F temp(a);
    temp -= value;
    return temp;
}

Matrix3F operator-(const Matrix3F &a, float value) {
    Matrix3F temp(a);
    temp -= value;
    return temp;
}

Matrix3F operator*(const Matrix3F &a, const Matrix3F &b) {
    Matrix3F temp(a);
    temp *= b;
    return temp;
}

Matrix3F operator*(const Matrix3F &a, const Vector3F &v) {
    Matrix3F temp(a);
    temp *= v;
    return temp;
}

Matrix3F operator*(const Matrix3F &a, double value) {
    Matrix3F temp(a);
    temp *= value;
    return temp;
}

Matrix3F operator*(const Matrix3F &a, float value) {
    Matrix3F temp(a);
    temp *= value;
    return temp;
}

Matrix3F operator/(const Matrix3F &a, const Matrix3F &b) {
    Matrix3F temp(a.otrymatyRozmir());
    int m = a.otrymatyRozmir() < b.otrymatyRozmir() ? a.otrymatyRozmir() : b.otrymatyRozmir();
    for (int i = 0; i < m; i++) {
        int s = a[i].suma() * b[i].suma();
        temp[i] = Vector3F(s, s, s);
    }
    return temp;
}

Matrix3F operator/(const Matrix3F &a, int value) {
    Matrix3F temp(a);
    temp /= value;
    return temp;
}

Matrix3F operator/(const Matrix3F &a, float value) {
    Matrix3F temp(a);
    temp /= value;
    return temp;
}

Matrix3F operator%(const Matrix3F &a, int value) {
    Matrix3F temp(a);
    temp %= value;
    return temp;
}

istream &operator>>(istream &in, Matrix3F &m) {
    for (int i = 0; i < m.n; i++) {
        in >> m.data[i];
    }
    return in;
}

ostream &operator<<(ostream &out, const Matrix3F &m) {
    for (int i = 0; i < m.n; i++) {
        out << m.data[i] << "\n";
    }
    return out;
}

void testVektorFile() {
    ifstream fin("vector_input.txt");
    if (!fin) {
        cout << "Помилка відкриття файлу vector_input.txt\n";
        return;
    }

    int n = 0;
    fin >> n;
    VectorShort a(n);
    fin >> a;
    cout << "Вектор з файлу: " << a << "\n";
}

void testVektorVypadkovo() {
    VectorShort a(5);
    a.zapovnytyVypadkovo(-10, 10);
    cout << "Випадковий вектор: " << a << "\n";
}

void testVektorKlaviatura() {
    int n;
    cout << "Введіть розмір вектора: ";
    cin >> n;
    VectorShort a(n);
    cout << "Введіть елементи вектора:\n";
    cin >> a;
    cout << "Вектор з клавіатури: " << a << "\n";
}

void testVektorOperatsii() {
    VectorShort a(5, 2);
    VectorShort b(5, 3);
    VectorShort c(5);
    c[0] = 1;
    c[1] = 2;
    c[2] = 3;
    c[3] = 4;
    c[4] = 5;

    cout << "a = " << a << "\n";
    cout << "b = " << b << "\n";
    cout << "c = " << c << "\n";
    cout << "++a = " << ++a << "\n";
    cout << "b++ = " << b++ << "\n";
    cout << "Після b++: " << b << "\n";
    cout << "--c = " << --c << "\n";
    cout << "~a = " << ~a << "\n";
    cout << "-b = " << -b << "\n";
    cout << "!a = " << (!a) << "\n";

    VectorShort d = a + b;
    VectorShort e = d - c;
    VectorShort f = e * 2;
    VectorShort g = f / 2;
    VectorShort h = g % 3;
    VectorShort i = (a | b) ^ (c & g);
    VectorShort expr1 = (((b + c) - g) * 2 / 2) % 5;
    VectorShort expr2 = (((~b | c) ^ (g & h)) + (-c)) - a;

    cout << "d = " << d << "\n";
    cout << "e = " << e << "\n";
    cout << "f = " << f << "\n";
    cout << "g = " << g << "\n";
    cout << "h = " << h << "\n";
    cout << "i = " << i << "\n";
    cout << "expr1 = " << expr1 << "\n";
    cout << "expr2 = " << expr2 << "\n";

    cout << "a == b : " << (a == b) << "\n";
    cout << "a != b : " << (a != b) << "\n";
    cout << "b > c : " << (b > c) << "\n";
    cout << "b >= c : " << (b >= c) << "\n";
    cout << "b < g : " << (b < g) << "\n";
    cout << "b <= g : " << (b <= g) << "\n";
    cout << "c[2] = " << c[2] << "\n";
    cout << "c[50] = " << c[50] << ", codeError = " << c.otrymatyKodPomylky() << "\n";
    cout << "Сума g = " << g() << "\n";
    cout << "Кількість об'єктів = " << VectorShort::otrymatyKilnistObiektiv() << "\n";

    VectorShort *p = new VectorShort(3, 7);
    cout << "Новий вектор = " << *p << "\n";
    delete p;
}

void Task1() {
    cout << "\nЗавдання 1. VectorShort\n";
    testVektorFile();
    testVektorVypadkovo();
    testVektorOperatsii();
    testVektorKlaviatura();
}

void testTelefonFile() {
    ifstream fin("input.txt");
    if (!fin) {
        cout << "Помилка відкриття файлу input.txt\n";
        return;
    }

    int n = 0;
    fin >> n;
    EmailPhoneBook book(n);
    fin >> book;
    cout << "Дані з файлу:\n" << book;
    cout << "Телефон для alina@gmail.com: " << book["alina@gmail.com"] << "\n";
    cout << "Електронна пошта для +380671112233: " << book("+380671112233") << "\n";
    cout << "CodeError: " << book.otrymatyKodPomylky() << "\n";
}

void testTelefonVypadkovo() {
    EmailPhoneBook book(3);
    book.stvorytyNabir();
    cout << "Випадкові дані:\n" << book;
    cout << "Пошук none@gmail.com: " << book["none@gmail.com"] << "\n";
    cout << "CodeError: " << book.otrymatyKodPomylky() << "\n";
}

void testTelefonKlaviatura() {
    int n;
    cout << "Введіть кількість контактів: ";
    cin >> n;
    EmailPhoneBook book(n);
    cout << "Введіть email і телефон:\n";
    cin >> book;
    cout << "Дані з клавіатури:\n" << book;
    cout << "Телефон для user1@mail.com: " << book["user1@mail.com"] << "\n";
    cout << "CodeError: " << book.otrymatyKodPomylky() << "\n";
}

void Task2() {
    cout << "\nЗавдання 2. Електронна пошта і телефон\n";
    testTelefonFile();
    testTelefonVypadkovo();
    testTelefonKlaviatura();
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
            Task1();
        } else if (choice == 2) {
            Task2();
        } else if (choice == 3) {
            // Task3();
        }
    } while (choice != 0);

    return 0;
}
