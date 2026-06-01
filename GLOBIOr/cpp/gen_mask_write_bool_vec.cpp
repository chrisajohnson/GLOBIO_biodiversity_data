// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
int gen_mask_write_bool_vec(NumericVector &x, NumericVector &vals, std::string filename){

  int nx = x.size();
  std::vector<int> o(nx);
  int nvals = vals.size();
  int f;
  RcppThread::parallelFor(0, nx, [&] (int i) {
    if(std::isnan(x[i])) {
      o[i] = 0;
    }else{
      auto it = std::find(vals.begin(), vals.end(), x[i]);
      f = it - vals.begin();
      if(f>=nvals) {
        o[i] = 1;
      }else{
        o[i] = 0;
      }
    }
  },4);

  bool file_exists = true;
  std::ifstream file(filename);
  if(!file.is_open()) file_exists = false;

  if(file_exists){
    std::ofstream outfile{filename, std::ios::binary | std::ios_base::app};
    outfile.write(reinterpret_cast<const char *>(o.data()), o.size() * sizeof(decltype(o)::value_type));
    outfile.close();
  }else{
    std::ofstream outfile{filename, std::ios::binary};
    outfile.write(reinterpret_cast<const char *>(o.data()), o.size() * sizeof(decltype(o)::value_type));
    outfile.close();
  }

  int no = o.size();
  return no;

}
