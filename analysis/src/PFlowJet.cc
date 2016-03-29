#include "PFlowJet.h"
namespace analysis{


PFlowJet::PFlowJet(const std::vector<fastjet::PseudoJet> & JetConsts){
  PFjetConsts = JetConsts;
  tracks.clear();
  calcJetP4();
}

//-------------------------------------------------------------------
// Check if a hard muon (pT>200 GeV) is present inside the input jet 
bool PFlowJet::MuonInJet(){
	return ((jetP4.muon).Pt() > 200.);
}



//-----------------------------------------------------------------------
// Calculates net 4-momentum of tracks (including muons), towers and 
// the hardest muon (if any) inside input jet
void  PFlowJet::calcJetP4(){
	PFlowJetP4 p;
	TLorentzVector pConst;
	for (unsigned long i=0; i < PFjetConsts.size(); i++){
		fastjet::PseudoJet pJet = PFjetConsts[i];
		pConst.SetPxPyPzE(pJet.px(), pJet.py(), pJet.pz(), pJet.e());
		if (pJet.user_index() == 0) {
		  p.track += pConst;
		  tracks.push_back(PFjetConsts[i]);
		}
		else if (pJet.user_index() == 1) p.tower += pConst;
		else if (pJet.user_index() == 2) {
			p.track += pConst;
		    tracks.push_back(PFjetConsts[i]);
			if (pJet.pt() > (p.muon).Pt()) p.muon = pConst;
		}
	}
	jetP4 = p;
}


//-------------------------------------------------------------------
// Calculates jet mass 
// for jets with pT < 1 TeV, all particle flow information 
// (i.e. tracks + muons and towers) is used
// for jets with pT > 1 TeV, only tracks (incl. muons) are used to 
// reconstruct track-jet mass, and then scaling correction is applied 
// m_jet = m_track * p_jet/p_track
double PFlowJet::JetMass(){
	TLorentzVector pTrack = jetP4.track;
	TLorentzVector pTotal = pTrack + jetP4.tower;
	double JetPT = pTotal.Pt() ;
	if (JetPT < 1000.) 
		return pTotal.M();
	return pTrack.M() * JetPT/pTrack.Pt();
}

//return pT of the jet
double PFlowJet::pT(){
  TLorentzVector pTotal = jetP4.track + jetP4.tower;
  return pTotal.Pt();	
}

// Calculate N-subjettiness variable tau_3/tau_2
/// for jets with pT < 1 TeV, all particle flow info is used 
/// for jets with pT > 1 TeV, only track info is used
double PFlowJet::tau32(){
  double jetPT = pT(); 
  double R = 1.5; // include everything 
  fastjet::JetDefinition jetdef = 
				fastjet::JetDefinition(fastjet::antikt_algorithm, R);
  std::vector <fastjet::PseudoJet> input; input.clear();
  if (jetPT < 1000.) input = PFjetConsts;
  else input = tracks;
  if (input.empty()) return -1.; 
  fastjet::ClusterSequence clust_seq(input,jetdef);
  std::vector<fastjet::PseudoJet> incl_jets  
						= sorted_by_pt(clust_seq.inclusive_jets());
  if (incl_jets.empty()) return -1.;
  double beta = 2.7;
  fastjet::contrib::NsubjettinessRatio nSub32(3,2, 
							fastjet::contrib::OnePass_WTA_KT_Axes(), 
							fastjet::contrib::UnnormalizedMeasure(beta));
  return nSub32(incl_jets[0]);
}


} // end namespace analysis
