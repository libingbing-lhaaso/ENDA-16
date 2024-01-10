#include "G4VAccumulable.hh"
#include "globals.hh"

class ProcCounterAccumulable : public G4VAccumulable
{
  public:
    ProcCounterAccumulable(const G4String& name="")
      : G4VAccumulable(name) {
		  for(int i=0;i<16;i++)
		  {
			  fProcCounter[i]=0;
		  }
	 }//name,0
    virtual ~ProcCounterAccumulable() {}

    //void CountProcesses(G4String procName);

    virtual void Merge(const G4VAccumulable& other);//override
    virtual void Reset();
	G4double fProcCounter[16];
};
