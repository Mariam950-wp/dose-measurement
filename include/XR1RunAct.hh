//
// ********************************************************************
// *                                                                  *
// ********************************************************************
//
//
/// \file XR1RunAct.hh
/// \brief Definition of the XR1RunAct class

#ifndef XR1RunAct_h
#define XR1RunAct_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

#include "XR1Analysis.hh"
#include "XR1ConMan.hh"
#include "XR1PriGenAct.hh"
#include "XR1DetCon.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class XR1RunAct : public G4UserRunAction
{
  public:
    XR1RunAct(XR1ConMan* CM);
    virtual ~XR1RunAct();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
      //config object
      XR1ConMan* m_CM;
      
      // limits for 1D histogram
      G4double m_BeamKE;
      
      // number of patient parts
      G4int      m_PDVX;
      G4int      m_PDVY;
      G4int      m_PDVZ;
      
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

#endif

