
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
	T->Add("../output/Seg1-out/myIAEA.root");

	T->SetBranchAddress("Ekine",&E);
 	T->SetBranchAddress("X",&x);
 	T->SetBranchAddress("Y",&y);
 	T->SetBranchAddress("Z",&z);
 	T->SetBranchAddress("dX",&dx);
 	T->SetBranchAddress("dY",&dy);
 	T->SetBranchAddress("dZ",&dz);
 	T->SetBranchAddress("Weight",&weight);


	TH2D *histoEmittanceXTheta;
	histoEmittanceXTheta = new TH2D("histoEmittanceXTheta", "Emittance X #theta",1000, -50, 50, 1000, -50, 50);

	TH2D *histoEmittanceZPhi;
	histoEmittanceZPhi = new TH2D("histoEmittanceZPhi", "Emittance Z #phi",1000, -50, 50, 1000, -50, 50);

	TH2D *histoSpotSize;
	histoSpotSize = new TH2D("histoSpotSize", "Spot",1000, -50, 50, 1000, -50, 50);

	TH1D *histoEnergy;
	histoEnergy = new TH1D("histoEnergy", "Energy",600, 0, 6);

	int n = T->GetEntries();
	cout<<"\nNb of particles in the PhS = "<<n<<endl;

	for (int i=0; i<n; i++)
	{   
		T->GetEntry(i);

		histoEmittanceXTheta->Fill(x,atan(dx/dy)*1000.,weight); // x-axis in mm and z-axis in mrad
		histoEmittanceZPhi->Fill(z,atan(dz/dy)*1000,weight);
		
		histoSpotSize->Fill(x,z,E);
		histoEnergy->Fill(E,weight);
	}

	// Plot
	gStyle->SetOptFit(1111);
	gStyle->SetPalette(1);

	TCanvas * fenetre1 = new TCanvas("fenetre1","fefe",1);

	fenetre1->Divide(2,2);

	fenetre1->cd(1);
	histoEmittanceXTheta->Draw("COLZ");

	fenetre1->cd(2);
	histoEmittanceZPhi->Draw("COLZ");

	fenetre1->cd(3);
	histoSpotSize->Draw("COLZ");

	fenetre1->cd(4);
	histoEnergy->Draw();

}
