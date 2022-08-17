#include "G4VisAttributes.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"

#include "XR1SphDetCon.hh"

#include "G4RunManager.hh"
#include "G4PVPlacement.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1SphDetCon::XR1SphDetCon(XR1ConMan* CM)
: G4VUserDetectorConstruction(),
  fScoringVolume(0), m_CM(CM)
{ 
    nist = G4NistManager::Instance();
    
    //reaction area
    m_InterXL = m_CM->GetInteXL() * mm;
    m_InterYL = m_CM->GetInteYL() * mm;
    m_InterYL = m_CM->GetInteZL() * mm;
    m_WorldMat= nist->FindOrBuildMaterial(m_CM->GetLabMat());

	//std::cout << "m_InterXL = " << m_InterXL << ", m_InterYL = " << m_InterYL << ", m_InterZL = " << m_InterYL << std::endl;
      
    // number of detectors and detector map
    m_PM        = m_CM->GetPatiMap();
      
    // patient
    m_NumOfS    = m_CM->GetNumOfS();
    m_radInS    = m_CM->GetRadInS();
    m_patSpQ    = m_CM->GetPatSpQ();
    
    m_PatiMat   = nist->FindOrBuildMaterial(m_CM->GetPatiMat());
      
    //m_SphDetCon = this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1SphDetCon::~XR1SphDetCon()
{ 
    //m_SphDetCon = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* XR1SphDetCon::Construct()
{     
    G4bool checkOverlaps = false;

    // World
    G4Box* solidWorld =    
        //new G4Box("World",m_InterXL/2.0, m_InterYL/2.0, m_InterZL/2.0); 
        new G4Box("World", 2000.0, 2000.0, 2000.0);
    G4LogicalVolume* logicWorld =                         
        new G4LogicalVolume(solidWorld,m_WorldMat,"World");    
                                   
    G4VPhysicalVolume* physWorld = 
        new G4PVPlacement(0,G4ThreeVector(),logicWorld,"World",0,false,0,checkOverlaps);  
    
    // big Sphere
    m_Big_Sphere = new G4Sphere("Big_Sphere", 0.0, 95.0/2, 0.0, 2*M_PI, 0.0, M_PI);
    m_Logic_Big_Sphere = new G4LogicalVolume(m_Big_Sphere, m_PatiMat, "Big_Sphere");
    new G4PVPlacement(0,G4ThreeVector(0.0, 0.0, 0.0),m_Logic_Big_Sphere, "Big_Sphere", logicWorld, false, 0, checkOverlaps);
    
    for (int i = m_NumOfS - 1; i > -1; i--){
        //m_Sphere = new G4Sphere(m_PM->GetSphDetNameFromDetID(i), 0.0, m_radInS*pow(m_patSpQ, i-1), 0.0, 2*M_PI, 0.0, M_PI);
        m_Sphere = new G4Sphere(m_PM->GetSphDetNameFromDetID(i), 0.0, m_radInS*(i+1), 0.0, 2*M_PI, 0.0, M_PI);
        m_LogicSphere = new G4LogicalVolume(m_Sphere,m_PatiMat, m_PM->GetSphDetNameFromDetID(i));
        m_LogicSphere->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
        if (i == m_NumOfS - 1)
            new G4PVPlacement(0,G4ThreeVector(0.0, 0.0, 0.0),m_LogicSphere, 
                                      m_PM->GetSphDetNameFromDetID(i), m_Logic_Big_Sphere, false, 0, checkOverlaps);
        else
            new G4PVPlacement(0,G4ThreeVector(0.0, 0.0, 0.0),m_LogicSphere, 
                                      m_PM->GetSphDetNameFromDetID(i), m_PreLogicSphere, false, 0, checkOverlaps);
        m_PreLogicSphere = m_LogicSphere;
        m_logicPatient.push_back(m_LogicSphere);
    }
    
    
    std::cout << "XR1SphDetCon Construct" << std::endl;
    fScoringVolume = logicWorld;
    
    
    //always return the physical World
    return physWorld;
}

