#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "Run.hh"
#include <G4StepPoint.hh>
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh" 

#include "G4UserRunAction.hh"
#include "G4SystemOfUnits.hh"
#include <G4Triton.hh>
#include "RunAction.hh"
#include "Randomize.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{	
	const G4String processName = step->GetPostStepPoint()->
		GetProcessDefinedStep()->GetProcessName(); 
	const std::vector<const G4Track*>* secondaries =step->GetSecondaryInCurrentStep();
    //G4double posZ = step->GetTrack()->GetPosition().z()/cm;
    //G4Track* track = step->GetTrack();
        //const G4String ParticleName = track->GetDynamicParticle()->
                                 //GetParticleDefinition()->GetParticleName();
    /*if (ParticleName == "neutron")
    {
      if (posZ > 7.5 && posZ < 8.5){
       std::ofstream resultFile("E_n_all.txt",std::ios_base::app);
       resultFile << track->GetKineticEnergy()/MeV <<G4endl;
      }
    }*/
    G4String common_part = "Detector";
	for(int i=0;i<16;i++)
	{
        G4String name = common_part+std::to_string(i);
		
        if (step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == name)
		{
            //G4double posZ = step->GetTrack()->GetPosition().z();// /cm;
//            if((posZ<(5+0.05)*cm)&&(posZ>(5-0.05)*cm))//(posZ<0.05*cm)&&(posZ>-0.05*cm))
                 /*if (ParticleName == "neutron")
          {
             std::ofstream resultFile("neutron_det.txt",std::ios_base::app);
             G4cout <<"position= "<<posZ<<"  "<<step->GetTotalEnergyDeposit()/MeV <<G4endl;
             resultFile << step->GetTotalEnergyDeposit()/MeV << " " <<posZ <<G4endl;
           }*/

			G4double time=step->GetTrack()->GetGlobalTime();
			if (time/microsecond <= 1.)
		            fEventAction->AddEdep(step->GetTotalEnergyDeposit()/MeV, 0, i);
			else if (time/microsecond > 100 && time/ms < 20)
			{
				if (processName == "neutronInelastic")
				{
					if ((*secondaries->begin())->GetDefinition()->GetParticleName() == "alpha")
					{
						step->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
						fEventAction->AddEdep(0, 1, i);
					}
				}
			}
            //}
		}
	}
}


