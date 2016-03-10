#ifndef Analysis_h
#define Analysis_h
class Analysis{
  private :
  	Int_t entry;
  	float weight;
  	bool IsHist, IsWeighted, IsEventPass;
  	ExRootTreeReader *treeReader;
  	Long64_t numberOfEntries;
  	Plots* plots;
    TFile *file;
  	TClonesArray *branchEvent, *branchJet, *branchMuon; 
  	TClonesArray *branchParticle, *branchIsoMuon, *branchIsoEl;
  	TClonesArray *branchMissingET, *branchScalarHT;
  	vector <float> CutFlow, MuonPT; 
  	vector <string> CutName; 
    int CutFlowIt;
    float zVar;
	bool IsHTcuts, IsMETcuts;
    bool IsJetCuts, IsZCuts, IsDphiCuts, IsWriteOutput; 
    bool IsTopTagOne, IsTopTagTwo, IsLepCuts;
  public :
  	Analysis(ExRootTreeReader*); 
  	void WeightsOn(), WeightsOff();
  	void DrawHist(), BookHist(), FillHist(), PrintHist();
  	void LoadEvent(), CutFlowUpdate(), PrintCutFlow() ;
    void TopTag(), CalcZ(), ApplyJetCuts(), ApplyZCuts();
    void Run(), ApplyTopTagOne(), ApplyTopTagTwo();
    void ApplyLepCuts(), ApplyDphiCuts();
	void ApplyHTcuts(), ApplyMETcuts();
    void FillHist_MET(int), FillHist_HT(int), FillHist_MET_HT(int);
    void DrawHist(TH2*), DrawHist(TH1*), WriteOutput(const char*);
  	bool JetCuts(), TopTagOne(), TopTagTwo();
	bool HTcuts(), METcuts();
    bool ZCuts(), LepCuts(), DphiCuts();
  	void GenMuonTag(int), CheckMuJets(int);
	void IsoMuonTag(int),  JetMuonTag(int);	
};
#endif
