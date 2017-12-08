/**
Binary index Tree with creation in nlogn, query in logn, update in logn time.

For getting next Tree node use following steps:
1. 2's complement current node index
2. AND it with current node index
3. Add it with current node index

For getting parent node index in case of query:
1. 2's complement of current node
2. And it with current node index
3. Subtract it from current node index

*/
/**
Author @Aitto_sang
CSE@Buet
*/
#include<stdio.h>
#include<iostream>
//#include<cmath>
//#include<cstdlib>
//#include<algorithm>
//#include<stack>
#include<cstring>
//#include<bits/stdc++.h>

#define lli long long int
#define pf printf
#define sf scanf
#define pi 3.141592653589793116
#define inf 1e9
#define linf 1e15
#define NULL_VALUE -999999
#define maxNEG -99999999.0
#define debug cout<<"Hello here!"<<endl;
#define readFile freopen("in.txt","r",stdin);
#define syncronize ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

using namespace std;

void updateTree(int *binaryTree,int value,int index,int len);

//Creating binary index tree. On sum property.
//You can write your own function here

void createBinaryIndexTree(int *arr,int *binaryTree,int len){

    int index;
    for(int i=1;i<=len;i++){
        index=i;

        //updating tree value
        updateTree(binaryTree,arr[i-1],i,len);
    }

}

//Updating Tree with sum property
void updateTree(int *binaryTree,int value,int index,int len){
    while(index<=len){

        //Sum property... Add your own function here
        binaryTree[index]+=value;
        index+=(index&-index); //getting next
    }
}

//Function for getting sum from node (0 to i)
/**
Here remember one thing, always sum 1 with index, because binary index tree always starts indexing from 1
zero index is dumi node which stores zero
*/
int getSum(int *binaryTree,int index){
    int sum=0;
    index++;
    while(index>0){
        sum+=binaryTree[index];
        index-=(index & -index);
    }

    return sum;
}

void print(int *arr,int len){
    for(int i=0;i<=len;i++) cout<<arr[i]<< " ";
}

int main(){
    syncronize

    int n;
    cin>>n;
    int *arr=new int[n +1], *binaryTree=new int[n +1];

    for(int i=0;i<=n;i++) binaryTree[i]=arr[i]=0;

    for(int i=0;i<n;i++) cin>>arr[i];

    createBinaryIndexTree(arr,binaryTree,n);

    cout<< "Binary Tree: ", print(binaryTree,n);


    cout<<endl<< "Sum: " <<getSum(binaryTree,0);

    return 0;
}
// dumy input: 11 3 2 -1 6 5 4 -3 3 7 2 3
