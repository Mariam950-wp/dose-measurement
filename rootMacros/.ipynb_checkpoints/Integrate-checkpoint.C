using namespace std;
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"

TCanvas *c = new TCanvas("cbraggPeak", "braggPeak", 0.0, 0.0, 800.0, 1200.0);
TCanvas *e = new TCanvas("cEdep", "total_energy_depositions", 0.0, 0.0, 800.0, 1200.0);

TCanvas *g = new TCanvas("cEdeptoSPD", "total_energy_deposition_SPD", 0.0, 0.0, 1200.0, 1200.0);

Double_t totalEnergy(int i, TH2D *H){
	Double_t integral = 0.0;
	for (int j = 0; j < H->GetNbinsY(); j++)
		integral += H->GetYaxis()->GetBinCenter(j)*H->GetBinContent(i,j)/10;
	return integral;
}

void Integrate(TString rootFileName) {

	TFile *f = new TFile(rootFileName);

	TH2D *H_Pro = (TH2D*)f->Get("Proton_Edep_CV_VolID");
	TH2D *H_Pho = (TH2D*)f->Get("Photon_Edep_CV_VolID");
	TH2D *H_Ele = (TH2D*)f->Get("Electron_Edep_CV_VolID");
    
    TH3D *H_Gamma = (TH3D*)f->Get("Angular_dist_of_Prompt_Gamma_EDep_on_SD");

	TH1D *h_Pro = new TH1D("bragg_peak", "bragg peak", H_Pro->GetNbinsX(), 0.0, H_Pro->GetNbinsX());
	TH1D *h_Pho = new TH1D("Photon_Edep", "Photon Energy deposition", H_Pho->GetNbinsX(), 0.0, H_Pho->GetNbinsX());
	TH1D *h_Ele = new TH1D("e+_e-_Edep", "electron-positron Energy deposition", H_Ele->GetNbinsX(), 0.0, H_Ele->GetNbinsX());
	
	// proton information
	for(int i = 0; i < H_Pro->GetNbinsX(); i++)
		h_Pro->SetBinContent(i,totalEnergy(i,H_Pro));

	//Photon information
	for(int i = 0; i < H_Pho->GetNbinsX(); i++)
		h_Pho->SetBinContent(i,totalEnergy(i,H_Pho));

	// electron information
	for(int i = 0; i < H_Ele->GetNbinsX(); i++)
		h_Ele->SetBinContent(i,totalEnergy(i,H_Ele));

	c->Divide(1,3);

	// draw
	c->cd(1);
	h_Pro->Draw();
	c->cd(2);
	h_Pho->Draw();
	c->cd(3);
	h_Ele->Draw();

	// 2D histogram for protons 
	e->cd();
	H_Pro->Draw();
    
    // 3D histogram for gammas 
	g->cd();
	H_Gamma->Draw();

	// save
	c->SaveAs("PPE_energy_distributions.pdf");
	c->SaveAs("PPE_energy_distributions.root");
	c->SaveAs("PPE_energy_distributions.eps");

	e->SaveAs("total_energy_distributions.pdf");
	e->SaveAs("total_energy_distributions.root");
	e->SaveAs("total_energy_distributions.eps");

    g->SaveAs("tot_energy_of_gammas_in_SPD.pdf");
	g->SaveAs("ot_energy_of_gammas_in_SPD.root");
	g->SaveAs("ot_energy_of_gammas_in_SPD.eps");
}



