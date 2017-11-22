#ifndef SCANNER_H
#define SCANNER_H

#include "global.h"


#include <string>
#include <vector>
#include <sstream>
using std::string;
using std::vector;

class Scanner {
public:
  Scanner (string in=""):buffer(in), pos(0){}
  void setInput(string in) {buffer = in;}

  string nextToken() {
      if (skipLeadingWhiteSpace() >= buffer.length())
        return string("Error");
      else if (isdigit(currentChar())) {
        return extractNumber();
      }
      else if (islower(currentChar())) {
        return extractAtom();
      }
	  else if (isSpecialCh(currentChar())) {
		  return extractAtomSC();
	  }
      else if (isupper(currentChar()) || currentChar() == '_') {
        return extractVar();
      }
      else {
        return string(1,extractChar());
      }
  }
string lookforward() {
      if (skipLeadingWhiteSpace() >= buffer.length())
        return string("Error");
      else if (isdigit(currentChar())) {
        int resetpos = pos;
        string temp = extractNumber();
        pos = resetpos;
        return temp;
      }
      else if (islower(currentChar())) {
        int resetpos = pos;
        string temp = extractAtom();
        pos = resetpos;
        return temp;
      }
      else if (isupper(currentChar()) || currentChar() == '_') {
        int resetpos = pos;
        string temp = extractVar();
        pos = resetpos;
        return temp;
      }
	  else if (isSpecialCh(currentChar())) {
		  int resetpos = pos;
		  string temp = extractAtomSC();
		  pos = resetpos;
		  return temp;
	  }
      else {
        int resetpos = pos;
        string temp(1,extractChar());
        pos = resetpos;
        return temp;
      }
  }

  int skipLeadingWhiteSpace() {
    for (; (buffer[pos] == ' ' || buffer[pos] == '\t') && pos<buffer.length(); ++pos);
    return position();
  }

  int position() const {return pos;}

  char currentChar() {
    return buffer[pos];
  }

  // extractX: extract X and set position right after X
  string extractNumber() {
    int posBegin = position();
    for (;isdigit(buffer[pos]); ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }

  string extractAtom() {
    int posBegin = position();
    for (;isalnum(buffer[pos])||buffer[pos] == '_'; ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }
  string extractAtomSC() {
	  int posBegin = position();
	  for (; isSpecialCh(buffer[pos]); ++pos);
	  return buffer.substr(posBegin, pos - posBegin);
  }
  string extractVar() {
    int posBegin = position();
    for (;isalnum(buffer[pos]) || buffer[pos] == '_'; ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }

  char extractChar() {
    return buffer[pos++];
  }
  int buffersize() {
	  return buffer.size();
  }
  int pos;
private:
  string buffer;
};


#endif
