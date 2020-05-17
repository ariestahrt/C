#include <bits/stdc++.h>
using namespace std;

#define DEBUG true
#define _(x) if (DEBUG){cout << #x << " = " << x << endl;}
#define __(x) if (DEBUG){cout << #x << " = " << x << " ";}

/*

Floating number is 6 digit

*/

const double E = 1e-8;
const double PI = acos(-1);

typedef struct Number{
    bool positive; // is number positive or not
    string intnum; // as integer number
    double floatnum;    // as floating number stored as double
                        // example 0.000001
                        // example 0.1
                        // example 0.001
}Number;

class BigNumber{
    
    public:
        bool isSmaller(Number A, Number B);
        Number Plus(Number A, Number B, bool isMin);
        Number Minus(Number A, Number B);
        Number Miltiply(Number A, Number B);
        Number Divide(Number A, Number B);
};

bool BigNumber::isSmaller(Number A, Number B) // is A smaller than B
{
    if(A.intnum.length() < B.intnum.length())
    {
        return true;
    }
    else if(A.intnum.length() > B.intnum.length())
    {
        return false;
    }
    else // both are equal
    {
        if(!A.intnum.compare(B.intnum))
        {
            // check floating number
            if(A.floatnum < B.floatnum) return true;
            else return false;
        }
        else
        {
            for(int i=0; i<A.intnum.length(); i++)
            {
                if(A.intnum[i] < B.intnum[i])
                {
                    return true;
                }
            }
        }
    }

    return false;
}

Number BigNumber::Plus(Number A, Number B, bool isMin=false)
{
    // A must be the longest number
    if(A.intnum.length() < B.intnum.length()) swap(A,B);

    // Reverse
    reverse(A.intnum.begin(), A.intnum.end());
    reverse(B.intnum.begin(), B.intnum.end());

    Number result;
    result.intnum   = "";    
    int carry=0;

    // sum floatnum first
    result.floatnum = A.floatnum + B.floatnum;
    if(result.floatnum>1)
    {
        carry = 1;
        result.floatnum -= 1;
    }

    // Sum intnum then
    for(int i=0; i<B.intnum.length(); i++)
    {
        int sum = A.intnum[i]-'0' + B.intnum[i]-'0' + carry;
        result.intnum.push_back(sum%10 + '0');
        carry = sum/10;
    }

    for(int i=B.intnum.length(); i<A.intnum.length(); i++){
        int sum = A.intnum[i]-'0' + carry;
        result.intnum.push_back(sum%10 + '0');
        carry = sum/10;
    }

    // Add remaining carry
    if(!isMin)
        if(carry) result.intnum.push_back(carry+'0');

    // Reverse
    reverse(result.intnum.begin(), result.intnum.end());

    return result;
}

Number BigNumber::Minus(Number A, Number B)
{
    Number result;
    result.positive = false;
    result.intnum   = "";
    result.floatnum = 0;

    // A must be biggest number
    if(this->isSmaller(A,B))
    {
        swap(A.intnum,B.intnum);
        if(A.floatnum - B.floatnum < 0) swap(A.floatnum,B.floatnum);
        result.positive = false;
    }
    else
    {
        result.positive = true;
    }
    
    // Reverse
    reverse(A.intnum.begin(), A.intnum.end());
    reverse(B.intnum.begin(), B.intnum.end());

    // equalize the lenght of two int number
    if(A.intnum.length() < B.intnum.length())
        while(A.intnum.length() < B.intnum.length())
            A.intnum.push_back('0');
    else
        while(B.intnum.length() < A.intnum.length())
            B.intnum.push_back('0');
    
    // Reverse
    reverse(A.intnum.begin(), A.intnum.end());
    reverse(B.intnum.begin(), B.intnum.end());

    // Komplement kan dulu
    for(int i=0; i<B.intnum.length(); i++)
    {
        int temp = abs(B.intnum[i]-='9');
        B.intnum[i] = temp + '0';
    }

    Number temp;
    temp.intnum = "1";
    temp.floatnum = 0;
    // Add B+carry
    B = this->Plus(B, temp, true);

    Number temp_A = A;
    temp_A.floatnum = 0;
    Number temp_B = B;
    temp_B.floatnum = 0;

    // The result for complete intnumber calculation is
    result.intnum = this->Plus(temp_A, temp_B, true).intnum;

    // if floating number is negative, result - 1;
    if(A.floatnum - B.floatnum < 0) result.intnum = this->Minus(result,temp).intnum;
    // Add complete the floating number
    result.floatnum = A.floatnum - B.floatnum;
    if(result.floatnum < 0) result.floatnum += 1;
    return result;
}

int main() {
    ios::sync_with_stdio(false);

    BigNumber _bigNumber;
    Number a;
    Number b;

    // double test = 0.56;
    // cout << to_string(test);


    cout << "A : ";
    cin >> a.intnum >> a.floatnum;

    cout << "B : ";
    cin >> b.intnum >> b.floatnum;

    Number num = _bigNumber.Minus(a, b);
    if(!num.positive) cout << "-";
    cout << num.intnum << "." << num.floatnum*1000000;
}
