#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "Globals.hh"
//#include "G4Accumulable.hh"
#include "ProcCounterAccumulable.hh"

class G4Run;
class EventAction;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
	
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
	//void AddEdep (ProcCounterAccumulable edep, ProcCounterAccumulable neuNum)
    void AddEdep (G4double edep, G4double neuNum, G4int i);//
	ProcCounterAccumulable fEdep;//*
	ProcCounterAccumulable fNeuNum;//*
  //private:
    //G4Accumulable<G4double> fEdep[16];//
    //G4Accumulable<G4int> fNeuNum[16];//
    G4int sum;
    int PTime[16];
    int ndet;
    void GetTime(int PT, int i){
         PTime[i]=PT;
         ndet=i;
    }
};

#endif

