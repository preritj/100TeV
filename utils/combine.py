#!/usr/bin/env python
import config, processes
import glob, os, subprocess, sys
from ROOT import gROOT, TFile, TH1F, TCanvas, TVector

paths = config.paths

Hist1D = ["jet_pt_1", "jet_pt_2", "jet_pt_3", "jet_pt_4",
				"MET", "MET_1tag", "MET_2tag",
				"HT", "HT_1tag", "HT_2tag",
				"mu_pt", "z"]

Hist2D = ["MET_HT", "MET_HT_1tag", "MET_HT_2tag"]

Cuts = ["Total", "HT cuts", "MET cuts", "Jet Cuts", 
		"lepton Cuts", "dPhi Cuts", "One Top Tag", "Two Top Tags"]

class CombineRoots:

	def __init__(self , norm=None):
		self.Files = []
		self.norm = norm
		self.Hist = {}
		self.CutFlow = None

	def SetNorm(norm):
		self.norm=norm

	def AddFile(self, RootFile):
		self.Files.append(RootFile)

	def Combine(self):
		for file in self.Files: 
			f = TFile(file, "read")
			CutFlow = f.Get("CutFlow")
			# combine histograms
			for hist in (Hist1D + Hist2D):
				h = f.Get(hist) # retrieve histogram from file
				h.SetDirectory(0) # detach histogram from file
				if not hist in self.Hist.keys() :
					self.Hist[hist] = h
				else :
					self.Hist[hist].Add(h)
			# combine cutflow
			if self.CutFlow == None:
				self.CutFlow = CutFlow
			else :
				for i in range(len(Cuts)):
					self.CutFlow[i] = self.CutFlow[i] + CutFlow[i]
			f.Close()
		# preform normalizations for histograms and cutflow :
		if self.norm :
			scale = self.norm/self.CutFlow[0]
			for hist in Hist1D+Hist2D:
				self.Hist[hist].Scale(scale)	
			for i in range(len(Cuts)):
				self.CutFlow[i] = self.CutFlow[i]*scale

	def WriteFile(self, OutFile):
		f_out = TFile(OutFile, "recreate")
		for hist in Hist1D+Hist2D:
			self.Hist[hist].Write()
		self.CutFlow.Write("CutFlow")
		f_out.Close()

	def Print(self):
		saves=[]
		c={}
		for i in range(len(Cuts)):
			print Cuts[i] +" : "+str(self.CutFlow[i])
		for hist in Hist1D:
			c[hist] = TCanvas()
			self.Hist[hist].Draw()
			c[hist].Update()
		for hist in Hist2D:
			c[hist] = TCanvas()
			self.Hist[hist].Draw("COLZ")
			c[hist].Update()
 		raw_input() 


def CombineEvents(process, bin, luminosity=1.):
	# events = xsec (in pb) x luminosity (in ifb) * 1000
	norm = luminosity * 1000. * processes.xs[process][bin]
	DIR = os.path.join(paths['OutDIR'] , process , bin)
	# exit if input directory does not exist
	if not os.path.exists(DIR):
		print "Did not find : " + DIR
		return
	OutFile = os.path.join(DIR, "combined.root")
	# remove combined root file if one already exists
	if os.path.isfile(OutFile):
		os.remove(OutFile) 
	# make a list of all root files 
	Files = glob.glob(os.path.join(DIR , "*.root"))
	# exit if no root files present
	if not Files:
		print "No root files found in " + DIR
		return
	comb = CombineRoots(norm)
	for file in Files:
		comb.AddFile(file)
		comb.Combine()
		comb.WriteFile(OutFile)

def CombineBins(process):
	xs = processes.xs[process]
	DIR = os.path.join(paths['OutDIR'] , process)
	if not os.path.exists(DIR):
		print "Did not find : " + DIR
		print "Aborting... "
		sys.exit()
	OutFile = os.path.join(DIR, "combined.root")
	# remove combined root file if one already exists
	if os.path.isfile(OutFile):
		os.remove(OutFile) 
	comb = CombineRoots(None)	
	for bin in xs :
		InFile = os.path.join(DIR , bin, "combined.root")
		if not os.path.isfile(InFile):
			print "Did not find the file : " + InFile
			continue
		else :
			comb.AddFile(InFile)
	comb.Combine()
	comb.WriteFile(OutFile)
	comb.Print()	
		
		

#debug
if __name__ == "__main__":
	#CombineEvents("ttB", "9000-100000", 3000)
	CombineBins("ttB")

