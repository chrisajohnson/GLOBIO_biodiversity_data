// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector app_predict_oneinf(
                  NumericVector &x, double &intercept,
                  double &slope, double &interceptBin, double &slopeBin)
                  {
                    int n = x.size();
                    NumericVector o(n);
                    double tmp_beta = 0.0;
                    double tmp_oneinf = 0.0;
                    for (int i=0; i < n; ++i) {
                    //RcppThread::parallelFor(0, n, [&] (int i) {
                      if(std::isnan(x[i])) {
                        o[i] = x[i];
                      }else{
                        tmp_beta = intercept + x[i] * slope;
                        tmp_oneinf = interceptBin + x[i] * slopeBin;
                        tmp_beta = exp(tmp_beta)/(1 + exp(tmp_beta));
                        tmp_oneinf = exp(tmp_oneinf)/(1 + exp(tmp_oneinf));
                        o[i] = tmp_oneinf + (1 - tmp_oneinf) * tmp_beta;
                      }
                    //}, 4);
                    }
                    return o;
                  }
