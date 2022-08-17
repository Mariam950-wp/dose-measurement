#include "TFile.h"
#include "TH1D.h"

TFile f("/home/abuladze/simulations/HadronTheraphy1/Output/2020-10-23-16:50.root");


TH1D *h = new TH1D("brag_peak", "breg peak", 20, 0.0, 500.0);

for(int i = 0, i < 20, i++){
   h->Add((TH1F*)f.Get("Proton_Edep_in_Patient_" + i);->GetIntegral());
}

h->Draw();