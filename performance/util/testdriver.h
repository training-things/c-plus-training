#ifndef UTIL_TESTDRIVER_H
#define UTIL_TESTDRIVER_H


typedef int (*testfunc)(int, unsigned long);
void test_driver(testfunc* flist, int argc=0, char** argv=0);
void test_driver(testfunc f, int argc=0, char** argv=0);


#endif // UTIL_TESTDRIVER_H