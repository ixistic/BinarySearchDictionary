#include <iostream>     // cout
#include <algorithm>    // binary_search, sort
#include <vector>       // vector
#include <string>
using namespace std;

bool myfunction (int i,int j) { return (i<j); }

int main () {
  string* list[5] = {"a","orange","apple","mobile","car"};
  int size = sizeof(list)/sizeof(*list);
  for(int i=0;i < size ;i++){
    string myString = list[i];
    cout << list[i];
    string binary_outputInformations;
    for (size_t j = 0; i < myString.size(); ++j)
    {
      bitset<8> b(myString.c_str()[j]);
      binary_outputInformations+= b.to_string();
    }
    cout << binary_outputInformations;
  }
  // cout << "Please enter word: ";
  // getline(cin, input);

  // int myints[] = {1,2,3,4,5,4,3,2,1};
  // vector<int> v(myints,myints+9);                         // 1 2 3 4 5 4 3 2 1
  //
  // // using default comparison:
  // sort (v.begin(), v.end());
  //
  // cout << "looking for a 3... ";
  // if (binary_search (v.begin(), v.end(), 3))
  //   cout << "found!\n"; else cout << "not found.\n";
  //
  // // using myfunction as comp:
  // sort (v.begin(), v.end(), myfunction);
  //
  // cout << "looking for a 6... ";
  // if (binary_search (v.begin(), v.end(), 6, myfunction))
  //   cout << "found!\n"; else cout << "not found.\n";
  //
  return 0;
}
