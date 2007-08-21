/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2006
 *
 *  Last modified:
 *     $Date$ by $Author$
 *     $Revision$
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "examples/support.hh"

static const int n = 15;
static const int m = 90;
static const int p[n] = {16,35,90,42,88,6,40,42,64,48,46,5,90,29,70};

/**
 * \brief %Example: Stress test for element constraint (involving integers)
 *
 * This stress test is an adaption of the benchmark for element posted
 * by Neng-Fa Zhou for B-Prolog, November, 2005.
 *
 * \ingroup ExStress
 *
 */
class StressElement : public Example {
protected:
  /// Variables
  IntVarArray x;
public:
  /// The actual problem
  StressElement(const Options& opt)
    : x(this,n,0,n-1) {

    IntVarArgs s(n);
    for (int i=0; i<n; i++) {
      IntVar si(this,0,m); s[i]=si;
    }

    for (int i=0; i<n-1; i++)
      rel(this, s[i], IRT_LQ, s[i+1]);

    IntArgs e(n,p);

    for (int i=0; i<n; i++)
      element(this, e, x[i], s[i]);

    distinct(this, x);
    branch(this, x, INT_VAR_SIZE_MIN, INT_VAL_MIN);
  }

  /// Constructor for cloning \a s
  StressElement(bool share, StressElement& s) : Example(share,s) {
    x.update(this, share, s.x);
  }

  /// Perform copying during cloning
  virtual Space*
  copy(bool share) {
    return new StressElement(share,*this);
  }

  /// Print solution
  virtual void
  print(void) {
    std::cout << "\tx[" << n << "] = {";
    for (int i = 0; i < n; i++)
      std::cout << x[i] << ((i<n-1)?",":"};\n");
  }
};

/** \brief Main-function
 *  \relates StressElement
 */
int
main(int argc, char* argv[]) {
  Options opt("StressElement");
  opt.parse(argc,argv);
  Example::run<StressElement,DFS,Options>(opt);
  return 0;
}

// STATISTICS: example-any

