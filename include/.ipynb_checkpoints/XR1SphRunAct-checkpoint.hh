//
// ********************************************************************
// *                                                                  *
// ********************************************************************
//
//
/// \file XR1SphRunAct.hh
/// \brief Definition of the XR1SphRunAct class

#ifndef XR1SphRunAct_h
#define XR1SphRunAct_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include "XR1Analysis.hh"
#include "XR1ConMan.hh"
#include "XR1PriGenAct.hh"
#include "XR1DetCon.hh"
#include "XR1SphDetCon.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class XR1SphRunAct : public G4UserRunAction
{
  public:
    XR1SphRunAct(XR1ConMan* CM, XR1SphDetCon* SDC);
    virtual ~XR1SphRunAct();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    
    void TotEDepToPati(G4double Edep, G4int ID){m_EdepFromID[ID] += Edep;};
    void TotEDep2ToPati(G4double Edep, G4int ID){m_Edep2FromID[ID] += Edep;};

  private:
      //config object
      XR1ConMan*    m_CM;
      XR1SphDetCon* m_SDC;
      
      // energy deposition variables
      std::map<G4int, G4double> m_EdepFromID;
      std::map<G4int, G4double> m_Edep2FromID;
      
      // number of spheres
      int        m_NumOfSph;
      G4double   m_radInS;
      
      G4double   m_TotDos = 0.0;
};

#endif

