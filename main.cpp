//
//  main.cpp
//  Project4
//
//  Created by Christian Lung on 5/31/22.
//

#include <iostream>
#include <cassert>
#include "NameTable.h"
using namespace std;
//
//int main(int argc, const char * argv[]) {
//    NameTable nt;
//    assert(nt.declare("alpha", 1));
//    assert(nt.declare("beta", 2));
//    assert(nt.declare("p1", 3));
//    assert(nt.find("alpha") == 1);   // the alpha declared in line 1
//    assert(nt.declare("p2", 4));
//    assert(nt.find("beta") == 2);    // the beta declared in line 2
//    assert(nt.declare("p3", 5));
//    assert(nt.find("gamma") == -1);  // Error!  gamma hasn't been declared
//    assert(nt.declare("f", 6));
//    nt.enterScope();
//    assert(nt.declare("beta", 7));
//    assert(nt.declare("gamma", 8));
//    assert(nt.find("alpha") == 1);   // the alpha declared in line 1
//    assert(nt.find("beta") == 7);    // the beta declared in line 7
//    assert(nt.find("gamma") == 8);   // the gamma declared in line 8
//    nt.enterScope();
//    assert(nt.declare("alpha", 13));
//    assert(nt.declare("beta", 14));
//    assert(!nt.declare("beta", 15)); // Error! beta already declared
//    assert(nt.find("alpha") == 13);  // the alpha declared in line 13
//    assert(nt.exitScope());
//    assert(nt.find("alpha") == 1);   // the alpha declared in line 1
//    assert(nt.find("beta") == 7);    // the beta declared in line 7
//    nt.enterScope();
//    assert(nt.declare("beta", 21));
//    assert(nt.find("beta") == 21);   // the beta declared in line 21
//    assert(nt.exitScope());
//    assert(nt.exitScope());
//    assert(nt.declare("p4", 25));
//    assert(nt.find("alpha") == 1);   // the alpha declared in line 1
//    assert(nt.declare("p5", 26));
//    assert(nt.find("beta") == 2);    // the beta declared in line 2
//    assert(nt.declare("p6", 27));
//    assert(nt.find("gamma") == -1); // Error! gamma is not in scope
//    assert(nt.declare("main", 28));
//    nt.enterScope();
//    assert(nt.declare("beta", 29));
//    assert(nt.find("beta") == 29);   // the beta declared in line 29
//    assert(nt.find("f") == 6);       // the f declared in line 6
//    assert(nt.exitScope());
//    cout << "All Test Cases Passed" <<endl;
//    return 0;
//}
//
