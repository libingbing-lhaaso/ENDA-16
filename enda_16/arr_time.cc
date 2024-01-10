#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
//#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BIC_HP.hh"
#include "FTFP_BERT.hh"
#include "QGSP_BERT_HP.hh"
#include "Randomize.hh"
#include "G4NeutronHPThermalScattering.hh"
#include "G4NeutronHPThermalScatteringData.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"//
#include "RunAction.hh"//
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4SystemOfUnits.hh"
#include "Globals.hh"
#include "Randomize.hh"
#include "time.h"

int waterfraction = 0;
int startpoint = 0;
std::ifstream fin, fin1, fdet;
std::ofstream fout;

int main(int argc, char **argv)
{
  //string cmd = "xrdcp "+ argv[1];
  //istringstream result = read_eos(cmd.c_str());
  fin.open(argv[1]);
  int length=0;
  std::string line;
  while (getline(fin, line))
  //while (getline(result, line))
     length++;
  fin.close();
  G4cout << "the number of enerties is "<< length << G4endl;
 
  fin.open(argv[1]);      //shower data
  fout.open(argv[2]);     //result data
  fin1.open(argv[1]);     //shower data
  fdet.open(argv[3]);     //detector information data
  //G4Random::setTheEngine(new CLHEP::MTwistEngine);
  //G4long seed=time(NULL);
  //CLHEP::HepRandom::setTheSeed(seed);
  //G4cout << "Random Seed is "<< seed << G4endl;
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4Random::setTheSeed(108798);

  //G4MTRunManager* runManager = new G4MTRunManager;
  G4RunManager* runManager = new G4RunManager;
  runManager->SetVerboseLevel(0);
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new MyPhysicsList());

  runManager->SetUserInitialization(new ActionInitialization);

  //runManager->SetNumberOfThreads(1);//
  runManager->Initialize();
//  G4VisManager* visManager = new G4VisExecutive;
  
  //G4UImanager* UImanager = G4UImanager::GetUIpointer();//

//#ifdef G4UI_USE
  //G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  //UImanager->ApplyCommand("/control/execute vis.mac");//0
  runManager->BeamOn(length);
  //ui->SessionStart();
  
  fin.close();
  fout.close();
  fin1.close();
  fdet.close();
  //delete ui;
  delete runManager;
  
  return 0;
}

