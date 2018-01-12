#include <sak/meta/unroll.hpp>

int main(){
  sak::unroll<10>([&](auto val){

  });
}