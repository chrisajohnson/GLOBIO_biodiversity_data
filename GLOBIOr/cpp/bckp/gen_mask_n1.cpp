// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector gen_mask_n1(NumericVector &x, NumericVector &y, NumericVector &vals)
                {
                  //std::cout << "Processing block" << std::endl;
                  int nx = x.size();
                  NumericVector o(nx);
                  int nvals = vals.size();
                  int f;
                  RcppThread::parallelFor(0, nx, [&] (int i) {
                    if(std::isnan(x[i])) {
                      o[i] = NA_REAL;
                    }else{
                      auto it = std::find(vals.begin(), vals.end(), x[i]);
                      f = it - vals.begin();
                      if(f>=nvals) {
                        o[i] = y[i];
                      }else{
                        o[i] = NA_REAL;
                      }
                    }
                  },4);
                  //std::cout << "Done!" << std::endl;
                  return o;
                }
