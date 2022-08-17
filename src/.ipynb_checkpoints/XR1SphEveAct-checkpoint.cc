/// \file XR1SphEveAct.cc
/// \brief Implementation of the XR1SphEveAct class

#include "XR1SphEveAct.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1SphEveAct::XR1SphEveAct(XR1SphRunAct* RA, XR1ConMan* CM)
: G4UserEventAction(),m_RA(RA), m_CM(CM)
{
    m_NumOfSph = m_CM->GetNumOfS();
    
    m_EdepFromID.clear();
    m_Edep2FromID.clear();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1SphEveAct::~XR1SphEveAct()
{
    delete &m_EdepFromID;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1SphEveAct::BeginOfEventAction(const G4Event*)
{
    //std::cout << "------------------BeginOfEventAction--------------------" << std::endl;

	// initial enegry deposition is zero
    for (int i = 0; i<m_NumOfSph; i++){
        m_EdepFromID[i] = 0.0;
        m_Edep2FromID[i] = 0.0;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1SphEveAct::EndOfEventAction(const G4Event*)
{   
  //G4AnalysisManager* m_AM = G4AnalysisManager::Instance();
			
	for (int i = 0; i<m_NumOfSph; i++){
        if (m_EdepFromID[i] > 0.0){
            //std::cout << "vol " << i << " edep " << m_EdepFromID[i] << " and " << m_Edep2FromID[i] << std::endl;
            m_RA->TotEDepToPati(m_EdepFromID[i], i);
        }
        if (m_Edep2FromID[i] > 0.0){
            m_RA->TotEDep2ToPati(m_Edep2FromID[i], i);
        }
    }
}
