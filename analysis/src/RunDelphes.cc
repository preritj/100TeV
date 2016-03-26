//========================================================
//
// Desciption : Delphes analysis for stop pair production 
// 				at future 100 TeV collider 
//
//     Author : Prerit Jaiswal
//
//========================================================


#include "StlHeaders.h" /// STL classes
#include "RootHeaders.h" /// ROOT classes
#include "Delphesheaders.h" /// Delphes classes

#include "Analysis.h"


//------------------------------------------------------------------------------
// Main Analysis

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
	std::cout << "Usage : RunDelphes <input_file> <output_file>" << std::endl;    		
	std::cout << "<input_file>  : root file with all the events" << std::endl;    		
	std::cout << "<output_file> : root file after analysis is run" << std::endl;  
    return EXIT_FAILURE; 
  } 


  /// get filenames		
  const std::string InputFile = argv[1];
  const std::string OutputFile = argv[2];


  /// Create chain of root trees
  TChain chain("Delphes");
  chain.Add(InputFile.c_str());


  /// Create object of class ExRootTreeReader
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);

  /// create object for analysis
  analysis::Analysis *an = new analysis::Analysis(treeReader, OutputFile);

  /// run analysis
  an->RunEvents();

  /// write output
  an->Write();

  delete an;
  delete treeReader;
  return EXIT_SUCCESS;
}

