#include <stdio.h>

void upwardHeapify(int array[], int n){
    int new = array[n];
    int child = n;
    int parent = (child-1)/2;

    while(child>0 && array[parent]<new){
        array[child] = array[parent];
        child = parent;
        parent = (child-1)/2;
    }
    array[child] = new;
}

void downwardHeapify(int array[],int i, int n){
    int temp = array[i];
    int j= 2*i+1;
    while(j<=n){
        if(j<n && array[j]<array[j+1]);{
            j+=1;
        }
        if(temp>=array[j]){
            break;
        }
        else{
            array[i] = array[j];
            i = j;
        }
        array[i] = temp;
    }
}

int main(){

    int array[10] = {2,10,17,8,19,0,13,4,11,1};

    //for(int i = 0; i<10; i++){
    //    upwardHeapify(array, i);
    //}

    for(int i = 10/2-1; i>0; i--){
        downwardHeapify(array, i, 10);
    }
    for(int i=0; i< 10; i++){
        printf("%d ", array[i]);
    }
}