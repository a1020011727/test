// codeding test.cpp : 定义控制台应用程序的入口点。
//
#include "StdAfx.h"
#include "iostream"
#include "stdlib.h"
using namespace std;

char check(char A[12]){
	int i=0;
	int p=0;
	char temp;
	long B=0;
	while(i<12){
		temp=A[i];
		if(temp==',')
			for(p=i;p<12;p++){
				A[p]=A[p+1];
			}
		i++;
	}
	return  A[12];
}

int main()
{
	char A[12]={0};
	char B[12]={0};
	int i=0;
	int sum=0;
	while(cin>>A>>B){
		check(A);
		check(B);
		i=atoi(A);
		sum=atoi(B);
		cout <<i+sum<<endl;
	}
	return 0;
}
