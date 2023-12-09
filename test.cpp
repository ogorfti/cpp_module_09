#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


void merge(std::vector<int> s) {
    int size = s.size();
    int mid = size / 2;
    if (s.size() < 2)
        return ;
    std::vector<int> left;
    std::vector<int> right;
    int i  =-1;
    while (++i < mid)
        left.push_back(s[i]);
    i = mid - 1;
    while (++i < size)
        right.push_back(s[i]);
    merge(left);
    merge(right);
    
}   


int main() {
    int gen[] = {20, 50,1 ,3, 9, 8, 20, 50,1 ,3, 9, 8};
    std::vector<int> num;
    int i = 0;
    while (i < 6) {
        num.push_back(gen[i]);
        i++;
    }


}