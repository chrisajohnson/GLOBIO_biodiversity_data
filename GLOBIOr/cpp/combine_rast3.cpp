// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector combine_rast3(NumericVector &v1, NumericVector &v2, NumericVector &v3){
    int vn = v1.size();
    NumericVector o(vn);
    double val1 = 0.0;
    double val2 = 0.0;
    double val3 = 0.0;
    RcppThread::parallelFor(0, vn, [&] (int i) {
        if(std::isnan(v1[i]) && std::isnan(v2[i]) && std::isnan(v3[i])) {
            o[i] = NA_REAL;
        }else{
            val1 = v1[i];
            val2 = v2[i];
            val3 = v3[i];
            if(std::isnan(val1)) val1 = 100.00;
            if(std::isnan(val2)) val2 = 100.00;
            if(std::isnan(val3)) val3 = 100.00;
            o[i] = (val1*val2*val3) / 1e6;
        }
    },1);
    return o;
}

