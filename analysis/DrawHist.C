void Analysis::PrintHist(){
  TCanvas* c1 = new TCanvas;
  c1->Divide(2,2);
  // Plot pT of the 4 leading jets
  for(int i =0; i<4; i++){
    c1->cd(i+1);
    DrawHist(plots->h_JetPT[i]);
  }
  //c1->Print("Plot1.png");
  TCanvas* c2 = new TCanvas;
  c2->Divide(3,1);
  c2->cd(1);
  DrawHist(plots->h_MET[0]);
  c2->cd(2);
  DrawHist(plots->h_HT[0]);
  c2->cd(3);
  DrawHist(plots->h_MET_HT[0]);
  //c2->Print("Plot2.png");
  TCanvas* c3 = new TCanvas;
  c3->Divide(2,1);
  c3->cd(1);
  DrawHist(plots->h_muPT);
  c3->cd(2);
  DrawHist(plots->h_z);
  //c3->Print("Plot3.png");
  if (IsWriteOutput){
    DrawHist(plots->h_MET[1]);
    DrawHist(plots->h_MET[2]);
    DrawHist(plots->h_HT[1]);
    DrawHist(plots->h_HT[2]);
    DrawHist(plots->h_MET_HT[1]);
    DrawHist(plots->h_MET_HT[2]);
  }
}  

void Analysis::DrawHist(TH1* hist){
  //float scale = norm/hist->Integral();
  //hist->Scale(scale);
  if (IsWriteOutput) hist->Write();
  else hist->Draw();
}

void Analysis::DrawHist(TH2* hist){
  //float scale = norm/hist->Integral();
  //hist->Scale(scale);
  gStyle->SetPalette(1);
  if (IsWriteOutput) hist->Write();
  else hist->Draw("COLZ");
}
