#include "XR1PhyList.hh"
#include "globals.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"

#include "G4HadronInelasticQBBC.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4ChargeExchangePhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"

#include "G4IonPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4HadronElasticPhysics.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

//////////////////////////////////////////////////
//   Constructors and destructor                //
//////////////////////////////////////////////////
XR1PhyList::XR1PhyList():G4VModularPhysicsList(){
	SetVerboseLevel(1);      

	
	RegisterPhysics( new G4EmStandardPhysics(1) );

	RegisterPhysics( new G4StoppingPhysics(1) );

	RegisterPhysics( new G4IonPhysics(1) );
}


XR1PhyList::~XR1PhyList()
{
}

void XR1PhyList::SetCuts()
{
	G4VUserPhysicsList::SetCuts();
}  

	
