#ifndef EVENTANALYSIS_H
#define EVENTANALYSIS_H
#include "StlHeaders.h"
#include "RootHeaders.h"
#include "DelphesHeaders.h"
namespace analysis{

struct EventOutput{
  double HT;
  double MET;
  std::vector<double> Jet_Pt;
  std::vector<double> CAJet_Pt;
  std::vector<double> CAJet_Mass;
  std::vector<double> Jet_MET_DeltaR;
  std::vector<double> IsoEl_Pt;
  std::vector<double> IsoMu_Pt;
};

class Event
{
private:
  Long64_t entry=0;
  ExRootTreeReader *treeReader;
  TClonesArray *branchMET, *branchJet, *branchCAJet;
  TClonesArray *branchIsoMuon, *branchIsoEl;
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
#endif // EVENTANALYSIS_H
