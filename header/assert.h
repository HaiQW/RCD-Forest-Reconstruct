#ifndef ASSERT_H
#define ASSERT_H

#include <iostream>
#include "header/easylogging++.h" ///logging

#define ASSERT_NULL_POINTER(expr, msg) if(!(expr)){\
  std::cout<<msg<<std::endl; \
  std::cout<<"in line "<<__LINE__<<". file "\
  <<__FILE__<<std::endl;\
  asm("int3");\
  }

#define ASSERT_CSV_READ(expr, parser) if(!(expr)){\
  std::cout<<"CSV READ ERROR! "<<std::endl; \
  std::cout<<"in line "<<__LINE__<<". file "\
  <<__FILE__<<std::endl;\
  parser->state = error;\
  asm("int3");\
  }
#define ASSERT_FAIL(expr, msg) if(!(expr)){\
  }
#endif // ASSERT_H
