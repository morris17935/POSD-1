
/**
 * 
 * Here are some examples for exception handling,
 * the actual testing way is base on your implementation.
 * 
 */
 #ifndef UTEXPRESSION_H
 #define UTEXPRESSION_H
 #include "global.h"
 #include "struct.h"
 #include "variable.h"
 #include "atom.h"
 #include "number.h"
 #include "list.h"
 #include "scanner.h"
 #include "parser.h"
 TEST(Shell, varMatchAtomSuc) {
    Scanner s("FILCO=awesome.");
    Parser p(s);
    try{
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("FILCO = awesome.", result);
    } catch (std::string & msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, atomMatchAtomFail) {
    Scanner s("smog=natural_disaster.");
    Parser p(s);
    try{
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("false.", result);
    } catch (std::string & msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, varMatchList) {
    Scanner s("Painful=[Clerk,forgot,pipette].");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("Painful = [Clerk, forgot, pipette].", result);
    } catch (std::string & msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, varMatchStruct) {
    Scanner s("Pitiful=binding([rope,rope,rope], Turtle, oil).");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("Pitiful = binding([rope, rope, rope], Turtle, oil).", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, varMatchItself) {
    Scanner s("Taiwan=Taiwan.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("true.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, varMachingListThatIncludeVar) {
    Scanner s("X=[Y,tom], Y=marry.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = [marry, tom], Y = marry.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, varMachingStructThatIncludeVar) {
    Scanner s("X=s(Y,marry), Y=tom.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = s(tom, marry), Y = tom.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  
  TEST(Shell, conjunctionMatching_false) {
    Scanner s("X=1, X=2.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("false.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, conjunctionMatching_diffExp) {
    result= "";
    Scanner s1("X=1, Y=2.");
    Parser p2(s1);
    try {
      p2.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = 1, Y = 2.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, conjunctionMatching_sameExp) {
    Scanner s("X=1, X=1.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = 1.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, conjunctionMatching_true) {
    Scanner s("X=X, X=X.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("true.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, conjunctionMatching_trueAndExp) {
    Scanner s("X=X, Y=1.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("Y = 1.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, conjunctionMatching_expAndtrue) {
    Scanner s("Y=1, X=X.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("Y = 1.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, conjunctionMatching_trueAndfalse) {
    Scanner s("X=X, 1=2.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("false.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, conjunctionMatching_falseAndtrue) {
    Scanner s("3=2, X=X.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("false.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, conjunctionMatching_falseAndfalse) {
    Scanner s("X=1, X=2, 1=2.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("false.", result);
    } catch (std::string &msg) { 
      FAIL() << msg;
    }
  }
  
  TEST(Shell, conjunctionMatching_duplicateExp) {
    Scanner s("Y=1, X=2, X=2.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("Y = 1, X = 2.", result);
    } catch (std::string &msg) { 
      FAIL() << msg;
    }
  }
  
  TEST(Shell, disjunctionMatching1) {
    Scanner s("X=1; X=2.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = 1; X = 2.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, disjunctionMatching2) {
    Scanner s("X=1; X=1, X=2.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = 1.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, disjunctionMatching3) {
    Scanner s("X=1; X=1, Y=2.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = 1; X = 1, Y = 2.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, disjunctionMatching4) {
    Scanner s("X=1; X=3, X=X.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = 1; X = 3.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, disjunctionMatching5) {
    Scanner s("X=1; X=X; Y=2.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = 1; true; Y = 2.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  
  TEST(Shell, disjunctionMatching6) {
    Scanner s("X=1; X=1, X=2; Z=3.");
    Parser p(s);
    try {
      p.buildExpression();
      
       /**
       *  maybe your implementation here.
       */
  
      ASSERT_EQ("X = 1; Z = 3.", result);
    } catch (std::string &msg) {
      FAIL() << msg;
    }
  }
  #endif