#ifndef ASSERT_H
#define ASSERT_H

#include <iostream>
#include "header/easylogging++.h" //logging

namespace ASSERT
{

  inline void ctree_assert(const char *e, const char *file, int line)
  {
    LOG(ERROR) << "NULL VALUD OF THE ROOT POINTER! AND EXIT THE RCD-FOREST.";
    asm("int3");//inline assembling:set breakpoint
  }

}
#endif // ASSERT_H
