#include "IntMaxHeap.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
  int num = 5;
  int *a = new int[num];

  IntMaxHeap *h = new IntMaxHeap();
  h->init();

  std::srand(std::time(NULL));
  int max = 100;

  std::cout << "Original nums\n";
  for(int i=0; i<num; i++) {
    a[i] = std::rand() % max;
    std::cout << a[i] << std::endl;
    h->insert(a+i);
  }

  std::cout << "Pop off some heap-sorted nums\n";
  for(int i=0; i<2; i++) 
    std::cout << *(h->pop()) << std::endl;

  std::cout << "add a few more\n";
  num =3;
  int *b = new int[num];
  for(int i=0; i<num; i++) {
    b[i] = std::rand() % max;
    std::cout << b[i] << std::endl;
    h->insert(b+i);
  }


  std::cout << "Pop 'em all off\n";
  while(int *cur = h->pop()) 
    std::cout << *cur << std::endl;

  delete h;
}
