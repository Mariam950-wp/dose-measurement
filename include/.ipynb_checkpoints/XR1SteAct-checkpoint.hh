//
// ********************************************************************
// *                                                                  *
// ********************************************************************
//
//
/// \file XR1SteAct.hh
/// \brief Definition of the XR1SteAct class

#ifndef XR1SteAct_h
#define XR1SteAct_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include "XR1EveAct.hh"
#include "XR1SphEveAct.hh"
#include "XR1DetCon.hh"

class G4LogicalVolume;

/// Stepping action class
/// 

class XR1SteAct : public G4UserSteppingAction
{
    public:
        XR1SteAct(XR1EveAct*     EA, XR1PatMap* PM);
        XR1SteAct(XR1SphEveAct* SEA, XR1PatMap* PM);
        virtual ~XR1SteAct();

        // method from the base class
        virtual void UserSteppingAction(const G4Step*);

    private:
        XR1EveAct*    m_EA;
        XR1SphEveAct* m_SEA;
        XR1PatMap* m_PM;
        int        m_ID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
