#include "QGSP_BIC_HP.hh"

class MyPhysicsList : public QGSP_BIC_HP {
public:
 MyPhysicsList();
 virtual ~MyPhysicsList();
 virtual void ConstructProcess();
};
