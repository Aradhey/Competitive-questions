#include<bits/stdc++.h>
using namespace std;

void buildTree(int* arr, int* tree, int start, int end, int treeNode){
    if(start == end){
        tree[treeNode] = arr[start];
        return;
    }
    int mid = (start + end)/2;
    buildTree(arr, tree, start, mid, 2*treeNode);
    buildTree(arr, tree, mid+1, end, 2*treeNode + 1);
    tree[treeNode] = min(tree[2*treeNode], tree[2*treeNode + 1]);
}

int query(int* tree, int start, int end, int treeNode, int left, int right) {
    // Completely outside range
    if(start > right || end < left) return INT_MAX;
    
    // Completely inside
    if(start >= left && end <= right) return tree[treeNode];
    
    // Partially inside and partially outside
    int mid = (start + end)/2;
    int ans1 = query(tree, start, mid, 2*treeNode, left, right);
    int ans2 = query(tree, mid + 1, end, 2*treeNode + 1, left, right);
    return min(ans1, ans2);
}

void updateTree(int *arr, int *tree, int start, int end, int treeNode, int idx, int value) {
    
    if(start == end) {
        arr[idx] = value;
        tree[treeNode] = value;
        return;
    }
    int mid = (start + end)/2;
    if(idx > mid) updateTree(arr, tree, mid + 1, end, 2*treeNode + 1, idx, value);
    else updateTree(arr, tree, start, mid, 2*treeNode, idx, value);
    
    tree[treeNode] = min(tree[2*treeNode], tree[2*treeNode + 1]);
}


int main(){
    int n, q;
    cin >> n >> q;
    int arr[n];
    for(int i = 0 ; i < n; i++) cin >> arr[i];
    
    int* tree = new int[4*n];
    buildTree(arr, tree, 0, n-1, 1);
    while(q--){
        int a, b;
        char type;
        cin >> type >> a >> b;
        if(type == 'u'){
            updateTree(arr, tree, 0, n-1, 1, a, b);
        }
        else{
            cout << query(tree, 0, n-1, 1, a-1, b-1) << endl;
        }
    }
    
    return 0;
}