#include "PrimaryGeneratorAction.hh"
#include "ParticleTime.hh"
#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4GeneralParticleSource.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <globals.hh> 
#include "Globals.hh"
#include <G4SPSEneDistribution.hh>
#include <G4SPSPosDistribution.hh>
#include <G4SPSAngDistribution.hh>
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
PrimaryGeneratorAction :: PrimaryGeneratorAction()
		:G4VUserPrimaryGeneratorAction(), 
		fParticleGun(0)
		
			     
{}

PrimaryGeneratorAction :: ~ PrimaryGeneratorAction()
{
	delete fParticleGun;
	
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle;
    G4String particleName;
    
    G4int id;
    G4double p, x, y;
    G4double ene, theta, phi;
    if(fin.is_open())
    {
            fin >> id >> p >> x >> y >> ene >> theta >> phi >> Pt;
            switch(id)
            {
            case 1:
                particleName="gamma";
                break;
            case 2:
                particleName="e+";
                break;
            case 3:
                particleName="e-";
                break;
            case 4:
                particleName="nu_e";
                break;
            case 5:
                particleName="mu+";
                break;
            case 6:
                particleName="mu-";
                break;
            case 7:
                particleName="pi0";
                break;
            case 8:
                particleName="pi+";
                break;
            case 9:
                particleName="pi-";
                break;
            case 10:
                particleName="kaon0L";
                break;
            case 11:
                particleName="kaon+";
                break;
            case 12:
                particleName="kaon-";
                break;
            case 13:
                particleName="neutron";
                break;
            case 14:
                particleName="proton";
                break;
            case 15:
                particleName="anti_proton";
                break;
            case 16:
                particleName="kaon0S";
                break;
            case 17:
                particleName="eta";
                break;
            case 18:
                particleName="lambda";
                break;
            case 19:
                particleName="sigma+";
                break;
            case 20:
                particleName="sigma0";
                break;
            case 21:
                particleName="sigma-";
                break;
            case 22:
                particleName="xi0";
                break;
            case 23:
                particleName="xi-";
                break;
            case 24:
                particleName="omega-";
                break;
            case 25:
                particleName="anti_neutron";
                break;
            default:
                particleName="proton";
                break;
            }
    }
    fParticleGun  = new G4ParticleGun(1);
    particle = particleTable->FindParticle(particleName);
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(p*GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(x*cm,y*cm,1*m));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

