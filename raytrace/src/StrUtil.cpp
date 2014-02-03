#include "StrUtil.h"

void splitWidthHeightParam(char *param, int &width, int &height) {

  char * split = strchr(param, ':');

  (*split++) = '\0';
  width = atoi(param);
  height = atoi(split);

}
