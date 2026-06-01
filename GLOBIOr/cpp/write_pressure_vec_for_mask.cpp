#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
int write_pressure_vec_for_mask(const Rcpp::NumericVector& y, std::string filename){

    std::vector<double> x(y.size());
    for (int i = 0; i < y.size(); i++) x[i] = y[i];
    std::ofstream outfile{filename, std::ios::binary};
	outfile.write(reinterpret_cast<const char *>(x.data()), x.size() * sizeof(decltype(x)::value_type));
	outfile.close();
    int n = x.size();
    return n;
}
