{
	// Read varian data

	fstream file;
	file.open("6FFF_Depth10_Size10.txt", ios::in);

	TGraph *gr = new TGraph();

	while(1)
	{
		double x, y;

		file >> x >> y;
		gr->SetPoint(gr->GetN(), x, y);

		if(file.eof()) break;
	}

	file.close();

	TCanvas *c1 = new TCanvas();
	gr->Draw("ALP");
}