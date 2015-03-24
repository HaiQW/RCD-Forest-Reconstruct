#include <iostream>
#include <fstab.h>
#include "header/easylogging++.h"
#include "header/data_struct.h"
#include "header/file.h"

INITIALIZE_EASYLOGGINGPP
//using namespace std;

int main()
{
  /* Set Up Log*/
  el::Configurations defaultConf;
  defaultConf.setToDefault();
  defaultConf.set(el::Level::Info,
                  el::ConfigurationType::Format,
                  "%datetime %level %msg");
  el::Loggers::reconfigureLogger("default", defaultConf);

  std::vector<t_Data> data_set;
  char *cfg_file = "glass/glass_config.txt";

  LOG(INFO) << "Reading configuration file...";
  file::ReadConfiguraion(cfg_file);

  LOG(INFO) << "Reading Data file...";
  //std::fstream f_out("A.txt",std::ios::out);
   return 0;
}
