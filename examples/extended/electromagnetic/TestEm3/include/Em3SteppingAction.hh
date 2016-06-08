// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: Em3SteppingAction.hh,v 1.2 1999/12/15 14:49:02 gunter Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef Em3SteppingAction_h
#define Em3SteppingAction_h 1

#include "G4UserSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class Em3SteppingAction : public G4UserSteppingAction
{
  public:
    Em3SteppingAction();
   ~Em3SteppingAction();

    void UserSteppingAction(const G4Step*);
};

#endif