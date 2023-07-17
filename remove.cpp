// #include <iostream>
// #include <list>
// #include <algorithm>
// using namespace std;

// int main()
// {
//     list<int> myList = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//     auto isEven = [](int i)
//     { return i % 2 == 0; };

//     // Print the even numbers in the list
//     for (int i : myList)
//     {
//         if (isEven(i))
//         {
//             cout << i << " ";
//         }
//     }

//     // Remove all the even numbers from the list
//     auto removeEven = remove_if(myList.begin(), myList.end(), isEven);
//     myList.erase(removeEven, myList.end());

//     // Print the remaining elements in the list
//     for (int i : myList)
//     {
//         cout << i << " ";
//     }

//     // Print the elements that were removed from the list
//     for (auto it = removeEven; it != myList.end(); ++it)
//     {
//         cout << *it << " ";
//     }

//     return 0;
// }

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
    list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto isEven = [](int i)
    { return i % 2 == 0; };

    // Remove all the even numbers from the list
    auto removeEven = remove_if(list.begin(), list.end(), isEven);

   
    return 0;
}
