// Implementation of karatsuba algorithm for multiplication using bit strings
// suppose X=ab ie. X=a*2^(n/2)+b
// similarly Y=cd ie. Y=c*2^(n/2)+d
// then X*Y=ac*2^n+(ad+bc)*2^(n/2)++bd
// if we calculate this by multiplying ad and bc seperatly then
// T(n)=4T(n/2)+O(n)
// this whould not imporve the complexity from O(n^2)
// so , we use ad+bc=(a+b)*(c+d)-ac-bd
// this way we use only 3 multiplication i.e
// X*Y=ac*2^(n)+((a+b)*(c+d)-ac-bd)*2^(n/2)+bd T(n)=3T(n/2)+O(n) this gives
// O(n^1.59)
// to implement wee need X and  Y to be of same length so we first apend zero to
// the one smaller
// then recursivly call to calculate ac,bd,(a+b)*(c+d)
// then return X*Y as ac*2^(n)+((a+b)*(c+d)-ac-bd)*2^(n/2)+bd
#include <bits/stdc++.h>
using namespace std;
#define ll long long

string subString(string larger, string shorter);
string addString(string larger, string shorter);
string trim_zeros(string s);

int makeSizeSame(string &A, string &B) {
  int l1 = A.size();
  int l2 = B.size();
  if (l1 > l2) {
    for (int i = l2; i < l1; i++) {
      B = "0" + B;
    }
    return l1;
  } else {
    for (int i = l1; i < l2; i++) {
      A = "0" + A;
    }
    return l2;
  }
}

string karatsuba(string A, string B) {
  int leng = makeSizeSame(A, B);
  if (leng == 0) {
    return "0";
  }
  if (leng == 1) {
    return to_string(stoi(A) * stoi(B));
  }

  string a = A.substr(0, leng / 2);
  string b = A.substr(leng / 2, INT_MAX);
  string c = B.substr(0, leng / 2);
  string d = B.substr(leng / 2, INT_MAX);
  string ac = karatsuba(a, c);
  string bd = karatsuba(b, d);
  string apbcpd = karatsuba(addString(a, b), addString(c, d));
  string fin = subString(subString(apbcpd, bd), ac);
  for (int i = 0; i < b.size(); i++) {
    ac = ac + "00";
    fin = fin + "0";
  }
  return trim_zeros(addString(addString(ac, fin), bd));
}

int main() {
  cout << karatsuba("255", "53654") << " : " << (ll)(255) * 53654 << "\n";
}

string trim_zeros(string s) {
  int i = 0;
  while (s[i] == '0') ++i;
  if (i == s.length()) return "0";
  return s.substr(i, s.length());
}

string addString(string larger, string shorter) {
  if (larger[0] == '-' && shorter[0] == '-')
    return "-" + addString(larger.substr(1, larger.length() - 1),
                           shorter.substr(1, shorter.length() - 1));
  if (shorter[0] == '-')
    return subString(larger, shorter.substr(1, shorter.length() - 1));
  if (larger[0] == '-')
    return "-" + subString(larger.substr(1, larger.length() - 1), shorter);
  while (larger.length() < shorter.length()) larger = "0" + larger;
  while (shorter.length() < larger.length()) shorter = "0" + shorter;
  int n = larger.length();
  for (int i = n - 1; i >= 0; --i) {
    larger[i] = larger[i] + shorter[i] - '0';
  }
  int i = n - 1, carry = 0;
  while (i >= 0) {
    larger[i] += carry;
    if (larger[i] > '9') {
      larger[i] = larger[i] - 10;
      carry = 1;
    } else
      carry = 0;
    --i;
  }
  if (carry) larger = "1" + larger;
  return trim_zeros(larger);
}

string subString(string larger, string shorter) {
  if (larger[0] == '-' && shorter[0] == '-')
    return "-" + subString(larger.substr(1, larger.length() - 1),
                           shorter.substr(1, shorter.length() - 1));
  if (shorter[0] == '-')
    return addString(larger, shorter.substr(1, shorter.length() - 1));
  if (larger[0] == '-')
    return "-" + addString(larger.substr(1, larger.length() - 1), shorter);
  while (larger.length() < shorter.length()) larger = "0" + larger;
  while (shorter.length() < larger.length()) shorter = "0" + shorter;
  int n = larger.length();
  for (int i = n - 1; i >= 0; --i) {
    larger[i] = larger[i] - shorter[i] + '0';
  }
  int i = n - 1, borrow = 0;
  while (i >= 0) {
    larger[i] -= borrow;
    if (larger[i] < '0') {
      larger[i] = larger[i] + 10;
      borrow = 1;
    } else
      borrow = 0;
    --i;
  }
  if (borrow) {
    int i = 0;
    while (larger[i] == '0' && i < n) ++i;
    string temp = "1";
    while (i++ < n) temp += "0";
    return "-" + trim_zeros(subString(temp, larger));
  }
  return trim_zeros(larger);
}
