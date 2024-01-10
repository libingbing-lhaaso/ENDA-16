#include "G4HadronicInteractionRegistry.hh"
#include "G4HadronicProcess.hh"
#include "G4HadronicProcessStore.hh"
#include "G4HadronicProcessType.hh"
#include "G4Neutron.hh"
#include "G4NeutronHPThermalScattering.hh"
#include "G4NeutronHPThermalScatteringData.hh"
#include "G4HadronElasticProcess.hh"
#include "G4NeutronHPElastic.hh"
#include "G4SystemOfUnits.hh"
#include "PhysicsList.hh"
#include <assert.h>

MyPhysicsList::MyPhysicsList():QGSP_BIC_HP()
{}

MyPhysicsList::~MyPhysicsList()
{}

void MyPhysicsList::ConstructProcess() {
 G4VModularPhysicsList::ConstructProcess();

  /*G4HadronElasticProcess *elasticnp = new G4HadronElasticProcess;
  G4NeutronHPElastic *elasticn = new G4NeutronHPElastic;
  elasticn->SetMinEnergy(4.*eV);
  G4NeutronHPThermalScattering *thermaln = new G4NeutronHPThermalScattering;
  thermaln->SetMaxEnergy(4.*eV);
  elasticnp->RegisterMe(thermaln);
  G4NeutronHPThermalScatteringData *hpthermaldata= new G4NeutronHPThermalScatteringData;
  elasticnp->AddDataSet(hpthermaldata);*/
}
