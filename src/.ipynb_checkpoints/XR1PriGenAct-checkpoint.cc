/// \file XR1PriGenAct.cc
/// \brief Implementation of the XR1PriGenAct class

#include "XR1PriGenAct.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <vector>
#include <string>
#include <iostream> 
#include <sstream>  
#include <fstream> 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1PriGenAct::XR1PriGenAct(XR1ConMan* CM)
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),m_CM(CM)
{
    //m_Infile.open ("/home/abuladze/simulations/HadronTheraphy5/XR1/Inputs/beamInfo2Million.txt");
    m_Infile.open ("/home/abuladze/simulations/HadronTheraphy5/XR1/Inputs/BeamInfo1Million.txt");
    //m_Infile.open ("/home/abuladze/simulations/HadronTheraphy5/XR1/Inputs/1M.txt");
      
    // beam parameters 
    m_SParName = m_CM -> GetParName();
    fParticleGun  = new G4ParticleGun();

    // default particle kinematic
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(m_SParName);
    fParticleGun->SetParticleDefinition(particle);
      
    m_NumFibBeam = 144;
    //m_NumFibBeam = 2;
      
    m_NumOfDX = 6;
    m_NumOfDY = 6;
    m_NumOfDZ = 2;
      
    m_DisRadX = 1.0 * mm;
    m_DisRadY = 1.0 * mm;
    m_DisRadZ = 0.0 * mm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1PriGenAct::~XR1PriGenAct()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1PriGenAct::GeneratePrimaries(G4Event* anEvent)
{
    // index for uniform rotations
    //m_RotIndx = anEvent->GetEventID()%(m_NumOfRX*m_NumOfRY);
    
    // index for fibonacci rotations
    //m_RotIndx = anEvent->GetEventID()%(2*m_NumFibBeam + 1);
    
    //index for fibonachi pluss paraller movements
    m_RotIndx = anEvent->GetEventID()%((2*m_NumFibBeam + 1)*m_NumOfDX*m_NumOfDY*m_NumOfDZ);
    
    // index for paraller movements 
    //m_RotIndx = anEvent->GetEventID()%(m_NumOfDX*m_NumOfDY*m_NumOfDZ);
    
    //std::cout << "Event ID: " << anEvent->GetEventID() << std:: endl;
    if(anEvent->GetEventID()%50000 == 0) std::cout << anEvent->GetEventID() << std::endl;
    
    if(m_RotIndx == 0){
        m_CurrXI = -(2*(m_NumOfDX/2) - 1);
        m_CurrYI = -(2*(m_NumOfDY/2) - 1);
        m_CurrZI = -(2*(m_NumOfDZ/2) - 1);
        
        std::string var1, var2, var3, var4, var5, var6, var7, var8;
        if(!m_Infile.eof()){
            m_Infile >> var1 >> var2 >> var3 >> var4 >> var5 >> var6 >> var7 >> var8;
            
            m_XposIn = std::stold(var6)*1000.0 * mm;
            m_YposIn = std::stold(var7)*1000.0 * mm;
            m_ZposIn = std::stold(var8)*1000.0 * mm - 500.0 * mm;
        
            m_XposFi = std::stold(var1)*1000.0 * mm;
            m_YposFi = std::stold(var2)*1000.0 * mm;
            m_ZposFi = 0.0 * mm;
            
            m_GammKE = std::stod(var3) * keV;
        }else{
            std::cout << "ERROR: The data is already fully read" << std::endl;
            exit(0);
        }
    }

    if (m_RotIndx%(2*m_NumFibBeam + 1) == 0 && m_RotIndx!=0) m_CurrXI += 2;
    
    //m_CurrXI += 2;
    if (m_CurrXI > (2*(m_NumOfDX/2) - 1)) {
        m_CurrYI += 2;
        m_CurrXI  = -(2*(m_NumOfDX/2) - 1);
    }
    if (m_CurrYI > (2*(m_NumOfDY/2) - 1)){
       m_CurrZI += 2;
       m_CurrYI  = -(2*(m_NumOfDY/2) - 1); 
    }
    if(m_CurrZI > (2*(m_NumOfDZ/2) - 1)){
        m_CurrZI  = -(2*(m_NumOfDZ/2) - 1);
    }
    
    //std::cout << "rotIndex = " << m_RotIndx << ". X indx = " << m_CurrXI << ". Y indx = " << m_CurrYI << ". Z indx = " << m_CurrZI << std::endl;
    
    G4int i =  m_RotIndx - (2*m_NumFibBeam + 1)/2;
    G4double lat = M_PI*i*(sqrt(5) - 1);
    G4double lon = asin(2.0*i/(2*m_NumFibBeam + 1));
    
    // set momentum direction
    m_XMomDi = m_XposFi - m_XposIn;
    m_YMomDi = m_YposFi - m_YposIn;
    m_ZMomDi = m_ZposFi - m_ZposIn;
    m_MomNor = sqrt(m_XMomDi*m_XMomDi + m_YMomDi*m_YMomDi + m_ZMomDi*m_ZMomDi);
    m_ParMom = G4ThreeVector(m_XMomDi/m_MomNor, m_YMomDi/m_MomNor, m_ZMomDi/m_MomNor);
    G4ThreeVector m_TemMom = m_ParMom;
    
    // fibonachi rotations
    m_TemMom.rotateX(lon);
    m_TemMom.rotateY(lat);
    fParticleGun->SetParticleMomentumDirection(m_TemMom);
    
    // set kinetic energy
    fParticleGun->SetParticleEnergy(m_GammKE);
    
    // fibonachi rotations
    m_ParPos = G4ThreeVector(m_XposIn + m_CurrXI*m_DisRadX/2.0, m_YposIn + m_CurrYI*m_DisRadY/2.0, m_ZposIn + m_CurrZI*m_DisRadZ/2.0);
    //m_ParPos = G4ThreeVector(m_XposIn, m_YposIn, m_ZposIn);
    G4ThreeVector m_TemPos = m_ParPos;
    m_TemPos.rotateX(lon);
    m_TemPos.rotateY(lat);
    fParticleGun->SetParticlePosition(m_TemPos);
    
    // generate primaries 
    fParticleGun->GeneratePrimaryVertex(anEvent);
    
    
    /*
    if(anEvent->GetEventID()%1000 == 0) std::cout << anEvent->GetEventID() << std::endl;
    
    if(m_RotIndx == 0) m_CurrYRI = 0;
    
    // choose radius and angle
    G4double R = abs(G4RandGauss::shoot(m_lensRa,m_lensRa/9));
    G4double theta = 2*M_PI*(G4UniformRand()-0.5);
    
    m_XposIn = R*sin(theta)* mm;
    m_YposIn = R*cos(theta)* mm;
    m_ZposIn = -m_FocalL * mm;
    
    G4double r = abs(G4RandGauss::shoot(0.0,1.0/3.0));
    G4double thet2 = 2*M_PI*(G4UniformRand()-0.5);
    
    m_XposFi = r*sin(thet2) * mm;
    m_YposFi = r*cos(thet2) * mm;
    m_ZposFi = 0.0 * mm;
    
     // set values to position vector
    m_ParPos.setX(m_XposIn);
    m_ParPos.setY(m_YposIn);
    m_ParPos.setZ(m_ZposIn);
    
    m_XMomDi = m_XposFi - m_XposIn;
    m_YMomDi = m_YposFi - m_YposIn;
    m_ZMomDi = m_ZposFi - m_ZposIn;
    m_MomNor = sqrt(m_XMomDi*m_XMomDi + m_YMomDi*m_YMomDi + m_ZMomDi*m_ZMomDi);
    m_ParMom = G4ThreeVector(m_XMomDi/m_MomNor, m_YMomDi/m_MomNor, m_ZMomDi/m_MomNor);
    
    // set momentum direction
    if((m_RotIndx+1)%m_NumOfRX == 0) m_CurrYRI++ ;
    m_ParMom.rotateY(m_CurrYRI*2*M_PI/m_NumOfRY);
    m_ParMom.rotateX(m_RotIndx%m_NumOfRX*2*M_PI/m_NumOfRX);
    
     // set momentum direction
    fParticleGun->SetParticleMomentumDirection(m_ParMom);
    //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(m_XMomDi/m_MomNor, m_YMomDi/m_MomNor, m_ZMomDi/m_MomNor));
   
    // set kinetic energy
    fParticleGun->SetParticleEnergy(abs(G4RandGauss::shoot(m_MeanKE, 1.0)) * keV);
    
    // set position to particlegun
    m_ParPos.rotateY(m_CurrYRI*2*M_PI/m_NumOfRY);
    m_ParPos.rotateX(m_RotIndx%m_NumOfRX*2*M_PI/m_NumOfRX);
    fParticleGun->SetParticlePosition(m_ParPos);

    // generate primaries 
    fParticleGun->GeneratePrimaryVertex(anEvent);
    */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

