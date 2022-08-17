#include "G4VisAttributes.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"

#include "XR1DetCon.hh"

#include "G4RunManager.hh"
#include "G4PVPlacement.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1DetCon::XR1DetCon(XR1ConMan* CM)
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
    m_NDX       = m_CM->GetPatDVX();
    m_NDY       = m_CM->GetPatDVY();
    m_NDZ       = m_CM->GetPatDVZ();
    m_PM        = m_CM->GetPatiMap();
      
    // patient
    m_PatiXL    = m_CM->GetPatiXL();
    m_PatiYL    = m_CM->GetPatiYL();
    m_PatiZL    = m_CM->GetPatiZL();
    
    m_PatiQX    = m_CM->GetPatiQX();
    m_PatiQY    = m_CM->GetPatiQY();
    m_PatiQZ    = m_CM->GetPatiQZ();
    m_PatiBX    = m_CM->GetPatiBX();
    m_PatiBY    = m_CM->GetPatiBY();
    m_PatiBZ    = m_CM->GetPatiBZ();
    
    m_PatiMat   = nist->FindOrBuildMaterial(m_CM->GetPatiMat());
	
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1DetCon::~XR1DetCon()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* XR1DetCon::Construct()
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
    
    // big box
    G4Box* BigBox = new G4Box ("Big_Box", 100.0/2, 100.0/2, 100.0/2);
    G4LogicalVolume* LogcalBigBox = new G4LogicalVolume(BigBox, m_PatiMat,"Big_Box"); 
    //LogcalBigBox->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
    G4ThreeVector BigBoxPos = G4ThreeVector(0.0, 0.0, 0.0);
    new G4PVPlacement(0,BigBoxPos,LogcalBigBox, "Big_Box", logicWorld, false, 0, checkOverlaps);
    
    // solid volumes
    for (int k = -m_NDZ/2; k<m_NDZ/2; k++)
        for (int j = -m_NDY/2; j<m_NDY/2; j++)
            for (int i = -m_NDX/2; i<m_NDX/2; i++) {
                m_VoxelUn = new G4Box (m_PM->GetDetNameFromDetID(i + m_NDX*j + m_NDX*m_NDY*k),
                                               m_PatiXL/(2*m_NDX),m_PatiYL/(2*m_NDY),m_PatiZL/(2*m_NDZ));
                m_LogicVoxel = new G4LogicalVolume(m_VoxelUn,m_PatiMat,
                                                             "logic"+m_PM->GetDetNameFromDetID(i + m_NDX*j + m_NDX*m_NDY*k));
                m_LogicVoxel->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
                m_VoxelPos = G4ThreeVector((i+1.0/2)*m_PatiXL/m_NDX, (j+1.0/2)*m_PatiYL/m_NDY, (k+1.0/2)*m_PatiZL/m_NDZ);
                new G4PVPlacement(0,m_VoxelPos,m_LogicVoxel, 
                                  m_PM->GetDetNameFromDetID(i + m_NDX*j + m_NDX*m_NDY*k), LogcalBigBox, false, 0, checkOverlaps);
            }
    
    /*
     // solid volumes
    for (int k = -m_NDZ/2; k<m_NDZ/2 + 1; k++)
        for (int j = -m_NDY/2; j<m_NDY/2; j++)
            for (int i = -m_NDX/2; i<m_NDX/2 + 1; i++){
                if (i !=0 && k!=0){
                    m_VoxelUn = new G4Box (m_PM->GetDetNameFromDetID(i + m_NDX*j + m_NDX*m_NDY*k),
                                                   m_PatiBX*pow(m_PatiQX,abs(i)-1)/2,m_PatiYL/(2*m_NDY),m_PatiBZ*pow(m_PatiQZ,abs(k)-1)/2 );
                    m_LogicVoxel = new G4LogicalVolume(m_VoxelUn,m_PatiMat,
                                                             "logic"+m_PM->GetDetNameFromDetID(i + m_NDX*j + m_NDX*m_NDY*k));
                    m_LogicVoxel->SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
                    m_VoxelPos = G4ThreeVector(i*(m_PatiBX*(pow(m_PatiQX,abs(i) -1)-1.0)/(m_PatiQX-1.0)+m_PatiBX*pow(m_PatiQX,abs(i)-1)/2)/abs(i), 
                                                (j+1.0/2)*m_PatiYL/m_NDY, 
                                                k*(m_PatiBZ*(pow(m_PatiQZ,abs(k)-1)-1.0)/(m_PatiQZ-1.0)+m_PatiBZ*pow(m_PatiQZ,abs(k)-1)/2)/abs(k));
                    new G4PVPlacement(0, m_VoxelPos, m_LogicVoxel, 
                                  m_PM->GetDetNameFromDetID(i + m_NDX*j + m_NDX*m_NDY*k), logicWorld, false, 0, checkOverlaps);
                }
            }
            */
    
    std::cout << "XR1DetCon Construct" << std::endl;
    fScoringVolume = logicWorld;
    
    
    //always return the physical World
    return physWorld;
}

