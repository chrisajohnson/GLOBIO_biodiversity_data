// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
List combine_rast3_file(std::string fn1, std::string fn2, std::string fn3, int n1, int n2, int n3){

	std::vector<int> v1(n1);
	std::vector<int> v2(n2);
	std::vector<int> v3(n3);
		
    std::ifstream infile1{fn1, std::ios::binary};
    infile1.read(reinterpret_cast<char *>(v1.data()),v1.size() * sizeof(decltype(v1)::value_type));
    std::ifstream infile2{fn2, std::ios::binary};
    infile2.read(reinterpret_cast<char *>(v2.data()),v2.size() * sizeof(decltype(v2)::value_type));
    std::ifstream infile3{fn3, std::ios::binary};
    infile3.read(reinterpret_cast<char *>(v3.data()),v3.size() * sizeof(decltype(v3)::value_type));

    int vn = v1.size();
    std::vector<double> o(vn);

    double val1 = 0.0;
    double val2 = 0.0;
    double val3 = 0.0;
    
    RcppThread::parallelFor(0, vn, [&] (int i) {
        if(v1[i]<0 && v2[i]<0 && v3[i]<0) {
            o[i] = NA_REAL;
        }else{
            val1 = v1[i];
            val2 = v2[i];
            val3 = v3[i];
            if(val1<0) val1 = 100.00;
            if(val2<0) val2 = 100.00;
            if(val3<0) val3 = 100.00;
            o[i] = (val1*val2*val3) / 1e6;
        }
    },1);

    List L = List::create(_["MSA"] = o, _["size"] = o.size());
    return L;
}

