#include <TROOT.h>
#include <TH2F.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>

void sample_plot() {
    // Open the ROOT file and retrieve the 2D probability mass function (PMF)
    TFile *file = new TFile("frequency.root", "READ");
    TH2F* hist = (TH2F*)file->Get("probability_mass_function");  // Use the normalized PMF

    if (!hist) {
        std::cerr << "Error: Histogram not found in ROOT file!" << std::endl;
        return;
    }

    int x_bins = hist->GetNbinsX();
    int y_bins = hist->GetNbinsY();
    
    // Create a new 2D histogram to store sampled (E, theta) events
    TH2F* sampled_hist = new TH2F("sampled_ITS", "Sampled (E, theta) Histogram", 
                                  x_bins, hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax(),
                                  y_bins, hist->GetYaxis()->GetXmin(), hist->GetYaxis()->GetXmax());

    // Initialize random generator
    TRandom3 randGen(0);  // Seed = 0 for reproducibility

    // Define number of samples
    int num_samples = 100000;

    // Loop to generate events
    for (int n = 0; n < num_samples; n++) {
        double U1 = randGen.Uniform();  // Random number for theta
        double U2 = randGen.Uniform();  // Random number for E

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

        // Step 5: Fill the sampled histogram
        sampled_hist->Fill(sampled_E, sampled_theta);
    }

    // Save the sampled histogram to a new ROOT file
    TFile *output_file = new TFile("ITS_sampled_events.root", "RECREATE");
    sampled_hist->GetXaxis()->SetTitle("Muon energy (GeV)");  // Set the x-axis title
    sampled_hist->GetYaxis()->SetTitle("Zenith angle (Degree)");  // Set the y-axis title
    sampled_hist->SetTitle("Frequency plot of sampled 100000 events");
    sampled_hist->Write();
    output_file->Close();

    // Step 6: Display the histogram in a canvas
    TCanvas* c1 = new TCanvas("c1", "Sampled (E, theta) Histogram", 800, 600);
    sampled_hist->Draw("COLZ");
    c1->SaveAs("ITS_sampled_events.png");  // Save as an image

    // Close input file
    file->Close();
}
