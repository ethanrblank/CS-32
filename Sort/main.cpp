// Recursive solution
    // • must always terminate
    // • if it does terminate, does it do the right thing?
    // • needs base cases!!
// Base case(s): Path(s) through the function that don't make any recursive call
// Recursive case(s): verify every recursive call is to solve a "smaller" problem (i.e. "closer" to a base case)

/*
 sort a pile of N Items
    if (N >= 2) {
     • split the pile into two piles of about N/2 items each
     • sort the left pile
     • sort the right pile
     • merge the two sorted subpiles into one pile
    }
 
*/



void sort(int a[], int b, int e);
void merge(int a[], int b, int c, int e);


#include <iostream>
using namespace std;

int main() {
    return 0;
}

void sort(int a[], int b, int e) {
    if (e - b >= 2) {
        int mid = (b + e)/2;
        sort(a, b, mid);
        sort(a, mid, e);
        merge(a, b, mid, e);
    }
}
