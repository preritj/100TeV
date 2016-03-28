#include "PFlowJet.h"
namespace analysis{


PFlowJet::PFlowJet(const std::vector<fastjet::PseudoJet> & JetConsts){
  PFjetConsts = JetConsts;
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
		if (pJet.user_index() == 0) p.track += pConst;
		else if (pJet.user_index() == 1) p.tower += pConst;
		else if (pJet.user_index() == 2) {
			p.track += pConst;
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


} // end namespace analysis
