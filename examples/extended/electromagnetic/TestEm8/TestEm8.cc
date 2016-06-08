// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: TestEm8.cc,v 1.1 2000/01/07 14:49:19 grichine Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 
// --------------------------------------------------------------
//      GEANT 4 - TestEm8 
//
//      For information related to this code contact:
//      CERN, IT Division, ASD Group
// --------------------------------------------------------------
// Comments
//     
//   
// --------------------------------------------------------------

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "Randomize.hh"

#ifdef G4VIS_USE
#include "Em8VisManager.hh"
#endif

#include "Em8DetectorConstruction.hh"
#include "Em8PhysicsList.hh"
#include "Em8PrimaryGeneratorAction.hh"
#include "Em8RunAction.hh"
#include "Em8EventAction.hh"
#include "Em8SteppingAction.hh"
#include "Em8SteppingVerbose.hh"

int main(int argc,char** argv) 
{

  //choose the Random engine

  HepRandom::setTheEngine(new RanecuEngine);
  
  //my Verbose output class

  G4VSteppingVerbose::SetInstance(new Em8SteppingVerbose);
    
  // Construct the default run manager

  G4RunManager * runManager = new G4RunManager;

  // set mandatory initialization classes

  Em8DetectorConstruction* detector;
  detector = new Em8DetectorConstruction;
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new Em8PhysicsList(detector));
  
#ifdef G4VIS_USE

  // visualization manager

  G4VisManager* visManager = new Em8VisManager;
  visManager->Initialize();

#endif 
 
  // set user action classes

  runManager->SetUserAction(new Em8PrimaryGeneratorAction(detector));

  Em8RunAction* runAction = new Em8RunAction;

  runManager->SetUserAction(runAction);

  Em8EventAction* eventAction = new Em8EventAction(runAction);

  runManager->SetUserAction(eventAction);

  Em8SteppingAction* steppingAction = new Em8SteppingAction(detector,
                                                            eventAction, 
                                                            runAction);
  runManager->SetUserAction(steppingAction);
  
  //Initialize G4 kernel, physics tables ...

  runManager->Initialize();
    
  // get the pointer to the User Interface manager 

  G4UImanager* UI = G4UImanager::GetUIpointer();  
 
  if (argc==1)   // Define UI terminal for interactive mode  
  { 
     G4UIsession * session = new G4UIterminal;
     UI->ApplyCommand("/control/execute init.mac");    
     session->SessionStart();
     delete session;
  }
  else           // Batch mode
  { 
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
  }
    
  // job termination

#ifdef G4VIS_USE
  delete visManager;
#endif  
  delete runManager;

  return 0;
}
