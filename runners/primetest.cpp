#include <iostream>
#include "LinkedBigNumber.h"

typedef unsigned long long int ull;

sll WITNESSES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
int nWitnesses = 13;

using namespace std;


int main()
{

    // cool ones: 3221225473

    BigNumber numToCheck = BigNumber("12345678910987654321");
    cout << "executing the Miller-Rabin primality test on p = " << numToCheck << endl;

    // rewrite number
    cout << "[ Step 1 ] rewrite p as 2^r * d + 1 ==> ";

    bool isPrime = true;

    BigNumber d = numToCheck - 1; // = number - 1, but cooler
    ull r = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        r++;
    }

    cout << numToCheck << " = 2^" << r << "*" << d << " + 1" << endl;

    for (int i = 0; i < nWitnesses; i++)
    {
        BigNumber witness = BigNumber(WITNESSES[i]);
        cout << "[ Step 2." << (i + 1) << " ] for witness a = " << witness << " do: " << endl;

        cout << "--( 1  ) calculate a^d mod n ==> ";

        BigNumber result = powMod(witness, d, numToCheck);

        /*
        this is some slow shit
        for (ull exponent = 0; exponent < d; exponent++)
        {
            result *= witness;
            result %= numToCheck;
        }
        */

        cout << witness << "^" << d << " mod " << numToCheck << " = " << result << endl;

        bool isOne = result == 1 || numToCheck - 1 == result;
        cout << "--( 2  ) is result = 1 or (p - 1) ? " << (isOne ? "Yes" : "No") << endl;

        if (!isOne)
        {

            cout << "--( 3B ) in that case, we should check further" << endl;

            BigNumber oldSecondaryResult = result;
            BigNumber secondaryResult = result;
            for (ull j = 0; j < r; j++)
            {
                secondaryResult = oldSecondaryResult * oldSecondaryResult;
                secondaryResult %= numToCheck;

                isOne = secondaryResult == 1 || secondaryResult == numToCheck - 1;

                cout << "--( 3B." << (j + 1) << " ] is result^2 mod p = 1 or (p-1) ? " << oldSecondaryResult << "^2 mod " << numToCheck << " = " << secondaryResult << "? " << (isOne ? "yes" : "no") << endl;

                if (isOne)
                {
                    break;
                }
                else
                {
                    cout << "--( 3B.2B )-[ " << (j + 1) << " ] continuing search " << endl;
                }

                oldSecondaryResult = secondaryResult;
            }
        }

        cout << "--( 4 ) ";

        if (isOne)
        {
            cout << "p = " << numToCheck << " passes the Miller-Rabin primality test for witness " << witness << endl;
        }
        else
        {
            cout << "p = " << numToCheck << " is not a prime" << endl;
        }
        cout << endl;

        isPrime &= isOne;
    }

    cout << "[ Conclusion ] ";
    if (isPrime)
    {
        cout << numToCheck << " passes the Miller-Rabin primality test for " << nWitnesses << " witnesses";
    }
    else
    {
        cout << numToCheck << " is not a prime";
    }
    cout << endl;

    return 0;
}