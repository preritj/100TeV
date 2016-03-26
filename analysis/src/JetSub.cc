#include "JetSub.h"
namespace analysis{
//=======================================================


JetSub::JetSub(ExRootTreeReader *t_Reader){
  entry =0; /// event index 
  treeReader = t_Reader;
  branchCAJet        = treeReader->UseBranch("CAJet");
  branchTrack        = treeReader->UseBranch("EFlowTrack");
  branchTower        = treeReader->UseBranch("EFlowTower");
  branchEFlowMuon    = treeReader->UseBranch("EFlowMuon");
  branchParticle     = treeReader->UseBranch("Particle");
}
  
//=======================================================
} /// namespace analysis
