#include <TROOT.h>
#include <TH2F.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <iostream>
#include <cmath>

void sampling() {
    // Open the ROOT file and retrieve the 2D histogram
    TFile *file = new TFile("frequency.root", "READ");
    TH2F* hist = (TH2F*)file->Get("probability_mass_function");  // Use the normalized PMF

    if (!hist) {
        std::cerr << "Error: Histogram not found in ROOT file!" << std::endl;
        return;
    }

    int x_bins = hist->GetNbinsX();
    int y_bins = hist->GetNbinsY();
    
    // Generate random numbers
    TRandom3 randGen(0);  // Random generator with seed=0 for reproducibility
    double U1 = randGen.Uniform();  // Uniform [0,1] random number
    double U2 = randGen.Uniform();  // Another independent uniform [0,1] number

    // Step 1: Compute the 1D marginal CDF for P(theta)
    std::vector<double> marginal_CDF_theta(y_bins, 0.0);
    double total_sum = hist->Integral();
    
    for (int iy = 1; iy <= y_bins; iy++) {
        double sum = 0.0;
        for (int ix = 1; ix <= x_bins; ix++) {
            sum += hist->GetBinContent(ix, iy);
        }
        marginal_CDF_theta[iy-1] = (iy == 1) ? sum / total_sum : marginal_CDF_theta[iy-2] + sum / total_sum;
    }

    // Step 2: Find the bin for theta using U1
    int theta_bin = 1;
    for (int i = 0; i < y_bins; i++) {
        if (U1 < marginal_CDF_theta[i]) {
            theta_bin = i + 1;
            break;
        }
    }
    double sampled_theta = hist->GetYaxis()->GetBinCenter(theta_bin);

    // Step 3: Compute the conditional CDF P(E | theta_bin)
    std::vector<double> conditional_CDF_E(x_bins, 0.0);
    double sum_theta = 0.0;
    
    for (int ix = 1; ix <= x_bins; ix++) {
        sum_theta += hist->GetBinContent(ix, theta_bin);
    }

    if (sum_theta > 0) {  // Avoid division by zero
        double cumulative = 0.0;
        for (int ix = 1; ix <= x_bins; ix++) {
            cumulative += hist->GetBinContent(ix, theta_bin) / sum_theta;
            conditional_CDF_E[ix-1] = cumulative;
        }
    }

    // Step 4: Find the bin for E using U2
    int E_bin = 1;
    for (int i = 0; i < x_bins; i++) {
        if (U2 < conditional_CDF_E[i]) {
            E_bin = i + 1;
            break;
        }
    }
    double sampled_E = hist->GetXaxis()->GetBinCenter(E_bin);

    // Step 5: Print the sampled (theta, E)
    std::cout << "Sampled event: theta = " << sampled_theta << " deg, E = " << sampled_E << " GeV" << std::endl;

    // Close file
    file->Close();
}