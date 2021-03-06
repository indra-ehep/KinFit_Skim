#include "../interface/Utils.h"
#include "TVector2.h"

double dR(double eta1, double phi1, double eta2, double phi2){
    double dphi = phi2 - phi1;
    double deta = eta2 - eta1;
    static const double pi = TMath::Pi();
    dphi = TMath::Abs( TMath::Abs(dphi) - pi ) - pi;
    return TMath::Sqrt( dphi*dphi + deta*deta );
}

// double dR(double eta1, double phi1, double eta2, double phi2){
//   double dphi = TVector2::Phi_mpi_pi(phi2 - phi1);
//   double deta = eta2 - eta1;
//   return TMath::Sqrt( dphi*dphi + deta*deta );
// }
