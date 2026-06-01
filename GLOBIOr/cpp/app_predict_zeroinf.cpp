#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector app_predict_zeroinf(
                NumericVector &x, double &intercept, double &slope,
                double &interceptBin, double &slopeBin)
                {
                  int n = x.size();
                  NumericVector o(n);
                  double tmp_beta = 0.0;
                  double tmp_zeroinf = 0.0;
                  for (int i=0; i < n; ++i) {
                  //RcppThread::parallelFor(0, n, [&] (int i) {
                    if(std::isnan(x[i])) {
                      o[i] = x[i];
                    }else{
                      tmp_beta = intercept + x[i] * slope;
                      tmp_zeroinf = interceptBin + x[i] * slopeBin;
                      tmp_beta = exp(tmp_beta)/(1 + exp(tmp_beta));
                      tmp_zeroinf = exp(tmp_zeroinf)/(1 + exp(tmp_zeroinf));
                      o[i] = (1 - tmp_zeroinf)*tmp_beta;
                    }
                  //},4);
                  }
                  return o;
                }
