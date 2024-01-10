#include "EventAction.hh"
#include "RunAction.hh"
#include "Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "Globals.hh"
#include "ParticleTime.hh"

EventAction::EventAction(RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
  //fEdep(0.),
  //fNeuNum(0)
{
	
} 


EventAction::~EventAction()
{}



void EventAction::BeginOfEventAction(const G4Event*)
{
	for(int i=0;i<16;i++)
	{
		fEdep[i] = 0.;
		fNeuNum[i] = 0;
	}
    /*
    fEdep = 0.;
    fNeuNum = 0;
    */
}


void EventAction::EndOfEventAction(const G4Event*)
{   
    G4int idi, arrivTime;
    G4double pi, xi, yi;
    G4double Ei, thi, phii;
    if(fin1.is_open()){fin1 >>idi>>pi>>xi>>yi>>Ei>>thi>>phii>>arrivTime;}

    const PrimaryGeneratorAction* generatorAction
           = static_cast<const PrimaryGeneratorAction*>
    (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    G4String eventCondition;
    if (generatorAction)
       {
        const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
        eventCondition += particleGun->GetParticleDefinition()->GetParticleName();
        eventCondition += " of ";
        G4double particleEnergy = particleGun->GetParticleEnergy();
        eventCondition += G4BestUnit(particleEnergy,"Energy");
       }
    G4cout<<"The particle is "<<eventCondition<<G4endl;
    for(int i=0;i<16;i++){
       fRunAction->AddEdep(fEdep[i], fNeuNum[i], i);
       if(fEdep[i]>0){   
          if(pt[i]>arrivTime){
             pt[i] = arrivTime;
             fRunAction->GetTime(int(pt[i]),i);
          }
       }
    }
}
