/******************************************************************************/
/* SAMPLE PROGRAM                                                             */
/*                                                                            */
/* COPYRIGHT:                                                                 */
/* ----------                                                                 */
/* Copyright (C) International Business Machines Corp., 1991,1992.            */
/*                                                                            */
/* DISCLAIMER OF WARRANTIES:                                                  */
/* -------------------------                                                  */
/* The following [enclosed] code is sample code created by IBM                */
/* Corporation.  This sample code is not part of any standard IBM product     */
/* and is provided to you solely for the purpose of assisting you in the      */
/* development of your applications.  The code is provided "AS IS",           */
/* without warranty of any kind.  IBM shall not be liable for any damages     */
/* arising out of your use of the sample code, even if they have been         */
/* advised of the possibility of such damages.                                */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/*  Sample to demonstrate exception handling                                  */
/*                                                                            */
/*    This example demonstrates a vector class that throws an exception       */
/*    to check for upper bound exceeded.                                      */
/*                                                                            */
/*    A vector class is created which contains a constructor and an           */
/*    overloaded [] operator.  The constructor stores the size of the         */
/*    vector when it is instantiated (sz) and uses that size in the []        */
/*    operator to check for bounds exceeded.                                  */
/*                                                                            */
/*    If the user tries to access element greater than the instantiated       */
/*    size, an exception will be thrown.  The user is responsible for         */
/*    catching the out of bound exception.                                    */
/*                                                                            */
/******************************************************************************/

#include <iostream.h>
#include <terminat.h>


typedef void (*PFV)();
void my_terminate()
{
   cout << "FATAL ERROR: Please contact you service representative\n";
}


class Vector {
    int* p;
    int sz;
  public:
    enum { max = 32000 };
    class Range {             // Range exception to be thrown
      public:
        int index;
        Range(int i) : index(i) { }
    };

    Vector(int s);              // constructor
    int& operator [] (int i);   // operator
    ~Vector() { delete [] p; }  // destructor clean up storage
};

Vector::Vector(int size) {
   p = new int[sz=size];               // save initial size of vector in sz
}

int& Vector::operator[] (int i) {
   if (0<=i && i<sz) return p[i];      // check bounds
   throw Range(i);                     // throw exception
}


void main(void)
{

  // set the terminate function to catch unexpected exceptions
  PFV oldterm = set_terminate(my_terminate);

  // try block using the vector class
  try {
      Vector v(10);

      for (int i=0; i<10; i++) v[i] = i;

      for (i=0; i<10; i++) cout << v[i] << " ";

      cout << v[20] << endl;
  }
  // catch block for out of range errors
  catch (Vector::Range x) {
     cout << "Vector::Range error: invalid index:" << x.index << endl;
  }
  // match for any exception not caught above
  catch (...) {
     cout << "Catch other exceptions\n";
  }

}
