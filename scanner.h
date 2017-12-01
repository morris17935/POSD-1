#ifndef SCANNER_H
#define SCANNER_H

#include "global.h"


#include <string>
#include <vector>
using std::string;
using std::vector;

class Scanner {
public:
  Scanner (string in=""):buffer(in), pos(0), _tokenValue(NONE){}
  void setInput(string in) {buffer = in;}
  string convertoString(){
    string result;
    while(nextToken()){
      if( _tokenValue == NUMBER){
        result += std::to_string(_tokenValue);
      }
      if(_tokenValue == ','){
        result += ",";
      }
      else if (_tokenValue == (int)';'){
        result += ";";
      }
      else if (_tokenValue== (int)'='){
        result += "=";
      }
      else{
        result +=  symtable[_tokenValue].first;
      }
      return result;
    }
  }
  int nextToken() {
      if (skipLeadingWhiteSpace() >= buffer.length())
        return EOS;
      else if (isdigit(currentChar())) {
        _tokenValue = extractNumber();
        return NUMBER;
      }  else if (islower(currentChar()) ) {
        string s = extractAtom();
        processToken<ATOM>(s);
        return ATOM;
      } else if (isSpecialCh(currentChar())) {
        string s = extractAtomSC();
        processToken<ATOMSC>(s);
        return ATOMSC;
      } else if (isupper(currentChar()) || currentChar() == '_') {
        string s = extractVar();
        processToken<VAR>(s);
        return VAR;
      } else {
        _tokenValue = NONE;
        return extractChar();
      }
  }

  int tokenValue() const {return _tokenValue;}

  int skipLeadingWhiteSpace() {
    for (; (buffer[pos] == ' ' || buffer[pos] == '\t') && pos<buffer.length(); ++pos);
    return position();
  }

  int position() const {return pos;}

  int buffersize() {
    return buffer.size();
  }
  char currentChar() {
    return buffer[pos];
  }

  // extractX: extract X and set position right after X
  int extractNumber() {
    int posBegin = position();
    for (;isdigit(buffer[pos]); ++pos);
    return stoi(buffer.substr(posBegin, pos-posBegin));
  }

  string extractAtom() {
    int posBegin = position();
    for (;isalnum(buffer[pos]); ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }

  string extractAtomSC() {
    int posBegin = position();
    for (;isSpecialCh(buffer[pos]); ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }

  string extractVar() {
    int posBegin = position();
    for (;isalnum(buffer[pos]) || buffer[pos] == '_'; ++pos);
    return buffer.substr(posBegin, pos-posBegin);
  }

  char extractChar() {
    if(buffer[pos] == ','){
      _tokenValue = (int)','; 
    }
    else if (buffer[pos] == ';'){
      _tokenValue = (int)';'; 
    }
    else if (buffer[pos] == '='){
      _tokenValue = (int)'='; 
    }
    return buffer[pos++];
  }

private:
  string buffer;
  int pos;
  int _tokenValue;

private:
  // case-based populating symtable and setting _tokenValue
  template <int TokenType>
  void processToken(string const & s) {
    int val = -1;
    if (symbolExist(s,val)) {
        _tokenValue = val;
    } else {
      symtable.push_back(pair<string, int>(s,TokenType));
       _tokenValue = symtable.size()-1; // index to symtable
    }
  }
};


#endif
