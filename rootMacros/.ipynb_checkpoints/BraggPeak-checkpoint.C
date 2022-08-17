using namespace std;
#include "TFile.h"
#include "TH1D.h"

TCanvas *c = new TCanvas("cbraggPeak", "braggPeak", 0.0, 0.0, 800.0, 1200.0);
TCanvas *e = new TCanvas("cEdep", "total_energy_depositions", 0.0, 0.0, 800.0, 1200.0);

Double_t integral(TH1D *H){
	Double_t integral = 0.0;
	for (int j = 0; j < H->GetNbinsX(); j++)
		integral += H->GetBinContent(j)*H->GetBinCenter(j)/10;
	return integral;
}

int NumParticles(TH1D *H){
	int num = 0;
	for (int j = 0; j < H->GetNbinsX(); j++)
		num += H->GetBinContent(j);
	return num;
}

void BraggPeak(TString rootFileName, int numbn, Double_t histlength) {

	TFile *f = new TFile(rootFileName);

	TH1D *h_Pro = new TH1D("bragg_peak", "bragg peak", numbn, 0.0, histlength);
	TH1D *h_Pho = new TH1D("Photon_Edep", "Photon Energy deposition", numbn, 0.0, histlength);
	TH1D *h_Ele = new TH1D("e+_e-_Edep", "electron-positron Energy deposition", numbn, 0.0, histlength);
	h_Pro->SetXTitle("mm");
	h_Pho->SetXTitle("mm");
	h_Ele->SetXTitle("mm");
	
	TH1D *H;
	TString num;
	
	// proton information
	for(int i = 0; i < numbn; i++){
		num.Form("Proton_Edep_in_Patient_%d",i);		
		H = (TH1D*)f->Get(num.Data());
		h_Pro->SetBinContent(i,integral(H));
	}

	// Photon information
	for(int i = 0; i < numbn; i++){
		num.Form("Photon_Edep_in_Patient_%d",i);		
		H = (TH1D*)f->Get(num.Data());
		h_Pho->SetBinContent(i,integral(H));
	}

	// electron information
	for(int i = 0; i < numbn; i++){
		num.Form("Electron_Edep_in_Patient_%d",i);		
		H = (TH1D*)f->Get(num.Data());
		h_Ele->SetBinContent(i,integral(H));
	}

	c->Divide(1,3);

	// draw
	c->cd(1);
	h_Pro->Draw();
	c->cd(2);
	h_Pho->Draw();
	c->cd(3);
	h_Ele->Draw();

	e->cd();
	H = (TH1D*)f->Get("Proton_Edep_CV_Zcoor");
	H->Draw();

	// save
	c->SaveAs("PPE_energy_distributions.pdf");
	c->SaveAs("PPE_energy_distributions.root");
	c->SaveAs("PPE_energy_distributions.eps");

	e->SaveAs("total_energy_distributions.pdf");
	e->SaveAs("total_energy_distributions.root");
	e->SaveAs("total_energy_distributions.eps");
}



