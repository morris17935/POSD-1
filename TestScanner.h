#ifndef TESTSCANNER
#define TESTSCANNER

#include "scanner.h"

class TestScanner : public ::testing::Test {
protected:
  void SetUp() {
    symtable.clear();
  }
};

TEST_F (TestScanner, position) {
    Scanner scanner("abc,C,d,GGm,=,=,;");   
    
    ASSERT_EQ("abc,C,d,GG",scanner.convertoString());
}


#endif