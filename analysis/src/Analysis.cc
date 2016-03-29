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
  eventTree->Branch("CAJet_Pt", &eventJSOut.CAJet_Pt); 
  eventTree->Branch("CAJet_Mass", &eventJSOut.CAJet_Mass); 
  eventTree->Branch("FHTop_Pt", &eventJSOut.FHTop_Pt); 
  eventTree->Branch("FHTop_Mass", &eventJSOut.FHTop_Mass); 
  eventTree->Branch("FHTop_Tau32", &eventJSOut.FHTop_Tau32); 

  /// initialize analysis
  treeReader = t_Reader;
  nEvents = treeReader->GetEntries();
}

void Analysis::RunEvents(){
  Event ev(treeReader);
  JetSub js(treeReader);
  for (Long64_t i=0; i < nEvents; i++){
	ev.next();
    js.next();
    eventOut = ev.Output();
    eventJSOut = js.Output();
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
