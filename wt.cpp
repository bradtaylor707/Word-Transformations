#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector <string> build (const int length)
{
  ifstream input ("dictionary.txt", std::ios::in);
  string word;
  vector <string> words;
  while (getline (input, word)) {
    if (word.length () == length || word.length () == length - 1)
      words.push_back (word);
  }
  return words;
}

bool searchDict (const vector <string> & v, const string word)
{
  for (int i = 0; i < v.size (); i++)
    if (word == v[i])
      return true;
  return false;
}

int findMatches (const vector <string> & v, const string word)
{
  cout << endl;

  vector <string> matches;

  // 97 to 122
  for (int i = 0; i < word.length (); i++) { // for each char in the word
    for (int c = 97; c <= 122; c++) { // for each letter of alphabet

      string newWord = word;
      
      newWord.erase (i, 1); // erase character at i index
      newWord.insert (i, 1, (char) c); // insert char c onto string

      if (searchDict (v, newWord)) {
	if (!searchDict (matches, newWord))
	  if (newWord != word)
	    matches.push_back (newWord);
	if (newWord != word)
	cout << newWord << endl;
      }
    }

    if (i != word.length () - 1)
      cout << "-----------" << endl;
    else 
      cout << endl << word << " scores a " << matches.size () << endl;    
  }

  return matches.size ();
}


void max (const vector <string> & v, int len)
{
  int most = 0;
  int score = 0;

  vector <string> maxes;

  for (int i = 0; i < v.size (); i++) {
    if (v[i].length () == len)
      score = findMatches (v, v[i]);
    if (score >= most && v[i].length () == len) {
      maxes.push_back (v[i]);
      most = score;
    }
  }
  cout << "\nmaxes for " << len << endl;
  for (int i = 0; i < maxes.size (); i++)
    cout << maxes[i] << " scores most with " << most << endl;
}

void min (const vector <string> & v, int len)
{
  int score = 0;

  vector <string> zeroes;

  for (int i = 0; i < v.size (); i++) {
    if (v[i].length () == len)
      score = findMatches (v, v[i]);
    if (score == 0 && v[i].length () == 3)
      zeroes.push_back (v[i]);
  }
  cout << "\nzeroes for " << len << endl;
  for (int i = 0; i < zeroes.size (); i++)
    cout << zeroes[i] << " had zero mutations" << endl;
}      

int main ()
{
  string what;
  cout << "do what - enter 'word' to specify\nelse we find min and max score for length 3-5" << endl;
  cin >> what;
  
  if (what == "word") {
    string baseWord = "foo";
    cout << "whats the word" << endl;
    cin >> baseWord;
    int length = baseWord.length ();
    vector <string> words = build (length); // read from dictionary and build vector to look in  
    findMatches (words, baseWord);
  } 
  
  else {
    int len;
    cout << "len" << endl;
    cin >> len;
    vector <string> words = build (len);
    max (words, len);
    min (words, len);
  }
  return 0;
}

