void Analysis::DrawHist(){
	IsHist=true;
	BookHist();
}

void Analysis::BookHist(){
  plots = new Plots;
  plots->h_JetPT[0]     = new TH1F("jet_pt_1", "j_{1} p_{T}", 40, 300.,5300.);
  plots->h_JetPT[1]     = new TH1F("jet_pt_2", "j_{2} p_{T}", 32, 200.,4200.);
  plots->h_JetPT[2]     = new TH1F("jet_pt_3", "j_{3} p_{T}", 16, 100.,2100.);
  plots->h_JetPT[3]     = new TH1F("jet_pt_4", "j_{4} p_{T}", 16, 100.,2100.);
  plots->h_MET[0]       = new TH1F("MET", "MET", 16, 0., 4000.);
  plots->h_MET[1]       = new TH1F("MET_1tag", "MET", 16, 0., 4000.);
  plots->h_MET[2]       = new TH1F("MET_2tag", "MET", 16, 0., 4000.);
  plots->h_HT[0]        = new TH1F("HT", "HT", 40, 2000., 22000.);
  plots->h_HT[1]        = new TH1F("HT_1tag", "HT", 40, 2000., 22000.);
  plots->h_HT[2]        = new TH1F("HT_2tag", "HT", 40, 2000., 22000.);
  plots->h_MET_HT[0]    = new TH2F("MET_HT", "MET vs HT", 20, 0., 5000., 40, 3000., 23000.);
  plots->h_MET_HT[1]    = new TH2F("MET_HT_1tag", "MET vs HT", 20, 0., 5000., 40, 3000., 23000.);
  plots->h_MET_HT[2]    = new TH2F("MET_HT_2tag", "MET vs HT", 20, 0., 5000., 40, 3000., 23000.);
  plots->h_muPT         = new TH1F("mu_pt", "Leading muon p_{T}", 40, 0., 1000.);
  plots->h_z            = new TH1F("z", "z", 20, 0., 2.0);
}

//
void Analysis::FillHist(){
  //Fill jet pT histograms
  if (branchJet){
    int nJets = branchJet->GetEntriesFast();	
	if (nJets > 4) nJets=4;
    for(int i=0; i< nJets; i++){
      Jet *jet = (Jet*) branchJet->At(i); 
  	  plots->h_JetPT[i]->Fill(jet->PT, weight);
    }
  }
  //Fill MET histograms
  FillHist_MET(0);
  //Fill HT histograms
  FillHist_HT(0);
  // Fill MET & HT 2D histogram
  FillHist_MET_HT(0);
  //Fill leading muon pT
  plots->h_muPT->Fill(MuonPT[0], weight);
  //Fill z variable
  plots->h_z->Fill(zVar,weight); 
}

void Analysis::FillHist_MET_HT(int nTopTags){
  // Fill MET & HT 2D histogram
  if (branchMissingET && branchScalarHT){
    MissingET *met = (MissingET*) branchMissingET->At(0);
    ScalarHT *hT = (ScalarHT*) branchScalarHT->At(0);
    plots->h_MET_HT[nTopTags]->Fill(met->MET, hT->HT, weight);
  }	
}

void Analysis::FillHist_MET(int nTopTags){
  // Fill MET  histogram
  if (branchMissingET){
    MissingET *met = (MissingET*) branchMissingET->At(0);
    plots->h_MET[nTopTags]->Fill(met->MET, weight);
  }	
}

void Analysis::FillHist_HT(int nTopTags){
  // Fill HT histogram
  if (branchScalarHT){
    ScalarHT *hT = (ScalarHT*) branchScalarHT->At(0);
    plots->h_HT[nTopTags]->Fill(hT->HT, weight);
  }	
}
