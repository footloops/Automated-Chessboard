#ifndef PAIR_H
#define PAIR_H

// Light-weight pair class similar to that of the stl pair class in c++
template<class X, class Y>
struct Pair{
  X val1;
  Y val2;

  Pair(){
    val1 = X{};
    val2 = Y{};
  }

  Pair(X val1, Y val2){
    this->val1 = val1;
    this->val2 = val2;
  }

  X first(){
    return this->val1;
  }

  Y second(){
    return this->val2;
  }
};

#endif