#ifndef XR1CONMAN_h
#define XR1CONMAN_h 1

////////////////////////////////////////////////////////////////////////////////
//   XR1ConMan.hh for hadron theraphy                                         //
//                                                                            //
//              - 20. Sep. 2020. Mariam Abuladze (mariam.abuladze@kiu.edu.ge) //
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <vector>
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4String.hh"
#include "G4VModularPhysicsList.hh"

#include "XR1PatMap.hh"
#include "XR1PhyList.hh"

class XR1ConMan
{
    public:
	// ructors and Destructor
	XR1ConMan();
	XR1ConMan(const G4String fileName);
	~XR1ConMan();

	// Initialize
	void Init(const G4String fileName = "");

    // Load configuration file
	bool Load(const G4String fileName);

    // print config file
    void PrintConfiguration();
    
	//Computing
	void SetUseMTD( G4bool   useMTD){m_UseMTD = useMTD;};
	G4bool   GetUseMTD(){return m_UseMTD;};
    
	void SetNofTRD( G4int    nofTRD){m_NofTRD = nofTRD;};
	G4int    GetNofTRD(){return m_NofTRD;};

	// physics list
	void SetHTPhys(G4VModularPhysicsList* PhyList){m_PhyList = PhyList;};
	G4VModularPhysicsList*	GetHTPhys(){return m_PhyList;};

    //reaction area
    void SetInteXL(G4double ractXL){m_InterXL = ractXL;};
	G4double GetInteXL(){return m_InterXL;};
    
	void SetInteYL(G4double ractYL){m_InterYL = ractYL;};
	G4double GetInteYL(){return m_InterYL;};
    
    void SetInteZL(G4double ractZL){m_InterZL = ractZL;};
	G4double GetInteZL(){return m_InterZL;};
    
    void SetLabMat(G4String matname){m_SLabMat = matname;};
	G4String GetLabMat(){return m_SLabMat;};   
    
	//Beam
	void SetBeamKE(G4double beamKE){m_BeamKE = beamKE * MeV;};
	G4double GetBeamKE(){return m_BeamKE;};
    
    void SetBeamOR(G4double beamOR){m_BeamOR = beamOR * mm;};
	G4double GetBeamOR(){return m_BeamOR;};
    
	void SetParName(G4String parname){m_SParName = parname;};
	G4String GetParName(){return m_SParName;};
    
    // choice of geometry
    void SetGeomID( G4int    GeomID){m_GeomID = GeomID;};
	G4int    GetGeomID(){return m_GeomID;};
    
    // patient
    void SetCollToPat(G4double Colltopat){m_ColltoPat = Colltopat * mm;};
	G4double GetCollToPat(){return m_ColltoPat;};
    
    void SetPatiXL(G4double patiXL){m_PatiXL = patiXL * mm;};
	G4double GetPatiXL(){return m_PatiXL;};
    
    void SetPatiYL(G4double patiYL){m_PatiYL = patiYL * mm;};
	G4double GetPatiYL(){return m_PatiYL;};
    
    void SetPatiZL(G4double patiZL){m_PatiZL = patiZL * mm;};
	G4double GetPatiZL(){return m_PatiZL;};
    
    void SetPatDVX(G4int patiDV){m_PatDVX = patiDV;};
	G4int GetPatDVX(){return m_PatDVX;};
    
    void SetPatDVY(G4int patiDV){m_PatDVY = patiDV;};
	G4int GetPatDVY(){return m_PatDVY;};
    
    void SetPatDVZ(G4int patiDV){m_PatDVZ = patiDV;};
	G4int GetPatDVZ(){return m_PatDVZ;};
    
    void SetPatiQX(G4double patiQX){m_PatiQX = patiQX;};
	G4double GetPatiQX(){return m_PatiQX;};
    
    void SetPatiQY(G4double patiQY){m_PatiQY = patiQY;};
	G4double GetPatiQY(){return m_PatiQY;};
    
    void SetPatiQZ(G4double patiQZ){m_PatiQZ = patiQZ;};
	G4double GetPatiQZ(){return m_PatiQZ;};
    
    void SetPatiBX(G4double patiBX){m_PatiBX = patiBX * mm;};
	G4double GetPatiBX(){return m_PatiBX;};
    
    void SetPatiBY(G4double patiBY){m_PatiBY = patiBY * mm;};
	G4double GetPatiBY(){return m_PatiBY;};
    
    void SetPatiBZ(G4double patiBZ){m_PatiBZ = patiBZ * mm;};
	G4double GetPatiBZ(){return m_PatiBZ;};
    
    void SetPatiMat(G4String matname){m_SPatiMat = matname;};
	G4String GetPatiMat(){return m_SPatiMat;};
    
    // patient 2
    void SetNumOfS(G4int NumOfS){m_NumOfS = NumOfS;};
	G4int GetNumOfS(){return m_NumOfS;};
    
    void SetRadInS(G4double radInS){m_radInS = radInS * mm;};
	G4double GetRadInS(){return m_radInS;};
    
    void SetPatSpQ(G4double patSpQ){m_patSpQ = patSpQ;};
	G4double GetPatSpQ(){return m_patSpQ;};
    
    // Maps
	void SetPatiMap0(G4int DVX, G4int DVY, G4int DVZ){m_PM = new XR1PatMap(DVX, DVY, DVZ);};
    void SetPatiMap1(G4int DVR){m_PM = new XR1PatMap(DVR);};
    XR1PatMap* GetPatiMap(){return m_PM;};
    
	// Does the line start with specific word?
	bool StartsWith(const std::string& line, const std::string& token);

  private:
	void SetDefault();

	// Computing resource
    G4bool   m_UseMTD;
    G4int    m_NofTRD;

	// physics list	
	G4VModularPhysicsList* m_PhyList;
    
    //reaction area
    G4double m_InterXL;
    G4double m_InterYL;
    G4double m_InterZL;
    G4String m_SLabMat;

    // Beam 
    G4double m_BeamKE;
    G4double m_BeamOR;
	G4String m_SParName;
    
    // choice of geometry
    G4int    m_GeomID;
    
    // patient 
    G4double m_ColltoPat;
    G4double m_PatiXL;
    G4double m_PatiYL;
    G4double m_PatiZL;
    G4double m_PatiQX;
    G4double m_PatiQY;
    G4double m_PatiQZ;
    G4double m_PatiBX;
    G4double m_PatiBY;
    G4double m_PatiBZ;
    G4int    m_PatDVX;
    G4int    m_PatDVY;
    G4int    m_PatDVZ;
    G4String m_SPatiMat;
    
    // patient 2
    G4int    m_NumOfS;
    G4double m_radInS;
    G4double m_patSpQ;
    
    // detector maps
    XR1PatMap*    m_PM;
};

#endif
