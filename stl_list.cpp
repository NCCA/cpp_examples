#include <list>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
    // Create a static array of integers
    int nums[] = {3,2,4,1};
 
    // Import the array into a list using iterators (pointers)
    list<int> mylist(nums,nums+4);

    // Sort the list using the list.sort function (not algorithm)
    mylist.sort();

    // Use the copy algorithm and iterators to dump the contents to std::cout
    copy( mylist.begin(), mylist.end(), ostream_iterator<int>(cout, "\n"));

    // End
    return 0;
}
