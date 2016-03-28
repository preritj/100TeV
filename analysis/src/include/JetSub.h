#ifndef JETSUBSTRUCT_H
#define JETSUBSTRUCT_H
#include "StlHeaders.h"
#include "RootHeaders.h"
#include "DelphesHeaders.h"
#include "PFlowJet.h"
namespace analysis{

struct JetSubOutput{
  std::vector<double> CAJet_Pt; 	
  std::vector<double> CAJet_Mass; 	
  std::vector<double> FHTop_Pt; 	
  std::vector<double> FHTop_Mass; 	
  std::vector<double> FHTop_Tau32; 	 
};

class JetSub
{
private:
  ExRootTreeReader *treeReader;
  TClonesArray *branchCAJet;
  TClonesArray *branchTrack, *branchTower;
  TClonesArray *branchEFlowMuon, *branchParticle;
  JetSubOutput eventJS; 
public:
  JetSub(ExRootTreeReader *);
  void Reset(), next();
  void GetCAjetInfo();
  void DelphesToFastjet(Jet *jet, 
		std::vector<fastjet::PseudoJet> & JetConsts, bool verbose = false); 
  void ReCluster(const std::vector<fastjet::PseudoJet> &, 
						 std::vector<PFlowJet> & ,double);
  inline JetSubOutput Output();
};

inline JetSubOutput JetSub::Output(){return eventJS;}


}
#endif // JETSUBSTRUCT_H
