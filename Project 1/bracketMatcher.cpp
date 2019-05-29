// Programmer: Daniel Anzola
// Last modification date: Mon Jan 29 10:45 AM

#include <stack>
#include <cassert>
#include <iostream>
#include "bracketMatcher.h"

bool is_left(char c)
{
  return left_brackets.find(c) != string::npos;
}

bool is_right(char c)
{
  return right_brackets.find(c) != string::npos;
}

bool matches(char L, char R)
{
  assert(is_left(L) && is_right(R));
  return left_brackets.find(L) ==  right_brackets.find(R);
}

bool balanced(string str)
{
  stack<char> S;
  int i;
  bool aux = false;

  for (i = 0 ; i < str.length() ; i++)
  {
    if (is_left(str[i]))
    {
      if (aux == false)
        S.push(str[i]);
      else
      {
        cout << "Unmatched bracket at index " << i << ": " << str[i] << endl;
        return false;
      }
    }
    else if (is_right(str[i]))
    {
      aux = true;
            
      if (S.empty() || !matches(S.top(), str[i]))
      {
        if (S.empty())
          cout << "Unmatched bracket at index " << i << ": " << str[i] << endl;
        else
          cout << "Bracket mismatch at index " << i << ": " << S.top() << " and " << str[i] << endl;
                
        return false;
      }
      else
        S.pop();
    }
  }

  if (S.empty())
  {
    cout << "The brackets in your string are properly matched." << endl;
    return true;
  }
  else
    return false;
}
    
