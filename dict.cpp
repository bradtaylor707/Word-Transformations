#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

bool isIn (vector <string> & v, string word)
{
  for (int i = 0; i < v.size (); i++)
    if (word == v[i])
      return true;
  return false;
}

int main ()
{
  ifstream allFile ("allwords.txt", std::ios::in);
  string aWord;
  vector <string> shortWords;
  while (getline (allFile, aWord)) {
    if (aWord.length () <= 5) {
      transform (aWord.begin (), aWord.end (), aWord.begin (), ::tolower); // convert to lowercase
      if (!isIn (shortWords, aWord))
	shortWords.push_back (aWord);
    }
  }

  sort (shortWords.begin (), shortWords.end ());

  ofstream dictionary ("dictionary.txt", std::ios::trunc);
  for (int i = 0; i < shortWords.size (); i++)
    dictionary << shortWords[i] << endl;
  return 0;
}
