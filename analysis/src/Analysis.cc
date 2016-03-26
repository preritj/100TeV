#include "Analysis.h"
namespace analysis{
//==========================================================================

Analysis::Analysis(ExRootTreeReader *t_Reader, std::string OutputFile){
  /// Initialize output file
  file = TFile::Open(OutputFile.c_str(),"RECREATE"); 
  if (!file) {
	std::cout <<"Could not open file for writing. aborting..." << std::endl;
	abort();
  }

  /// Create tree with event info
  eventTree = new TTree("event", "Tree with event info");
  /// Following info is stored in output root file
  eventTree->Branch("MET", &eventOut.MET); 
  eventTree->Branch("HT", &eventOut.HT); 
  eventTree->Branch("Jet_Pt", &eventOut.Jet_Pt); 
  eventTree->Branch("Jet_MET_DeltaR", &eventOut.Jet_MET_DeltaR); 
  eventTree->Branch("IsoEl_Pt", &eventOut.IsoEl_Pt); 
  eventTree->Branch("IsoMu_Pt", &eventOut.IsoMu_Pt); 
  eventTree->Branch("CAJet_Pt", &eventOut.CAJet_Pt); 
  eventTree->Branch("CAJet_Mass", &eventOut.CAJet_Mass); 

  /// initialize analysis
  treeReader = t_Reader;
  nEvents = treeReader->GetEntries();
}

void Analysis::RunEvents(){
  Event ev(treeReader);
  for (Long64_t i=0; i < nEvents; i++){
	ev.next();
    eventOut = ev.Output();
    eventTree->Fill(); 
  }
}

void Analysis::Write(){
  file->Write();
  //delete eventTree;
  delete file;
}


//==========================================================================
} // namespace analysis
