#include<bits/stdc++.h>
using namespace std;
string arr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string enCeasar(string s,int k)
{
	string t = "";
	for(auto i: s ){
		int p = i-'A';
		int c = (p+k)%26;
		t += arr[c];
	}
	return t;
}
string deCeasar(string s,int k)
{
	string t = "";
	for(auto i: s ){
		int p = i-'A';
		int c = (abs(p-k)) %26;
		t += arr[c];
	}
	return t;
}
int main(){
	int k;
	string s;
	cout<<"Nhap input: "; cin>>s;
	cout<<"Nhap khoa K: "; cin>>k;
	string decode = enCeasar(s,k);
	cout<<decode<<endl;
	cout<<deCeasar(s,k);
	
}


