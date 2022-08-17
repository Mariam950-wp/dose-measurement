#ifndef XR1PATMAP_h
#define XR1PATMAP_h 1

////////////////////////////////////////////////////////////////////////////////
//   XR1PatMap.cc for Hadron Theraphy                                         //
//                                                                            //
//   Definitions of XR1PatMap class's function definition                     //
//                                                                            //
//              - 20. Ock. 2020. Mariam Abuladze (mariam.abuladze@kiu.edu.ge) //
////////////////////////////////////////////////////////////////////////////////

#include <map>
#include "G4String.hh"

class XR1PatMap
{
  public:
	// Constructor and destructor
	XR1PatMap(G4int NDX, G4int NDY, G4int NDZ);
    XR1PatMap(G4int NDR);
	~XR1PatMap();

	// Initializaion
	void Init0();
    void Init1();
    
	// Get
	G4String GetDetNameFromDetID(G4int id){return m_NameFromID[id];};
	G4int GetDetIDFromDetName(G4String name){return m_IDFromName[name];};
    
    G4String GetSphDetNameFromDetID(G4int id){return m_SphNameFromID[id];};
	G4int GetSphDetIDFromDetName(G4String name){return m_SphIDFromName[name];};

  private:
	// naming for patient parts 
	std::map<G4int, G4String> m_NameFromID;
	std::map<G4String, G4int> m_IDFromName;
    
    std::map<G4int, G4String> m_SphNameFromID;
	std::map<G4String, G4int> m_SphIDFromName;
    
	// number of detectors 
	G4int m_NDX;
    G4int m_NDY;
    G4int m_NDZ;
    
    // number of spheres
    G4int m_NDR;
};

#endif
