#include <iostream>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdio.h>
#include <chrono>
using namespace std;
long long ST = 0;
int fe[500]={0};
int *row[500];
//int* a = row[2];
int last_row = 0;
int pos = 0;

int *linear_sort(int *row1, int *row2, int length)
{
    int a = 0;
    int b = 0;
    int i = 0;
    int n_row = length * 2;
  //  cout << p_row << ":" << n_row<<endl;
    int *sorted = new int[n_row];
    while(a < length && b < length){

        if(row1[a] >= row2[b])
            sorted[i++] = row2[b++];
        else
            sorted[i++] = row1[a++];
    }
    while(a < length){
        sorted[i++] = row1[a++];
    }
    while(b < length){
        sorted[i++] = row2[b++];
    }
    delete row1;
    delete row2;
    return sorted;
}
int binary_search(int arr[],int target, int length)
{
    int l = 0, r = length;

    while(l <= r){
        int mid = floor(l + (r-l)/2);
        if(arr[mid] > target){
            r = mid - 1;
        }else if(arr[mid] < target){
            l = mid + 1;
        }else if(arr[mid] == target){
            return mid;
        }
    }
    return -1;
}


void insert(int v){
    
    int *new_row = new int;
    new_row[0] = v;
    int i = 0;
    while(fe[i] != 0){  //logn
        //0000 0001 right shift i
        new_row = linear_sort(row[i], new_row, 1<<i);//n
        fe[i++] = 0;
    }
    row[i] = new_row;
    fe[i] = 1;
    if(i > last_row) last_row = i;
   
    
}

int search(int target){
    int i = 0;
    for(i = 0; i <= last_row; i++){//logn
        if(fe[i] == 0)continue;
        int length = pow(2,i);
        pos = binary_search(row[i], target, length); //logn
        if(pos != -1)return i;
      //  cout << i << endl;
    }
    return -1;

}

void print(){


    for(int i = 0; i <= last_row; i++){
        for(int j = 0; j < pow(2,i); j++){
            if(fe[i] == 0){
                cout << "0 ";
                continue;
            }
            cout << row[i][j] <<" ";
        }
        cout << endl;
    }
}
int main(){
     LARGE_INTEGER t1, t2, ts;
 
    int s = 0;
    int num ;
    int min = 1;
    int max = 100000;
    int notin = 0;
    cout << "Dynamic Binary Search Operation:\n";

    while(s < 100000){
        num = rand() % (max - min + 1) + min;
        int tmp = search(num);
        if(tmp == -1){
            chrono::time_point<std::chrono::high_resolution_clock> starting,ending;
            starting=chrono::high_resolution_clock::now();
            insert(num);
            ending = chrono::high_resolution_clock::now();
            ST += chrono::duration_cast<std::chrono::nanoseconds>(ending-starting).count();
        }else{
            notin ++;
        }
        s++;
    }
    cout << endl;

//    s = 0;
//    min = 30;
//    max = 150000;
//  QueryPerformanceFrequency(&ts);
//    QueryPerformanceCounter(&t1);
//  while(s < 10000){
//    num = rand() % (max - min + 1) + min ;
//      int tmp = search(num);
//      s++;
//        }
    cout << notin <<endl;
    cout << ST << endl;
  //  QueryPerformanceCounter(&t2);
  //  printf("Lasting Time: %lf\n",(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart));

}



//        switch(i){
//            //insert
//            case 1:{
//                int num ;
//                cin >> num;
//                insert(num);
//                cout << "  ***Insert***  \n";
//                break;
//            }
//            //search
//            case 2:{
//                int num ;
//                cout << "  ***Search***  \n"
//                     << " Input a number...>\n";
//                cin >> num;
//                int  i = search(num);
//                if(i == -1){
//                    cout << "Not found\n";
//                    continue;
//                }
//                cout << num <<":[" << i << "][" << pos << "]\n";
//                break;
//            }
//            case 3:
//                print();
//                break;
//            case 4:
//                return 0;
//        }