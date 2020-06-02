////////////////////////////////////////////////////////////////////////////////
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <iostream>

void TTbarAnalysis::define_histograms()
{
  // HISTOGRAMS

  // Global histograms
  hist_etmiss       = new TH1F("hist_etmiss",      "Missing Transverse Momentum;E_{T}^{miss} [GeV];Events / bin", 20, 0, 300);
  hist_mtw          = new TH1F("hist_mtw",         "Transverse Mass; M^{W}_{T} [GeV];Events / bin", 20, 0, 300);

  // Leading Lepton histograms
  hist_leadleptpt   = new TH1F("hist_leadleptpt",  "Leading Lepton Transverse Momentum;p_{T}^{leadlep} [GeV];Events / bin", 20, 0, 200);
 
  hist_leadlepteta  = new TH1F("hist_leadlepteta", "Leading Lepton Pseudorapidity; #eta^{leadlep}; Events / bin", 30, -3, 3);
  hist_leadleptE    = new TH1F("hist_leadleptE",   "Leading Lepton Energy; E^{leadlep} [GeV]; Events / bin", 30, 0, 300);
  hist_leadleptphi  = new TH1F("hist_leadleptphi", "Leading Lepton Azimuthal Angle ; #phi^{leadlep}; Events / bin", 32, -3.2, 3.2);
  hist_leadleptch   = new TH1F("hist_leadleptch",  "Leading Lepton Charge; Q^{leadlep}; Events / bin", 7, -1.75, 1.75);
  hist_leadleptID   = new TH1F("hist_leadleptID",  "Leading Lepton Absolute PDG ID; |PDG ID|^{leadlep}; Events / bin",  15, 5.5, 20.5);
  hist_leadlept_ptc  = new TH1F("hist_leadlept_ptc", "Leading Lepton Relative Transverse Momentum Isolation; ptconerel30^{leadlep}; Events / bin", 20, -0.1, 0.2);
  hist_leadleptetc  = new TH1F("hist_leadleptetc", "Leading Lepton Relative Transverse Energy Isolation; etconerel20^{leadlep}; Events / bin", 20, -0.1, 0.2);
  hist_leadlepz0    = new TH1F("hist_leadlepz0",   "Leading Lepton z0 impact parameter; z_{0}^{leadlep} [mm]; Events / bin", 20, -1, 1);
  hist_leadlepd0    = new TH1F("hist_leadlepd0",   "Leading Lepton d0 impact parameter; d_{0}^{leadlep} [mm]; Events / bin", 20, -0.2, 0.2);
}

////////////////////////////////////////////////////////////////////////////////
void TTbarAnalysis::FillOutputList()
{
  // histograms

  // Add Global histograms
  GetOutputList()->Add(hist_etmiss);
  GetOutputList()->Add(hist_mtw);

  // Add Leading Lepton histograms
  GetOutputList()->Add(hist_leadleptpt);
  GetOutputList()->Add(hist_leadlepteta);
  GetOutputList()->Add(hist_leadleptE);
  GetOutputList()->Add(hist_leadleptphi);
  GetOutputList()->Add(hist_leadleptch);
  GetOutputList()->Add(hist_leadleptID);
  GetOutputList()->Add(hist_leadlept_ptc);
  GetOutputList()->Add(hist_leadleptetc);
  GetOutputList()->Add(hist_leadlepz0);
  GetOutputList()->Add(hist_leadlepd0);

}

////////////////////////////////////////////////////////////////////////////////
void TTbarAnalysis::WriteHistograms()
{
  // histograms

  // Write Global histograms
  hist_etmiss->Write();
  hist_mtw->Write();

  // Write Leading Lepton histograms
  hist_leadleptpt->Write();
  hist_leadlepteta->Write();
  hist_leadleptE->Write();
  hist_leadleptphi->Write();
  hist_leadleptch->Write();
  hist_leadleptID->Write();
  hist_leadlept_ptc->Write();
  hist_leadleptetc->Write();
  hist_leadlepz0->Write();
  hist_leadlepd0->Write();

}

void TTbarAnalysis::FillHistogramsGlobal( double m, float w , TString s)
{
  //Fill Global histograms
  if (s.Contains("hist_etmiss")) hist_etmiss->Fill(m,w);
  if (s.Contains("hist_mtw")) hist_mtw->Fill(m,w);

}

void TTbarAnalysis::FillHistogramsTTbar( double m, float w , TString s)
{
}



void TTbarAnalysis::FillHistogramsLeadlept( double m, float w , TString s)
{
  //Leading lepton histograms
  if (s.Contains("hist_leadleptpt")) hist_leadleptpt->Fill(m,w);
  if (s.Contains("hist_leadlepteta")) hist_leadlepteta->Fill(m,w);
  if (s.Contains("hist_leadleptE")) hist_leadleptE->Fill(m,w);
  if (s.Contains("hist_leadleptphi")) hist_leadleptphi->Fill(m,w);
  if (s.Contains("hist_leadleptch")) hist_leadleptch->Fill(m,w);
  if (s.Contains("hist_leadleptID")) hist_leadleptID->Fill(m,w);
  if (s.Contains("hist_leadlept_ptc")) hist_leadlept_ptc->Fill(m,w);
  if (s.Contains("hist_leadleptetc")) hist_leadleptetc->Fill(m,w);
  if (s.Contains("hist_leadlepz0")) hist_leadlepz0->Fill(m,w);
  if (s.Contains("hist_leadlepd0")) hist_leadlepd0->Fill(m,w);
}


void TTbarAnalysis::FillHistogramsLeadJet( double m, float w , TString s)
{
}


////////////////////////////////////////////////////////////////////////////////
