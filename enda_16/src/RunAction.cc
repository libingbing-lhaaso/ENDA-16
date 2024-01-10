
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "SteppingAction.hh"
#include "Run.hh"
#include "EventAction.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "Globals.hh"
#include <fstream>
#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
: G4UserRunAction(),
  sum(0)
{
  //G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  //accumulableManager->RegisterAccumulable(&fEdep);//
  //accumulableManager->RegisterAccumulable(&fNeuNum);//
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
  // inform the runManager to save random number seed
  //G4MTRunManager::GetRunManager()->SetRandomNumberStore(true);//false
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  // reset accumulables to their initial values
  //G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  //accumulableManager->Reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  // Merge accumulables
  //G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  //accumulableManager->Merge();
  
  //char name[100];
  //sprintf(name, "e_n.txt", startpoint);
  //std::ofstream file(name);
  
  G4double sum_edep(0), sum_n(0);
  for(int i=0;i<16;i++)
  {
      sum_edep += fEdep.fProcCounter[i];
      sum_n += fNeuNum.fProcCounter[i];
  }

  if (IsMaster()) {
    G4cout
    << G4endl
    << "--------------------End of Global Run-----------------------"
    << G4endl
    << " The run consists of " << nofEvents << " "
    << G4endl
    << " Cumulated Energy deposit per run, in scoring volume : "
    << G4endl
    << sum_edep << " MeV"
    << G4endl
    << " Cumulated neutron number per run, in scoring volume : "
    << sum_n
    << G4endl
    << "Detector responses:"
    << G4endl;
    for (int i = 0; i < 16; ++i)
        G4cout << fEdep.fProcCounter[i]/(0.006) << " " << fNeuNum.fProcCounter[i] <<" "<<PTime[i]<< G4endl;
    G4cout << "------------------------------------------------------------"
    << G4endl;
 }
  if(fout.is_open()){
    for(int i=0;i<16;i++)
       {
        G4double edep = fEdep.fProcCounter[i];//->
        G4double neuNum = fNeuNum.fProcCounter[i];//->
        fout<< i << " " << edep << " " << neuNum<<" "<<PTime[i]<< G4endl;
       }
  }
  //file.close();
}

void RunAction::AddEdep(G4double edep, G4double neuNum, G4int i)//
{
  fEdep.fProcCounter[i]  += edep;//->
  fNeuNum.fProcCounter[i] += neuNum;//->
}
