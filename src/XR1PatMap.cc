#include "XR1PatMap.hh"

//////////////////////////////////////////////////
//   Constructors and destructor                //
//////////////////////////////////////////////////
XR1PatMap::XR1PatMap(G4int NDX, G4int NDY, G4int NDZ):m_NDX(NDX),m_NDY(NDY),m_NDZ(NDZ)
{
	m_NameFromID.clear();
	m_IDFromName.clear();
    
	Init0();
}

XR1PatMap::XR1PatMap(G4int NDR):m_NDR(NDR)
{
	m_SphNameFromID.clear();
	m_SphIDFromName.clear();
    
	Init1();
}

XR1PatMap::~XR1PatMap()
{
}


//////////////////////////////////////////////////
//   Initialization                             //
//////////////////////////////////////////////////
void XR1PatMap::Init0()
{
    for (int k = -m_NDZ/2; k<m_NDZ/2; k++){
        for (int j = -m_NDY/2; j<m_NDY/2; j++){
            for (int i = -m_NDX/2; i<m_NDX/2; i++){
                // Mapping from ID to name
                m_NameFromID[i + m_NDX*j + m_NDX*m_NDY*k]   = "Patient_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k);
                // Mapping from name to ID
                m_IDFromName["Patient_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(k)] = i + m_NDX*j + m_NDX*m_NDY*k;
            }
        }
    }                
}

void XR1PatMap::Init1()
{
    for (int i = 0; i<m_NDR; i++){
        // Mapping from ID to name
        m_SphNameFromID[i]   = "Patient_" + std::to_string(i);
        // Mapping from name to ID
        m_SphIDFromName["Patient_" + std::to_string(i)] = i;
    }                
}