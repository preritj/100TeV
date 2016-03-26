#include "Event.h"
namespace analysis{
//=======================================================


Event::Event(ExRootTreeReader *t_Reader){
  entry =0; /// event index 
  treeReader = t_Reader;
  branchJet        = treeReader->UseBranch("Jet");
  branchCAJet        = treeReader->UseBranch("CAJet");
  branchIsoEl        = treeReader->UseBranch("Electron");
  branchIsoMuon      = treeReader->UseBranch("Muon");
  branchMET          = treeReader->UseBranch("MissingET");
  //branchParticle   = treeReader->UseBranch("Particle");
}

void Event::next(){
  // Read the event entry
  treeReader->ReadEntry(entry++);
  Reset();
  GetMETjetInfo();
  GetIsoLepInfo();
  GetCAjetInfo();
}

void Event::Reset(){
  event.MET=0.; event.HT=0.;
  event.Jet_Pt.clear();
  event.CAJet_Pt.clear();
  event.CAJet_Mass.clear();
  event.Jet_MET_DeltaR.clear();
  event.IsoEl_Pt.clear();
  event.IsoMu_Pt.clear();
}

void Event::GetMETjetInfo(){
  /// MET and jet info
  MissingET *met;
  bool IsMET = false;
  if (branchMET){
    IsMET=true;
    met = (MissingET*) branchMET->At(0);
	event.MET = met->MET;
  }
  if(branchJet){
	Int_t nJets = branchJet->GetEntriesFast();
	double ScalarHT = 0.;	
	for (Int_t i=0; i< nJets; i++){
      Jet *jet = (Jet*) branchJet->At(i); 
	  double JetPT = jet->PT;
	  if (JetPT < 200. || std::abs(jet->Eta) > 2.5) continue;
	  event.Jet_Pt.push_back(JetPT);
	  double deltaR = -1.;
	  if (IsMET) {
        met = (MissingET*) branchMET->At(0);
		deltaR=jet->P4().DeltaR(met->P4());
      }
	  event.Jet_MET_DeltaR.push_back(deltaR);
	  ScalarHT += JetPT;
	}
	event.HT = ScalarHT;
  } 
}

void Event::GetIsoLepInfo(){
  /// check for isolated muons
  if (branchIsoMuon){
    for (int i=0; i < branchIsoMuon->GetEntriesFast(); i++){
      Muon* muon = (Muon*) branchIsoMuon->At(i);
      if (muon->PT < 50.) continue;
	  event.IsoMu_Pt.push_back(muon->PT);
	}
  }

  /// check for isolated electrons
  if (branchIsoEl){
    for (int i=0; i < branchIsoEl->GetEntriesFast(); i++){
      Electron* electron = (Electron*) branchIsoEl->At(i);
      if (electron->PT < 50.) continue;
	  event.IsoEl_Pt.push_back(electron->PT);
	}
  }
}

void Event::GetCAjetInfo(){
  if(branchCAJet){
	Int_t nJets = branchCAJet->GetEntriesFast();
	for (Int_t i=0; i< nJets; i++){
      Jet *jet = (Jet*) branchCAJet->At(i); 
	  double JetPT = jet->PT;
	  if (JetPT < 500. || std::abs(jet->Eta) > 2.5) continue;
	  event.Jet_Pt.push_back(JetPT);
	  event.CAJet_Mass.push_back(jet->Mass);
    }
  }
}
  
//=======================================================
} /// namespace analysis
