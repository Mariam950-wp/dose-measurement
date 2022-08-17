/// \file XR1RunAct.cc
/// \brief Implementation of the XR1RunAct class

#include <ctime>
using namespace std;

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "XR1RunAct.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1RunAct::XR1RunAct(XR1ConMan* CM)
: G4UserRunAction(), m_CM(CM)
{ 
    // Get analysis manager
    auto m_AM = G4AnalysisManager::Instance();
    
    // limits for 1D histogram
    m_BeamKE = m_CM -> GetBeamKE();
    
    // number of patient parts 
    m_PDVX = m_CM->GetPatDVX();
    m_PDVY = m_CM->GetPatDVY();
    m_PDVZ = m_CM->GetPatDVZ();
    
    m_PtXL = m_CM->GetPatiXL();
    m_PtYL = m_CM->GetPatiYL();
    m_PtZL = m_CM->GetPatiZL();
    
    m_PatiQX    = m_CM->GetPatiQX();
    m_PatiQY    = m_CM->GetPatiQY();
    m_PatiQZ    = m_CM->GetPatiQZ();
    m_PatiBX    = m_CM->GetPatiBX();
    m_PatiBY    = m_CM->GetPatiBY();
    m_PatiBZ    = m_CM->GetPatiBZ();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1RunAct::~XR1RunAct()
{
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1RunAct::BeginOfRunAction(const G4Run*)
{
    auto m_AM = G4AnalysisManager::Instance();
    
        //time_t rawtime;
        //struct tm * timeinfo;
        //char buffer [80];
        //time (&rawtime);
        //timeinfo = localtime (&rawtime);
        //strftime (buffer,80,"%Y-%m-%d-%H:%M",timeinfo);
        // Open an output file
        //m_AM->OpenFile("/home/abuladze/simulations/HadronTheraphy1/Output/" + std::string(buffer));

        m_AM->OpenFile("/home/abuladze/simulations/HadronTheraphy5/XR1/Output/XR1_Output");
        /*
        // 2D histogramm for dose distribution XY plane
        for (int k = 0; k<m_PDVZ/3; k++){
            m_AM->CreateH2("Edep_CV_Vol_Z=" + std::to_string((3*k)*m_PtZL/m_PDVZ), "Edep_CV_Vol_Z=" + std::to_string((3*k)*m_PtZL/m_PDVZ), 
                       m_PDVX, -m_PtXL/2, m_PtXL/2, m_PDVY, -m_PtYL/2, m_PtYL/2, "mm", "mm", "X Axis", "Y Axis");
        }
        
        // 2D histogramm for dose distribution XZ plane
        for (int k = 0; k<m_PDVY/3; k++){
            m_AM->CreateH2("Edep_CV_Vol_Y=" + std::to_string((3*k)*m_PtYL/m_PDVY), "Edep_CV_Vol_Y=" + std::to_string((3*k)*m_PtYL/m_PDVY), 
                       m_PDVZ, -m_PtZL/2, m_PtZL/2, m_PDVX, -m_PtXL/2, m_PtXL/2, "mm", "mm", "Z Axis", "X Axis");
        }
    
        // 2D histogramm for dose distribution YZ plane
        for (int k = 0; k<m_PDVX/3; k++){
            m_AM->CreateH2("Edep_CV_Vol_X=" + std::to_string((3*k)*m_PtXL/m_PDVX), "Edep_CV_Vol_X=" + std::to_string((3*k)*m_PtXL/m_PDVX), 
                       m_PDVZ, -m_PtZL/2, m_PtZL/2, m_PDVY, -m_PtYL/2, m_PtYL/2, "mm", "mm", "Z Axis", "Y Axis");
        }
        */
        /*
        m_AM->CreateH2("Edep_XZ_Plane", "Edep_XZ_Plane", m_PDVZ, -m_PDVZ/2.0, m_PDVZ/2.0, m_PDVX, -m_PDVX/2.0, m_PDVX/2.0,  
                       "mm", "mm", "Z Axis", "X Axis");
        */
        /*
        m_AM->CreateH2("Edep_XZ_Plane", "Edep_XZ_Plane", 
                       m_PDVZ, -m_PtZL/2, m_PtZL/2, m_PDVX, -m_PtXL/2, m_PtXL/2, "mm", "mm");
        */
        
        m_AM->CreateH2("Edep_XY_Plane", "Edep_XY_Plane", 
                       m_PDVX, -m_PtXL/2, m_PtXL/2, m_PDVY, -m_PtYL/2, m_PtYL/2, "mm", "mm", "X Axis", "Y Axis");
        /*
        m_AM->CreateH3("3_Dose_Distribution", "3_Dose_Distribution", 
                       m_PDVX, 0.0, m_PtXL, m_PDVY, 0.0, m_PtYL, m_PDVZ, 0.0, m_PtZL, "mm", "mm", "mm", "X Axis", "Y Axis", "Z Axis");
        */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1RunAct::EndOfRunAction(const G4Run* run)
{ 
    auto m_AM = G4AnalysisManager::Instance();

        // Save histograms
        m_AM->Write();
        // close file
        m_AM->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

