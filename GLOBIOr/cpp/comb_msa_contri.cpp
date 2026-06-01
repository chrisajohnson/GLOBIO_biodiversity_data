// [[Rcpp::depends(RcppThread)]]

#include <RcppThread.h>
#include <Rcpp.h>
#include <iostream>
#include <fstream>
#include <vector>
// [[Rcpp::plugins(cpp11)]]

using namespace Rcpp;

// [[Rcpp::export]]
List comb_msa_contri(NumericMatrix &m){

    int nr = m.nrow();
    int nc = m.ncol();
    // std::cout << "nr: " << nr << std::endl;
    // std::cout << "nc: " << nc << std::endl;
    // std::cout << "vers: " << "1.1" << std::endl;

    NumericMatrix contriMSAloss(nr,nc); 
    NumericVector combMSA(nr);
    double msa_val = 0.00;
    double msa_gc = 1.00;
    double msaloss_gc_total = 0.00;
    std::vector<double> tempVec(nc,0.00);
    std::vector<double> msaloss_tempVec(nc,0.00);

    for(int i=0; i<nr; i++) {

        for(int j=0; j<nc; j++) tempVec[j] = m( i , j );
        
        bool allNAN = true;
        for(int j=0; j<nc; j++) {
            if(!std::isnan(tempVec[j])) {
                allNAN = false;
                break;
            }
        }
        if(allNAN) {
            combMSA[i] = NA_REAL;
            continue;
        }

        msa_gc = 1.00;
        for(int j=0; j<nc; j++) {
            msa_val = tempVec[j];
            if(!std::isnan(msa_val)) {
                msa_gc = msa_gc * msa_val;
                msaloss_tempVec[j] = 1.00 - msa_val;
            }else{
                msaloss_tempVec[j] = 0.00;
            }
        }
        combMSA[i] = msa_gc;

        msaloss_gc_total = 0.00;
        for(int j=0; j<nc; j++) {
            msaloss_gc_total = msaloss_gc_total + msaloss_tempVec[j];
        }

        
        // if(i==1) {
        //     for(int j=0; j<nc; j++) {
        //         std::cout << "msaloss_tempVec[j]: " << msaloss_tempVec[j] << std::endl;
        //     }
        //     std::cout << "msaloss_gc_total: " << msaloss_gc_total << std::endl;
        // }

        for(int j=0; j<nc; j++) {
            contriMSAloss( i , j ) = msaloss_tempVec[j] / msaloss_gc_total * (1.00-msa_gc);
        }

        // if(i==1) {
        //     for(int j=0; j<nc; j++) {
        //         std::cout << "contriMSAloss( i , j ): " << contriMSAloss( i , j )<< std::endl;
        //     }
        //     std::cout << "(1.00-msa_gc): " << (1.00-msa_gc) << std::endl;
        // }

    }

    List L = List::create(_["combinedMSA"] = combMSA, _["contriMatrix"] = contriMSAloss);
    
    // return combMSA;
    return L;
}
