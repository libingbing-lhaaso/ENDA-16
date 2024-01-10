#include "ProcCounterAccumulable.hh"

void ProcCounterAccumulable::Merge(const G4VAccumulable& other)
{
  const ProcCounterAccumulable& otherProcCounterAccumulable
    = static_cast<const ProcCounterAccumulable&>(other);//static

  for (int i=0;i<16;i++)
  {
	fProcCounter[i]+=otherProcCounterAccumulable.fProcCounter[i];
    
  }
}

void ProcCounterAccumulable::Reset()
{
  for(int i=0;i<16;i++)
  {
	  fProcCounter[i]=0;
  }
}
