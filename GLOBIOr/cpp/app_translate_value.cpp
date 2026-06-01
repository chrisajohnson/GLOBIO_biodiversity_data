// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector app_translate_value(NumericVector &x, NumericVector &from, NumericVector &to)
                {
                  int nx = x.size();
                  int nfrom = from.size();
                  int f;
                  NumericVector o(nx);
                  RcppThread::parallelFor(0, nx, [&] (int i) {
                    if(std::isnan(x[i])) {
                      o[i] = x[i];
                    }else{
                      f = -1;
                      for(int j=0; j < nfrom; j++) {
                        if(from[j] == x[i]) {
                          f = j;
                          break;
                        }
                      }
                      if(f==-1) {
                        o[i] = NA_REAL;
                      }else{
                        o[i] = to[ f ];
                      }
                    }
                  },4);
                  return o;
                }
