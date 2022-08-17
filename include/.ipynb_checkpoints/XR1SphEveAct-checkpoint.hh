/// \file XR1SphEveAct.hh
/// \brief Definition of the XR1SphEveAct class

#ifndef XR1SphEveAct_h
#define XR1SphEveAct_h 1

#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

#include "XR1SphRunAct.hh"

/// Event action class
///

class XR1SphEveAct : public G4UserEventAction
{
  public:
  	XR1SphEveAct(XR1SphRunAct* RA, XR1ConMan* CM);
	virtual ~XR1SphEveAct();

	virtual void BeginOfEventAction(const G4Event* event);
	virtual void EndOfEventAction(const G4Event* event);
        
	// energy deposition to degrader, collimator nad patient
	void EDepToPati(G4double Edep, G4int ID){m_EdepFromID[ID] += Edep;};
    void EDep2ToPati(G4double Edep, G4int ID){m_Edep2FromID[ID] += Edep*Edep;};

	private:
	XR1SphRunAct* m_RA;
        
	//config object
	XR1ConMan* m_CM;
        
	// energy deposition variables
	std::map<G4int, G4double> m_EdepFromID;
    std::map<G4int, G4double> m_Edep2FromID;
    
    // number of spheres
    int        m_NumOfSph;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
