//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// $Id: RE01EventAction.hh,v 1.1 2004/11/26 07:37:40 asaim Exp $
// GEANT4 tag $Name: geant4-07-01 $
//


#ifndef RE01EventAction_h
#define RE01EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4PrimaryParticle;

class RE01EventAction : public G4UserEventAction
{
  public:
    RE01EventAction();
    ~RE01EventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

  private:
    G4int trackerCollID;
    G4int calorimeterCollID;
    G4int muonCollID;

    void PrintPrimary(G4PrimaryParticle* pp,G4int ind);
};

#endif

    