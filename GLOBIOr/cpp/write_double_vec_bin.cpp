#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
void write_double_vec_bin(const Rcpp::NumericVector& y, std::string filename){
//void write_double_vec_bin(NumericVector &y, std::string filename){

 std::vector<int> x(y.size());
 for(int i = 0; i < y.size(); i++) {
  if(std::isnan(y[i])){
    x[i] = -1;
  }else{
    x[i]= y[i]*100;
  }
 }

  std::ofstream outfile{filename, std::ios::binary};
	outfile.write(reinterpret_cast<const char *>(x.data()), x.size() * sizeof(decltype(x)::value_type));
	outfile.close();
}
