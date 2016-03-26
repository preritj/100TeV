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
  TClonesArray *branchTrack, *branchTower, *branchEFlowMuon;
  EventOutput event; 
public:
  Event(ExRootTreeReader *);
  void Reset(), next(), GetMETjetInfo(), GetIsoLepInfo();
  void GetCAjetInfo();
  inline double HT(), MET();
  inline EventOutput Output();
};

inline double Event::MET(){return event.MET;}
inline double Event::HT(){return event.HT;}
inline EventOutput Event::Output(){return event;}

}
#endif // JETSUBSTRUCT_H
