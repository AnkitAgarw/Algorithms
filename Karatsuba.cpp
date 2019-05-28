//Implementation of karatsuba algorithm for multiplication using bit strings
//suppose X=ab ie. X=a*2^(n/2)+b
//similarly Y=cd ie. Y=c*2^(n/2)+d
//then X*Y=ac*2^n+(ad+bc)*2^(n/2)++bd
//if we calculate this by multiplying ad and bc seperatly then
//T(n)=4T(n/2)+O(n)
//this whould not imporve the complexity from O(n^2)
// so , we use ad+bc=(a+b)*(c+d)-ac-bd
//this way we use only 3 multiplication i.e X*Y=ac*2^(n)+((a+b)*(c+d)-ac-bd)*2^(n/2)+bd
//T(n)=3T(n/2)+O(n) this gives O(n^1.59)
// to implement wee need X and  Y to be of same length so we first apend zero to the one smaller
//then recursivly call to calculate ac,bd,(a+b)*(c+d)
//then return X*Y as ac*2^(n)+((a+b)*(c+d)-ac-bd)*2^(n/2)+bd
#include <bits/stdc++.h>
using namespace std;
#define ll long long

//a function that takes a char(bool) and returns not in integer format 
int notFunc(char a){
	if(a=='0'){
		return 1;
	}
	return 0;
}

//takes int and returns 1 if input not 0
int convertToBool(int a){
	if(a) return 1;
	return 0;
}

//converts binary number(string) to decimal(long long)
ll binToDec(string a){
	ll ans=0;
	ll temp;
	for(int i=a.size()-1;i>=0;i--){
		temp=a[i]-'0';
		ans+=(temp<<((int)a.size()-i-1));
		// cout<<i<<"\n";
	}
	return ans;
}



//find differnce A-B assuming A>B
string findDiff(string A,string B){
	int l1=0,l2=0;
	l1=A.length();
	l2=B.length();
	int borrow=0;
	string result;
	int S;
	for(int i=l2-1;i>=0;i--){
		//using expression for full subtrator 
		S=notFunc(A[l1-l2+i])*notFunc(B[i])*borrow +(A[l1-l2+i]-'0')*notFunc(B[i])*notFunc(borrow+'0')+borrow*(A[l1-l2+i]-'0')*(B[i]-'0')+notFunc(A[l1-l2+i])*(B[i]-'0')*notFunc(borrow+'0');
		borrow=notFunc(A[l1-l2+i])*borrow +notFunc(A[l1-l2+i])*(B[i]-'0')+borrow*(B[i]-'0');
		result=(char)(convertToBool(S)+'0')+result;
	}
	int i=l2;


	while(A[l1-i-1]=='0' && borrow==1){
		// cout<<"l1-i="<<l1-i<<" A[l1-i]="<<A[l1-i]<<" borrow= "<<borrow<<"\n";
		result='1'+result;
		i++;
	}
	if(borrow==1){
		result='0'+result;
		i++;
	}
	while(i<l1-1){
		result=A[l1-i-1] + result;
		i++;
	}
	return result;
}
int makeSizeSame(string &A,string &B){
	int l1=A.size();
	int l2=B.size();
	if(l1>l2){
		// cout<<"here\n";
		for(int i=l2;i<l1;i++){
			B='0'+B;
		}
		return l1;
	}else{
		for(int i=l1;i<l2;i++){
			A='0'+A;
		}
		return l2;
	}
	return 0;
}

string findSum(string A,string B){
	int tw=makeSizeSame(A,B);
	string result;
	int carry=0;
	int S=0;
	for(int i=A.size()-1;i>=0;i--){
		S=(A[i]-'0')^(B[i]-'0')^(carry);
		carry=(B[i]-'0')*(carry)+(A[i]-'0')*carry+(A[i]-'0')*(B[i]-'0');
		carry=convertToBool(carry);
		result=(char)(convertToBool(S)+'0')+result;
	}
	if(carry){
		result='1'+result;
	}
	return result;
}
string karatsuba(string A,string B){
	int leng=makeSizeSame(A,B);
	// cout<<" length= "<<leng<<" A="<<A<<" B="<<B<<"\n";
	if (leng==0){

		return ""+'0';
	}
	if(leng==1){
		char a=((A[0]-'0')*(B[0]-'0'))+'0';
		string b;
		b=a+b;


		cout<<"ans :"<<b<<"\n";
		return b;
	}

	string a= A.substr(0,leng/2);
	string b= A.substr(leng/2,leng-leng/2);
	string c= B.substr(0,leng/2);
	string d= B.substr(leng/2,leng-leng/2);
	string ac= karatsuba(a,c);
	string bd=karatsuba(b,d);
	string apbcpd=karatsuba(findSum(a,b),findSum(c,d));
	string fin =findDiff(findDiff(apbcpd,bd),ac);
	for(int i=0;i<b.size();i++){
		ac=ac+"00";
	}
	for(int i=0;i<b.size();i++){
		fin=fin+"0";
	}
	// cout<<" A="<<A<<" B="<<B<<"fin "<<fin<<"ac= "<<ac<<" bd= 0"<<bd<<" A*B= "<<findSum(findSum(ac,fin),bd)<<"\n";
	return findSum(findSum(ac,fin),bd);

}


int main(){
	// string a,b,c;
	// cin>>b>>c;
	// cout<<findDiff(b,c)<<" ";
	string A="0011000111",B="100";
	string a=karatsuba(A,B);
	cout<<"\n"<<binToDec(A)<<" "<<binToDec(B)<<" "<<binToDec(a);	
	// string A="0011000111",B="";
	// string ans=karatsuba(A,B);
	// cout<<"A="<<A<<" B="<<B<<" ans"<<ans;

}