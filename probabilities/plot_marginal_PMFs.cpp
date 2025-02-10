#include <TROOT.h>
#include <TH2F.h>
#include <TH1F.h>
#include <TFile.h>
#include <TCanvas.h>
#include <iostream>

void plot_marginal_PMFs() {
    // Open the ROOT file and retrieve the 2D probability mass function (PMF)
    TFile *file = new TFile("frequency.root", "READ");
    TH2F* hist = (TH2F*)file->Get("probability_mass_function");  // Use the normalized PMF

    if (!hist) {
        std::cerr << "Error: Histogram not found in ROOT file!" << std::endl;
        return;
    }

    int x_bins = hist->GetNbinsX();
    int y_bins = hist->GetNbinsY();

    // Create histograms for the marginal PMFs
    TH1F* hist_marginal_theta = new TH1F("marginal_theta", "Marginal PMF of Theta", 
                                         y_bins, hist->GetYaxis()->GetXmin(), hist->GetYaxis()->GetXmax());

    TH1F* hist_marginal_E = new TH1F("marginal_E", "Marginal PMF of Energy", 
                                     x_bins, hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());

    // Compute Marginal PMF for Theta (Sum over E for each Theta bin)
    double total_sum = hist->Integral(); // Normalize by total sum
    for (int iy = 1; iy <= y_bins; iy++) {
        double sum_theta = 0.0;
        for (int ix = 1; ix <= x_bins; ix++) {
            sum_theta += hist->GetBinContent(ix, iy);
        }
        hist_marginal_theta->SetBinContent(iy, sum_theta / total_sum); // Normalize
    }

    // Compute Marginal PMF for E (Sum over Theta for each E bin)
    for (int ix = 1; ix <= x_bins; ix++) {
        double sum_E = 0.0;
        for (int iy = 1; iy <= y_bins; iy++) {
            sum_E += hist->GetBinContent(ix, iy);
        }
        hist_marginal_E->SetBinContent(ix, sum_E / total_sum); // Normalize
    }

    // Save the marginal PMFs to a new ROOT file
    TFile *output_file = new TFile("marginal_PMFs.root", "RECREATE");
    hist_marginal_theta->Write();
    hist_marginal_E->Write();
    output_file->Close();

    // Step 6: Plot and save the marginal PMFs
    TCanvas* c1 = new TCanvas("c1", "Marginal PMF of Theta", 800, 600);
    hist_marginal_theta->SetTitle("Marginal PMF of #theta");
    hist_marginal_theta->GetXaxis()->SetTitle("Theta (Deg)");
    hist_marginal_theta->Draw("HIST");
    c1->SaveAs("marginal_PMF_theta.png");

    TCanvas* c2 = new TCanvas("c2", "Marginal PMF of Energy", 800, 600);
    hist_marginal_E->SetTitle("Marginal PMF of Energy");
    hist_marginal_E->GetXaxis()->SetTitle("Energy (GeV)");
    hist_marginal_E->Draw("HIST");
    c2->SaveAs("marginal_PMF_E.png");

    // Close the input file
    file->Close();
}
