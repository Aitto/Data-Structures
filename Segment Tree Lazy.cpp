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

int nextPowerofTwo(int n){

    int i=1,mask=i;

    while(1){
        mask=mask<<1;
        if(mask>=n) return 1<<i;
        i++;
    }

}

//Making of a segment Tree
void makeSegmentTree(int *segmentTree,int *arr,int low,int high,int pos){

    if(low==high){
        //Means we're at bottom
        segmentTree[pos]=arr[low];
        return;
    }

    int mid=(low + high)/2;

    makeSegmentTree(segmentTree,arr,low,mid,2*pos);
    makeSegmentTree(segmentTree,arr,mid +1,high,2*pos +1);

    /**Write your own function here*/
    segmentTree[pos]=min(segmentTree[2*pos],segmentTree[2*pos +1]);

}

//Segment Tree Lazy Propagation
void segmentTreeLazy(int *segmentTree,int *lazyTree,int qlow,int qhigh,int low,int high,int pos,int value){
    if(low > high) return; //Un-handled condition may occur

    if(lazyTree[pos]!=0){
        //Means value hasn't propagated yet

        segmentTree[pos]+=lazyTree[pos];

        if(low!=high){
            //Meaning we're not at the bottom
            lazyTree[2*pos] += lazyTree[pos];
            lazyTree[2*pos +1]+=lazyTree[pos];
        }

        lazyTree[pos]=0; // Meaning we've propagated the value
    }

    //No overlap... So return
    if(qlow>high or qhigh<low ) return;

    if(qlow<=low and qhigh>=high){
        // total Overlap
        segmentTree[pos] +=value;
        if(low !=high){
            lazyTree[2*pos]+=value;
            lazyTree[2*pos +1]+=value;
        }
        //Lazy propagation... If we go down through the leaf... If won't be nlogn
        return;
    }

    int mid=(low + high)/2;

    segmentTreeLazy(segmentTree,lazyTree,qlow,qhigh,low,mid,2*pos,value);
    segmentTreeLazy(segmentTree,lazyTree,qlow,qhigh,mid +1,high,2*pos +1,value);
    segmentTree[pos]=min(segmentTree[2*pos],segmentTree[2*pos +1]);

}

/**
Write down your query function here
*/
int rangeMinQuer(int *segmentTree,int *lazyTree,int qlow,int qhigh,int low,int high,int pos){

    if( low > high ) return inf;

    if(lazyTree[pos]!=0){
        //Write query condition : sum, div...
        segmentTree[pos]+=lazyTree[pos];

        //Not in leaf node
        if( low != high){
            lazyTree[2* pos] +=lazyTree[pos];
            lazyTree[2*pos +1]+=lazyTree[pos];
        }
        lazyTree[pos]=0;
    }

    if(qlow > high or qhigh< low) return inf;

    if(qlow<=low and qhigh>= high) return segmentTree[pos];

    int mid= (low +high)/2;

    return min( rangeMinQuer(segmentTree,lazyTree,qlow,qhigh,low,mid,2*pos),
                rangeMinQuer(segmentTree,lazyTree,qlow,qhigh,mid +1,high,2*pos +1));

}

void printTree(int *arr,int len){
    for(int i=1;i<=len;i++) cout<< arr[i]<< " ";
}

int main(){
    syncronize

    int n,m,a,b,v;
    cin>>n>>m;

    int len=2*nextPowerofTwo(n);
    //cout<< "Length: "<<len<<endl;

    int *arr=new int[n +1];
    int *segmentTree,*lazyTree;
    segmentTree=new int[len +1], lazyTree=new int[len +1];

    for(int i=0;i<=len;i++) segmentTree[i]=0, lazyTree[i]=0;

    for(int i=1;i<=n;i++) cin>>arr[i];

    makeSegmentTree(segmentTree,arr,1,n,1);
    //cout<< "Seg Tree: ",printTree(segmentTree,len),cout<<endl;
    for(int i=0;i<m;i++) {

        cin>>a>>b>>v;
        segmentTreeLazy(segmentTree,lazyTree,a,b,1,n,1,v);

        cout<< "Segment Tree: ", printTree(segmentTree,len);
        cout<< "Lazy Tree: ", printTree(lazyTree,len);
        debug
    }

    cout<< "min in 3 to 5: "<<rangeMinQuer(segmentTree,lazyTree,3,5,1,n,1)<<endl;

    return 0;
}
