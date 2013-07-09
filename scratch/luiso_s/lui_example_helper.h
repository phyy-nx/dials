#ifndef DIALS_SCRATCH_LUI_HELPER_H
#define DIALS_SCRATCH_LUI_HELPER_H
#include <iostream>
#include <scitbx/vec2.h>
#include <scitbx/array_family/flex_types.h>
#include <math.h>
namespace dials { namespace scratch {
  using scitbx::af::flex_int;
  using scitbx::af::flex_double;
  using scitbx::vec2;

  int hello_tst() {
    std::cout << "Hello world \n";
    int a=5;
    return a;
  }

  flex_int tst_01(flex_int & data2d) {
    std::size_t ncol=data2d.accessor().all()[1];
    std::size_t nrow=data2d.accessor().all()[0];
    flex_int data2dtmp(data2d);
    for (int row = 0; row<=nrow-1;row++) {
      for (int col = 0; col<=ncol-1;col++) {
        data2dtmp(row,col)=row*nrow+col;

      }
    }

    return data2dtmp;

  }

  vec2<double> raw_2d_cut(flex_double & data2d, flex_int & mask2d,
      flex_double & background2d) {
      double i_tot = 0, tot_bkgr = 0;
      int npix_bkgr = 0, npix_mask = 0, cont = 0;
      double bkgr, sig;
      std::size_t ncol=data2d.accessor().all()[1];
      std::size_t nrow=data2d.accessor().all()[0];
      vec2<double> integr_data(0,1);

      for (int row = 0; row<=nrow-1;row++) {
        for (int col = 0; col<=ncol-1;col++) {
          if ( mask2d(row,col)==1 ){
            i_tot = i_tot + data2d(row,col);
            npix_mask++;
          } else {
            npix_bkgr++;
          }
          cont++;
          tot_bkgr+=background2d(row,col);

        }
      }
      if( tot_bkgr>0 && cont>0 && npix_mask>0 && npix_bkgr>0 ){
        bkgr = tot_bkgr / cont;
        sig = sqrt(i_tot + (1.0 + (npix_mask) / (npix_bkgr)) * (npix_mask * bkgr));

      } else {
        bkgr = 0;
        sig = sqrt(i_tot);
      }

      integr_data[0]=i_tot;        // intensity
      integr_data[1]=sig;          // intensity variance
      return integr_data;

  }


}}


#endif
