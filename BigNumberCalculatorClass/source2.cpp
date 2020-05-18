#include <bits/stdc++.h>
using namespace std;

#define DEBUG true
#define _(x) if (DEBUG){cout << #x << " = " << x << endl;}
#define __(x) if (DEBUG){cout << #x << " = " << x << " ";}

#define maxfloat 100

const string ZERO = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

const double E = 1e-8;
const double PI = acos(-1);

typedef struct Number{
    bool positive; // is number positive or not
    string intnum; // as integer number
    string floatnum; // as floating number stored as string max floating point is 100
}Number;

class BigNumber{
    
    public:
        bool isSmaller(Number A, Number B);
        Number Plus(Number A, Number B, bool fromMin);
        Number Minus(Number A, Number B, bool fromMin);
        Number Multiply(Number A, Number B);
        string MultiplyUtil(string A, string B);
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
            while(A.floatnum.length() < 100) A.floatnum.push_back('0');
            while(B.floatnum.length() < 100) B.floatnum.push_back('0');
            if(A.intnum.compare(B.intnum) < 0 ) return true;
            else return false;
        }
        else
        {
            if(A.intnum.compare(B.intnum) < 0) return true;
            else return false;
        }
    }

    return false;
}

Number BigNumber::Plus(Number A, Number B, bool fromMin=false)
{
    // A must be the longest number
    if(A.intnum.length() < B.intnum.length()) swap(A,B);

    Number result;
    result.intnum   = "";    
    result.floatnum = "";    

    int carry=0;

    // sum floating number
    while(A.floatnum.length() > maxfloat) A.floatnum.pop_back();
    while(B.floatnum.length() > maxfloat) B.floatnum.pop_back();
    while(A.floatnum.length() < maxfloat) A.floatnum.push_back('0');
    while(B.floatnum.length() < maxfloat) B.floatnum.push_back('0');

    // reverse floating number to count from behind
    reverse(A.floatnum.begin(), A.floatnum.end());
    reverse(B.floatnum.begin(), B.floatnum.end());

    for(int i=0; i<B.floatnum.length(); i++)
    {
        int sum = A.floatnum[i]-'0' + B.floatnum[i]-'0' + carry;
        result.floatnum.push_back(sum%10 + '0');
        carry = sum/10;
    }

    // reverse floating number again
    reverse(result.floatnum.begin(), result.floatnum.end());

    if(carry) // check is sum of floating number > 0
    {
        Number temp;
        temp.intnum   = "1";
        temp.floatnum = ZERO;

        // add to A.intnum
        A.intnum = this->Plus(A, temp).intnum;
    }

    carry = 0;

    // the sum intnum
    // Reverse intnum
    reverse(A.intnum.begin(), A.intnum.end());
    reverse(B.intnum.begin(), B.intnum.end());

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
    if(!fromMin)
        if(carry) result.intnum.push_back(carry+'0');

    // Reverse
    reverse(result.intnum.begin(), result.intnum.end());
    return result;
}

Number BigNumber::Minus(Number A, Number B, bool fromMin = false)
{
    Number result;
    result.positive = false;
    result.intnum   = "";
    result.floatnum = ZERO;

    // A must be biggest number
    if(this->isSmaller(A,B))
    {
        swap(A.intnum,B.intnum);

        Number temp1;
        temp1.intnum   = "0";
        temp1.floatnum = A.floatnum;

        Number temp2;
        temp2.intnum   = "0";
        temp2.floatnum = B.floatnum;
        
        if(this->isSmaller(temp1,temp2)) swap(A.floatnum,B.floatnum);
        result.positive = false;
    }
    else
    {
        result.positive = true;
    }

    while(A.floatnum.length() < 100) A.floatnum.push_back('0');
    while(B.floatnum.length() < 100) B.floatnum.push_back('0');
    
    // Reverse to equalize thoose number
    reverse(A.intnum.begin(), A.intnum.end());
    reverse(B.intnum.begin(), B.intnum.end());

    // equalize the lenght of two int number
    if(A.intnum.length() < B.intnum.length())
        while(A.intnum.length() < B.intnum.length())
            A.intnum.push_back('0');
    else
        while(B.intnum.length() < A.intnum.length())
            B.intnum.push_back('0');
    
    // Reverse again
    reverse(A.intnum.begin(), A.intnum.end());
    reverse(B.intnum.begin(), B.intnum.end());

    // Di komplement kan dulu
    for(int i=0; i<B.intnum.length(); i++)
    {
        int temp = abs(B.intnum[i]-='9');
        B.intnum[i] = temp + '0';
    }

    Number temp;
    temp.intnum = "1";
    temp.floatnum = ZERO;
    // Add B+carry
    B = this->Plus(B, temp, true);

    Number temp_A = A;
    temp_A.floatnum = ZERO;
    Number temp_B = B;
    temp_B.floatnum = ZERO;

    // The result for complete intnumber calculation is
    result.intnum = this->Plus(temp_A, temp_B, true).intnum;

    temp_A.intnum   = A.floatnum;
    temp_A.floatnum = ZERO;
    temp_B.intnum   = B.floatnum;
    temp_B.floatnum = ZERO;
    
    if(!fromMin)
        result.floatnum = this->Minus(temp_A, temp_B, true).intnum;
    
    return result;
}

string BigNumber::MultiplyUtil(string A, string B)
{
    string result = "";

    Number temp1;
    temp1.intnum   = A;
    temp1.floatnum = ZERO;

    Number temp2;
    temp2.intnum   = B;
    temp2.floatnum = ZERO;
    
    if(this->isSmaller(temp1,temp2)) swap(A, B);    
    string resultLine[B.length()];

    int currentIndex = B.length()-1;
    for(int i=0; i<B.length(); i++)
    {
        resultLine[i]="0";

        for(int j=B[currentIndex]-'0'; j>0; j--)
        {
            temp1.intnum = resultLine[i];
            temp2.intnum = A;
            resultLine[i] = this->Plus(temp1, temp2).intnum;
        }

        for(int j=0; j<i; j++) resultLine[i].push_back('0');
        currentIndex--;
    }

    for(int i=0; i<B.length(); i++)
    {
        temp1.intnum   = result;
        temp2.intnum   = resultLine[i];
        result = this->Plus(temp1, temp2).intnum;
    }

    return result;
}

Number BigNumber::Multiply(Number A, Number B)
{
    // (A.int + A.float) * (B.int + B.float)
    // (A.int * B.int) + (A.int * B.float) + (A.float * B.int) + (B.float * B.float)

    Number temp1;
    temp1.intnum   = "0";
    temp1.floatnum = ZERO;

    Number temp2;
    temp2.intnum   = "0";
    temp2.floatnum = ZERO;

    // clear floating number 0 value at the end
    for(int i=A.floatnum.length()-1; i>0; i--)
        if(A.floatnum[i] == '0') A.floatnum.pop_back();

    for(int i=B.floatnum.length()-1; i>0; i--)
        if(B.floatnum[i] == '0') B.floatnum.pop_back();

    // (A.int * B.int)
    Number step1;
    step1.intnum   = "0";
    step1.floatnum = ZERO;

    step1.intnum = this->MultiplyUtil(A.intnum, B.intnum);

    // (A.int * B.float)
    Number step2;
    step2.intnum   = "0";
    step2.floatnum = ZERO;

    step2.intnum = this->MultiplyUtil(A.intnum, B.floatnum);
    // check floatnum lenght, and pop from intnum and push to step2.floatnum about B.floatnum lenght times
    for(int i=0; i<B.floatnum.length(); i++)
    {
        if(step2.intnum.empty()) step2.intnum.push_back('0');
        step2.floatnum.push_back(step2.intnum.back());
        step2.intnum.pop_back();
        if(step2.intnum.empty()) step2.intnum.push_back('0');
    }
    reverse(step2.floatnum.begin(), step2.floatnum.end());

    // (A.float * B.int)
    Number step3;
    step3.intnum   = "0";
    step3.floatnum = ZERO;

    step3.intnum = this->MultiplyUtil(A.floatnum, B.intnum);
    // check floatnum lenght, and pop from intnum and push to step3.floatnum about B.floatnum lenght times
    for(int i=0; i<A.floatnum.length(); i++)
    {
        if(step3.intnum.empty()) step3.intnum.push_back('0');
        step3.floatnum.push_back(step3.intnum.back());
        step3.intnum.pop_back();
    }
    if(step3.intnum.empty()) step3.intnum.push_back('0');
    reverse(step3.floatnum.begin(), step3.floatnum.end());

    // (A.float * B.float)
    Number step4;
    step4.intnum   = "0";
    step4.floatnum = ZERO;

    step4.intnum = this->MultiplyUtil(A.floatnum, B.floatnum);
    // check floatnum lenght, and pop from intnum and push to step4.floatnum about B.floatnum lenght times
    for(int i=0; i<A.floatnum.length(); i++)
    {
        if(step4.intnum.empty()) step4.intnum.push_back('0');
        step4.floatnum.push_back(step4.intnum.back());
        step4.intnum.pop_back();
    }

    for(int i=0; i<B.floatnum.length(); i++)
    {
        if(step4.intnum.empty()) step4.intnum.push_back('0');
        step4.floatnum.push_back(step4.intnum.back());
        step4.intnum.pop_back();
    }
    if(step4.intnum.empty()) step4.intnum.push_back('0');

    reverse(step4.floatnum.begin(), step4.floatnum.end());

    // result = step1 + step2 + step3 + step4
    Number result;

    result = this->Plus(step1,step2);
    result = this->Plus(result,step3);
    result = this->Plus(result,step4);

    if(!A.positive || !B.positive)
        result.positive = false;
    else
        result.positive = true;

    return result;
}

int main() {
    ios::sync_with_stdio(false);

    BigNumber _bigNumber;
    Number a; a.positive = true;
    Number b; b.positive = true;

    cout << "A : ";
    cin >> a.intnum >> a.floatnum;

    cout << "B : ";
    cin >> b.intnum >> b.floatnum;

    // cout << _bigNumber.MultiplyUtil("654545454878786546546546545656","654545454878786546546546545656") << endl;
    // Number num = _bigNumber.Minus(a, b);

    Number num = _bigNumber.Multiply(a, b);
    if(!num.positive) cout << "-";
    cout << num.intnum << "." << num.floatnum;
}
