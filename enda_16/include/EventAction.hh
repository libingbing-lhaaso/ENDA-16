
#ifndef EventAction_h
#define EventAction_h 1
#include "G4UserEventAction.hh"
#include "globals.hh"
#include "Globals.hh"

class RunAction;
class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction);
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);
    /*
    void AddEdep(double edep, int neuNum) {
        fEdep += edep;
        fNeuNum += neuNum;
    }
    */
    void AddEdep(double edep, double neuNum, int i) {  //E deposition, Neutron
        fEdep[i] += edep;
        fNeuNum[i] += neuNum;
    }
    double pt[16]={1E6,1E6,1E6,1E6,
                1E6,1E6,1E6,1E6,
                1E6,1E6,1E6,1E6,
                1E6,1E6,1E6,1E6};

  private:
    RunAction* fRunAction;
    double     fEdep[16];
    double     fNeuNum[16];
};

#endif

    
