########################################################################################
#
# 		A simple introductional notebook to HEP analysis in python
#	In this notebook you can find an easy set of commands that show the basic 
	computing techniques commonly used in high energy physics (HEP) analyzes. 
	It also shows how to create a histogram, fill it and draw it, using ROOT 
	(https://root.cern.ch/). ROOT is a scientific software framework that 
	provides all the functionalities needed to deal with big data processing, 
	statistical analysis, visualisation and storage.
########################################################################################

#ROOT is imported to read the files in the .root data format.
import ROOT

# .root file consists of a tree having branches and leaves.
f = ROOT.TFile.Open("/Users/ashleymcdougall/Desktop/notebooks-collection-opendata/HZZ-analysis/Input/mc_105987.WZ.root")

canvas = ROOT.TCanvas("Canvas","a first way to plot a variable",800,600)

tree = f.Get("mini")
number_entries = tree.GetEntries()
print "Number of entries in the tree = ", number_entries

hist = ROOT.TH1F("variable","Example plot: Number of leptons; Number of leptons ; Events ",5,-0.5,4.5)

for event in tree:
    hist.Fill(tree.lep_n)
   
hist.SetLineColor(ROOT.kBlack) 
hist.SetLineWidth(2) 
hist.SetFillColor(ROOT.kAzure)
hist.Draw("HIST")
canvas.Print()

try:
    __IPYTHON__
except:
    raw_input('Press Enter to exit')

scale = hist.Integral()
hist.Scale(1/scale)
hist.SetLineColor(ROOT.kBlack)
hist.SetLineWidth(2)          
hist.SetFillColor(ROOT.kViolet)
hist.Draw("HIST")
canvas.Draw()

try:
    __IPYTHON__
except:
    raw_input('Press Enter to exit')

