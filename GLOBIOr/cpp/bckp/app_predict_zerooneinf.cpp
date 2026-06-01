#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector app_predict_zerooneinf(
                NumericVector &x,
                double &intercept, double &slope,
                double &intercept_zo, double &slope_zo,
                double &intercept_co, double &slope_co)
                {
                  int n = x.size();
                  NumericVector o(n);
                  double tmp_beta = 0.0;
                  double tmp_zo = 0.0;
                  double tmp_co = 0.0;
                  for (int i=0; i < n; ++i) {
                  //RcppThread::parallelFor(0, n, [&] (int i) {
                    if(std::isnan(x[i])) {
                        o[i] = x[i];
                    }else{
                      tmp_beta = intercept + x[i] * slope;
                      tmp_zo = intercept_zo + x[i] * slope_zo;
                      tmp_co = intercept_co + x[i] * slope_co;
                      tmp_beta = exp(tmp_beta)/(1 + exp(tmp_beta));
                      tmp_zo = exp(tmp_zo)/(1 + exp(tmp_zo));
                      tmp_co = exp(tmp_co)/(1 + exp(tmp_co));
                      o[i] = tmp_zo * tmp_co + (1 - tmp_zo)*tmp_beta;
                    }
                  //},4);
                  }
                  return o;
                }
