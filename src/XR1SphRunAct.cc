/// \file XR1SphRunAct.cc
/// \brief Implementation of the XR1SphRunAct class

#include <ctime>
using namespace std;

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "XR1SphDetCon.hh"
#include "XR1SphRunAct.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1SphRunAct::XR1SphRunAct(XR1ConMan* CM, XR1SphDetCon* SDC)
: G4UserRunAction(), m_CM(CM), m_SDC(SDC)
{ 
    
    // add new units for dose
    // 
    const G4double milligray = 1.e-3*gray;
    const G4double microgray = 1.e-6*gray;
    const G4double nanogray  = 1.e-9*gray;  
    const G4double picogray  = 1.e-12*gray;
    
    new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
    new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
    new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
    new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);
    
    // add new units for mass
    // 
    const G4double kilogramm = 1.e+3*g;
    const G4double decigramm = 1.e-1*g;
    const G4double milligram = 1.e-3*g;
    
    new G4UnitDefinition("kilogramm", "kilogramm" , "mass", kilogramm);
    new G4UnitDefinition("decigramm", "decigramm" , "mass", decigramm);
    new G4UnitDefinition("milligram", "milligram" , "mass", milligram);
    
    m_NumOfSph = m_CM->GetNumOfS();
    m_radInS   = m_CM->GetRadInS();
    
    m_EdepFromID.clear();
    m_Edep2FromID.clear();
    
    // Get analysis manager
    auto m_AM = G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1SphRunAct::~XR1SphRunAct()
{
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1SphRunAct::BeginOfRunAction(const G4Run*)
{
    auto m_AM = G4AnalysisManager::Instance();
    
    m_AM->OpenFile("/home/abuladze/simulations/HadronTheraphy5/XR1/Output/XR1_SphOutput");
    
    m_AM->CreateH1("Dose_Per_Mass[microGray]", "Dose_Per_Mass[microGray]", m_NumOfSph, 0.0, m_radInS*m_NumOfSph, "mm", "radius");
    
    m_AM->CreateH1("Total_Dose_In_Volume[Joul]", "Total_Dose_In_Volume[Joul]", m_NumOfSph, 0.0, m_radInS*m_NumOfSph, "mm", "radius");
    
    // initial enegry deposition is zero
    for (int i = 0; i<m_NumOfSph; i++){ 
        m_EdepFromID[i] = 0.0;
        m_Edep2FromID[i] = 0.0;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1SphRunAct::EndOfRunAction(const G4Run* run)
{ 
    
    G4int nofEvents = run->GetNumberOfEvent();
    if (nofEvents == 0) return;

    
    auto m_AM = G4AnalysisManager::Instance();
    
    G4cout
     << "\n--------------------End of Run------------------------------\n"
     << " The run consists of " << nofEvents << " events. Volume consists of " << m_NumOfSph << " spheres. "  
     << G4endl;
    
    for (int i = 0; i<m_NumOfSph; i++){
        // Compute dose
        //
        G4double energySum  = m_EdepFromID[i];
        G4double energy2Sum = m_Edep2FromID[i];
        G4double rms = energy2Sum - energySum*energySum/nofEvents;
        if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;

        G4double mass;
        if(i == 0) mass = m_SDC->GetLogicalVolume(i)->GetMass();
        else       mass = m_SDC->GetLogicalVolume(i)->GetMass() - m_SDC->GetLogicalVolume(i-1)->GetMass();
        G4double dose = energySum/mass;
        G4double rmsDose = rms/mass;
        
        //std::cout << "hist1 " << pow(10, 18)*m_EdepFromID[i]/mass << " and hist2 " << m_EdepFromID[i] << std::endl;
        
        m_AM->FillH1(0 ,   (i+1/2.0)*m_radInS, pow(10, 18)*m_EdepFromID[i]/mass);
        m_AM->FillH1(1 ,   (i+1/2.0)*m_radInS, m_EdepFromID[i]);
        
        G4cout  << "Dose in "  << m_SDC->GetLogicalVolume(i)->GetName() 
             <<" having mass " << G4BestUnit(mass,"mass") << " is " 
             << G4BestUnit(dose,"Dose")
             << " +- "                   << G4BestUnit(rmsDose,"Dose")
             << " and total dose is " << m_EdepFromID[i] 
         << G4endl;
        
        if(i == m_NumOfSph - 1) m_TotMas = m_SDC->GetLogicalVolume(i)->GetMass();
        m_TotDos = m_TotDos + energySum;
    }
    
    G4cout  
        << "total mass is : " << G4BestUnit(m_TotMas,"mass")
        << " and total dose per mass is " << G4BestUnit(m_TotDos/m_TotMas,"Dose") 
    << G4endl;
    
    // Save histograms
    m_AM->Write();
    // close file
    m_AM->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

