// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
List comp_contri_rast3_file(std::string fn1, std::string fn2, std::string fn3, int n1, int n2, int n3){

    std::vector<int> v1(n1);
    std::vector<int> v2(n2);
    std::vector<int> v3(n3);

    std::ifstream infile1{fn1, std::ios::binary};
    infile1.read(reinterpret_cast<char *>(v1.data()),v1.size() * sizeof(decltype(v1)::value_type));
    std::ifstream infile2{fn2, std::ios::binary};
    infile2.read(reinterpret_cast<char *>(v2.data()),v2.size() * sizeof(decltype(v2)::value_type));
    std::ifstream infile3{fn3, std::ios::binary};
    infile3.read(reinterpret_cast<char *>(v3.data()),v3.size() * sizeof(decltype(v3)::value_type));

    int n = v1.size();
    NumericVector oMSA(n);
    std::vector<int> o1(n);
    std::vector<int> o2(n);
    std::vector<int> o3(n);
    double msaloss_p1 = 0.0;
    double msaloss_p2 = 0.0;
    double msaloss_p3 = 0.0;
    double msagc = 0.0;
    double cp1 = 0.0;
    double cp2 = 0.0;
    double cp3 = 0.0;
    double msaloss_pSum;
    RcppThread::parallelFor(0, n, [&] (int i) {
        if(v1[i]<0 && v2[i]<0 && v3[i]<0) {
            o1[i] = NA_REAL;
            o2[i] = NA_REAL;
            o3[i] = NA_REAL;
            oMSA[i] = NA_REAL;
        }else{
            msaloss_p1 = 1.00 - ( v1[i] / 100.00 );
            msaloss_p2 = 1.00 - ( v2[i] / 100.00 );
            msaloss_p3 = 1.00 - ( v3[i] / 100.00 );
            if(msaloss_p1<0) msaloss_p1 = 0.00;
            if(msaloss_p2<0) msaloss_p2 = 0.00;
            if(msaloss_p3<0) msaloss_p3 = 0.00;
            msagc = (1-msaloss_p1) * (1-msaloss_p2) * (1-msaloss_p3);
            oMSA[i] = msagc;
            msaloss_pSum = msaloss_p1 + msaloss_p2 + msaloss_p3;
            cp1 = (msaloss_p1) / (msaloss_pSum) * (1-msagc);
            cp2 = (msaloss_p2) / (msaloss_pSum) * (1-msagc);
            cp3 = (msaloss_p3) / (msaloss_pSum) * (1-msagc);
            o1[i] = cp1*100;
            o2[i] = cp2*100;
            o3[i] = cp3*100;
        }
    },1);

    std::string filename1 = fn1 + "contri_1";
    std::string filename2 = fn2 + "contri_2";
    std::string filename3 = fn3 + "contri_3";

    std::ofstream outfile1{filename1, std::ios::binary};
    outfile1.write(reinterpret_cast<const char *>(o1.data()),o1.size() * sizeof(decltype(o1)::value_type));
    outfile1.close();

    std::ofstream outfile2{filename2, std::ios::binary};
    outfile2.write(reinterpret_cast<const char *>(o2.data()),o2.size() * sizeof(decltype(o2)::value_type));
    outfile2.close();

    std::ofstream outfile3{filename3, std::ios::binary};
    outfile3.write(reinterpret_cast<const char *>(o3.data()),o3.size() * sizeof(decltype(o3)::value_type));
    outfile3.close();

    List L = List::create(_["MSA"] = oMSA,
                          _["co_fn1"] = "file1",
                          _["co_fn2"] = "file2",
                          _["co_fn3"] = "file3",
                          _["co_n1"] = o1.size(),
                          _["co_n2"] = o2.size(),
                          _["co_n3"] = o3.size());

    return L;
}
