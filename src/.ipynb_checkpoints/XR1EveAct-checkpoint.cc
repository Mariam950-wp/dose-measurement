/// \file XR1EveAct.cc
/// \brief Implementation of the XR1EveAct class

#include "XR1EveAct.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1EveAct::XR1EveAct(XR1RunAct* RA, XR1ConMan* CM)
: G4UserEventAction(),m_RA(RA), m_CM(CM)
{
    m_PatiDVX = m_CM->GetPatDVX();
    m_PatiDVY = m_CM->GetPatDVY();
    m_PatiDVZ = m_CM->GetPatDVZ();
    
    m_PtXL = m_CM->GetPatiXL();
    m_PtYL = m_CM->GetPatiYL();
    m_PtZL = m_CM->GetPatiZL();
    
    m_PatiQX    = m_CM->GetPatiQX();
    m_PatiQY    = m_CM->GetPatiQY();
    m_PatiQZ    = m_CM->GetPatiQZ();
    m_PatiBX    = m_CM->GetPatiBX();
    m_PatiBY    = m_CM->GetPatiBY();
    m_PatiBZ    = m_CM->GetPatiBZ();
    
    m_EdepFromID.clear();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1EveAct::~XR1EveAct()
{
    delete &m_EdepFromID;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1EveAct::BeginOfEventAction(const G4Event*)
{

	// initial enegry deposition is zero
    for (int k = -m_PatiDVZ/2; k<m_PatiDVZ/2; k++)
        for (G4int j = -m_PatiDVY/2; j<m_PatiDVY/2; j++)
            for (G4int i = -m_PatiDVX/2; i<m_PatiDVX/2; i++)
                m_EdepFromID[i + m_PatiDVX*j + m_PatiDVX*m_PatiDVY*k] = 0.0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1EveAct::EndOfEventAction(const G4Event*)
{   
  G4AnalysisManager* m_AM = G4AnalysisManager::Instance();
			

	for (int k = -m_PatiDVZ/2; k<m_PatiDVZ/2; k++)
        for (G4int j = -m_PatiDVY/2; j<m_PatiDVY/2; j++)
            for (G4int i = -m_PatiDVX/2; i<m_PatiDVX/2; i++)
                if (m_EdepFromID[i + m_PatiDVX*j + m_PatiDVX*m_PatiDVY*k] > 0.0){
                   /*
                    if(k%3 == 0)
                        m_AM->FillH2((m_PatiDVZ/2 + k)/3,                             (i+1.0/2)*m_PtXL/m_PatiDVX, (j+1.0/2)*m_PtYL/m_PatiDVY,
                                     m_EdepFromID[i + m_PatiDVX*j + m_PatiDVX*m_PatiDVY*k]); 
                    
                    if(j%3 == 0)
                        m_AM->FillH2((m_PatiDVY/2 + j)/3 + m_PatiDVZ/3,               (k+1.0/2)*m_PtZL/m_PatiDVZ, (i+1.0/2)*m_PtXL/m_PatiDVX,
                                     m_EdepFromID[i + m_PatiDVX*j + m_PatiDVX*m_PatiDVY*k]);
                    
                    if(i%3 == 0)
                        m_AM->FillH2((m_PatiDVX/2 + i)/3 + m_PatiDVZ/3 + m_PatiDVY/3, (k+1.0/2)*m_PtZL/m_PatiDVZ, (j+1.0/2)*m_PtXL/m_PatiDVX,
                                     m_EdepFromID[i + m_PatiDVX*j + m_PatiDVX*m_PatiDVY*k]);
                    */
                    
                    /*
                    m_AM->FillH2(0 , 
                                 k*(m_PatiBZ*(pow(m_PatiQZ,abs(k)-1)-1.0)/(m_PatiQZ-1.0)+m_PatiBZ*pow(m_PatiQZ,abs(k)-1)*G4UniformRand())/abs(k),
                                 i*(m_PatiBX*(pow(m_PatiQX,abs(i)-1)-1.0)/(m_PatiQX-1.0)+m_PatiBX*pow(m_PatiQX,abs(i)-1)*G4UniformRand())/abs(i),
                                 m_EdepFromID[i + m_PatiDVX*j + m_PatiDVX*m_PatiDVY*k]);
                    */
                    /*
                    m_AM->FillH2(0 , (k+1.0/2)*m_PtZL/m_PatiDVZ, (i+1.0/2)*m_PtXL/m_PatiDVX,
                                 m_EdepFromID[i + m_PatiDVX*j + m_PatiDVX*m_PatiDVY*k]);
                    */
                    
                
                    m_AM->FillH2(0 , (i+1.0/2)*m_PtXL/m_PatiDVX, (j+1.0/2)*m_PtYL/m_PatiDVY,
                                 m_EdepFromID[i + m_PatiDVX*j + m_PatiDVX*m_PatiDVY*k]);
                    /*
                    m_AM->FillH3(0 , (i+1.0/2)*m_PtXL/m_PatiDVX, (j+1.0/2)*m_PtYL/m_PatiDVY, (k+1.0/2)*m_PtZL/m_PatiDVZ,
                                 m_EdepFromID[i + m_PatiDVX*j + m_PatiDVX*m_PatiDVY*k]);
                                 */
                }

}
