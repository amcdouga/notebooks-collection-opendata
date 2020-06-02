/////////////////////////////////////////////////////////////
//// TTbarAnalysis code
//// Author: ATLAS Collaboration (2019)
////
////
//// DISCLAIMER:
//// This Software is intended for educational use only!
//// Under no circumstances does it qualify to reproduce actual ATLAS analysis results or produce publishable results!
/////////////////////////////////////////////////////////////

#define TTbarAnalysis_cxx

#include "TTbarAnalysis.h"
#include "TTbarAnalysisHistograms.h"
#include <iostream>
#include <cstring>
#include <string>

#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TRandom3.h>

string name;

void TTbarAnalysis::Begin(TTree * )
{

  nEvents=0;
  sumWeightall=0.;
  sumWeightselected=0.;

}

void TTbarAnalysis::SlaveBegin(TTree * )
{
  TString option = GetOption();
  printf("Starting analysis with process option: %s \n", option.Data());
  
  name=option;
  
  define_histograms();
  
  FillOutputList();
}

Bool_t TTbarAnalysis::Process(Long64_t entry)
{

  // allow for only reading a part of the data
  Int_t nmax = fChain->GetTree()->GetEntries()/20;
  if (nEvents > nmax) return kTRUE;

  fChain->GetTree()->GetEntry(entry);
  nEvents++;
  if (nEvents % 50000 == 0) std::cout << "Analysed a total of: " << nEvents << " events out of " << fChain->GetTree()->GetEntries() << " in this sample" << std::endl;
  
  if(fChain->GetTree()->GetEntries()>0)
    {
      // **********************************************************************************************//
      // Begin analysis selection, largely based on: ATLAS Collaboration, JHEP 11 (2017) 191           //
      // **********************************************************************************************//
      
      //Scale factors (adding b-tagging as it is used)
      Float_t scaleFactor = scaleFactor_ELE*scaleFactor_MUON*scaleFactor_LepTRIGGER*scaleFactor_PILEUP*scaleFactor_BTAG;

      //MC weight
      Float_t m_mcWeight = mcWeight;

      // read input option
      TString option = GetOption();
      if(option.Contains("single")) { m_mcWeight = (mcWeight/TMath::Abs(mcWeight)); } // set to 1 or -1 for single top MCs

      //Total weight
      Float_t weight = scaleFactor*m_mcWeight;

      // Make difference between data and MC
      if(option.Contains("data")) {  weight = 1.; }
      
      sumWeightall+=weight;

// start lepton selection code

      // Preselection cut for electron/muon trigger, Good Run List, and good vertex
      if(trigE || trigM)
        {

	  // Preselection of good leptons
	  int goodlep_index =0;
	  int goodlep_n = 0;
	  int lep_index =0;
	  
	  for(unsigned int i=0; i<lep_n; i++)
	    {
              TLorentzVector leptemp;  leptemp.SetPtEtaPhiE(lep_pt->at(i)/1000., lep_eta->at(i), lep_phi->at(i), lep_E->at(i)/1000.);

	      // Lepton is Tight
	      if( lep_isTightID->at(i) )
		{
		  // Lepton is isolated and hard pT
		  if( lep_pt->at(i) > 25000. && ( (lep_ptcone30->at(i)/lep_pt->at(i)) < 0.15) && ( (lep_etcone20->at(i) / lep_pt->at(i)) < 0.15 ) )
		    {
		      // electron selection in fiducial region excluding candidates in the transition region between the barrel and endcap electromagnetic calorimeters
		      if ( lep_type->at(i)==11 && TMath::Abs(lep_eta->at(i)) < 2.47 && ( TMath::Abs(lep_eta->at(i)) < 1.37 || TMath::Abs(lep_eta->at(i)) > 1.52 ) ) {
			if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 5 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
			  goodlep_n = goodlep_n + 1;
			  goodlep_index = i;
			  lep_index++;
			}
		      }
		      // muon selection
		      if ( lep_type->at(i) == 13 && TMath::Abs(lep_eta->at(i)) < 2.5 ) {
			if( TMath::Abs(lep_trackd0pvunbiased->at(i))/lep_tracksigd0pvunbiased->at(i) < 3 && TMath::Abs(lep_z0->at(i)*TMath::Sin(leptemp.Theta())) < 0.5) {
			  
			  goodlep_n = goodlep_n + 1;
			  goodlep_index = i;
			  lep_index++;
			}
		      }
		    }
		}
	    } // end for loop over leptons

        //Exactly one good lepton
        if(goodlep_n==1)
          {

        // Select non-zero missing ET
           if (met_et > 20000.)
             {

               // event is selected!
               sumWeightselected+=weight;

               // TLorentzVector definitions
               TLorentzVector Lepton_1  = TLorentzVector();
	       TLorentzVector      MeT  = TLorentzVector();
	    
               // nominal values		      
	       Lepton_1.SetPtEtaPhiE(lep_pt->at(goodlep_index), lep_eta->at(goodlep_index), lep_phi->at(goodlep_index),lep_E->at(goodlep_index));
	       MeT.SetPtEtaPhiE(met_et, 0, met_phi , met_et);

               //Calculation of MTW
               float mtw = sqrt(2*Lepton_1.Pt()*MeT.Et()*(1-cos(Lepton_1.DeltaPhi(MeT))));

	       ///////// SAVE HISTOGRAMS /////////
				  
               double names_of_global_variable[]={met_et/1000.,mtw/1000.};
               TString histonames_of_global_variable[]={"hist_etmiss","hist_mtw"};

               int length_global = sizeof(names_of_global_variable)/sizeof(names_of_global_variable[0]);
               for (int i=0; i<length_global; i++)
                  {
                    FillHistogramsGlobal( names_of_global_variable[i], weight, histonames_of_global_variable[i]);
                  }

               double ptc = lep_ptcone30->at(goodlep_index)/lep_pt->at(goodlep_index);
               double etc = lep_etcone20->at(goodlep_index)/lep_pt->at(goodlep_index);
               double z0 = lep_z0->at(goodlep_index);
               double d0 = lep_trackd0pvunbiased->at(goodlep_index);
 
	       double names_of_leadlep_variable[]={Lepton_1.Pt()/1000., Lepton_1.Eta(), Lepton_1.E()/1000., Lepton_1.Phi(), (double)lep_charge->at(goodlep_index), (double)lep_type->at(goodlep_index), ptc, etc, z0, d0};
				  
	       TString histonames_of_leadlep_variable[]={"hist_leadleptpt", "hist_leadlepteta","hist_leadleptE","hist_leadleptphi","hist_leadleptch","hist_leadleptID","hist_leadlept_ptc","hist_leadleptetc","hist_leadlepz0","hist_leadlepd0"};
				  
	       int length_leadlep = sizeof(names_of_leadlep_variable)/sizeof(names_of_leadlep_variable[0]);
				  
	       for (int i=0; i<length_leadlep; i++)
	         {
	           FillHistogramsLeadlept( names_of_leadlep_variable[i], weight, histonames_of_leadlep_variable[i]);
	         }
              } // end MET selection

          } //end 1 good lepton

        } // end trigger requirement
        
// end lepton selection code

    } //end of analysis code for this event
  return kTRUE;
}

void TTbarAnalysis::SlaveTerminate()
{
}

void TTbarAnalysis::Terminate()
{

  std::cout << "Sum of all weights: " << sumWeightall << std::endl;
  std::cout << "Sum of weights selected events: " << sumWeightselected << std::endl;
  sumWeightall=0.;
  sumWeightselected=0.;

  TString filename_option = GetOption();
  printf("Writting with name option: %s \n", filename_option.Data());
  TString output_name="Output_TTbarAnalysis/"+filename_option+".root";
  const char* filename = output_name;

  TFile physicsoutput_TTbar(filename,"recreate");
  WriteHistograms();
  physicsoutput_TTbar.Close();
}
