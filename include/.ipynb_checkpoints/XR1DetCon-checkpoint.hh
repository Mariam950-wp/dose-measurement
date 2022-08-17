#ifndef XR1DetCon_h
#define XR1DetCon_h 1

////////////////////////////////////////////////////////////////////////////////
//   XR1DetCon.hh for hadron theraphy                                         //
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

class XR1DetCon : public G4VUserDetectorConstruction
{
  public:
    XR1DetCon(XR1ConMan* CM);
    virtual ~XR1DetCon();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume*  fScoringVolume;
    G4NistManager*    nist;
    
    private:
    
        XR1ConMan* m_CM;
        
        //reaction area (world)
        G4double    m_InterXL;
        G4double    m_InterYL;
        G4double    m_InterZL;
        G4Material* m_WorldMat;
    
        // patient
        G4double                        m_ColltoPat;
        G4double                        m_PatiXL;
        G4double                        m_PatiYL;
        G4double                        m_PatiZL;
        G4int                           m_NDX;
        G4int                           m_NDY;
        G4int                           m_NDZ;
        
        G4double m_PatiQX;
        G4double m_PatiQY;
        G4double m_PatiQZ;
        G4double m_PatiBX;
        G4double m_PatiBY;
        G4double m_PatiBZ;
        
        G4Material*                     m_PatiMat;
        std::vector< G4Box* >           m_Patient;
        std::vector< G4LogicalVolume* > m_logicPatient;
        std::vector< G4ThreeVector >    m_PatientPos;
        
        XR1PatMap*                      m_PM;
        
        G4Box*                          m_VoxelUn;
        G4LogicalVolume*                m_LogicVoxel;
        G4ThreeVector                   m_VoxelPos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

