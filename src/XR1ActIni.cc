//
//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file XR1ActIni.cc
/// \brief Implementation of the XR1ActIni class

#include "XR1ActIni.hh"

#include "XR1RunAct.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1ActIni::XR1ActIni(XR1ConMan* CM, XR1DetCon* DC, XR1SphDetCon* SDC)
 : G4VUserActionInitialization(), m_CM(CM), m_DC(DC), m_SDC(SDC)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XR1ActIni::~XR1ActIni()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1ActIni::BuildForMaster() const
{
  XR1RunAct* RA = new XR1RunAct(m_CM);
  SetUserAction(RA);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XR1ActIni::Build() const
{
  SetUserAction(new XR1PriGenAct(m_CM));

  if(m_CM->GetGeomID() == 0) {
      XR1RunAct* RA = new XR1RunAct(m_CM);                    
      SetUserAction(RA);
      XR1EveAct* EA = new XR1EveAct(RA, m_CM);                     
      SetUserAction(EA);
      SetUserAction(new XR1SteAct(EA, m_CM->GetPatiMap()));
  }else{
      XR1SphRunAct* RA = new XR1SphRunAct(m_CM, m_SDC);
      SetUserAction(RA);
      XR1SphEveAct* EA = new XR1SphEveAct(RA, m_CM);
      SetUserAction(EA);
      SetUserAction(new XR1SteAct(EA, m_CM->GetPatiMap()));
  }
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
