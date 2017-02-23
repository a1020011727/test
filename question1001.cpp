#include "iostream"
using namespace std;

int input(int array[10][10],int a,int b)
{
	int i,m,temp;
	i = m = temp = 0;
	while(m<=10){
		if(m>=a)
			break;
		i=0;
		while(i<=10){

			if(i>b-1){
				break;
			}
			cin>>temp;
			array[m][i]=temp;
			i++;

		}
		m++;
	}
	return array[10][10];
	delete []array;
}

void count(int array[10][10],int a,int b){
	int r,c,sum,count;
	r=c=sum=count=0;
	for (r=0 ;r<a;r++)
	{
		sum=0;
		for(c=0;c<b;c++)
			sum+=array[r][c];
		if(sum==0)
			count++;
	}
	for (c=0 ;c<b;c++)
	{
		sum=0;
		for(r=0;r<a;r++)
			sum+=array[r][c];
		if(sum==0)
			count++;
	}

	cout<<count<<endl;
}

int main()
{
	int a,b,r,c;
	a=b=r=c=0;

	while(1){
	cin>>a;
	if(a==0)
		break;
    cin>>b;
    if(b==0)
		break;
    int arr1[10][10]={0};
	int arr2[10][10]={0};
	int sum[10][10]={0};
	input(arr1,a,b);
	input(arr2,a,b);
	for (r=0 ;r<a;r++)
	{
		for(c=0;c<b;c++)
		{
			sum[r][c]= arr1[r][c]+arr2[r][c];
		}
	}
	count(sum,a,b);

	}
	return 0;
}

