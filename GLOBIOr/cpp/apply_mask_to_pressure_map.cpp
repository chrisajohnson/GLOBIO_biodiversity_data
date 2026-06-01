// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector apply_mask_to_pressure_map(NumericVector &x, NumericVector &vals, NumericVector &pm) {

  int nx = x.size();
  NumericVector o(nx); //std::vector<int> o(nx);
  int nvals = vals.size();
  int f;
  RcppThread::parallelFor(0, nx, [&] (int i) {
    if(std::isnan(x[i])) {
      o[i] = NA_REAL;
    }else{
      auto it = std::find(vals.begin(), vals.end(), x[i]);
      f = it - vals.begin();
      if(f>=nvals) {
        o[i] = pm[i];
      }else{
        o[i] = NA_REAL;
      }
    }
  },4);

  return o;
}
