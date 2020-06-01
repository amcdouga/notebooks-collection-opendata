########################################################################################
#                                                                                      #
# 		A simple introductional notebook to HEP analysis in python             #
#	In this notebook you can find an easy set of commands that show the basic      #
#	computing techniques commonly used in high energy physics (HEP) analyzes.      #
#	It also shows how to create a histogram, fill it and draw it, using ROOT       #
#	(https://root.cern.ch/). ROOT is a scientific software framework that          #
#	provides all the functionalities needed to deal with big data processing,      #
#	statistical analysis, visualisation and storage.			       #
#										       #
# Run this script by typing:							       #
#       >> python A-simple-example.py						       #
#										       #
#	At the end you get a plot with the number of leptons.			       #
########################################################################################

#ROOT is imported to read the files in the .root data format.
import ROOT

# Here we open the data that we want to analyse, which is in the form of a .root file. A .root file consists of a tree having branches and leaves.
f = ROOT.TFile.Open("HZZ-analysis/Input/mc_105987.WZ.root")

# Define a 'canvas' on which to draw a histogram. Its name is "canvas" and its header is "plot a variable". The two following arguments define the width and the height of the canvas.
canvas = ROOT.TCanvas("canvas","plot a variable",800,600)

# Here we define a tree named "tree" to extract the data from the input .root file.
tree = f.Get("mini")
number_entries = tree.GetEntries()
print "Number of entries in the tree = ", number_entries

# Define a histogram. Its name is variable and the header of the histogram is "Example plot: Number of leptons". It's x and y axis labels are in the next 2 arguments. The three following arguments indicate that this histogram contains 5 bins which have a range from -0.5 to 4.5. 
hist = ROOT.TH1F("variable","Example plot: Number of leptons; Number of leptons; Events ",5,-0.5,4.5)

# Loop over the data (in the tree) and store it in the histogram.
#	Here you could place any cuts you want to apply, before filling the histogram
for event in tree:
    hist.Fill(tree.lep_n)

print "Histogram is filled" # Signifies the end of the event loop above
 
# Now want to draw the histogram, and set the fill colour
hist.SetLineColor(ROOT.kBlack) 
hist.SetLineWidth(2) 
hist.SetFillColor(ROOT.kAzure)
hist.Draw("HIST")

# Draw the canvas, which contains the histogram
canvas.Draw()

# The following lines allow the canvas to be displayed, 
#	until you press enter in the command line.
try:
    __IPYTHON__
except:
    raw_input('Press Enter to exit')

# Next we can also normalise the histogram (so the integral is 1), to allow us to see the proportions. By doing this, you can directly read of the y-axis what fraction of events fall into each bin. 
scale = hist.Integral()
hist.Scale(1/scale)

# Set some new colour settings for the histogram
hist.SetLineColor(ROOT.kBlack)
hist.SetLineWidth(2)          
hist.SetFillColor(ROOT.kViolet)

# Again we re-draw the histogram and canvas. 
hist.Draw("HIST")
canvas.Draw()

try:
    __IPYTHON__
except:
    raw_input('Press Enter to exit')

##############################################################################################################################################
#
#       Exercise to try: How could you select to have exactly 2 leptons (i.e. lep_n ==2) ? 
# 		You can check if you've done it correctly by looking at the resulting histograms. What do you expect will change? 
#		What do you notice about the number of entries in the histogram now? 
# 		*Hint*: There's a comment above indicating where in the code you should place your cuts. 
#
#	Bonus exercise: Can you try plotting another variable, instead of "number of leptons" 
#		e.g. What about the pT of the leptons? 
# 		*Hint*: the pT variable is labelled "" in the tree. 
#		You might also need to change the x-axis range of the histogram. 
#
##############################################################################################################################################
