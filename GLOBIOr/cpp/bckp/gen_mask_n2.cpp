// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector gen_mask_n2(NumericVector &x,
                                                          NumericVector &y,
                                                          NumericVector &z,
                                                          NumericVector &vals1,
                                                          NumericVector &vals2)
                {
                  //std::cout << "Processing block" << std::endl;
                  int nz = z.size();
                  NumericVector o = z;
                  int nvals1 = vals1.size();
                  int nvals2 = vals2.size();
                  int f1;
                  int f2;
                  RcppThread::parallelFor(0, nz, [&] (int i) {
                    if(std::isnan(z[i])) {
                      o[i] = NA_REAL;
                    }else{
                      auto it1 = std::find(vals1.begin(), vals1.end(), x[i]);
                      auto it2 = std::find(vals2.begin(), vals2.end(), y[i]);
                      f1 = it1 - vals1.begin();
                      f2 = it2 - vals2.begin();
                      if(f1<nvals1 || f2<nvals2) {
                        o[i] = NA_REAL;
                      }
                    }
                  },8);
                  //std::cout << "Done!" << std::endl;
                  return o;
                }
