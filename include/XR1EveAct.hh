/// \file XR1EveAct.hh
/// \brief Definition of the XR1EveAct class

#include "XR1RunAct.hh"

#ifndef XR1EveAct_h
#define XR1EveAct_h 1

#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

#include "XR1RunAct.hh"

/// Event action class
///

class XR1EveAct : public G4UserEventAction
{
  public:
  	XR1EveAct(XR1RunAct* RA, XR1ConMan* CM);
	virtual ~XR1EveAct();

	virtual void BeginOfEventAction(const G4Event* event);
	virtual void EndOfEventAction(const G4Event* event);
        
	// energy deposition to degrader, collimator nad patient
	void EDepToPati(G4double Edep, G4int ID){m_EdepFromID[ID] += Edep;};

	private:
	XR1RunAct* m_RA;
        
	//config object
	XR1ConMan* m_CM;
        
	// energy deposition variables
	std::map<G4int, G4double> m_EdepFromID;

	// number of patient parts
	G4int      m_PatiDVX;
    G4int      m_PatiDVY;
    G4int      m_PatiDVZ;
    
    // patient dmensions 
    G4double   m_PtXL;
    G4double   m_PtYL;
    G4double   m_PtZL;
    
    G4double m_PatiQX;
    G4double m_PatiQY;
    G4double m_PatiQZ;
    G4double m_PatiBX;
    G4double m_PatiBY;
    G4double m_PatiBZ;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
