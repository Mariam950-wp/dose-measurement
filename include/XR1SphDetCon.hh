#ifndef XR1SphDetCon_h
#define XR1SphDetCon_h 1

////////////////////////////////////////////////////////////////////////////////
//   XR1SphDetCon.hh for hadron theraphy                                         //
//                                                                            //
//              - 20. Sep. 2020. Mariam Abuladze (mariam.abuladze@kiu.edu.ge) //
////////////////////////////////////////////////////////////////////////////////

#include "G4NistManager.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4MagneticField.hh"

#include "XR1ConMan.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class XR1SphDetCon : public G4VUserDetectorConstruction
{
  public:
    XR1SphDetCon(XR1ConMan* CM);
    virtual ~XR1SphDetCon();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    
    G4LogicalVolume* GetLogicalVolume(int ID) {return m_logicPatient[m_NumOfS - ID - 1]; }
    
    // static access method
    //static XR1SphDetCon* Instance(){return this;};

  protected:
    G4LogicalVolume*  fScoringVolume;
    G4NistManager*    nist;
    
    private:
        //static XR1SphDetCon* m_SphDetCon;  
    
        XR1ConMan* m_CM;
        
        //reaction area (world)
        G4double    m_InterXL;
        G4double    m_InterYL;
        G4double    m_InterZL;
        G4Material* m_WorldMat;
    
        // patient
        G4Material* m_PatiMat;
        G4int       m_NumOfS;
        G4double    m_radInS;
        G4double    m_patSpQ;
        
        G4Sphere*         m_Big_Sphere; 
        G4LogicalVolume*  m_Logic_Big_Sphere;
        
        G4Sphere*         m_Sphere;   
        G4LogicalVolume*  m_LogicSphere;
        G4ThreeVector     m_SpherePos;
        
        G4LogicalVolume*  m_PreLogicSphere;
        std::vector<G4LogicalVolume* > m_logicPatient;
        
        XR1PatMap*  m_PM;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

