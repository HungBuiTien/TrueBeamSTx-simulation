{
  float E;
  float x, y, z;
  float dx, dy, dz;
  float weight;
  char volumeName[64];
  char particleName[64];
  char procName[64];

  TChain *  T = new TChain("PhaseSpace");

  // select one of the four following phase spaces you wish to visualize:
  T->Add("phsp/10x10_1E9.root");

  T->SetBranchAddress("ParticleName",&particleName);
  T->SetBranchAddress("ProductionVolume",&volumeName);
  T->SetBranchAddress("CreatorProcess",&procName);
  T->SetBranchAddress("Ekine",&E);
  T->SetBranchAddress("X",&x);
  T->SetBranchAddress("Y",&y);
  T->SetBranchAddress("Z",&z);
  T->SetBranchAddress("dX",&dx);
  T->SetBranchAddress("dY",&dy);
  T->SetBranchAddress("dZ",&dz);
  T->SetBranchAddress("Weight",&weight);
 
  TH2D *histoEmittanceXTheta;
  histoEmittanceXTheta = new TH2D("histoEmittanceXTheta", "Emittance X #theta",200, -50, 50, 200, -50, 50);

  TH2D *histoEmittanceYPhi;
  histoEmittanceZPhi = new TH2D("histoEmittanceZPhi", "Emittance Z #phi",200, -50, 50, 200, -50, 50);

  TH2D *histoSpotSize;
  histoSpotSize = new TH2D("histoSpotSize", "Spot", 400, -200, 200, 400, -200, 200);

  TH1D *histoEnergy;
  histoEnergy = new TH1D("Energy spectrum", "Energy", 1200, 0, 6);

  // get entries
  int n = T->GetEntries();
  cout<<"\nNb of particles in the PhS = "<<n<<endl;

  for (int i=0; i<n; i++)
  {   
    T->GetEntry(i);
    histoEmittanceXTheta->Fill(x,atan(dx/dy)*1000.,weight); // x-axis in mm and z-axis in mrad
    histoEmittanceZPhi->Fill(z,atan(dz/dy)*1000,weight);
    histoSpotSize->Fill(x,z,weight);
    histoEnergy->Fill(E,weight);
  }
  gStyle->SetOptFit(1111);
  gStyle->SetPalette(1);

  ///
  ///      Set-up plotting
  ///

  // Define a canvas and set the dimension
  Double_t w = 1200;
  Double_t h = 800;
  TCanvas * fenetre1 = new TCanvas("fenetre1","fefe", w, h);
  fenetre1->SetWindowSize(w + (w - fenetre1->GetWw()), h + (h - fenetre1->GetWh())); // set dimension
  fenetre1->Divide(2,2); // sub-plot set-up

  fenetre1->cd(1);
  histoEmittanceXTheta->Draw("COLZ");
  fenetre1->cd(2);
  histoEmittanceZPhi->Draw("COLZ");
  fenetre1->cd(3);
  histoSpotSize->Draw("COLZ");
  fenetre1->cd(4);
  histoEnergy->Draw();
}
