#ifndef JETSUBSTRUCT_H
#define JETSUBSTRUCT_H
#include "StlHeaders.h"
#include "RootHeaders.h"
#include "DelphesHeaders.h"
namespace analysis{

struct JetSubOutput{
  std::vector<double> FHTop_Mass; 	
  std::vector<double> FHTop_Tau32; 	 
};

class JetSub
{
private:
  Long64_t entry=0;
  ExRootTreeReader *treeReader;
  TClonesArray *branchCAJet;
  TClonesArray *branchTrack, *branchTower;
  TClonesArray *branchEFlowMuon, *branchParticle;
  JetSubOutput jsub; 
public:
  JetSub(ExRootTreeReader *);
  void Reset(), next();
  inline JetSubOutput Output();
};

inline JetSubOutput JetSub::Output(){return jsub;}

}
#endif // JETSUBSTRUCT_H
