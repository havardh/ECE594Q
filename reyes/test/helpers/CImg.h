#ifndef _CIMG_H_
#define _CIMG_H_

#include <string>

namespace cimg_library {
  
  template<class T>
  class CImg {
    
  public:

    CImg(int w, int h, int i, int j, int k) {
      (void) w; (void) h; (void) i; (void) j; (void) k; 
    }

    int & operator()(int i, int j, int m, int k) {
      (void) i; (void) j; (void) m; (void) k; 
      return *new int(1);
    }

    void save(std::string s) { (void) s; }

  };

}

#endif /* _CIMG_H_ */
