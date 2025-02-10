#include <TROOT.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iostream>
#include <TSystem.h>
gSystem->Load("libMathCore");

void fitting() {
    // Open the ROOT file and retrieve the 2D PMF histogram
    TFile *file = new TFile("frequency.root", "READ");
    TH2F* hist = (TH2F*)file->Get("muon_flux");

    if (!hist) {
        std::cerr << "Error: Histogram not found in ROOT file!" << std::endl;
        return;
    }

    int x_bins = hist->GetNbinsX();
    int y_bins = hist->GetNbinsY();

    // Step 1: Find the bin corresponding to theta = 0
    int theta_bin = hist->GetYaxis()->FindBin(0.0);

    // Step 2: Create a 1D histogram for energy at theta = 0
    TH1F* hist_E_theta0 = new TH1F("E_theta0", "Energy Distribution at #theta = 0", 
                                   x_bins, hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());

    // Fill the histogram
    for (int ix = 1; ix <= x_bins; ix++) {
        double N = hist->GetBinContent(ix, theta_bin);  // Extract P(E) at theta = 0
        hist_E_theta0->SetBinContent(ix, N);
    }

    // Step 3: Define the fit function
    TF1* fit_func = new TF1("fit_func", "([0]/x) * exp(-(log(x) - [1])*(log(x) - [1]) / (2 * [2] * [2]))", 0.1, 10);
    fit_func->SetParameters(0.1, -1.102, 1.436);  // Initial guesses for (a, b, c)

    // Step 4: Perform the fit
    hist_E_theta0->Fit(fit_func, "R M");  // Use Migrad (default, robust)
    //hist_E_theta0->Fit(fit_func, "R L");  // Use Log-likelihood instead of Chi-square
    //hist_E_theta0->Fit(fit_func, "R W");  // Use Weights for better statistics
    //hist_E_theta0->Fit(fit_func, "R S");  // Run **scan** to check parameter dependence


    // Step 5: Plot the histogram and the fitted function on the same canvas
    TCanvas* c1 = new TCanvas("c1", "Fit of Energy Distribution at #theta = 0", 800, 600);
    hist_E_theta0->SetTitle("Energy Distribution at #theta = 0 with Fit");
    hist_E_theta0->GetXaxis()->SetTitle("Energy (GeV)");
    hist_E_theta0->SetLineColor(kBlue);
    hist_E_theta0->Draw("HIST");

    fit_func->SetLineColor(kRed);
    fit_func->Draw("SAME");

    c1->SaveAs("fit_E_theta0.png");  // Save the figure

    // Close the file
    file->Close();
}
