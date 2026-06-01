#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector mask_pressure_values(std::string fm, int nm, std::string fr, int nr) {

    // read mask file
    std::vector<int> mask(nm);
    std::ifstream infile1{fm, std::ios::binary};
    infile1.read(reinterpret_cast<char *>(mask.data()),mask.size() * sizeof(decltype(mask)::value_type));

    // read pressure file
    std::vector<double> pressure(nr);
    std::ifstream infile2{fr, std::ios::binary};
    infile2.read(reinterpret_cast<char *>(pressure.data()),pressure.size() * sizeof(decltype(pressure)::value_type));

    // mask pressure values
    NumericVector pressure_masked(nr);
    for (int i = 0; i < nr; i++) {
        if (mask[i] == 0) {
            pressure_masked[i] = NA_REAL;
        }else{
            pressure_masked[i] = pressure[i];
        }
    }

    return pressure_masked;
}

