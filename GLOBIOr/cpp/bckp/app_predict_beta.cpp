#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector app_predict_beta(NumericVector &x, double &intercept, double &slope)
                  {
                    int n = x.size();
                    NumericVector o(n);
                    double tmp_beta = 0.0;
                    for (int i=0; i < n; ++i) {
                    //RcppThread::parallelFor(0, n, [&] (int i) {
                      tmp_beta = intercept + x[i] * slope;
                      o[i] = exp(tmp_beta)/(1 + exp(tmp_beta));
                    //},4);
                    }
                    return o;
                  }
