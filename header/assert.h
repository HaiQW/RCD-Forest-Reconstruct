#ifndef ASSERT_H
#define ASSERT_H

#include <iostream>
#include "header/easylogging++.h" //logging

namespace ASSERT
{

  inline void ctree_assert(const char *e, const char *file, int line)
  {
    if(!e)
      {
        LOG(ERROR) << "NULL VALUD OF THE ROOT POINTER! AND EXIT THE RCD-FOREST.";
        asm("int3");//inline assembling:set breakpoint
      }
  }

  inline void cforest_assert(const char *e, const char *file, int line)
  {
    LOG(ERROR) << "WRONG VALUE OF CTREE NUMBER OR SUB SAMPLE NUM!"
               << "IN LINE:" <<line<<" FILE:"<<file;
    asm("int3");
  }

}
#endif // ASSERT_H
