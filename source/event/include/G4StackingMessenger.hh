// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4StackingMessenger.hh,v 2.2 1998/07/12 03:42:17 urbi Exp $
// GEANT4 tag $Name: geant4-00 $
//

#ifndef G4StackingMessenger_h
#define G4StackingMessenger_h 1

#include "G4UImessenger.hh"
class G4StackManager;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;

class G4StackingMessenger: public G4UImessenger
{
  public:
    G4StackingMessenger(G4StackManager* fCont);
    ~G4StackingMessenger();
    void SetNewValue(G4UIcommand * command,G4String newValues);
  private:
    G4StackManager * fContainer;
    G4UIdirectory* stackDir;
    G4UIcmdWithoutParameter* statusCmd;
    G4UIcmdWithAnInteger* clearCmd;
};

#endif
