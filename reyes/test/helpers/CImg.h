#ifndef _CIMG_H_
#define _CIMG_H_

#include <string>
#include <vector>

namespace cimg_library {
  
  template<class T>
  class CImg {
    
  private:
    std::vector<std::vector<unsigned char> > pixels;
    int _w, _h, _i, _j, _k;

    void allocate() {
      for (int m=0; m<_w*_h; m++) {
        pixels.push_back(std::vector<unsigned char>());
        for (int n=0; n<_k; n++) 
          pixels[(size_t)m].push_back(0);
      }
    }

  public:

    CImg(int w, int h, int i, int j, int k) : _w(w), _h(h), _i(i), _j(j), _k(k) {
      this->allocate();
    }
    
    CImg(const char * filename) : _w(10), _h(10), _i(0), _j(1), _k(3) {
      (void) filename;
      this->allocate();

      (*this)(4,4,0,0) = 255;
      (*this)(4,4,0,1) = 255;
      (*this)(4,4,0,2) = 255;

      (*this)(9,9,0,0) = 100;
      (*this)(9,9,0,1) = 100;
      (*this)(9,9,0,2) = 100;
    }

    int width() const { return _w; }
    int height() const { return _h; }
    
    unsigned char & operator()(int i, int j, int m, int k) {
      (void) i; (void) j; (void) m; (void) k; 
      return pixels[(size_t)(i*_w+j)][(size_t)k];
    }

    void save(std::string s) { (void) s; }

  };

}

#endif /* _CIMG_H_ */
