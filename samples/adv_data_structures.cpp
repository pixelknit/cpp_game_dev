#include <iostream>
#include <vector>

//struct Dummy{
//  int val;
//};

//struct Test{
//  int num;
//  std::string name;
//  float f_num;
//  Dummy dm;
//};


union Holder{
  std::int32_t num;
  std::uint16_t low_num;
  std::uint8_t really_low_num;
};

enum Levels {
  FOREST, MOUNTAIN, HELL, SNOW
};

int main(){
  
  Holder test;
  test.num = 10;
  test.low_num = 18;
  test.really_low_num = 4;

  std::cout << sizeof(test) << "\n";
  std::cout << "---------------------------\n";

  enum Levels myLevel = HELL;
  std::cout << myLevel << "\n";

  return 0;
}
