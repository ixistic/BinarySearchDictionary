// This program demonstrates the binarySearch function, which
// performs a binary search on an integer array.

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

typedef struct header
{
	uint32_t id;
	uint16_t lang:2;
	uint16_t length:10;
	uint16_t tailSpace:1;
	uint16_t isUnused:1;
	uint16_t numeric:1;
	uint16_t _filler:1;
	uint32_t mapFilePos;
} header;

typedef struct word
{
	int id;
	string text;
	string binary;
} word;

struct less_than_key
{
  inline bool operator() (const word& struct1, const word& struct2)
  {
    return (struct1.text < struct2.text);
  }
};

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;

  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }

  return internal;
}

string UnicodeToUTF8(unsigned int codepoint)
{
  std::string out;

  if (codepoint <= 0x7f)
      out.append(1, static_cast<char>(codepoint));
  else if (codepoint <= 0x7ff)
  {
      out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
      out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
  }
  else if (codepoint <= 0xffff)
  {
      out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
      out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
      out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
  }
  else
  {
      out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
      out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
      out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
      out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
  }
  return out;
}

string toBinary(string word) {
	string binary_outputInformations;
	for (size_t j = 0; j < word.size(); ++j)
	{
		bitset<8> b(word.c_str()[j]);
		binary_outputInformations+= b.to_string();
	}
	return binary_outputInformations;
}

int binarySearch(string dict[], int size, string value)
{
	int first = 0;
	int last = size - 1;
	int middle = (first+last)/2;

	while (first <= last) {
		if (dict[middle] < value){
			first = middle + 1;
		}
		else if (dict[middle] == value) {
			return middle+1;
		}
		else{
			last = middle - 1;
		}
		middle = (first + last)/2;
	}
	if (first > last)
		return -1;
	return 0;
}

vector<word> loadDict(string fileName){
  vector<word> dict;
  ifstream file (fileName, ios::in|ios::binary);
  file.ignore(256);
  unsigned char c;
  string text;
  while(!file.eof()){
    text = "";
    header st;
    file.read(reinterpret_cast<char*>(&st), sizeof(header));
    file.ignore(12);
    for(int i=0;i < st.length;i++){
      file.read(reinterpret_cast<char*>(&c), 1);
      int a = (int)c;
      if(a >= 161) {
        a += 3424;
        text += UnicodeToUTF8(a);
      }
      else
        text += c;
    }
    word x;
    x.id = st.id;
    x.text = text;
		string temp = toBinary(text);
		x.binary = temp;
    dict.push_back(x);
    file.ignore(1);
  }
  file.close();
  return dict;
}

int main()
{
  vector<word> dict = loadDict("SyllableDB-V1.dat");
  const int NUM_NAMES = dict.size();
  sort(dict.begin(), dict.end(), less_than_key());
  string line;
	string texts[10000];
	string texts2[10000];
  string fileName = "textInput1000W_v3.txt";
	ifstream file2 (fileName, ios::in|ios::binary);
	int countFound = 0;
	int countNotFound = 0;
	int size = 0;
	while ( getline (file2,line) )
  {
    int results;
  	bool check = false;
	  vector<string> sep = split(line, ' ');
		string binary = toBinary(sep[3]);
		texts[size] = binary;
		texts2[size] = sep[3];
		size++;
  }
	string wordInDict[188387];
	for(int i=0;i<dict.size();i++){
		wordInDict[i] = dict[i].text;
		// cout << wordInDict[i] <<endl;
		// getchar();
	}
	clock_t c1 = clock();
	for(int i=0;i<size;i++){
		int results = binarySearch(wordInDict,188387,texts2[i]);
		if (results == -1){
      cout << "Not found: "<< texts2[i] << endl;
      countNotFound++;
    }
    else
    {
      cout << "id: " << dict[results].id << " , Text: " << dict[results].text << endl;
  	  countFound++;
    }
	}
  clock_t c2 = clock();
  float diff = (c2 - c1) *1.0 / CLOCKS_PER_SEC;
  cout << "Found: " << countFound << endl;
  cout << "Not Found: " << countNotFound << endl;
  cout << "Time: " << diff << " seconds" << endl;

  // string input;
  // cout << "Please enter word: ";
  // getline(cin, input);
  // clock_t c1 = clock();
  // results = binarySearch(dict, dict.size(), input);
  // clock_t c2 = clock();
  // float diff = (c2 - c1) *1.0 / CLOCKS_PER_SEC;
  // cout << "Time: " << diff << " seconds" << endl;
  // //
  // if (results == -1)
  //   cout << "That name does not exist in the array.\n";
  // else
  // {
  //   cout << "That name is found at element " << results;
  //   cout << " in the array.\n";
  // }
  return 0;
}
