/**
*   Segment Tree is a advanced data structure. Segment Tree stores data in O(n) space, created in O(n) time and query in(log n) time

    Segment tree is used for ranged query. Such as minimum between a-b, sum between a-b etc.
*/

#include<stdio.h>
#include<iostream>
//#include<cmath>
//#include<cstdlib>
#include<algorithm>
//#include<stack>
//#include<cstring>
//#include<bits/stdc++.h>

#define lli long long int
#define pf printf
#define sf scanf
#define pi 3.141592653589793116
#define inf 1e9
#define linf 1e15
#define maxNEG -99999999.0
#define debug cout<<"Hello here!"<<endl;
#define readFile freopen("in.txt","r",stdin);
#define syncronize ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

using namespace std;

//Finds next 2's power
int nextPowerOfTwo(lli n){
    lli flag=1;
    int i=0;

    while(1){
        i++;
        flag=flag<<1;
        if(flag>=n) return 1<<i;
    }
}

/**
    Creates segment Tree, according to choice in given function. Can be created minimum segment tree, maximum segment tree,
    sum-range segment Tree, multiply segment Tree etc
*/
void createSegmentTree(lli *segTree,lli *arr,int l,int h,int pos,lli (*f)(lli,lli)){
    if(l==h) {
        segTree[pos]=arr[l];  //if l==h means we've reached at bottom
        return;
    }

    int mid=(l + h)/2; //Partitioning the tree into two segments

    //Creating segment tree,
    createSegmentTree(segTree,arr,l,mid,pos*2,(*f)), createSegmentTree(segTree,arr,mid+1,h, pos*2 +1,(*f));

    segTree[pos]=(*f)(segTree[2*pos],segTree[2*pos +1]);
}

/**
    Doing Range query. According to choice. Whatever function given in create Segment Tree, must be given in this query function too.
    else, it'll give false result
*/
lli rangeQuery(lli *segTree,lli *arr,int querylow,int queryhigh,int low,int high,int pos,lli (*f)(lli,lli)){

    //debug
    if(low>=querylow and high<=queryhigh) return segTree[pos];
    if(querylow > high or queryhigh < low) return linf;

    int mid=(low + high)/2;
    return (*f)(rangeQuery(segTree,arr,querylow,queryhigh,low,mid,2*pos,(*f)), rangeQuery(segTree,arr,querylow,queryhigh,mid +1,high,2*pos +1, (*f)) );

}

/**
Functions defining type of segment Tree
*/
lli minimum(lli a,lli b){
    return a<b?a:b;
}

lli maximum(lli a,lli b){
    return a>b?a:b;
}

lli sum(lli a,lli b,lli k=-1){
    if(k==-1)
        return a+b;
    return (a+b)%k;
}

lli multi(lli a,lli b,lli k=-1){
    if(k==-1) return a*b;
    return (a*b)%k;
}

int main(){

    syncronize

    int n;
    cin>>n; //Input size of array

    int len=2*nextPowerOfTwo(n); //Determining size of segment Tree using 2*length -1 formula
    cout<< "Segment Tree Size: "<<len<<endl;

    //array memory allocation for input array and segment Tree
    lli *arr,*segTree;
    arr=new lli[2*n], segTree=new lli[len];

    //Taking input and initializing
    for(int i=1;i<=n;i++) cin>>arr[i], segTree[i]=inf;
    for(int i=n+1;i<=len;i++) segTree[i]=inf;

    //Creating Segment Tree
    createSegmentTree(segTree,arr,1,n,1,minimum);

    //Display Segment Tree
    cout<< "Segment Tree is: "<<endl;
    for(int i=1;i<len;i++) cout<< i<< " "<<segTree[i]<<endl;

    int left,right;
    cout<< "Enter Range"<<endl;
    cin>>left>>right, cout<< "Smallest between the range: "<<rangeQuery(segTree,arr,left,right,1,n,1,minimum);

    return 0;
}

/**
7
5 9 8 7 6 4 1
3 5
*/
