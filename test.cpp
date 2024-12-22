#include <iostream>

class B;  // Vorwärtsdeklarationen
class C;

class A {
public:
    int value;

    A(int v) : value(v) {}

    // A zu B konvertieren
    operator B() const;

    // A zu C konvertieren
    operator C() const;

    friend A operator+(const A& ,const A& );
};

class B {
public:
    int value;

    B(int v) : value(v) {}

    // B zu A konvertieren
    operator A() const {
        std::cout << "B to A\n"; return A(value); }

    // B zu C konvertieren
    operator C() const;

    friend B operator+(const B& ,const B& );
};

class C {
public:
    int value;

    C(int v) : value(v) {}

    // C zu A konvertieren
    operator A() const {
        std::cout << "C to A\n"; return A(value); }

    // C zu B konvertieren
    operator B() const {
        std::cout << "C to B\n"; return B(value); }

    friend C operator+(const C& ,const C& );
};

// Implementierung der Konvertierungen

A::operator B() const {
    std::cout << "A to B\n";
    return B(value);  // A zu B
}

A::operator C() const {
    std::cout << "A to C\n";
    return C(value);  // A zu C
}

B::operator C() const {
    std::cout << "B to C\n";
    return C(value);  // B zu C
}



A operator+(const A & a1, const A &a2) {
    return A(a1.value+a2.value);
}

B operator+(const B & b1, const B &b2) {
    return B(b1.value+b2.value);
}

C operator+(const C & c1, const C &c2) {
    return C(c1.value+c2.value);
}


int main() {
    A a(10);
    B b(20);
    C c(30);

    // Beispiele für die Operationen:
    std::cout << "---\n";
    C result1 = static_cast<C>(a) + c;   // A wird zu C konvertiert
    std::cout << "---\n";
    C result2 = static_cast<C>(b) + c;   // B wird zu C konvertiert
    std::cout << "---\n";
    A result3 = static_cast<A>(c) + a;   // A wird zu C konvertiert
    std::cout << "---\n";

    std::cout << "result1 (A + C): " << result1.value << '\n';
    std::cout << "result2 (B + C): " << result2.value << '\n';
    std::cout << "result3 (C + A): " << result3.value << '\n';

    return 0;
}