#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void countingSort(vector<int>& arr) {
    if(arr.empty()) return;
    
    int max_val = *max_element(arr.begin(), arr.end());
    vector<int> count(max_val + 1, 0);
    
    for(int num : arr)
        count[num]++;
    
    int index = 0;
    for(int i = 0; i <= max_val; i++)
        while(count[i]-- > 0)
            arr[index++] = i;
}

int main() {
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    countingSort(arr);
    for(int num : arr)
        cout << num << " ";
    return 0;
}