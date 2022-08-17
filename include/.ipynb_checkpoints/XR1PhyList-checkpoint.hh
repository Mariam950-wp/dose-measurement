#ifndef XR1PHYLIST_h
#define XR1PHYLIST_h 1

////////////////////////////////////////////////////////////////////////////////
//   XR1PhyList.hh for hadron theraphy                                        //
//                                                                            //
//              - 20. Sep. 2020. Mariam Abuladze (mariam.abuladze@kiu.edu.ge) //
////////////////////////////////////////////////////////////////////////////////

#include "G4VModularPhysicsList.hh"

class XR1PhyList: public G4VModularPhysicsList
{
  public:
		XR1PhyList();
		virtual ~XR1PhyList();
   
		virtual void SetCuts();
    
};

#endif
