#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "RootHeaders.h"
#include "DelphesHeaders.h"
#include "Event.h"
namespace analysis{
//========================================================

class Analysis{
private: 
  ExRootTreeReader *treeReader;
  Long64_t nEvents;
  TTree *eventTree;
  TFile *file;
  EventOutput eventOut;
public:
  Analysis(ExRootTreeReader *, std::string);
  void RunEvents(), Write();
};


//========================================================
}
#endif // ANALYSIS_H
