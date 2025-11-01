#include <bits/stdc++.h>
#include "bigint.h"
#include <ctime>

using namespace std;

bigint pow(bigint base, bigint exp, bigint mod);

// 1. Prime numbers
const vector<bigint> smallPrimes = {
      3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,  97, 101, 103, 107, 109, 113, 127,
    131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
    211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
    293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383,
    389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467,
    479, 487, 491, 499, 503, 509, 521, 523, 541
};

bool test(bigint a, bigint n, bigint k, bigint m){
    bigint mod = pow(a, m, n);
    bigint one = 1;
    if (mod == one || mod == n - one)
        return true;

    for (int l = 1; l < k; ++l){
        mod = (mod * mod) % n;
        if (mod == n - one)
            return true;
    }
    return false;
}

bool MillerRabin(bigint n){
    static vector<bigint> checkSet = {2, 3, 7, 11, 13};
    bigint two = 2;
    if (n < two)
        return false;

    bigint k = 0, m = n - to_bigint(1);
    while (m % to_bigint(2) == to_bigint(0)){
        m /= 2;
        k++;
    }

    for (bigint a : checkSet){
        if (a >= n) continue;
        if (!test(a, n, k, m))
            return false;
    }
            
    return true;
}

bigint randomOddBigint(int bytes) {
    vector<unsigned char> data(bytes);
    for (int i = 0; i < bytes; i++) data[i] = rand() & 0xFF;

    if (bytes > 1)
        data[0] |= 0x80;
    data.back() |= 1;

    bigint result = 0;
    for (unsigned char c : data)
        result = result * to_bigint(256) + to_bigint(c);

    return result;
}


bigint genPrime(int bytelength){
    int count = 0;
    while(true){
        bigint p = randomOddBigint(bytelength);
        bool isComposite = false;
        for (bigint prime : smallPrimes) {
            if (p == prime) {
                isComposite = false;
                break;
            }

            if (p % prime == to_bigint(0)) { 
                isComposite = true;
                break;
            }
        }
        if (isComposite)
            continue;
        if (MillerRabin(p))
            return p;
        count++;
        if(count == 10)
            cout << "Checked 10 random numbers!!!\n";
    }
}

// 2. Greatest common divisor (using Euclidean Algorithm)
bigint myGCD(bigint a, bigint b) {
    if (a == to_bigint(0))
        return b;
    return myGCD(b % a, a);
}


// 3. Modular exponentiation
bigint pow(bigint base, bigint exp, bigint mod) {
    bigint res = bigint(1);
    base %= mod;

    while (exp > bigint(0)) {
        if (exp % bigint(2) == bigint(1))
            res = (res * base) % mod;
        exp /= bigint(2);
        base = (base * base) % mod;
    }
    return res;
}


int main() {
    srand(time(NULL));
    cout << "This is my program related to Number Theory\n";
    while(true){
        int choice;
        cout << "\nHere is the menu selection:\n";
        cout << "1. PRIME NUMBERS\n";
        cout << "2. GREATEST COMMON DIVISOR\n";
        cout << "3. MODULAR EXPONENTIATION\n";
        cout << "4. Exit the program\n";
        cout << "Enter your choice (1, 2, 3, 4): "; cin >> choice;
        if(choice == 1){
            int bytelength;
            cout << "\n-------------PRIME NUMBERS-------------\n";
            cout << "--Generate random primes with bit-length--\n";
            cout << "Enter your byte selection: "; cin >> bytelength;
            bigint z = genPrime(bytelength);
            cout << "Here is your " << bytelength << "-byte prime number: " << z << endl;
            cout << "Check prime numbers: "; cin >> z;
            if(MillerRabin(z))
                cout << z << " is a prime number\n";
            else
                cout << z << " is not a prime number\n";
        } else if(choice == 2){
            bigint x, y;
            cout << "\n---GREATEST COMMON DIVISOR---\n";
            cout << "Enter first number: "; cin >> x;
            cout << "Enter second number: "; cin >> y;
            bigint res2 = myGCD(x, y);
            cout << "Result: gcd(" << x << ", " << y << ") = " << res2 << endl;
        } else if (choice == 3){
            bigint b, e, p;
            cout << "\n----MODULAR EXPONENTIATION----\n";
            cout << "Enter base: "; cin >> b;
            cout << "Enter exponent: "; cin >> e;
            cout << "Enter modulo: "; cin >> p;
            bigint res3 = pow(b, e, p);
            cout << "The value of " << b << "^" << e << " mod " << p << " is: " << res3 << endl;
        } else if (choice == 4){
            return 0;
        } else cout << "This is not a valid selection, please re-enter!!!\n";
    }
}