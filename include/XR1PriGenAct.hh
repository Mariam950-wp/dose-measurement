/// \file XR1PriGenAct.hh
/// \brief Definition of the XR1PriGenAct class

#ifndef XR1PriGenAct_h
#define XR1PriGenAct_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include <fstream>
#include <iostream>

#include "XR1ConMan.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class XR1PriGenAct : public G4VUserPrimaryGeneratorAction
{
    public:
        XR1PriGenAct(XR1ConMan* CM);    
        virtual ~XR1PriGenAct();

        // method from the base class
        virtual void GeneratePrimaries(G4Event*); 
  
        // method to access particle gun
        const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
    private:
        G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    
        // config file
        XR1ConMan* m_CM;
        
        // constants 
        G4double      m_FocalL = 500.0;
        G4double      m_lensRa = 38.10;
        //G4double      m_lensRa = 3.10;
        G4double      m_MeanKE = 59.27;
        //G4double      m_MeanKE = 59000.27;
        
        // beam
        G4double      m_GammKE;
        G4double      m_BeamOR;
        G4String      m_SParName;
        
        int           m_NumFibBeam;
        
        // position
        G4ThreeVector m_ParPos;
        G4ThreeVector m_ParMom;
        G4ThreeVector m_MovVec;
        G4double      m_XposIn;
        G4double      m_YposIn;
        G4double      m_ZposIn;
        G4double      m_XposFi;
        G4double      m_YposFi;
        G4double      m_ZposFi;
        
        // momentum
        G4double      m_XMomDi;
        G4double      m_YMomDi;
        G4double      m_ZMomDi;
        G4double      m_MomNor;
        
        std::ifstream      m_Infile;
        
        int           m_NumOfRY;
        int           m_NumOfRX;
        int           m_RotIndx;
        G4bool        m_180_0In = true;
        
        G4double      m_DisRadX;
        G4double      m_DisRadY;
        G4double      m_DisRadZ;
        int           m_NumOfDY;
        int           m_NumOfDX;
        int           m_NumOfDZ;
        
        int           m_CurrXI = 0;
        int           m_CurrYI = 0;
        int           m_CurrZI = 0;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
