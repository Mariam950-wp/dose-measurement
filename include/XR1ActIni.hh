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
/// \file XR1ActIni.hh
/// \brief Definition of the XR1ActIni class

#ifndef XR1ActIni_h
#define XR1ActIni_h 1

#include "G4VUserActionInitialization.hh"

#include "XR1PriGenAct.hh"
#include "XR1EveAct.hh"
#include "XR1SphEveAct.hh"
#include "XR1SteAct.hh"
#include "XR1SphDetCon.hh"

/// Action initialization class.

class XR1ActIni : public G4VUserActionInitialization
{
    public:
        XR1ActIni(XR1ConMan* CM, XR1DetCon* DC, XR1SphDetCon* SDC);
        virtual ~XR1ActIni();

        virtual void BuildForMaster() const;
        virtual void Build() const;
    
    private:
        XR1ConMan*    m_CM;
        XR1DetCon*    m_DC;
        XR1SphDetCon* m_SDC;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
