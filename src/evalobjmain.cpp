#include <string>
#include <iostream>

using namespace std;

#include "evalobj.h"

int main(int argc, const char *argv[]) {
    /**
     * Test 1
     */
    Exp *e1, *e2, *e3, *e4, *e5;
    ExpList *l = nullptr;
    l = new ExpList(new Constant(23), l);
    l = new ExpList(new Constant(42), l);
    l = new ExpList(new Constant(666), l);
    e1 = new OpApp(plusop, l);

    cout << e1->eval(nullptr) << endl; // should print 731

    /**
     * Test 2
     */
    l = nullptr;
    l = new ExpList(new Constant(5), l);
    l = new ExpList(new Constant(3), l);
    l = new ExpList(new Constant(2), l);

    e1 = new OpApp(plusop, l);

    l = nullptr;
    l = new ExpList(new Var("x"), l);
    l = new ExpList(new Var("x"), l);
    l = new ExpList(new Var("x"), l);

    e2 = new OpApp(timesop, l);
    e1 = new Let("x", e1, e2);

    cout << e1->eval(nullptr) << endl; // should print 1000

    /**
     * Test 3
     */
    l = nullptr;
    l = new ExpList(new Constant(5), l);
    l = new ExpList(new Constant(3), l);
    l = new ExpList(new Constant(2), l);

    e1 = new OpApp(plusop, l);

    l = nullptr;
    l = new ExpList(new Var("y"), l);
    l = new ExpList(new Var("x"), l);
    l = new ExpList(new Var("z"), l);

    e2 = new OpApp(timesop, l);
    e3 = new Let("x", e1, e2);
    e4 = new Let("y", new Constant(5), e3);
    e5 = new Let("z", new Constant(40), e4);

    cout << e5->eval(nullptr) << endl; // should print 2000

    /**
     * Test 4
     */
    l = nullptr;
    l = new ExpList(new Constant(3), l);
    l = new ExpList(new Var("x"), l);

    e2 = new OpApp(plusop, l);

    l = nullptr;
    l = new ExpList(new Constant(9), l);
    l = new ExpList(new Var("x"), l);

    e5 = new OpApp(plusop, l);
    e4 = new Let("x", new Constant(4), e5);

    l = nullptr;
    l = new ExpList(e4, l);
    l = new ExpList(new Var("x"), l);

    e3 = new OpApp(plusop, l);
    e1 = new Let("x", new Let("x", new Constant(2), e2), e3);

    cout << e1->eval(nullptr) << endl; // should print 18
}

