#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
NumericVector read_double_vec_bin(std::string fn1, int n1, std::string fval1, int nval1){
 
    std::vector<int> v1(n1);
    std::ifstream infile1{fn1, std::ios::binary};
    infile1.read(reinterpret_cast<char *>(v1.data()),v1.size() * sizeof(decltype(v1)::value_type));

    std::vector<int> val(nval1);
    std::ifstream infile2{fval1, std::ios::binary};
    infile2.read(reinterpret_cast<char *>(val.data()),val.size() * sizeof(decltype(val)::value_type));

    NumericVector v2(n1);
    for(int i = 0; i<n1; i++) {
        if(val[i]==-1) {
            v2[i] = NA_REAL;
        }else{
            v2[i] = v1[i] / 100000.00;
        }
    }

    return v2;
}
