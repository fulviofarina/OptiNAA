
#include <math.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <process.h>



#define ML 250 // # MAX LINES POSSIBLE TO HANDLE
#define MR 100 // # MAX RATIOS from ITER
#define M5 235.0439
#define M8 238.0508
#define YTe 0.04312
#define lTe 1.4765405175527124007694958279187E-4
#define g 7.9459459459459459459459459459459 //ratio between gTe and gNp
#define sigma58 218.28358208955223880597014925373 // ratio cross sections 5 vs 8

#pragma once

namespace optinaa {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;



#pragma region Structures

struct isodata
	{
		
		string Iso,Sym,meas,channel,ID;
		
		double Eres,Eresfis,Qo1,Qo2,Qofis;
		double Fc,f,alfa,Ge,Gt;
		char ENAA, fis;
		double R[3];

		double T2,T3,T4,F1,F2,F3,F4,Cd,L2,L3,L4,ti,tc,td;
		int MD;
		double T[6];

		double counts,BG,unc,Energy,ro,ro2,res,mass;
		int pos,line;

		double Np[ML][5],Npunc[ML][5],Ro[ML][5],Rounc[ML][5];
		double E[ML],Ko[ML],Kounc[ML];
		double Yield[ML],Code[ML];
		string Quote[ML];
		
		double COI[ML][5],Effi[ML][5];
		
		double match,tries,frq,factor;
		int index;

		double eta;

};



struct enrichment
	{
		string sample;
		string time;
		double ratio;
		int outlier;
		int total;
		double ro5, ro8, sd5, sd8;
		double theta5;
		double theta8;
		double sd;
		double ro;
		double band;
		double M;
		double sd_obs;
		double k;
		double conf;
		double chi2;
		char const *timestring;
	};

struct isodata F[ML];
struct isodata NF[ML];
struct isodata *pF[ML];
struct isodata *pNF[ML];
struct enrichment Ratio[MR];
struct enrichment *pRatio[MR];
struct enrichment Rat;
struct enrichment *pRat;
struct isodata gen;
struct isodata *pp;

#pragma endregion

// Constants and variables
int anc=0,irs=0,wir=0,res=0,np=0,raw=0,recommended=0;
int panic=0;
double theta5_nat=0.00720;
double theta8_nat=0.99275;
double ratio_nat=(theta5_nat/theta8_nat);
double M_nat=(theta5_nat*M5) + (theta8_nat*M8);
double MW_U=0;
double MW_Fis=0;
string samp;



	public ref class Form1 : public System::Windows::Forms::Form
	{


	

	public: Form1(void)
			{
				InitializeComponent();
			}
	protected: 	~Form1()
				{
					if (components)
					{
						delete components;
					}
				}
	



#pragma region Form Objects

public: System::Windows::Forms::Button^  go_Header;
public: System::String^ header, ^labelname,^sample, ^root;
	public: System::Windows::Forms::OpenFileDialog^  FileDialog_KPG;
	public: System::Windows::Forms::TextBox^  HeaderBox;
	public: System::Windows::Forms::GroupBox^  groupBox_Samples_List;
	public: System::Windows::Forms::TextBox^  Box_Samples_List;
	private: System::Windows::Forms::TextBox^  Gth;
	private: System::Windows::Forms::TextBox^  Gepi;
	private: System::Windows::Forms::TextBox^  ENAA;
	private: System::Windows::Forms::TextBox^  ti;
	private: System::Windows::Forms::Label^  label_Gth;
	private: System::Windows::Forms::Label^  label_Gepi;
	private: System::Windows::Forms::Label^  label_irradiation_time;
	private: System::Windows::Forms::Label^  label_ENAA;
	private: System::Windows::Forms::Button^  go_KPG_Import;
	private: System::Windows::Forms::CheckBox^  ancBox1;
	private: System::Windows::Forms::TextBox^  Sample1;
	private: System::Windows::Forms::TextBox^  Sample2;
	private: System::Windows::Forms::TextBox^  Sample3;
	private: System::Windows::Forms::TextBox^  Sample4;
	private: System::Windows::Forms::TextBox^  Sample5;
	private: System::Windows::Forms::TextBox^  Sample6;
	private: System::Windows::Forms::CheckBox^  ancBox2;
	private: System::Windows::Forms::CheckBox^  ancBox3;
	private: System::Windows::Forms::CheckBox^  ancBox4;
	private: System::Windows::Forms::CheckBox^  ancBox5;
	private: System::Windows::Forms::CheckBox^  ancBox6;
	private: System::Windows::Forms::Button^  batch;
	private: System::Windows::Forms::Button^  go_ANC;
	private: System::Windows::Forms::GroupBox^  groupBox_Import;
	private: System::Windows::Forms::GroupBox^  groupBox_ANC;
	private: System::Windows::Forms::GroupBox^  groupBox_Samples_TODO;
	private: System::Windows::Forms::TextBox^  WIR;
	private: System::Windows::Forms::TextBox^  U235;
	private: System::Windows::Forms::TextBox^  U238;
	private: System::Windows::Forms::TextBox^  RO;
	private: System::Windows::Forms::Label^  label_WIR;
	private: System::Windows::Forms::Label^  label_U235;
	private: System::Windows::Forms::Label^  label_U238;
	private: System::Windows::Forms::Label^  label_RO;
	private: System::Windows::Forms::TextBox^  SD;
	private: System::Windows::Forms::Label^  label_SD;
	private: System::Windows::Forms::Label^  quoteU;
	private: System::Windows::Forms::GroupBox^  groupBox_Results;
	private: System::Windows::Forms::Label^  label_AW;
	private: System::Windows::Forms::TextBox^  AW;
	private: System::Diagnostics::Process^  process;
	private: System::Windows::Forms::Button^  edit_anc;
	private: System::Windows::Forms::OpenFileDialog^  FileDialog_Header;
	private: System::Windows::Forms::Button^  go_KPG_browse;
	private: System::Windows::Forms::TextBox^  KPGBox;
	private: System::Windows::Forms::GroupBox^  groupBox_Header;
	private: System::Windows::Forms::LinkLabel^  help_ANC;
	private: System::Windows::Forms::LinkLabel^  linkLabel4;
	private: System::Windows::Forms::RichTextBox^  LOG;
	private: System::Windows::Forms::GroupBox^  groupBox_Results_Data;
	private: System::Windows::Forms::Label^  label_RO5;
	private: System::Windows::Forms::TextBox^  RO5;
	private: System::Windows::Forms::Label^  label_RO8;
	private: System::Windows::Forms::TextBox^  RO8;
private: System::Windows::Forms::Button^  edit_raw;
	private: System::Windows::Forms::Button^  go_KPG_view;
	private: System::Windows::Forms::Label^  label_step1;
	private: System::Windows::Forms::Label^  label_step0;
private: System::Windows::Forms::GroupBox^  groupBox_IRS;
private: System::Windows::Forms::LinkLabel^  help_IRS;
private: System::Windows::Forms::Button^  edit_irs;
private: System::Windows::Forms::Button^  go_IRS;
	private: System::Windows::Forms::CheckBox^  irsBox1;
	private: System::Windows::Forms::CheckBox^  irsBox2;
	private: System::Windows::Forms::CheckBox^  irsBox3;
	private: System::Windows::Forms::CheckBox^  irsBox4;
	private: System::Windows::Forms::CheckBox^  irsBox5;
	private: System::Windows::Forms::CheckBox^  irsBox6;
private: System::Windows::Forms::GroupBox^  groupBox_RES;
private: System::Windows::Forms::Button^  edit_res;
private: System::Windows::Forms::LinkLabel^  help_RES;
	private: System::Windows::Forms::CheckBox^  resBox1;
private: System::Windows::Forms::Button^  go_RES;
	private: System::Windows::Forms::CheckBox^  resBox2;
	private: System::Windows::Forms::CheckBox^  resBox3;
	private: System::Windows::Forms::CheckBox^  resBox4;
	private: System::Windows::Forms::CheckBox^  resBox5;
	private: System::Windows::Forms::CheckBox^  resBox6;
private: System::Windows::Forms::GroupBox^  groupBox_WIR;
private: System::Windows::Forms::LinkLabel^  help_WIR;
	private: System::Windows::Forms::CheckBox^  wirBox1;
private: System::Windows::Forms::Button^  go_WIR;
private: System::Windows::Forms::Button^  edit_wir;
	private: System::Windows::Forms::CheckBox^  wirBox2;
	private: System::Windows::Forms::CheckBox^  wirBox3;
	private: System::Windows::Forms::CheckBox^  wirBox4;
	private: System::Windows::Forms::CheckBox^  wirBox5;
	private: System::Windows::Forms::CheckBox^  wirBox6;
private: System::Windows::Forms::GroupBox^  groupBox_228;
private: System::Windows::Forms::Button^  go_228;
	private: System::Windows::Forms::CheckBox^  NpBox1;
	private: System::Windows::Forms::CheckBox^  NpBox2;
	private: System::Windows::Forms::CheckBox^  NpBox6;
	private: System::Windows::Forms::CheckBox^  NpBox3;
	private: System::Windows::Forms::CheckBox^  NpBox5;
	private: System::Windows::Forms::CheckBox^  NpBox4;
	private: System::Windows::Forms::CheckBox^  rawBox1;
	private: System::Windows::Forms::CheckBox^  rawBox6;
	private: System::Windows::Forms::CheckBox^  rawBox5;
	private: System::Windows::Forms::CheckBox^  rawBox3;
	private: System::Windows::Forms::CheckBox^  rawBox4;
	private: System::Windows::Forms::CheckBox^  rawBox2;
private: System::Windows::Forms::LinkLabel^  link_author;
private: System::Windows::Forms::Label^  email_data;
private: System::Windows::Forms::Label^  author_data;
private: System::Windows::Forms::LinkLabel^  link_email;
	private: System::Windows::Forms::GroupBox^  author;
	private: System::Windows::Forms::Button^  LOG_Print;
	private: System::Windows::Forms::Button^  LOG_Clear;
	private: System::Windows::Forms::Label^  WSAMPLE;
	private: System::Windows::Forms::Label^  DT;
private: System::Windows::Forms::GroupBox^  groupBox_INFO;
private: System::Windows::Forms::Button^  tutorial;
private: System::Windows::Forms::LinkLabel^  help_Import;
private: System::Windows::Forms::LinkLabel^  help_Header;

private: System::Windows::Forms::LinkLabel^  help_228;
private: System::Windows::Forms::Button^  PANIC;
private: System::Windows::Forms::Label^  label_PANIC;

private: System::Windows::Forms::Label^  label_all;

private: System::Windows::Forms::Button^  all;
private: System::Windows::Forms::TextBox^  SDexp;

private: System::Windows::Forms::TextBox^  SDobs;
private: System::Windows::Forms::Label^  label_SDobs;
private: System::Windows::Forms::Label^  label_SDexp;

private: System::ComponentModel::IContainer^  components;

#pragma endregion

#pragma region Form Events

private: System::Void go_Header_Click(System::Object^  sender, System::EventArgs^  e) {
				
			 
			 FileDialog_Header->Filter = "OptiNAA Header (.h) |*.h";
				 FileDialog_Header->FilterIndex = 1;
				 FileDialog_Header->RestoreDirectory = true;

				 FileDialog_Header->ShowDialog(); 

			 }


private: System::Void go_KPG_Import_Click(System::Object^  sender, System::EventArgs^  e) {


						
		 
				 if (File::Exists(KPGBox->Text->ToString()))

				 {

				

				 string filetoimport;
				 string gth,gepi,tirr,enaa;

				MarshalString(Gth->Text->ToString(), gth);
				MarshalString(Gepi->Text->ToString(), gepi);
				MarshalString(ENAA->Text->ToString(), enaa);
				MarshalString(ti->Text->ToString(), tirr);
     			 MarshalString(KPGBox->Text->ToString(), filetoimport);

 HeaderBox->Clear();

				LOG->Text="\n----------------------------------------------------------------------------\n";
				LOG->Text+= "\nImporting Data from the KayZero PerGamma Report:\n\n";
				LOG->Text+= KPGBox->Text;
				LOG->Text+= "\n\nReading Data from Sample:\n\n";
				

				 pp=&gen;

				 Tools_KPG(pp,1,filetoimport,gth,gepi,enaa,tirr);


 	 LOG->Text= LOG->Text->ToString() + "\n----------------------------------------------------------------------------\n"	;

	 LOG->SaveFile(KPGBox->Text->Substring(0,	KPGBox->Text->Length::get()-4) + ".log.rtf");

	HeaderBox->Text=KPGBox->Text->Substring(0,	KPGBox->Text->Length::get()-4);	  

			
			

				 }

		


			 }




private: System::Void go_ANC_Click(System::Object^  sender, System::EventArgs^  e) {
				
			LOG->Text=LOG->Text->ToString() + "\n----------------------------------------------------------------------------\n";
	 		LOG->Text+= "Converting Apparent concentrations into natural-Uranium concentrations:\n\n";
			LOG->Text+= "\n\nReading Data from Sample:\n\n";
			
			go_ANC_Cases (ancBox1,irsBox1,wirBox1, resBox1,NpBox1, Sample1);
			go_ANC_Cases (ancBox2,irsBox2,wirBox2, resBox2,NpBox2, Sample2);
			go_ANC_Cases (ancBox3,irsBox3,wirBox3, resBox3,NpBox3, Sample3);
			go_ANC_Cases (ancBox4,irsBox4,wirBox4, resBox4,NpBox4, Sample4);
			go_ANC_Cases (ancBox5,irsBox5,wirBox5, resBox5,NpBox5, Sample5);
			go_ANC_Cases (ancBox6,irsBox6,wirBox6, resBox6,NpBox6, Sample6);

			LOG->Text=LOG->Text->ToString() +  "\n----------------------------------------------------------------------------\n";
			
			LOG->SaveFile(HeaderBox->Text->ToString() + ".log.rtf");

			 }


private: System::Void go_batch_Click(System::Object^  sender, System::EventArgs^  e) {


			 go_batch_Cases(rawBox1,ancBox1,NpBox1);
	 go_batch_Cases(rawBox2,ancBox2,NpBox2);
	 	 go_batch_Cases(rawBox3,ancBox3,NpBox3);
		 	 go_batch_Cases(rawBox4,ancBox4,NpBox4);
			 	 go_batch_Cases(rawBox5,ancBox5,NpBox5);
				 	 go_batch_Cases(rawBox6,ancBox6,NpBox6);

	 System::Windows::Forms::Application::DoEvents();
				System::Windows::Forms::Application::DoEvents();
				 go_ANC_Click(sender,e);
				
					 System::Windows::Forms::Application::DoEvents();
				System::Windows::Forms::Application::DoEvents();		
				 go_IRS_Click(sender,e);
				
				 System::Windows::Forms::Application::DoEvents();
				System::Windows::Forms::Application::DoEvents();
				 go_WIR_Click(sender,e);
				
					 System::Windows::Forms::Application::DoEvents();
				System::Windows::Forms::Application::DoEvents();
				 go_RES_Click(sender,e);


		 }

		 public: void go_batch_Cases(Windows::Forms::CheckBox^ RAW,Windows::Forms::CheckBox^ ANC,Windows::Forms::CheckBox^ NP)

				 {
				 if(RAW->Checked)
				 {
					 ANC->Checked::set(true);
					 NP->Checked::set(true);
					 NP->Text="Optional";
				 }
				 else
				 {
					 ANC->Checked::set(false);
					 NP->Checked::set(false);
				
				 }

					
								
			  
			 }
	private: System::Void edit_wir_Click(System::Object^  sender, System::EventArgs^  e) {

			
		edit_GEN_Cases(wirBox1, Sample1,".wir.txt");
edit_GEN_Cases(wirBox2, Sample2,".wir.txt");
edit_GEN_Cases(wirBox3, Sample3,".wir.txt");
edit_GEN_Cases(wirBox4, Sample4,".wir.txt");
edit_GEN_Cases(wirBox5, Sample5,".wir.txt");
edit_GEN_Cases(wirBox6, Sample6,".wir.txt");



			 }
	private: System::Void go_IRS_Click(System::Object^  sender, System::EventArgs^  e) {

				

				 LOG->Text=LOG->Text->ToString() + "\n----------------------------------------------------------------------------\n";
			LOG->Text+= "Calculating Isotopic Ratios for each pair of U-235 vs. U-238 gamma lines:\n\n";

	LOG->Text+= "\n\nReading Data from Sample:\n\n";
			
			go_IRS_Cases (ancBox1,irsBox1,wirBox1, resBox1,NpBox1, Sample1);
			go_IRS_Cases (ancBox2,irsBox2,wirBox2, resBox2,NpBox2, Sample2);
	go_IRS_Cases (ancBox3,irsBox3,wirBox3, resBox3,NpBox3, Sample3);
			go_IRS_Cases (ancBox4,irsBox4,wirBox4, resBox4,NpBox4, Sample4);
	go_IRS_Cases (ancBox5,irsBox5,wirBox5, resBox5,NpBox5, Sample5);
			go_IRS_Cases (ancBox6,irsBox6,wirBox6, resBox6,NpBox6, Sample6);


				 LOG->Text=LOG->Text->ToString() +  "\n----------------------------------------------------------------------------\n";
				
				 LOG->SaveFile(HeaderBox->Text->ToString() + ".log.rtf");


			 }
public: void go_IRS_Cases (Windows::Forms::CheckBox^ ANC,Windows::Forms::CheckBox^ IRS,Windows::Forms::CheckBox^ WIR, Windows::Forms::CheckBox^ RES,Windows::Forms::CheckBox^ NP, Windows::Forms::TextBox^ Sample)

					 {
 string inputpg2;
				 string x;
				 ifstream file;
				 const char* f;

				 if( IRS->Checked)
				 {

					 MarshalString(HeaderBox->Text->ToString() +"."+ Sample->Text->ToString(),inputpg2);

					 x=inputpg2;
					 x.append(".anc.xls");
					 System::String^ S= gcnew String(x.c_str());	 
					 f=x.data();
					 file.open(f);
					 if (file.fail()) 
					 {


						 LOG->Text=LOG->Text->ToString() +"\t"+ Sample->Text->ToString() + "\t\t...\t\t";
						 
					if (!String::IsNullOrEmpty(Sample->Text))	
						
					{
						
						LOG->Text=LOG->Text->ToString()+ "ERROR!\nFile " + S + " not Found!\nDo Step 2 First!!!\t\t...\n" ; 
						 ANC->Checked::set(true);
					 ANC->Text="Step 2";
					 IRS->Text="ERROR 2";
				
					}
						 
						
					else

					{
						IRS->Text="Step 3";
				

					}

						  IRS->Checked::set(false);
						 WIR->Text="Step 4";
						 RES->Text="Step 5";
						 NP->Text="Optional";
						
						 WIR->Checked::set(false);
						
						 RES->Checked::set(false);
						 NP->Checked::set(false);


						 file.close();

					 }
					 else
					 {
						 file.close();
						 IRS->Text="Calculating";
						 LOG->Text=LOG->Text->ToString() + "\t" +  Sample->Text->ToString() + "\t\t...\t\t";
						 System::Windows::Forms::Application::DoEvents();
						 Tools_IRS(inputpg2,0);
						 IRS->Text="Done!";
						 IRS->Checked::set(false);
						 WIR->Checked::set(true);
						 WIR->Text="Step 4";
						 RES->Text="Step 5";
						 NP->Text="Optional";

						 RES->Checked::set(false);
						 NP->Checked::set(false);

						 LOG->Text=LOG->Text->ToString()+ "DONE\n";
					 }
				 }

		

			 }							   

	private: System::Void go_WIR_Click(System::Object^  sender, System::EventArgs^  e) {



				 LOG->Text=LOG->Text->ToString() + "\n----------------------------------------------------------------------------\n";

LOG->Text+= "Calculating the Weighted Overall U-235 vs. U-238 Isotopic Ratio:\n\n";

	LOG->Text+= "\n\nReading Data from Sample:\n\n";
	

				 	go_WIR_Cases (ancBox1,irsBox1,wirBox1, resBox1,NpBox1, Sample1);
			go_WIR_Cases (ancBox2,irsBox2,wirBox2, resBox2,NpBox2, Sample2);
			go_WIR_Cases (ancBox3,irsBox3,wirBox3, resBox3,NpBox3, Sample3);
			go_WIR_Cases (ancBox4,irsBox4,wirBox4, resBox4,NpBox4, Sample4);
			go_WIR_Cases (ancBox5,irsBox5,wirBox5, resBox5,NpBox5, Sample5);
			go_WIR_Cases (ancBox6,irsBox6,wirBox6, resBox6,NpBox6, Sample6);
				 
				 LOG->Text=LOG->Text->ToString()+ "\n----------------------------------------------------------------------------\n";
				 LOG->SaveFile(HeaderBox->Text->ToString() + ".log.rtf");



			 }

public: void go_WIR_Cases (Windows::Forms::CheckBox^ ANC,Windows::Forms::CheckBox^ IRS,Windows::Forms::CheckBox^ WIR, Windows::Forms::CheckBox^ RES,Windows::Forms::CheckBox^ NP, Windows::Forms::TextBox^ Sample)

					 {

				 
				 string x;
				 ifstream file;
				 const char* f;


				 string inputpg2;


				 if( WIR->Checked)
				 {
					 MarshalString(HeaderBox->Text->ToString() +"."+ Sample->Text->ToString(),inputpg2);
					 x=inputpg2;
					 x.append(".irs.xls");
					 System::String^ S= gcnew String(x.c_str());	 
					 f=x.data();
					 file.open(f);
					 if (file.fail()) 
					 {
						 LOG->Text=LOG->Text->ToString() +"\t"+ Sample->Text->ToString() + "\t\t...\t\t";
						 
				if (!String::IsNullOrEmpty(Sample->Text))	
					
						{
						
						LOG->Text=LOG->Text->ToString()+ "ERROR 3\nFile " + S + " not Found!\nDo Step 3 First!!!\t\t...\n" ; 
				
						 IRS->Checked::set(true);
						 IRS->Text="Step 3";
						 WIR->Text="ERROR 3";
				
					}
						 
						
					else

					{
				
						WIR->Text="Step 4";
				
					}

				
						


				
						 RES->Text="Step 5";
						 NP->Text="Optional";
		
						 WIR->Checked::set(false);

						 RES->Checked::set(false);
						 NP->Checked::set(false);





						 file.close();

					 }
					 else
					 {
						 file.close();


						 WIR->Text="Calculating";


						 LOG->Text=LOG->Text->ToString() +"\t"+ Sample->Text->ToString() + "\t\t...\t\t";

						 System::Windows::Forms::Application::DoEvents();


						 WSAMPLE->Text=Sample->Text->ToString();



						 

						 if (Tools_WIR(inputpg2)==1)  // sample very enriched apparently!

						 {
							  Tools_IRS(inputpg2,1);
							  Tools_WIR(inputpg2);


						 }




						 WIR->Text="Weighted";
						 RES->Text="Step 5";
						 RES->Checked::set(true);
						 WIR->Checked::set(false);
						 NP->Text="Ready!";

						 NP->Checked::set(true);

						 LOG->Text=LOG->Text->ToString()+ "DONE\n";
						}
				 }
		
			 }

	private: System::Void edit_irs_Click(System::Object^  sender, System::EventArgs^  e) {


				edit_GEN_Cases(irsBox1, Sample1,".irs.xls");
edit_GEN_Cases(irsBox2, Sample2,".irs.xls");
edit_GEN_Cases(irsBox3, Sample3,".irs.xls");
edit_GEN_Cases(irsBox4, Sample4,".irs.xls");
edit_GEN_Cases(irsBox5, Sample5,".irs.xls");
edit_GEN_Cases(irsBox6, Sample6,".irs.xls");


			 }
	private: System::Void edit_anc_Click(System::Object^  sender, System::EventArgs^  e) {

		edit_GEN_Cases(ancBox1, Sample1,".anc.xls");
edit_GEN_Cases(ancBox2, Sample2,".anc.xls");
edit_GEN_Cases(ancBox3, Sample3,".anc.xls");
edit_GEN_Cases(ancBox4, Sample4,".anc.xls");
edit_GEN_Cases(ancBox5, Sample5,".anc.xls");
edit_GEN_Cases(ancBox6, Sample6,".anc.xls");



			 }

public: void  edit_GEN_Cases(Windows::Forms::CheckBox^ GEN, Windows::Forms::TextBox^ Sample, System::String^ string)
		{
				
			
				 if(GEN->Checked)
				 {
					 process->StartInfo->FileName= HeaderBox->Text->ToString()+"."+Sample->Text->ToString()+ string ;
					
				if (File::Exists(process->StartInfo->FileName->ToString()))

					 {
						process->Start();
					 }
			

				 }

					
			 }


	private: System::Void FileDialog_Header_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {


				 //Display the Header path without the .h inside the HeaderBox
				 HeaderBox->Clear();
				 HeaderBox->Text=FileDialog_Header->FileName->Substring(0,FileDialog_Header->FileName->Length::get()-2);

			 }



	private: System::Void FileDialog_KPG_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

				 
				 KPGBox->Clear();
				 KPGBox->Text=FileDialog_KPG->FileName;



			 }


	private: System::Void go_KPG_browse_Click(System::Object^  sender, System::EventArgs^  e) {


				 FileDialog_KPG->Filter = "KayZero PerGamma Report (.kpg) |*.kpg";
				 FileDialog_KPG->FilterIndex = 1;
				 FileDialog_KPG->RestoreDirectory = true;

				 FileDialog_KPG->ShowDialog(); 

			 }


	private: System::Void HeaderBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {

				 if (File::Exists(HeaderBox->Text->ToString() + ".h"))
				 {

LOG_Clear_Click(sender,e);
				

				 
					 System::IO::StreamReader ^ sr = gcnew
				System::IO::StreamReader(HeaderBox->Text->ToString() + ".h");
				
				 Sample1->Text=sr->ReadLine(); 
				  Sample2->Text= sr->ReadLine(); 
				 Sample3->Text=sr->ReadLine(); 
				 Sample4->Text= sr->ReadLine(); 
				 Sample5->Text= sr->ReadLine(); 
				 Sample6->Text= sr->ReadLine(); 
			 sr->Close();

				 System::IO::StreamReader ^ nd = gcnew
					 System::IO::StreamReader(HeaderBox->Text->ToString() + ".h");
				 Box_Samples_List->Text=nd->ReadToEnd();
				 nd->Close();

			 }
				 if( File::Exists(HeaderBox->Text->ToString() + ".log.rtf") )
				 {

					 LOG->Clear();
					 LOG->LoadFile(HeaderBox->Text->ToString() + ".log.rtf");

				 }
			
			 }


	private: System::Void help_ANC_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {


				 MessageBox::Show("Module for converting the Apparent concentrations into natural-Uranium concentrations");



			 }
	private: System::Void help_IRS_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {

				 MessageBox::Show("Module for calculating a U-235 vs. U-238 Isotopic Ratio\nfrom each pair of U-235 & U-238 values");


			 }
	private: System::Void help_WIR_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
				
				 MessageBox::Show("Module for calculating the Weighted U-235 vs. U-238 Isotopic Ratio");


			 }

	private: System::Void go_RES_Click(System::Object^  sender, System::EventArgs^  e) {

				
	 LOG->Text=LOG->Text->ToString() + "\n----------------------------------------------------------------------------\n";

	 	LOG->Text+= "Calculating corrections for Apparent concentrations due to fission of U-235:\n\n";
			LOG->Text+= "\n\nReading Data from Sample:\n\n";


	 go_RES_Cases (ancBox1,irsBox1,wirBox1, resBox1,NpBox1, Sample1);
			go_RES_Cases (ancBox2,irsBox2,wirBox2, resBox2,NpBox2, Sample2);
			go_RES_Cases (ancBox3,irsBox3,wirBox3, resBox3,NpBox3, Sample3);
			go_RES_Cases (ancBox4,irsBox4,wirBox4, resBox4,NpBox4, Sample4);
			go_RES_Cases (ancBox5,irsBox5,wirBox5, resBox5,NpBox5, Sample5);
			go_RES_Cases (ancBox6,irsBox6,wirBox6, resBox6,NpBox6, Sample6);

 LOG->Text=LOG->Text->ToString() +  "\n----------------------------------------------------------------------------\n";
				 LOG->SaveFile(HeaderBox->Text->ToString() + ".log.rtf");
					



			 }

			 public: void go_RES_Cases (Windows::Forms::CheckBox^ ANC,Windows::Forms::CheckBox^ IRS,Windows::Forms::CheckBox^ WIR, Windows::Forms::CheckBox^ RES,Windows::Forms::CheckBox^ NP, Windows::Forms::TextBox^ Sample)

					 {

				 string x,y;
				 ifstream file,file2;
				 const char* f , *f2;

				 string inputpg2;
			

				 if( RES->Checked)
				 {
					 MarshalString(HeaderBox->Text->ToString() +"."+ Sample->Text->ToString(),inputpg2);

					 x=inputpg2;
					 y=inputpg2;
					 x.append(".anc.xls");
					 y.append(".wir.xls");

					 System::String^ S= gcnew String(x.c_str());
					 System::String^ S2= gcnew String(y.c_str());	
					 f=x.data();
					 f2=y.data();
					 file2.open(f2);
					 file.open(f);
					 if ( file.fail() ) 
					 {
						 file.close();
						 file2.close();
						 remove(f2);
						 LOG->Text=LOG->Text->ToString() +"\t"+ Sample->Text->ToString() + "\t\t...\t\t";
						 
						 if (!String::IsNullOrEmpty(Sample->Text))	
						 {
						LOG->Text=LOG->Text->ToString()+ "ERROR 2\nFile " + S + " not Found!\nDo Step 2 First!!!\t\t...\n"; 

						
						ANC->Checked::set(true);
					 ANC->Text="Step 2";
					
					RES->Text="ERROR 2";
						

						 }
											 
						 else RES->Text="Step 5";

	IRS->Checked::set(false);
	IRS->Text="Step 3";
						WIR->Checked::set(false);
				    	 WIR->Text="Step 4";
					
						
						 NP->Text="Optional";


						 RES->Checked::set(false);
						 NP->Checked::set(false);





					

					 }
					 else if (file2.fail())
					 {
						 file.close();
						 file2.close();
						 LOG->Text=LOG->Text->ToString() +"\t"+ Sample->Text->ToString() + "\t\t...\t\t";
						 
						 if (!String::IsNullOrEmpty(Sample->Text))	
						 {
							 
							 LOG->Text=LOG->Text->ToString()+ "\nERROR: File " + S2 + " not Found!\nDo Step 4 First!!!\n\n"; 

						WIR->Checked::set(true);
						WIR->Text="Step 4";
					
						RES->Text="ERROR 4";

						 }

						 else

						 {

							RES->Text="Step 5";

						 }

						 RES->Checked::set(false);
						
						 NP->Text="Optional";
						 NP->Checked::set(false);

					 }
					 else

					 {
						 file.close();
						 file2.close();


						 RES->Text="Calculating";
						 LOG->Text=LOG->Text->ToString() + "\t"+ Sample->Text->ToString() + "\t\t...\t\t";

						 System::Windows::Forms::Application::DoEvents();


						 Tools_RES(inputpg2);
						 RES->Checked::set(false);
						 RES->Text="Done!";
						 LOG->Text=LOG->Text->ToString() + "DONE\n";
					 }

				 }

					

			 }




	private: System::Void edit_res_Click(System::Object^  sender, System::EventArgs^  e) {

			edit_GEN_Cases(resBox1, Sample1,".res.xls");
edit_GEN_Cases(resBox2, Sample2,".res.xls");
edit_GEN_Cases(resBox3, Sample3,".res.xls");
edit_GEN_Cases(resBox4, Sample4,".res.xls");
edit_GEN_Cases(resBox5, Sample5,".res.xls");
edit_GEN_Cases(resBox6, Sample6,".res.xls");



			 }
	private: System::Void go_228_Click(System::Object^  sender, System::EventArgs^  e) {

				

				 LOG->Text=LOG->Text->ToString() + "\n----------------------------------------------------------------------------\n";

			LOG->Text+=	 "Correcting the Np-239's 228keV lines from Te-132 interference:\n\n";

	LOG->Text+= "\n\nReading Data from Sample:\n\n";


			go_228_Cases (ancBox1,irsBox1,wirBox1, resBox1,NpBox1, Sample1);
			go_228_Cases (ancBox2,irsBox2,wirBox2, resBox2,NpBox2, Sample2);
	go_228_Cases (ancBox3,irsBox3,wirBox3, resBox3,NpBox3, Sample3);
			go_228_Cases (ancBox4,irsBox4,wirBox4, resBox4,NpBox4, Sample4);
	go_228_Cases (ancBox5,irsBox5,wirBox5, resBox5,NpBox5, Sample5);
			go_228_Cases (ancBox6,irsBox6,wirBox6, resBox6,NpBox6, Sample6);

	 LOG->Text=LOG->Text->ToString() +  "\n----------------------------------------------------------------------------\n";
		
				 LOG->SaveFile(HeaderBox->Text->ToString() + ".log.rtf");
				
				 System::Windows::Forms::Application::DoEvents();
				System::Windows::Forms::Application::DoEvents();
				 
				go_IRS_Click(sender,e);
				 System::Windows::Forms::Application::DoEvents();
				System::Windows::Forms::Application::DoEvents();
				 go_WIR_Click(sender,e);
					 System::Windows::Forms::Application::DoEvents();
				System::Windows::Forms::Application::DoEvents();
				
				 go_RES_Click(sender,e);
				 System::Windows::Forms::Application::DoEvents();
				System::Windows::Forms::Application::DoEvents();



			 }



 public: void go_ANC_Cases (Windows::Forms::CheckBox^ ANC,Windows::Forms::CheckBox^ IRS,Windows::Forms::CheckBox^ WIR, Windows::Forms::CheckBox^ RES,Windows::Forms::CheckBox^ NP, Windows::Forms::TextBox^ Sample)

					 {

			 string x;
				 ifstream file;
				 const char* f;
				string inputpg2;

				 if (ANC->Checked)
				 {

					 MarshalString(HeaderBox->Text->ToString() +"."+ Sample->Text->ToString(),inputpg2);

					 x=inputpg2;
					 x.append(".xls");
					 System::String^ S= gcnew String(x.c_str());	 
					 f=x.data();
					 file.open(f);
					 if (file.fail()) 
					 {
			
				 	 	 LOG->Text=LOG->Text->ToString() + "\t"+  Sample->Text->ToString() + "\t\t...\t\t";
						 if (!String::IsNullOrEmpty(Sample->Text))	
						 {
							 LOG->Text=LOG->Text->ToString()+ "ERROR 1!\nFile " + S + " not Found!\nRe-import the KPG Report!!!\t\t...\n";

  						   KPGBox->Text=HeaderBox->Text->ToString()+ ".kpg";
							
						 ANC->Text="ERROR 1";

						 }


						 else
							 
						 {
						
						 ANC->Text="Step 2";
						
						 }

						 ANC->Checked::set(false);

						WIR->Text="Step 4";
						 RES->Text="Step 5";
						 NP->Text="Optional";
						 IRS->Text="Step 3";
						 WIR->Checked::set(false);
						 IRS->Checked::set(false);
						 RES->Checked::set(false);
						 NP->Checked::set(false);


						 file.close();

					 }
					 else
					 {
						 file.close();

						 ANC->Text="Calculating";
						   LOG->Text=LOG->Text->ToString() + "\t" + Sample->Text->ToString() + "\t\t...\t\t";
	
						   
						 	System::Windows::Forms::Application::DoEvents();


						 if( Tools_ANC(inputpg2)==0) 
						 {
						
						 LOG->Text=LOG->Text->ToString() + "DONE\n";

 						 ANC->Text="Done!";
						 ANC->Checked::set(false);
						 IRS->Checked::set(true);

						 
						 }
						 else 
						 {

 LOG->Text=LOG->Text->ToString() + "\n"; // a Fatal error occurred in Calculations
ANC->Text="ERROR 6";
						 ANC->Checked::set(true);
						 IRS->Checked::set(false);


						 }

						 IRS->Text="Step 3";

						 WIR->Text="Step 4";
						 RES->Text="Step 5";
						 NP->Text="Optional";
						 WIR->Checked::set(false);
						 RES->Checked::set(false);
						 NP->Checked::set(false);
					 }

				 }




		 }


			 public: void go_228_Cases (Windows::Forms::CheckBox^ ANC,Windows::Forms::CheckBox^ IRS,Windows::Forms::CheckBox^ WIR, Windows::Forms::CheckBox^ RES,Windows::Forms::CheckBox^ NP, Windows::Forms::TextBox^ Sample)

					 {

				 string x,y;
				 ifstream file,file2;
				 const char* f , *f2;
				string inputpg2;
			 
				if( NP->Checked)
				 {
					 MarshalString(HeaderBox->Text->ToString() +"."+ Sample->Text->ToString(),inputpg2);

					 x=inputpg2;
					 y=inputpg2;
					 x.append(".anc.xls");
					 y.append(".wir.xls");

					 System::String^ S= gcnew String(x.c_str());
					 System::String^ S2= gcnew String(y.c_str());	
					 f=x.data();
					 f2=y.data();
					 file2.open(f2);
					 file.open(f);
					 if ( file.fail() ) 
					 {
						 file.close();			 
						 remove(f2);
						
						 LOG->Text=LOG->Text->ToString() + "\t"+  Sample->Text->ToString() + "\t\t...\t\t";
						 if (!String::IsNullOrEmpty(Sample->Text))	
						 {
						LOG->Text=LOG->Text->ToString()+ "ERROR 2\nFile " + S + " not Found!\nDo Step 2 First!!!\t\t...\n"; 

					

						ANC->Checked::set(true);
						 ANC->Text="Step 2";
					
						NP->Text="ERROR 2";
						

						 }
					
						 
						 else
						 {
							 
							 NP->Text="Optional";

						 }
						 
						WIR->Checked::set(false);
						 WIR->Text="Step 4";
						IRS->Checked::set(false);
						 IRS->Text="Step 3";

						 RES->Text="Step 5";
						 RES->Checked::set(false);
						 NP->Checked::set(false);

					

					 }
					 else if (file2.fail())
					 {
						 file2.close();

					 	 LOG->Text=LOG->Text->ToString() + "\t"+  Sample->Text->ToString() + "\t\t...\t\t";
						 if (!String::IsNullOrEmpty(Sample->Text))
						 {
							 LOG->Text=LOG->Text->ToString()+ "ERROR 4\nFile " + S2 + " not Found!\nDo Step 4 First!!!\t\t...\n"; 

						 WIR->Checked::set(true);
						 WIR->Text="Step 4";
							NP->Text="WAIT 4";


						 }

						 else
						 {
						WIR->Checked::set(false);
						 NP->Text="Optional";

						 }

						 RES->Text="Step 5";
						


						 RES->Checked::set(false);
						 NP->Checked::set(false);

					 }
					 else
					 {
						 file.close();
						  file2.close();

						 NP->Text="Calculating";
					 	 LOG->Text=LOG->Text->ToString() + "\t"+  Sample->Text->ToString() + "\t\t...\t\t";
					
						System::Windows::Forms::Application::DoEvents();

						if (Tools_228(inputpg2)==0)
						 {
							LOG->Text=LOG->Text->ToString() + "DONE\n";
							NP->Text="Corrected";
							IRS->Checked::set(true);

						 }

						else 

						 {
							NP->Text="ERROR 6";
							LOG->Text=LOG->Text->ToString() + "ERROR 6\n"; //calculation failed
							IRS->Checked::set(false);
							ANC->Checked::set(true);
							ANC->Text="ERROR 6";

						 }
						 
						RES->Text="Step 5";
						 RES->Checked::set(false);
						 WIR->Text="Step 4";
						 WIR->Checked::set(false);
						 NP->Checked::set(false);
						 IRS->Text="Step 3";
						 System::Windows::Forms::Application::DoEvents();

					 }

				}

				

		
			

			

			 }




	private: System::Void Sample1_TextChanged(System::Object^  sender, System::EventArgs^  e) {


	SAMPLE_Text_Changed (rawBox1,ancBox1,irsBox1,wirBox1, resBox1,NpBox1, Sample1);


			 }

 public: void SAMPLE_Text_Changed (Windows::Forms::CheckBox^ RAW,Windows::Forms::CheckBox^ ANC,Windows::Forms::CheckBox^ IRS,Windows::Forms::CheckBox^ WIR, Windows::Forms::CheckBox^ RES,Windows::Forms::CheckBox^ NP, Windows::Forms::TextBox^ Sample)

					 {



				 IRS->Text="Step 3";
				 WIR->Text="Step 4";
				 NP->Text="Optional";
				 RES->Text="Step 5";

				 ANC->Text="Step 2";


				 string con,res,iso,rat,inputpg2,xls;


				 MarshalString(HeaderBox->Text->ToString() +"."+ Sample->Text->ToString(),inputpg2);


				 const char * fcon, *fres, *fiso, *frat,*fxls;
				 ifstream file;

				 con=res=iso=rat=xls=inputpg2;
				 con.append(".anc.xls");
				 rat.append(".irs.xls");
				 iso.append(".wir.txt");
				 res.append(".res.xls");
				 xls.append(".xls");
				 fxls=xls.data(); 
				 fres=res.data();
				 fiso=iso.data();
				 frat=rat.data();
				 fcon=con.data();

				 file.open(fxls);

				 if (file.fail()) 
				 {
					 RAW->Checked::set(false);

					 ANC->Checked::set(false);
				 }
				 else
				 {
					 RAW->Checked::set(true);
					 ANC->Checked::set(true);

				 }
				 file.close();




				 file.open(fcon);
				 if (file.fail()) 
				 {

					 IRS->Checked::set(false);
					 WIR->Checked::set(false);
					 NP->Checked::set(false);
					 RES->Checked::set(false);

					 file.close(); 

					 ifstream nfile;

					 nfile.open(fxls);

					 if (nfile.fail()) 
					 {
						 RAW->Checked::set(false);
						 ANC->Checked::set(false);
					 }
					 else
					 {
						 RAW->Checked::set(true);
						 ANC->Checked::set(true);

					 }
					 nfile.close();



				 }
				 else 
				 {

					 file.close();
					 ANC->Text="Done!";
					 ANC->Checked::set(false);
					 //IRS->Checked::set(true);

					 file.open(frat);
					 if (file.fail())
					 {

						 IRS->Checked::set(true);
						 WIR->Checked::set(false);
						 NP->Checked::set(false);
						 RES->Checked::set(false);
						 file.close();
					 }
					 else 

					 {
						 file.close();
						 IRS->Checked::set(false);
						 IRS->Text="Done!";
						 WIR->Checked::set(true);

						 file.open(fiso);
						 if (file.fail())
						 {
							 WIR->Checked::set(true);
							 NP->Checked::set(false);
							 RES->Checked::set(false);
							 file.close();
						 }
						 else

						 {
							 file.close();
							 WIR->Checked::set(false);
							 WIR->Text="Weighted!";
							 RES->Checked::set(true);
							 NP->Checked::set(true);

							 file.open(fres);
							 if (file.fail())
							 {

								 NP->Checked::set(true);
								 RES->Checked::set(true);
								 file.close();
							 }
							 else

							 {
								 file.close();
								 RES->Checked::set(false);
								 RES->Text="Done!";



							 }


						 }


					 }

				 }


			 }
	private: System::Void Sample2_TextChanged(System::Object^  sender, System::EventArgs^  e) {


				 SAMPLE_Text_Changed (rawBox2,ancBox2,irsBox2,wirBox2, resBox2,NpBox2, Sample2);

			 }

	private: System::Void Sample3_TextChanged(System::Object^  sender, System::EventArgs^  e) {


	 SAMPLE_Text_Changed (rawBox3,ancBox3,irsBox3,wirBox3, resBox3,NpBox3, Sample3);
			
			 }
	private: System::Void Sample4_TextChanged(System::Object^  sender, System::EventArgs^  e) {

 SAMPLE_Text_Changed (rawBox4,ancBox4,irsBox4,wirBox4, resBox4,NpBox4, Sample4);
			
			 }
	private: System::Void Sample5_TextChanged(System::Object^  sender, System::EventArgs^  e) {


 SAMPLE_Text_Changed (rawBox5,ancBox5,irsBox5,wirBox5, resBox5,NpBox5, Sample5);

			 }
	private: System::Void Sample6_TextChanged(System::Object^  sender, System::EventArgs^  e) {


 SAMPLE_Text_Changed (rawBox6,ancBox6,irsBox6,wirBox6, resBox6,NpBox6, Sample6);

			
			 }

	private: System::Void go_KPG_view_Click(System::Object^  sender, System::EventArgs^  e) {

			
				string x;
				 ifstream file;
				 const char * f;
				
				 process->StartInfo->FileName= KPGBox->Text->ToString();
			
				  MarshalString(process->StartInfo->FileName->ToString(),x);

					 f=x.data();

					 file.open(f);
					 if (file.fail()) file.close(); 
					 else 
						{
							file.close();
							process->Start();
						}
				 
				 
			 }					
	private: System::Void edit_raw_Click(System::Object^  sender, System::EventArgs^  e) {

		
edit_GEN_Cases(rawBox1, Sample1,".xls");
edit_GEN_Cases(rawBox2, Sample2,".xls");
edit_GEN_Cases(rawBox3, Sample3,".xls");
edit_GEN_Cases(rawBox4, Sample4,".xls");
edit_GEN_Cases(rawBox5, Sample5,".xls");
edit_GEN_Cases(rawBox6, Sample6,".xls");




			 }

	private: System::Void LOG_Print_Click(System::Object^  sender, System::EventArgs^  e) {





				 LOG->SaveFile(HeaderBox->Text->ToString() + ".log.rtf");


				 process->StartInfo->FileName = HeaderBox->Text->ToString() + ".log.rtf";

				 process->Start();


			 }
	private: System::Void LOG_Clear_Click(System::Object^  sender, System::EventArgs^  e) {

			LOG->Clear();


			 }
	private: System::Void help_RES_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {


				 MessageBox::Show("Module for calculating corrections to the Apparent concentrations due to U-235 fission");


			 }

	private: System::Void help_Import_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {

				 MessageBox::Show("Module for importing Sample(s) Data from a 'KayZero PerGamma Report'");


			 }
	private: System::Void help_Header_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {

				 MessageBox::Show("Module for accesing the OptiNAA Headers.\nA OptiNAA Header is just a pointer to Sample(s) Data\npreviously imported from a 'KayZero PerGamma Report'");

			 }



	private: System::Void help_228_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {

				 MessageBox::Show("Module for correcting the natural-Uranium concentrations obtained from\n238U(n,y)239U ---> Np-239 @ 228keV gamma line\ndue to interference from\n235U(n,f)132Te @ 228keV gamma line");

			 }
	private: System::Void groupBox_ANC_Enter(System::Object^  sender, System::EventArgs^  e) {

				 if (anc==0)

				 {
					 ancBox1->Checked::set(false);
					 ancBox2->Checked::set(false);
					 ancBox3->Checked::set(false);
					 ancBox4->Checked::set(false);
					 ancBox5->Checked::set(false);
					 ancBox6->Checked::set(false);
					 anc=1;
				 }
				 else
				 {
					 ancBox1->Checked::set(true);
					 ancBox2->Checked::set(true);
					 ancBox3->Checked::set(true);
					 ancBox4->Checked::set(true);
					 ancBox5->Checked::set(true);
					 ancBox6->Checked::set(true);
					 anc=0;
				 }



			 }
	private: System::Void groupBox_IRS_Enter(System::Object^  sender, System::EventArgs^  e) {

				 if (irs==0)

				 {
					 irsBox1->Checked::set(false);
					 irsBox2->Checked::set(false);
					 irsBox3->Checked::set(false);
					 irsBox4->Checked::set(false);
					 irsBox5->Checked::set(false);
					 irsBox6->Checked::set(false);
					 irs=1;
				 }
				 else
				 {
					 irsBox1->Checked::set(true);
					 irsBox2->Checked::set(true);
					 irsBox3->Checked::set(true);
					 irsBox4->Checked::set(true);
					 irsBox5->Checked::set(true);
					 irsBox6->Checked::set(true);
					 irs=0;
				 }



			 }
	private: System::Void groupBox_WIR_Enter(System::Object^  sender, System::EventArgs^  e) {


				 if (wir==0)

				 {
					 wirBox1->Checked::set(false);
					 wirBox2->Checked::set(false);
					 wirBox3->Checked::set(false);
					 wirBox4->Checked::set(false);
					 wirBox5->Checked::set(false);
					 wirBox6->Checked::set(false);
					 wir=1;
				 }
				 else
				 {
					 wirBox1->Checked::set(true);
					 wirBox2->Checked::set(true);
					 wirBox3->Checked::set(true);
					 wirBox4->Checked::set(true);
					 wirBox5->Checked::set(true);
					 wirBox6->Checked::set(true);
					 wir=0;
				 }


			 }
	private: System::Void groupBox_RES_Enter(System::Object^  sender, System::EventArgs^  e) {


				 if (res==0)

				 {
					 resBox1->Checked::set(false);
					 resBox2->Checked::set(false);
					 resBox3->Checked::set(false);
					 resBox4->Checked::set(false);
					 resBox5->Checked::set(false);
					 resBox6->Checked::set(false);
					 res=1;
				 }
				 else
				 {
					 resBox1->Checked::set(true);
					 resBox2->Checked::set(true);
					 resBox3->Checked::set(true);
					 resBox4->Checked::set(true);
					 resBox5->Checked::set(true);
					 resBox6->Checked::set(true);
					 res=0;
			  }
			 }
	private: System::Void groupBox_228_Enter(System::Object^  sender, System::EventArgs^  e) {


				 if (np==0)

				 {
					 NpBox1->Checked::set(false);
					 NpBox2->Checked::set(false);
					 NpBox3->Checked::set(false);
					 NpBox4->Checked::set(false);
					 NpBox5->Checked::set(false);
					 NpBox6->Checked::set(false);
					 np=1;
				 }
				 else
				 {
					 NpBox1->Checked::set(true);
					 NpBox2->Checked::set(true);
					 NpBox3->Checked::set(true);
					 NpBox4->Checked::set(true);
					 NpBox5->Checked::set(true);
					 NpBox6->Checked::set(true);
					 np=0;
			  }



			 }
	private: System::Void groupBox_Samples_TODO_Enter(System::Object^  sender, System::EventArgs^  e) {

				 if (raw==0)

				 {
					 rawBox1->Checked::set(false);
					 rawBox2->Checked::set(false);
					 rawBox3->Checked::set(false);
					 rawBox4->Checked::set(false);
					 rawBox5->Checked::set(false);
					 rawBox6->Checked::set(false);
					 raw=1;
				 }
				 else
				 {
					 rawBox1->Checked::set(true);
					 rawBox2->Checked::set(true);
					 rawBox3->Checked::set(true);
					 rawBox4->Checked::set(true);
					 rawBox5->Checked::set(true);
					 rawBox6->Checked::set(true);
					 raw=0;
				 }




			 }
	private: System::Void tutorial_Click(System::Object^  sender, System::EventArgs^  e) {

				 process->StartInfo->FileName= "help.ppt";

				 if (File::Exists(process->StartInfo->FileName->ToString())) process->Start();



			 }
	private: System::Void PANIC_Click(System::Object^  sender, System::EventArgs^  e) {

				 if (panic==0)
				 {
					 panic=1;
					 all->Visible::set(false);
					 label_all->Visible::set(false);
					 PANIC->Text="PANIC IS ON";
					 this->PANIC->ForeColor = System::Drawing::Color::Red;
					 MessageBox::Show("Only the I-131 @ 364 keV vs. Np-239 @ 277keV gammas will be considered");
					 label_PANIC->Text=("Only the I-131 @ 364 keV vs. Np-239 @ 277keV gammas will be considered");

				 }
				 else
				 {
				  panic=0;
				  all->Visible::set(true);
					 label_all->Visible::set(true);
					 
					PANIC->Text="PANIC IS OFF";
				this->PANIC->ForeColor = System::Drawing::Color::Black;
					label_PANIC->Text=("For complicated multi-elemental samples activate PANIC");
				 }


			 }
private: System::Void all_Click(System::Object^  sender, System::EventArgs^  e) {

			  if (recommended==0)
				 {
					 recommended=1;
					 all->Text="RECOMMENDED";
					 label_all->Text="Only the RECOMMENDED Isotope's Gammas will be considered";
					 process->StartInfo->FileName= "recommended.jpg";

				 if (File::Exists(process->StartInfo->FileName->ToString())) process->Start();
					
				 }
				 else
				 {
					recommended=0;
					label_all->Text="All the Isotope's Gammas will be considered";
					all->Text="ALL GAMMAS";

				 }

		 }


private: System::Void LOG_TextChanged(System::Object^  sender, System::EventArgs^  e) {


				 LOG->SelectionStart = LOG->Text->Length;
				 LOG->ScrollToCaret();



		 }

#pragma endregion

#pragma region Windows Form Designer generated code


void InitializeComponent(void)
			{
				System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
				this->go_Header = (gcnew System::Windows::Forms::Button());
				this->FileDialog_KPG = (gcnew System::Windows::Forms::OpenFileDialog());
				this->HeaderBox = (gcnew System::Windows::Forms::TextBox());
				this->groupBox_Samples_List = (gcnew System::Windows::Forms::GroupBox());
				this->Box_Samples_List = (gcnew System::Windows::Forms::TextBox());
				this->Gth = (gcnew System::Windows::Forms::TextBox());
				this->Gepi = (gcnew System::Windows::Forms::TextBox());
				this->ENAA = (gcnew System::Windows::Forms::TextBox());
				this->ti = (gcnew System::Windows::Forms::TextBox());
				this->label_Gth = (gcnew System::Windows::Forms::Label());
				this->label_Gepi = (gcnew System::Windows::Forms::Label());
				this->label_irradiation_time = (gcnew System::Windows::Forms::Label());
				this->label_ENAA = (gcnew System::Windows::Forms::Label());
				this->go_KPG_Import = (gcnew System::Windows::Forms::Button());
				this->ancBox1 = (gcnew System::Windows::Forms::CheckBox());
				this->Sample1 = (gcnew System::Windows::Forms::TextBox());
				this->Sample2 = (gcnew System::Windows::Forms::TextBox());
				this->Sample3 = (gcnew System::Windows::Forms::TextBox());
				this->Sample4 = (gcnew System::Windows::Forms::TextBox());
				this->Sample5 = (gcnew System::Windows::Forms::TextBox());
				this->Sample6 = (gcnew System::Windows::Forms::TextBox());
				this->ancBox2 = (gcnew System::Windows::Forms::CheckBox());
				this->ancBox3 = (gcnew System::Windows::Forms::CheckBox());
				this->ancBox4 = (gcnew System::Windows::Forms::CheckBox());
				this->ancBox5 = (gcnew System::Windows::Forms::CheckBox());
				this->ancBox6 = (gcnew System::Windows::Forms::CheckBox());
				this->batch = (gcnew System::Windows::Forms::Button());
				this->go_ANC = (gcnew System::Windows::Forms::Button());
				this->groupBox_Import = (gcnew System::Windows::Forms::GroupBox());
				this->help_Import = (gcnew System::Windows::Forms::LinkLabel());
				this->label_step0 = (gcnew System::Windows::Forms::Label());
				this->go_KPG_view = (gcnew System::Windows::Forms::Button());
				this->linkLabel4 = (gcnew System::Windows::Forms::LinkLabel());
				this->KPGBox = (gcnew System::Windows::Forms::TextBox());
				this->go_KPG_browse = (gcnew System::Windows::Forms::Button());
				this->edit_raw = (gcnew System::Windows::Forms::Button());
				this->groupBox_ANC = (gcnew System::Windows::Forms::GroupBox());
				this->help_ANC = (gcnew System::Windows::Forms::LinkLabel());
				this->edit_anc = (gcnew System::Windows::Forms::Button());
				this->groupBox_Samples_TODO = (gcnew System::Windows::Forms::GroupBox());
				this->rawBox1 = (gcnew System::Windows::Forms::CheckBox());
				this->rawBox6 = (gcnew System::Windows::Forms::CheckBox());
				this->rawBox5 = (gcnew System::Windows::Forms::CheckBox());
				this->rawBox3 = (gcnew System::Windows::Forms::CheckBox());
				this->rawBox4 = (gcnew System::Windows::Forms::CheckBox());
				this->rawBox2 = (gcnew System::Windows::Forms::CheckBox());
				this->WIR = (gcnew System::Windows::Forms::TextBox());
				this->U235 = (gcnew System::Windows::Forms::TextBox());
				this->U238 = (gcnew System::Windows::Forms::TextBox());
				this->RO = (gcnew System::Windows::Forms::TextBox());
				this->label_WIR = (gcnew System::Windows::Forms::Label());
				this->label_U235 = (gcnew System::Windows::Forms::Label());
				this->label_U238 = (gcnew System::Windows::Forms::Label());
				this->label_RO = (gcnew System::Windows::Forms::Label());
				this->SD = (gcnew System::Windows::Forms::TextBox());
				this->label_SD = (gcnew System::Windows::Forms::Label());
				this->quoteU = (gcnew System::Windows::Forms::Label());
				this->groupBox_Results = (gcnew System::Windows::Forms::GroupBox());
				this->DT = (gcnew System::Windows::Forms::Label());
				this->WSAMPLE = (gcnew System::Windows::Forms::Label());
				this->groupBox_Results_Data = (gcnew System::Windows::Forms::GroupBox());
				this->label_SDobs = (gcnew System::Windows::Forms::Label());
				this->label_SDexp = (gcnew System::Windows::Forms::Label());
				this->SDexp = (gcnew System::Windows::Forms::TextBox());
				this->SDobs = (gcnew System::Windows::Forms::TextBox());
				this->label_RO5 = (gcnew System::Windows::Forms::Label());
				this->RO5 = (gcnew System::Windows::Forms::TextBox());
				this->label_RO8 = (gcnew System::Windows::Forms::Label());
				this->RO8 = (gcnew System::Windows::Forms::TextBox());
				this->label_AW = (gcnew System::Windows::Forms::Label());
				this->AW = (gcnew System::Windows::Forms::TextBox());
				this->LOG = (gcnew System::Windows::Forms::RichTextBox());
				this->process = (gcnew System::Diagnostics::Process());
				this->FileDialog_Header = (gcnew System::Windows::Forms::OpenFileDialog());
				this->groupBox_Header = (gcnew System::Windows::Forms::GroupBox());
				this->help_Header = (gcnew System::Windows::Forms::LinkLabel());
				this->label_step1 = (gcnew System::Windows::Forms::Label());
				this->groupBox_228 = (gcnew System::Windows::Forms::GroupBox());
				this->help_228 = (gcnew System::Windows::Forms::LinkLabel());
				this->go_228 = (gcnew System::Windows::Forms::Button());
				this->NpBox1 = (gcnew System::Windows::Forms::CheckBox());
				this->NpBox2 = (gcnew System::Windows::Forms::CheckBox());
				this->NpBox6 = (gcnew System::Windows::Forms::CheckBox());
				this->NpBox3 = (gcnew System::Windows::Forms::CheckBox());
				this->NpBox5 = (gcnew System::Windows::Forms::CheckBox());
				this->NpBox4 = (gcnew System::Windows::Forms::CheckBox());
				this->groupBox_WIR = (gcnew System::Windows::Forms::GroupBox());
				this->help_WIR = (gcnew System::Windows::Forms::LinkLabel());
				this->wirBox1 = (gcnew System::Windows::Forms::CheckBox());
				this->go_WIR = (gcnew System::Windows::Forms::Button());
				this->edit_wir = (gcnew System::Windows::Forms::Button());
				this->wirBox2 = (gcnew System::Windows::Forms::CheckBox());
				this->wirBox3 = (gcnew System::Windows::Forms::CheckBox());
				this->wirBox4 = (gcnew System::Windows::Forms::CheckBox());
				this->wirBox5 = (gcnew System::Windows::Forms::CheckBox());
				this->wirBox6 = (gcnew System::Windows::Forms::CheckBox());
				this->groupBox_RES = (gcnew System::Windows::Forms::GroupBox());
				this->edit_res = (gcnew System::Windows::Forms::Button());
				this->help_RES = (gcnew System::Windows::Forms::LinkLabel());
				this->resBox1 = (gcnew System::Windows::Forms::CheckBox());
				this->go_RES = (gcnew System::Windows::Forms::Button());
				this->resBox2 = (gcnew System::Windows::Forms::CheckBox());
				this->resBox3 = (gcnew System::Windows::Forms::CheckBox());
				this->resBox4 = (gcnew System::Windows::Forms::CheckBox());
				this->resBox5 = (gcnew System::Windows::Forms::CheckBox());
				this->resBox6 = (gcnew System::Windows::Forms::CheckBox());
				this->groupBox_IRS = (gcnew System::Windows::Forms::GroupBox());
				this->help_IRS = (gcnew System::Windows::Forms::LinkLabel());
				this->edit_irs = (gcnew System::Windows::Forms::Button());
				this->go_IRS = (gcnew System::Windows::Forms::Button());
				this->irsBox1 = (gcnew System::Windows::Forms::CheckBox());
				this->irsBox2 = (gcnew System::Windows::Forms::CheckBox());
				this->irsBox3 = (gcnew System::Windows::Forms::CheckBox());
				this->irsBox4 = (gcnew System::Windows::Forms::CheckBox());
				this->irsBox5 = (gcnew System::Windows::Forms::CheckBox());
				this->irsBox6 = (gcnew System::Windows::Forms::CheckBox());
				this->link_author = (gcnew System::Windows::Forms::LinkLabel());
				this->link_email = (gcnew System::Windows::Forms::LinkLabel());
				this->author_data = (gcnew System::Windows::Forms::Label());
				this->email_data = (gcnew System::Windows::Forms::Label());
				this->author = (gcnew System::Windows::Forms::GroupBox());
				this->LOG_Print = (gcnew System::Windows::Forms::Button());
				this->LOG_Clear = (gcnew System::Windows::Forms::Button());
				this->groupBox_INFO = (gcnew System::Windows::Forms::GroupBox());
				this->tutorial = (gcnew System::Windows::Forms::Button());
				this->PANIC = (gcnew System::Windows::Forms::Button());
				this->label_PANIC = (gcnew System::Windows::Forms::Label());
				this->label_all = (gcnew System::Windows::Forms::Label());
				this->all = (gcnew System::Windows::Forms::Button());
				this->groupBox_Samples_List->SuspendLayout();
				this->groupBox_Import->SuspendLayout();
				this->groupBox_ANC->SuspendLayout();
				this->groupBox_Samples_TODO->SuspendLayout();
				this->groupBox_Results->SuspendLayout();
				this->groupBox_Results_Data->SuspendLayout();
				this->groupBox_Header->SuspendLayout();
				this->groupBox_228->SuspendLayout();
				this->groupBox_WIR->SuspendLayout();
				this->groupBox_RES->SuspendLayout();
				this->groupBox_IRS->SuspendLayout();
				this->author->SuspendLayout();
				this->groupBox_INFO->SuspendLayout();
				this->SuspendLayout();
				// 
				// go_Header
				// 
				this->go_Header->AccessibleDescription = nullptr;
				this->go_Header->AccessibleName = nullptr;
				resources->ApplyResources(this->go_Header, L"go_Header");
				this->go_Header->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->go_Header->BackgroundImage = nullptr;
				this->go_Header->Font = nullptr;
				this->go_Header->ForeColor = System::Drawing::Color::Black;
				this->go_Header->Name = L"go_Header";
				this->go_Header->UseVisualStyleBackColor = false;
				this->go_Header->Click += gcnew System::EventHandler(this, &Form1::go_Header_Click);
				// 
				// FileDialog_KPG
				// 
				resources->ApplyResources(this->FileDialog_KPG, L"FileDialog_KPG");
				this->FileDialog_KPG->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::FileDialog_KPG_FileOk);
				// 
				// HeaderBox
				// 
				this->HeaderBox->AccessibleDescription = nullptr;
				this->HeaderBox->AccessibleName = nullptr;
				resources->ApplyResources(this->HeaderBox, L"HeaderBox");
				this->HeaderBox->BackColor = System::Drawing::SystemColors::ControlLightLight;
				this->HeaderBox->BackgroundImage = nullptr;
				this->HeaderBox->Font = nullptr;
				this->HeaderBox->Name = L"HeaderBox";
				this->HeaderBox->ReadOnly = true;
				this->HeaderBox->TextChanged += gcnew System::EventHandler(this, &Form1::HeaderBox_TextChanged);
				// 
				// groupBox_Samples_List
				// 
				this->groupBox_Samples_List->AccessibleDescription = nullptr;
				this->groupBox_Samples_List->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_Samples_List, L"groupBox_Samples_List");
				this->groupBox_Samples_List->BackgroundImage = nullptr;
				this->groupBox_Samples_List->Controls->Add(this->Box_Samples_List);
				this->groupBox_Samples_List->ForeColor = System::Drawing::Color::Black;
				this->groupBox_Samples_List->Name = L"groupBox_Samples_List";
				this->groupBox_Samples_List->TabStop = false;
				this->groupBox_Samples_List->MouseCaptureChanged += gcnew System::EventHandler(this, &Form1::HeaderBox_TextChanged);
				// 
				// Box_Samples_List
				// 
				this->Box_Samples_List->AcceptsReturn = true;
				this->Box_Samples_List->AcceptsTab = true;
				this->Box_Samples_List->AccessibleDescription = nullptr;
				this->Box_Samples_List->AccessibleName = nullptr;
				this->Box_Samples_List->AllowDrop = true;
				resources->ApplyResources(this->Box_Samples_List, L"Box_Samples_List");
				this->Box_Samples_List->BackgroundImage = nullptr;
				this->Box_Samples_List->Font = nullptr;
				this->Box_Samples_List->Name = L"Box_Samples_List";
				// 
				// Gth
				// 
				this->Gth->AccessibleDescription = nullptr;
				this->Gth->AccessibleName = nullptr;
				resources->ApplyResources(this->Gth, L"Gth");
				this->Gth->BackgroundImage = nullptr;
				this->Gth->Font = nullptr;
				this->Gth->Name = L"Gth";
				// 
				// Gepi
				// 
				this->Gepi->AccessibleDescription = nullptr;
				this->Gepi->AccessibleName = nullptr;
				resources->ApplyResources(this->Gepi, L"Gepi");
				this->Gepi->BackgroundImage = nullptr;
				this->Gepi->Font = nullptr;
				this->Gepi->Name = L"Gepi";
				// 
				// ENAA
				// 
				this->ENAA->AccessibleDescription = nullptr;
				this->ENAA->AccessibleName = nullptr;
				resources->ApplyResources(this->ENAA, L"ENAA");
				this->ENAA->BackgroundImage = nullptr;
				this->ENAA->Font = nullptr;
				this->ENAA->Name = L"ENAA";
				// 
				// ti
				// 
				this->ti->AccessibleDescription = nullptr;
				this->ti->AccessibleName = nullptr;
				resources->ApplyResources(this->ti, L"ti");
				this->ti->BackgroundImage = nullptr;
				this->ti->Font = nullptr;
				this->ti->Name = L"ti";
				// 
				// label_Gth
				// 
				this->label_Gth->AccessibleDescription = nullptr;
				this->label_Gth->AccessibleName = nullptr;
				resources->ApplyResources(this->label_Gth, L"label_Gth");
				this->label_Gth->Name = L"label_Gth";
				// 
				// label_Gepi
				// 
				this->label_Gepi->AccessibleDescription = nullptr;
				this->label_Gepi->AccessibleName = nullptr;
				resources->ApplyResources(this->label_Gepi, L"label_Gepi");
				this->label_Gepi->Name = L"label_Gepi";
				// 
				// label_irradiation_time
				// 
				this->label_irradiation_time->AccessibleDescription = nullptr;
				this->label_irradiation_time->AccessibleName = nullptr;
				resources->ApplyResources(this->label_irradiation_time, L"label_irradiation_time");
				this->label_irradiation_time->Name = L"label_irradiation_time";
				// 
				// label_ENAA
				// 
				this->label_ENAA->AccessibleDescription = nullptr;
				this->label_ENAA->AccessibleName = nullptr;
				resources->ApplyResources(this->label_ENAA, L"label_ENAA");
				this->label_ENAA->Name = L"label_ENAA";
				// 
				// go_KPG_Import
				// 
				this->go_KPG_Import->AccessibleDescription = nullptr;
				this->go_KPG_Import->AccessibleName = nullptr;
				resources->ApplyResources(this->go_KPG_Import, L"go_KPG_Import");
				this->go_KPG_Import->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->go_KPG_Import->BackgroundImage = nullptr;
				this->go_KPG_Import->Font = nullptr;
				this->go_KPG_Import->Name = L"go_KPG_Import";
				this->go_KPG_Import->UseVisualStyleBackColor = false;
				this->go_KPG_Import->Click += gcnew System::EventHandler(this, &Form1::go_KPG_Import_Click);
				// 
				// ancBox1
				// 
				this->ancBox1->AccessibleDescription = nullptr;
				this->ancBox1->AccessibleName = nullptr;
				resources->ApplyResources(this->ancBox1, L"ancBox1");
				this->ancBox1->BackgroundImage = nullptr;
				this->ancBox1->Name = L"ancBox1";
				this->ancBox1->UseVisualStyleBackColor = true;
				// 
				// Sample1
				// 
				this->Sample1->AccessibleDescription = nullptr;
				this->Sample1->AccessibleName = nullptr;
				this->Sample1->AllowDrop = true;
				resources->ApplyResources(this->Sample1, L"Sample1");
				this->Sample1->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
				this->Sample1->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::FileSystem;
				this->Sample1->BackgroundImage = nullptr;
				this->Sample1->Font = nullptr;
				this->Sample1->Name = L"Sample1";
				this->Sample1->TextChanged += gcnew System::EventHandler(this, &Form1::Sample1_TextChanged);
				// 
				// Sample2
				// 
				this->Sample2->AccessibleDescription = nullptr;
				this->Sample2->AccessibleName = nullptr;
				this->Sample2->AllowDrop = true;
				resources->ApplyResources(this->Sample2, L"Sample2");
				this->Sample2->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
				this->Sample2->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::FileSystem;
				this->Sample2->BackgroundImage = nullptr;
				this->Sample2->Font = nullptr;
				this->Sample2->Name = L"Sample2";
				this->Sample2->TextChanged += gcnew System::EventHandler(this, &Form1::Sample2_TextChanged);
				// 
				// Sample3
				// 
				this->Sample3->AccessibleDescription = nullptr;
				this->Sample3->AccessibleName = nullptr;
				this->Sample3->AllowDrop = true;
				resources->ApplyResources(this->Sample3, L"Sample3");
				this->Sample3->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
				this->Sample3->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::FileSystem;
				this->Sample3->BackgroundImage = nullptr;
				this->Sample3->Font = nullptr;
				this->Sample3->Name = L"Sample3";
				this->Sample3->TextChanged += gcnew System::EventHandler(this, &Form1::Sample3_TextChanged);
				// 
				// Sample4
				// 
				this->Sample4->AccessibleDescription = nullptr;
				this->Sample4->AccessibleName = nullptr;
				this->Sample4->AllowDrop = true;
				resources->ApplyResources(this->Sample4, L"Sample4");
				this->Sample4->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
				this->Sample4->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::FileSystem;
				this->Sample4->BackgroundImage = nullptr;
				this->Sample4->Font = nullptr;
				this->Sample4->Name = L"Sample4";
				this->Sample4->TextChanged += gcnew System::EventHandler(this, &Form1::Sample4_TextChanged);
				// 
				// Sample5
				// 
				this->Sample5->AccessibleDescription = nullptr;
				this->Sample5->AccessibleName = nullptr;
				this->Sample5->AllowDrop = true;
				resources->ApplyResources(this->Sample5, L"Sample5");
				this->Sample5->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
				this->Sample5->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::FileSystem;
				this->Sample5->BackgroundImage = nullptr;
				this->Sample5->Font = nullptr;
				this->Sample5->Name = L"Sample5";
				this->Sample5->TextChanged += gcnew System::EventHandler(this, &Form1::Sample5_TextChanged);
				// 
				// Sample6
				// 
				this->Sample6->AccessibleDescription = nullptr;
				this->Sample6->AccessibleName = nullptr;
				this->Sample6->AllowDrop = true;
				resources->ApplyResources(this->Sample6, L"Sample6");
				this->Sample6->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
				this->Sample6->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::FileSystem;
				this->Sample6->BackgroundImage = nullptr;
				this->Sample6->Font = nullptr;
				this->Sample6->Name = L"Sample6";
				this->Sample6->TextChanged += gcnew System::EventHandler(this, &Form1::Sample6_TextChanged);
				// 
				// ancBox2
				// 
				this->ancBox2->AccessibleDescription = nullptr;
				this->ancBox2->AccessibleName = nullptr;
				resources->ApplyResources(this->ancBox2, L"ancBox2");
				this->ancBox2->BackgroundImage = nullptr;
				this->ancBox2->Name = L"ancBox2";
				this->ancBox2->UseVisualStyleBackColor = true;
				// 
				// ancBox3
				// 
				this->ancBox3->AccessibleDescription = nullptr;
				this->ancBox3->AccessibleName = nullptr;
				resources->ApplyResources(this->ancBox3, L"ancBox3");
				this->ancBox3->BackgroundImage = nullptr;
				this->ancBox3->Name = L"ancBox3";
				this->ancBox3->UseVisualStyleBackColor = true;
				// 
				// ancBox4
				// 
				this->ancBox4->AccessibleDescription = nullptr;
				this->ancBox4->AccessibleName = nullptr;
				resources->ApplyResources(this->ancBox4, L"ancBox4");
				this->ancBox4->BackgroundImage = nullptr;
				this->ancBox4->Name = L"ancBox4";
				this->ancBox4->UseVisualStyleBackColor = true;
				// 
				// ancBox5
				// 
				this->ancBox5->AccessibleDescription = nullptr;
				this->ancBox5->AccessibleName = nullptr;
				resources->ApplyResources(this->ancBox5, L"ancBox5");
				this->ancBox5->BackgroundImage = nullptr;
				this->ancBox5->Name = L"ancBox5";
				this->ancBox5->UseVisualStyleBackColor = true;
				// 
				// ancBox6
				// 
				this->ancBox6->AccessibleDescription = nullptr;
				this->ancBox6->AccessibleName = nullptr;
				resources->ApplyResources(this->ancBox6, L"ancBox6");
				this->ancBox6->BackgroundImage = nullptr;
				this->ancBox6->Name = L"ancBox6";
				this->ancBox6->UseVisualStyleBackColor = true;
				// 
				// batch
				// 
				this->batch->AccessibleDescription = nullptr;
				this->batch->AccessibleName = nullptr;
				resources->ApplyResources(this->batch, L"batch");
				this->batch->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->batch->BackgroundImage = nullptr;
				this->batch->Font = nullptr;
				this->batch->Name = L"batch";
				this->batch->UseVisualStyleBackColor = false;
				this->batch->Click += gcnew System::EventHandler(this, &Form1::go_batch_Click);
				// 
				// go_ANC
				// 
				this->go_ANC->AccessibleDescription = nullptr;
				this->go_ANC->AccessibleName = nullptr;
				resources->ApplyResources(this->go_ANC, L"go_ANC");
				this->go_ANC->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->go_ANC->BackgroundImage = nullptr;
				this->go_ANC->Font = nullptr;
				this->go_ANC->ForeColor = System::Drawing::Color::Black;
				this->go_ANC->Name = L"go_ANC";
				this->go_ANC->UseVisualStyleBackColor = false;
				this->go_ANC->Click += gcnew System::EventHandler(this, &Form1::go_ANC_Click);
				// 
				// groupBox_Import
				// 
				this->groupBox_Import->AccessibleDescription = nullptr;
				this->groupBox_Import->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_Import, L"groupBox_Import");
				this->groupBox_Import->BackColor = System::Drawing::Color::Wheat;
				this->groupBox_Import->BackgroundImage = nullptr;
				this->groupBox_Import->Controls->Add(this->help_Import);
				this->groupBox_Import->Controls->Add(this->label_step0);
				this->groupBox_Import->Controls->Add(this->go_KPG_view);
				this->groupBox_Import->Controls->Add(this->linkLabel4);
				this->groupBox_Import->Controls->Add(this->KPGBox);
				this->groupBox_Import->Controls->Add(this->go_KPG_browse);
				this->groupBox_Import->Controls->Add(this->label_irradiation_time);
				this->groupBox_Import->Controls->Add(this->Gth);
				this->groupBox_Import->Controls->Add(this->Gepi);
				this->groupBox_Import->Controls->Add(this->ENAA);
				this->groupBox_Import->Controls->Add(this->ti);
				this->groupBox_Import->Controls->Add(this->label_Gth);
				this->groupBox_Import->Controls->Add(this->label_Gepi);
				this->groupBox_Import->Controls->Add(this->label_ENAA);
				this->groupBox_Import->Controls->Add(this->go_KPG_Import);
				this->groupBox_Import->ForeColor = System::Drawing::Color::Black;
				this->groupBox_Import->Name = L"groupBox_Import";
				this->groupBox_Import->TabStop = false;
				// 
				// help_Import
				// 
				this->help_Import->AccessibleDescription = nullptr;
				this->help_Import->AccessibleName = nullptr;
				resources->ApplyResources(this->help_Import, L"help_Import");
				this->help_Import->BackColor = System::Drawing::Color::SaddleBrown;
				this->help_Import->Font = nullptr;
				this->help_Import->LinkColor = System::Drawing::Color::Yellow;
				this->help_Import->Name = L"help_Import";
				this->help_Import->TabStop = true;
				this->help_Import->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Form1::help_Import_LinkClicked);
				// 
				// label_step0
				// 
				this->label_step0->AccessibleDescription = nullptr;
				this->label_step0->AccessibleName = nullptr;
				resources->ApplyResources(this->label_step0, L"label_step0");
				this->label_step0->Font = nullptr;
				this->label_step0->ForeColor = System::Drawing::SystemColors::HotTrack;
				this->label_step0->Name = L"label_step0";
				// 
				// go_KPG_view
				// 
				this->go_KPG_view->AccessibleDescription = nullptr;
				this->go_KPG_view->AccessibleName = nullptr;
				resources->ApplyResources(this->go_KPG_view, L"go_KPG_view");
				this->go_KPG_view->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->go_KPG_view->BackgroundImage = nullptr;
				this->go_KPG_view->Font = nullptr;
				this->go_KPG_view->Name = L"go_KPG_view";
				this->go_KPG_view->UseVisualStyleBackColor = false;
				this->go_KPG_view->Click += gcnew System::EventHandler(this, &Form1::go_KPG_view_Click);
				// 
				// linkLabel4
				// 
				this->linkLabel4->AccessibleDescription = nullptr;
				this->linkLabel4->AccessibleName = nullptr;
				resources->ApplyResources(this->linkLabel4, L"linkLabel4");
				this->linkLabel4->Font = nullptr;
				this->linkLabel4->Name = L"linkLabel4";
				this->linkLabel4->TabStop = true;
				// 
				// KPGBox
				// 
				this->KPGBox->AccessibleDescription = nullptr;
				this->KPGBox->AccessibleName = nullptr;
				resources->ApplyResources(this->KPGBox, L"KPGBox");
				this->KPGBox->BackColor = System::Drawing::SystemColors::Info;
				this->KPGBox->BackgroundImage = nullptr;
				this->KPGBox->Font = nullptr;
				this->KPGBox->Name = L"KPGBox";
				this->KPGBox->ReadOnly = true;
				// 
				// go_KPG_browse
				// 
				this->go_KPG_browse->AccessibleDescription = nullptr;
				this->go_KPG_browse->AccessibleName = nullptr;
				resources->ApplyResources(this->go_KPG_browse, L"go_KPG_browse");
				this->go_KPG_browse->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->go_KPG_browse->BackgroundImage = nullptr;
				this->go_KPG_browse->Font = nullptr;
				this->go_KPG_browse->Name = L"go_KPG_browse";
				this->go_KPG_browse->UseVisualStyleBackColor = false;
				this->go_KPG_browse->Click += gcnew System::EventHandler(this, &Form1::go_KPG_browse_Click);
				// 
				// edit_raw
				// 
				this->edit_raw->AccessibleDescription = nullptr;
				this->edit_raw->AccessibleName = nullptr;
				resources->ApplyResources(this->edit_raw, L"edit_raw");
				this->edit_raw->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->edit_raw->BackgroundImage = nullptr;
				this->edit_raw->Font = nullptr;
				this->edit_raw->Name = L"edit_raw";
				this->edit_raw->UseVisualStyleBackColor = false;
				this->edit_raw->Click += gcnew System::EventHandler(this, &Form1::edit_raw_Click);
				// 
				// groupBox_ANC
				// 
				this->groupBox_ANC->AccessibleDescription = nullptr;
				this->groupBox_ANC->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_ANC, L"groupBox_ANC");
				this->groupBox_ANC->BackColor = System::Drawing::Color::DarkSeaGreen;
				this->groupBox_ANC->BackgroundImage = nullptr;
				this->groupBox_ANC->Controls->Add(this->help_ANC);
				this->groupBox_ANC->Controls->Add(this->edit_anc);
				this->groupBox_ANC->Controls->Add(this->ancBox1);
				this->groupBox_ANC->Controls->Add(this->ancBox6);
				this->groupBox_ANC->Controls->Add(this->ancBox5);
				this->groupBox_ANC->Controls->Add(this->ancBox3);
				this->groupBox_ANC->Controls->Add(this->ancBox4);
				this->groupBox_ANC->Controls->Add(this->go_ANC);
				this->groupBox_ANC->Controls->Add(this->ancBox2);
				this->groupBox_ANC->ForeColor = System::Drawing::Color::Black;
				this->groupBox_ANC->Name = L"groupBox_ANC";
				this->groupBox_ANC->TabStop = false;
				this->groupBox_ANC->MouseCaptureChanged += gcnew System::EventHandler(this, &Form1::groupBox_ANC_Enter);
				// 
				// help_ANC
				// 
				this->help_ANC->AccessibleDescription = nullptr;
				this->help_ANC->AccessibleName = nullptr;
				resources->ApplyResources(this->help_ANC, L"help_ANC");
				this->help_ANC->BackColor = System::Drawing::Color::SteelBlue;
				this->help_ANC->Font = nullptr;
				this->help_ANC->LinkColor = System::Drawing::Color::White;
				this->help_ANC->Name = L"help_ANC";
				this->help_ANC->TabStop = true;
				this->help_ANC->VisitedLinkColor = System::Drawing::Color::White;
				this->help_ANC->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Form1::help_ANC_LinkClicked);
				// 
				// edit_anc
				// 
				this->edit_anc->AccessibleDescription = nullptr;
				this->edit_anc->AccessibleName = nullptr;
				resources->ApplyResources(this->edit_anc, L"edit_anc");
				this->edit_anc->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->edit_anc->BackgroundImage = nullptr;
				this->edit_anc->Font = nullptr;
				this->edit_anc->ForeColor = System::Drawing::Color::Black;
				this->edit_anc->Name = L"edit_anc";
				this->edit_anc->UseVisualStyleBackColor = false;
				this->edit_anc->Click += gcnew System::EventHandler(this, &Form1::edit_anc_Click);
				// 
				// groupBox_Samples_TODO
				// 
				this->groupBox_Samples_TODO->AccessibleDescription = nullptr;
				this->groupBox_Samples_TODO->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_Samples_TODO, L"groupBox_Samples_TODO");
				this->groupBox_Samples_TODO->BackColor = System::Drawing::Color::Lavender;
				this->groupBox_Samples_TODO->BackgroundImage = nullptr;
				this->groupBox_Samples_TODO->Controls->Add(this->rawBox1);
				this->groupBox_Samples_TODO->Controls->Add(this->rawBox6);
				this->groupBox_Samples_TODO->Controls->Add(this->rawBox5);
				this->groupBox_Samples_TODO->Controls->Add(this->rawBox3);
				this->groupBox_Samples_TODO->Controls->Add(this->rawBox4);
				this->groupBox_Samples_TODO->Controls->Add(this->batch);
				this->groupBox_Samples_TODO->Controls->Add(this->rawBox2);
				this->groupBox_Samples_TODO->Controls->Add(this->Sample3);
				this->groupBox_Samples_TODO->Controls->Add(this->edit_raw);
				this->groupBox_Samples_TODO->Controls->Add(this->Sample5);
				this->groupBox_Samples_TODO->Controls->Add(this->Sample4);
				this->groupBox_Samples_TODO->Controls->Add(this->Sample6);
				this->groupBox_Samples_TODO->Controls->Add(this->Sample2);
				this->groupBox_Samples_TODO->Controls->Add(this->Sample1);
				this->groupBox_Samples_TODO->ForeColor = System::Drawing::Color::Black;
				this->groupBox_Samples_TODO->Name = L"groupBox_Samples_TODO";
				this->groupBox_Samples_TODO->TabStop = false;
				this->groupBox_Samples_TODO->MouseCaptureChanged += gcnew System::EventHandler(this, &Form1::groupBox_Samples_TODO_Enter);
				// 
				// rawBox1
				// 
				this->rawBox1->AccessibleDescription = nullptr;
				this->rawBox1->AccessibleName = nullptr;
				resources->ApplyResources(this->rawBox1, L"rawBox1");
				this->rawBox1->BackgroundImage = nullptr;
				this->rawBox1->Name = L"rawBox1";
				this->rawBox1->UseVisualStyleBackColor = true;
				// 
				// rawBox6
				// 
				this->rawBox6->AccessibleDescription = nullptr;
				this->rawBox6->AccessibleName = nullptr;
				resources->ApplyResources(this->rawBox6, L"rawBox6");
				this->rawBox6->BackgroundImage = nullptr;
				this->rawBox6->Name = L"rawBox6";
				this->rawBox6->UseVisualStyleBackColor = true;
				// 
				// rawBox5
				// 
				this->rawBox5->AccessibleDescription = nullptr;
				this->rawBox5->AccessibleName = nullptr;
				resources->ApplyResources(this->rawBox5, L"rawBox5");
				this->rawBox5->BackgroundImage = nullptr;
				this->rawBox5->Name = L"rawBox5";
				this->rawBox5->UseVisualStyleBackColor = true;
				// 
				// rawBox3
				// 
				this->rawBox3->AccessibleDescription = nullptr;
				this->rawBox3->AccessibleName = nullptr;
				resources->ApplyResources(this->rawBox3, L"rawBox3");
				this->rawBox3->BackgroundImage = nullptr;
				this->rawBox3->Name = L"rawBox3";
				this->rawBox3->UseVisualStyleBackColor = true;
				// 
				// rawBox4
				// 
				this->rawBox4->AccessibleDescription = nullptr;
				this->rawBox4->AccessibleName = nullptr;
				resources->ApplyResources(this->rawBox4, L"rawBox4");
				this->rawBox4->BackgroundImage = nullptr;
				this->rawBox4->Name = L"rawBox4";
				this->rawBox4->UseVisualStyleBackColor = true;
				// 
				// rawBox2
				// 
				this->rawBox2->AccessibleDescription = nullptr;
				this->rawBox2->AccessibleName = nullptr;
				resources->ApplyResources(this->rawBox2, L"rawBox2");
				this->rawBox2->BackgroundImage = nullptr;
				this->rawBox2->Name = L"rawBox2";
				this->rawBox2->UseVisualStyleBackColor = true;
				// 
				// WIR
				// 
				this->WIR->AccessibleDescription = nullptr;
				this->WIR->AccessibleName = nullptr;
				resources->ApplyResources(this->WIR, L"WIR");
				this->WIR->BackColor = System::Drawing::SystemColors::Info;
				this->WIR->BackgroundImage = nullptr;
				this->WIR->ForeColor = System::Drawing::SystemColors::WindowText;
				this->WIR->Name = L"WIR";
				this->WIR->ReadOnly = true;
				// 
				// U235
				// 
				this->U235->AccessibleDescription = nullptr;
				this->U235->AccessibleName = nullptr;
				resources->ApplyResources(this->U235, L"U235");
				this->U235->BackColor = System::Drawing::SystemColors::Info;
				this->U235->BackgroundImage = nullptr;
				this->U235->ForeColor = System::Drawing::SystemColors::WindowText;
				this->U235->Name = L"U235";
				this->U235->ReadOnly = true;
				// 
				// U238
				// 
				this->U238->AccessibleDescription = nullptr;
				this->U238->AccessibleName = nullptr;
				resources->ApplyResources(this->U238, L"U238");
				this->U238->BackColor = System::Drawing::SystemColors::Info;
				this->U238->BackgroundImage = nullptr;
				this->U238->ForeColor = System::Drawing::SystemColors::WindowText;
				this->U238->Name = L"U238";
				this->U238->ReadOnly = true;
				// 
				// RO
				// 
				this->RO->AccessibleDescription = nullptr;
				this->RO->AccessibleName = nullptr;
				resources->ApplyResources(this->RO, L"RO");
				this->RO->BackColor = System::Drawing::SystemColors::Info;
				this->RO->BackgroundImage = nullptr;
				this->RO->ForeColor = System::Drawing::SystemColors::WindowText;
				this->RO->Name = L"RO";
				this->RO->ReadOnly = true;
				// 
				// label_WIR
				// 
				this->label_WIR->AccessibleDescription = nullptr;
				this->label_WIR->AccessibleName = nullptr;
				resources->ApplyResources(this->label_WIR, L"label_WIR");
				this->label_WIR->Name = L"label_WIR";
				// 
				// label_U235
				// 
				this->label_U235->AccessibleDescription = nullptr;
				this->label_U235->AccessibleName = nullptr;
				resources->ApplyResources(this->label_U235, L"label_U235");
				this->label_U235->Name = L"label_U235";
				// 
				// label_U238
				// 
				this->label_U238->AccessibleDescription = nullptr;
				this->label_U238->AccessibleName = nullptr;
				resources->ApplyResources(this->label_U238, L"label_U238");
				this->label_U238->Name = L"label_U238";
				// 
				// label_RO
				// 
				this->label_RO->AccessibleDescription = nullptr;
				this->label_RO->AccessibleName = nullptr;
				resources->ApplyResources(this->label_RO, L"label_RO");
				this->label_RO->Name = L"label_RO";
				// 
				// SD
				// 
				this->SD->AccessibleDescription = nullptr;
				this->SD->AccessibleName = nullptr;
				resources->ApplyResources(this->SD, L"SD");
				this->SD->BackColor = System::Drawing::SystemColors::Info;
				this->SD->BackgroundImage = nullptr;
				this->SD->ForeColor = System::Drawing::SystemColors::WindowText;
				this->SD->Name = L"SD";
				this->SD->ReadOnly = true;
				// 
				// label_SD
				// 
				this->label_SD->AccessibleDescription = nullptr;
				this->label_SD->AccessibleName = nullptr;
				resources->ApplyResources(this->label_SD, L"label_SD");
				this->label_SD->Name = L"label_SD";
				// 
				// quoteU
				// 
				this->quoteU->AccessibleDescription = nullptr;
				this->quoteU->AccessibleName = nullptr;
				resources->ApplyResources(this->quoteU, L"quoteU");
				this->quoteU->ForeColor = System::Drawing::Color::Crimson;
				this->quoteU->Name = L"quoteU";
				// 
				// groupBox_Results
				// 
				this->groupBox_Results->AccessibleDescription = nullptr;
				this->groupBox_Results->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_Results, L"groupBox_Results");
				this->groupBox_Results->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->groupBox_Results->BackgroundImage = nullptr;
				this->groupBox_Results->Controls->Add(this->DT);
				this->groupBox_Results->Controls->Add(this->WSAMPLE);
				this->groupBox_Results->Controls->Add(this->groupBox_Results_Data);
				this->groupBox_Results->Controls->Add(this->quoteU);
				this->groupBox_Results->Name = L"groupBox_Results";
				this->groupBox_Results->TabStop = false;
				// 
				// DT
				// 
				this->DT->AccessibleDescription = nullptr;
				this->DT->AccessibleName = nullptr;
				resources->ApplyResources(this->DT, L"DT");
				this->DT->ForeColor = System::Drawing::Color::MidnightBlue;
				this->DT->Name = L"DT";
				// 
				// WSAMPLE
				// 
				this->WSAMPLE->AccessibleDescription = nullptr;
				this->WSAMPLE->AccessibleName = nullptr;
				resources->ApplyResources(this->WSAMPLE, L"WSAMPLE");
				this->WSAMPLE->ForeColor = System::Drawing::Color::MidnightBlue;
				this->WSAMPLE->Name = L"WSAMPLE";
				// 
				// groupBox_Results_Data
				// 
				this->groupBox_Results_Data->AccessibleDescription = nullptr;
				this->groupBox_Results_Data->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_Results_Data, L"groupBox_Results_Data");
				this->groupBox_Results_Data->BackgroundImage = nullptr;
				this->groupBox_Results_Data->Controls->Add(this->label_SDobs);
				this->groupBox_Results_Data->Controls->Add(this->label_SDexp);
				this->groupBox_Results_Data->Controls->Add(this->SDexp);
				this->groupBox_Results_Data->Controls->Add(this->SDobs);
				this->groupBox_Results_Data->Controls->Add(this->label_RO5);
				this->groupBox_Results_Data->Controls->Add(this->RO5);
				this->groupBox_Results_Data->Controls->Add(this->label_RO8);
				this->groupBox_Results_Data->Controls->Add(this->RO8);
				this->groupBox_Results_Data->Controls->Add(this->WIR);
				this->groupBox_Results_Data->Controls->Add(this->label_AW);
				this->groupBox_Results_Data->Controls->Add(this->label_U235);
				this->groupBox_Results_Data->Controls->Add(this->AW);
				this->groupBox_Results_Data->Controls->Add(this->label_U238);
				this->groupBox_Results_Data->Controls->Add(this->U238);
				this->groupBox_Results_Data->Controls->Add(this->label_WIR);
				this->groupBox_Results_Data->Controls->Add(this->label_RO);
				this->groupBox_Results_Data->Controls->Add(this->RO);
				this->groupBox_Results_Data->Controls->Add(this->label_SD);
				this->groupBox_Results_Data->Controls->Add(this->SD);
				this->groupBox_Results_Data->Controls->Add(this->U235);
				this->groupBox_Results_Data->Font = nullptr;
				this->groupBox_Results_Data->Name = L"groupBox_Results_Data";
				this->groupBox_Results_Data->TabStop = false;
				// 
				// label_SDobs
				// 
				this->label_SDobs->AccessibleDescription = nullptr;
				this->label_SDobs->AccessibleName = nullptr;
				resources->ApplyResources(this->label_SDobs, L"label_SDobs");
				this->label_SDobs->Name = L"label_SDobs";
				// 
				// label_SDexp
				// 
				this->label_SDexp->AccessibleDescription = nullptr;
				this->label_SDexp->AccessibleName = nullptr;
				resources->ApplyResources(this->label_SDexp, L"label_SDexp");
				this->label_SDexp->Name = L"label_SDexp";
				// 
				// SDexp
				// 
				this->SDexp->AccessibleDescription = nullptr;
				this->SDexp->AccessibleName = nullptr;
				resources->ApplyResources(this->SDexp, L"SDexp");
				this->SDexp->BackColor = System::Drawing::SystemColors::Info;
				this->SDexp->BackgroundImage = nullptr;
				this->SDexp->ForeColor = System::Drawing::SystemColors::WindowText;
				this->SDexp->Name = L"SDexp";
				this->SDexp->ReadOnly = true;
				// 
				// SDobs
				// 
				this->SDobs->AccessibleDescription = nullptr;
				this->SDobs->AccessibleName = nullptr;
				resources->ApplyResources(this->SDobs, L"SDobs");
				this->SDobs->BackColor = System::Drawing::SystemColors::Info;
				this->SDobs->BackgroundImage = nullptr;
				this->SDobs->ForeColor = System::Drawing::SystemColors::WindowText;
				this->SDobs->Name = L"SDobs";
				this->SDobs->ReadOnly = true;
				// 
				// label_RO5
				// 
				this->label_RO5->AccessibleDescription = nullptr;
				this->label_RO5->AccessibleName = nullptr;
				resources->ApplyResources(this->label_RO5, L"label_RO5");
				this->label_RO5->Name = L"label_RO5";
				// 
				// RO5
				// 
				this->RO5->AccessibleDescription = nullptr;
				this->RO5->AccessibleName = nullptr;
				resources->ApplyResources(this->RO5, L"RO5");
				this->RO5->BackColor = System::Drawing::SystemColors::Info;
				this->RO5->BackgroundImage = nullptr;
				this->RO5->ForeColor = System::Drawing::SystemColors::WindowText;
				this->RO5->Name = L"RO5";
				this->RO5->ReadOnly = true;
				// 
				// label_RO8
				// 
				this->label_RO8->AccessibleDescription = nullptr;
				this->label_RO8->AccessibleName = nullptr;
				resources->ApplyResources(this->label_RO8, L"label_RO8");
				this->label_RO8->Name = L"label_RO8";
				// 
				// RO8
				// 
				this->RO8->AccessibleDescription = nullptr;
				this->RO8->AccessibleName = nullptr;
				resources->ApplyResources(this->RO8, L"RO8");
				this->RO8->BackColor = System::Drawing::SystemColors::Info;
				this->RO8->BackgroundImage = nullptr;
				this->RO8->ForeColor = System::Drawing::SystemColors::WindowText;
				this->RO8->Name = L"RO8";
				this->RO8->ReadOnly = true;
				// 
				// label_AW
				// 
				this->label_AW->AccessibleDescription = nullptr;
				this->label_AW->AccessibleName = nullptr;
				resources->ApplyResources(this->label_AW, L"label_AW");
				this->label_AW->Name = L"label_AW";
				// 
				// AW
				// 
				this->AW->AccessibleDescription = nullptr;
				this->AW->AccessibleName = nullptr;
				resources->ApplyResources(this->AW, L"AW");
				this->AW->BackColor = System::Drawing::SystemColors::Info;
				this->AW->BackgroundImage = nullptr;
				this->AW->ForeColor = System::Drawing::SystemColors::WindowText;
				this->AW->Name = L"AW";
				this->AW->ReadOnly = true;
				// 
				// LOG
				// 
				this->LOG->AccessibleDescription = nullptr;
				this->LOG->AccessibleName = nullptr;
				resources->ApplyResources(this->LOG, L"LOG");
				this->LOG->BackgroundImage = nullptr;
				this->LOG->Name = L"LOG";
				this->LOG->TextChanged += gcnew System::EventHandler(this, &Form1::LOG_TextChanged);
				// 
				// process
				// 
				this->process->StartInfo->Domain = L"";
				this->process->StartInfo->LoadUserProfile = false;
				this->process->StartInfo->Password = nullptr;
				this->process->StartInfo->StandardErrorEncoding = nullptr;
				this->process->StartInfo->StandardOutputEncoding = nullptr;
				this->process->StartInfo->UserName = L"";
				this->process->SynchronizingObject = this;
				// 
				// FileDialog_Header
				// 
				resources->ApplyResources(this->FileDialog_Header, L"FileDialog_Header");
				this->FileDialog_Header->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::FileDialog_Header_FileOk);
				// 
				// groupBox_Header
				// 
				this->groupBox_Header->AccessibleDescription = nullptr;
				this->groupBox_Header->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_Header, L"groupBox_Header");
				this->groupBox_Header->BackColor = System::Drawing::Color::Black;
				this->groupBox_Header->BackgroundImage = nullptr;
				this->groupBox_Header->Controls->Add(this->help_Header);
				this->groupBox_Header->Controls->Add(this->label_step1);
				this->groupBox_Header->Controls->Add(this->HeaderBox);
				this->groupBox_Header->Controls->Add(this->go_Header);
				this->groupBox_Header->ForeColor = System::Drawing::SystemColors::GradientActiveCaption;
				this->groupBox_Header->Name = L"groupBox_Header";
				this->groupBox_Header->TabStop = false;
				// 
				// help_Header
				// 
				this->help_Header->AccessibleDescription = nullptr;
				this->help_Header->AccessibleName = nullptr;
				resources->ApplyResources(this->help_Header, L"help_Header");
				this->help_Header->BackColor = System::Drawing::Color::White;
				this->help_Header->Font = nullptr;
				this->help_Header->LinkColor = System::Drawing::Color::Black;
				this->help_Header->Name = L"help_Header";
				this->help_Header->TabStop = true;
				this->help_Header->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Form1::help_Header_LinkClicked);
				// 
				// label_step1
				// 
				this->label_step1->AccessibleDescription = nullptr;
				this->label_step1->AccessibleName = nullptr;
				resources->ApplyResources(this->label_step1, L"label_step1");
				this->label_step1->Font = nullptr;
				this->label_step1->ForeColor = System::Drawing::Color::OrangeRed;
				this->label_step1->Name = L"label_step1";
				// 
				// groupBox_228
				// 
				this->groupBox_228->AccessibleDescription = nullptr;
				this->groupBox_228->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_228, L"groupBox_228");
				this->groupBox_228->BackColor = System::Drawing::Color::SaddleBrown;
				this->groupBox_228->BackgroundImage = nullptr;
				this->groupBox_228->Controls->Add(this->help_228);
				this->groupBox_228->Controls->Add(this->go_228);
				this->groupBox_228->Controls->Add(this->NpBox1);
				this->groupBox_228->Controls->Add(this->NpBox2);
				this->groupBox_228->Controls->Add(this->NpBox6);
				this->groupBox_228->Controls->Add(this->NpBox3);
				this->groupBox_228->Controls->Add(this->NpBox5);
				this->groupBox_228->Controls->Add(this->NpBox4);
				this->groupBox_228->ForeColor = System::Drawing::Color::Yellow;
				this->groupBox_228->Name = L"groupBox_228";
				this->groupBox_228->TabStop = false;
				this->groupBox_228->MouseCaptureChanged += gcnew System::EventHandler(this, &Form1::groupBox_228_Enter);
				// 
				// help_228
				// 
				this->help_228->AccessibleDescription = nullptr;
				this->help_228->AccessibleName = nullptr;
				resources->ApplyResources(this->help_228, L"help_228");
				this->help_228->BackColor = System::Drawing::Color::Wheat;
				this->help_228->Font = nullptr;
				this->help_228->LinkColor = System::Drawing::Color::Black;
				this->help_228->Name = L"help_228";
				this->help_228->TabStop = true;
				this->help_228->VisitedLinkColor = System::Drawing::Color::Black;
				this->help_228->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Form1::help_228_LinkClicked);
				// 
				// go_228
				// 
				this->go_228->AccessibleDescription = nullptr;
				this->go_228->AccessibleName = nullptr;
				resources->ApplyResources(this->go_228, L"go_228");
				this->go_228->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->go_228->BackgroundImage = nullptr;
				this->go_228->Font = nullptr;
				this->go_228->ForeColor = System::Drawing::Color::Black;
				this->go_228->Name = L"go_228";
				this->go_228->UseVisualStyleBackColor = false;
				this->go_228->Click += gcnew System::EventHandler(this, &Form1::go_228_Click);
				// 
				// NpBox1
				// 
				this->NpBox1->AccessibleDescription = nullptr;
				this->NpBox1->AccessibleName = nullptr;
				resources->ApplyResources(this->NpBox1, L"NpBox1");
				this->NpBox1->BackgroundImage = nullptr;
				this->NpBox1->Name = L"NpBox1";
				this->NpBox1->UseVisualStyleBackColor = true;
				// 
				// NpBox2
				// 
				this->NpBox2->AccessibleDescription = nullptr;
				this->NpBox2->AccessibleName = nullptr;
				resources->ApplyResources(this->NpBox2, L"NpBox2");
				this->NpBox2->BackgroundImage = nullptr;
				this->NpBox2->Name = L"NpBox2";
				this->NpBox2->UseVisualStyleBackColor = true;
				// 
				// NpBox6
				// 
				this->NpBox6->AccessibleDescription = nullptr;
				this->NpBox6->AccessibleName = nullptr;
				resources->ApplyResources(this->NpBox6, L"NpBox6");
				this->NpBox6->BackgroundImage = nullptr;
				this->NpBox6->Name = L"NpBox6";
				this->NpBox6->UseVisualStyleBackColor = true;
				// 
				// NpBox3
				// 
				this->NpBox3->AccessibleDescription = nullptr;
				this->NpBox3->AccessibleName = nullptr;
				resources->ApplyResources(this->NpBox3, L"NpBox3");
				this->NpBox3->BackgroundImage = nullptr;
				this->NpBox3->Name = L"NpBox3";
				this->NpBox3->UseVisualStyleBackColor = true;
				// 
				// NpBox5
				// 
				this->NpBox5->AccessibleDescription = nullptr;
				this->NpBox5->AccessibleName = nullptr;
				resources->ApplyResources(this->NpBox5, L"NpBox5");
				this->NpBox5->BackgroundImage = nullptr;
				this->NpBox5->Name = L"NpBox5";
				this->NpBox5->UseVisualStyleBackColor = true;
				// 
				// NpBox4
				// 
				this->NpBox4->AccessibleDescription = nullptr;
				this->NpBox4->AccessibleName = nullptr;
				resources->ApplyResources(this->NpBox4, L"NpBox4");
				this->NpBox4->BackgroundImage = nullptr;
				this->NpBox4->Name = L"NpBox4";
				this->NpBox4->UseVisualStyleBackColor = true;
				// 
				// groupBox_WIR
				// 
				this->groupBox_WIR->AccessibleDescription = nullptr;
				this->groupBox_WIR->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_WIR, L"groupBox_WIR");
				this->groupBox_WIR->BackColor = System::Drawing::Color::SteelBlue;
				this->groupBox_WIR->BackgroundImage = nullptr;
				this->groupBox_WIR->Controls->Add(this->help_WIR);
				this->groupBox_WIR->Controls->Add(this->wirBox1);
				this->groupBox_WIR->Controls->Add(this->go_WIR);
				this->groupBox_WIR->Controls->Add(this->edit_wir);
				this->groupBox_WIR->Controls->Add(this->wirBox2);
				this->groupBox_WIR->Controls->Add(this->wirBox3);
				this->groupBox_WIR->Controls->Add(this->wirBox4);
				this->groupBox_WIR->Controls->Add(this->wirBox5);
				this->groupBox_WIR->Controls->Add(this->wirBox6);
				this->groupBox_WIR->ForeColor = System::Drawing::Color::White;
				this->groupBox_WIR->Name = L"groupBox_WIR";
				this->groupBox_WIR->TabStop = false;
				this->groupBox_WIR->MouseCaptureChanged += gcnew System::EventHandler(this, &Form1::groupBox_WIR_Enter);
				// 
				// help_WIR
				// 
				this->help_WIR->AccessibleDescription = nullptr;
				this->help_WIR->AccessibleName = nullptr;
				resources->ApplyResources(this->help_WIR, L"help_WIR");
				this->help_WIR->BackColor = System::Drawing::Color::SeaGreen;
				this->help_WIR->Font = nullptr;
				this->help_WIR->LinkColor = System::Drawing::Color::White;
				this->help_WIR->Name = L"help_WIR";
				this->help_WIR->TabStop = true;
				this->help_WIR->VisitedLinkColor = System::Drawing::Color::White;
				this->help_WIR->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Form1::help_WIR_LinkClicked);
				// 
				// wirBox1
				// 
				this->wirBox1->AccessibleDescription = nullptr;
				this->wirBox1->AccessibleName = nullptr;
				resources->ApplyResources(this->wirBox1, L"wirBox1");
				this->wirBox1->BackgroundImage = nullptr;
				this->wirBox1->Name = L"wirBox1";
				this->wirBox1->UseVisualStyleBackColor = true;
				// 
				// go_WIR
				// 
				this->go_WIR->AccessibleDescription = nullptr;
				this->go_WIR->AccessibleName = nullptr;
				resources->ApplyResources(this->go_WIR, L"go_WIR");
				this->go_WIR->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->go_WIR->BackgroundImage = nullptr;
				this->go_WIR->Font = nullptr;
				this->go_WIR->ForeColor = System::Drawing::Color::Black;
				this->go_WIR->Name = L"go_WIR";
				this->go_WIR->UseVisualStyleBackColor = false;
				this->go_WIR->Click += gcnew System::EventHandler(this, &Form1::go_WIR_Click);
				// 
				// edit_wir
				// 
				this->edit_wir->AccessibleDescription = nullptr;
				this->edit_wir->AccessibleName = nullptr;
				resources->ApplyResources(this->edit_wir, L"edit_wir");
				this->edit_wir->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->edit_wir->BackgroundImage = nullptr;
				this->edit_wir->Font = nullptr;
				this->edit_wir->ForeColor = System::Drawing::Color::Black;
				this->edit_wir->Name = L"edit_wir";
				this->edit_wir->UseVisualStyleBackColor = false;
				this->edit_wir->Click += gcnew System::EventHandler(this, &Form1::edit_wir_Click);
				// 
				// wirBox2
				// 
				this->wirBox2->AccessibleDescription = nullptr;
				this->wirBox2->AccessibleName = nullptr;
				resources->ApplyResources(this->wirBox2, L"wirBox2");
				this->wirBox2->BackgroundImage = nullptr;
				this->wirBox2->Name = L"wirBox2";
				this->wirBox2->UseVisualStyleBackColor = true;
				// 
				// wirBox3
				// 
				this->wirBox3->AccessibleDescription = nullptr;
				this->wirBox3->AccessibleName = nullptr;
				resources->ApplyResources(this->wirBox3, L"wirBox3");
				this->wirBox3->BackgroundImage = nullptr;
				this->wirBox3->Name = L"wirBox3";
				this->wirBox3->UseVisualStyleBackColor = true;
				// 
				// wirBox4
				// 
				this->wirBox4->AccessibleDescription = nullptr;
				this->wirBox4->AccessibleName = nullptr;
				resources->ApplyResources(this->wirBox4, L"wirBox4");
				this->wirBox4->BackgroundImage = nullptr;
				this->wirBox4->Name = L"wirBox4";
				this->wirBox4->UseVisualStyleBackColor = true;
				// 
				// wirBox5
				// 
				this->wirBox5->AccessibleDescription = nullptr;
				this->wirBox5->AccessibleName = nullptr;
				resources->ApplyResources(this->wirBox5, L"wirBox5");
				this->wirBox5->BackgroundImage = nullptr;
				this->wirBox5->Name = L"wirBox5";
				this->wirBox5->UseVisualStyleBackColor = true;
				// 
				// wirBox6
				// 
				this->wirBox6->AccessibleDescription = nullptr;
				this->wirBox6->AccessibleName = nullptr;
				resources->ApplyResources(this->wirBox6, L"wirBox6");
				this->wirBox6->BackgroundImage = nullptr;
				this->wirBox6->Name = L"wirBox6";
				this->wirBox6->UseVisualStyleBackColor = true;
				// 
				// groupBox_RES
				// 
				this->groupBox_RES->AccessibleDescription = nullptr;
				this->groupBox_RES->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_RES, L"groupBox_RES");
				this->groupBox_RES->BackColor = System::Drawing::Color::DarkSalmon;
				this->groupBox_RES->BackgroundImage = nullptr;
				this->groupBox_RES->Controls->Add(this->edit_res);
				this->groupBox_RES->Controls->Add(this->help_RES);
				this->groupBox_RES->Controls->Add(this->resBox1);
				this->groupBox_RES->Controls->Add(this->go_RES);
				this->groupBox_RES->Controls->Add(this->resBox2);
				this->groupBox_RES->Controls->Add(this->resBox3);
				this->groupBox_RES->Controls->Add(this->resBox4);
				this->groupBox_RES->Controls->Add(this->resBox5);
				this->groupBox_RES->Controls->Add(this->resBox6);
				this->groupBox_RES->ForeColor = System::Drawing::Color::Black;
				this->groupBox_RES->Name = L"groupBox_RES";
				this->groupBox_RES->TabStop = false;
				this->groupBox_RES->MouseCaptureChanged += gcnew System::EventHandler(this, &Form1::groupBox_RES_Enter);
				// 
				// edit_res
				// 
				this->edit_res->AccessibleDescription = nullptr;
				this->edit_res->AccessibleName = nullptr;
				resources->ApplyResources(this->edit_res, L"edit_res");
				this->edit_res->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->edit_res->BackgroundImage = nullptr;
				this->edit_res->Font = nullptr;
				this->edit_res->ForeColor = System::Drawing::Color::Black;
				this->edit_res->Name = L"edit_res";
				this->edit_res->UseVisualStyleBackColor = false;
				this->edit_res->Click += gcnew System::EventHandler(this, &Form1::edit_res_Click);
				// 
				// help_RES
				// 
				this->help_RES->AccessibleDescription = nullptr;
				this->help_RES->AccessibleName = nullptr;
				resources->ApplyResources(this->help_RES, L"help_RES");
				this->help_RES->BackColor = System::Drawing::Color::Khaki;
				this->help_RES->Font = nullptr;
				this->help_RES->LinkColor = System::Drawing::Color::Black;
				this->help_RES->Name = L"help_RES";
				this->help_RES->TabStop = true;
				this->help_RES->VisitedLinkColor = System::Drawing::Color::Black;
				this->help_RES->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Form1::help_RES_LinkClicked);
				// 
				// resBox1
				// 
				this->resBox1->AccessibleDescription = nullptr;
				this->resBox1->AccessibleName = nullptr;
				resources->ApplyResources(this->resBox1, L"resBox1");
				this->resBox1->BackgroundImage = nullptr;
				this->resBox1->Name = L"resBox1";
				this->resBox1->UseVisualStyleBackColor = true;
				// 
				// go_RES
				// 
				this->go_RES->AccessibleDescription = nullptr;
				this->go_RES->AccessibleName = nullptr;
				resources->ApplyResources(this->go_RES, L"go_RES");
				this->go_RES->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->go_RES->BackgroundImage = nullptr;
				this->go_RES->Font = nullptr;
				this->go_RES->ForeColor = System::Drawing::Color::Black;
				this->go_RES->Name = L"go_RES";
				this->go_RES->UseVisualStyleBackColor = false;
				this->go_RES->Click += gcnew System::EventHandler(this, &Form1::go_RES_Click);
				// 
				// resBox2
				// 
				this->resBox2->AccessibleDescription = nullptr;
				this->resBox2->AccessibleName = nullptr;
				resources->ApplyResources(this->resBox2, L"resBox2");
				this->resBox2->BackgroundImage = nullptr;
				this->resBox2->Name = L"resBox2";
				this->resBox2->UseVisualStyleBackColor = true;
				// 
				// resBox3
				// 
				this->resBox3->AccessibleDescription = nullptr;
				this->resBox3->AccessibleName = nullptr;
				resources->ApplyResources(this->resBox3, L"resBox3");
				this->resBox3->BackgroundImage = nullptr;
				this->resBox3->Name = L"resBox3";
				this->resBox3->UseVisualStyleBackColor = true;
				// 
				// resBox4
				// 
				this->resBox4->AccessibleDescription = nullptr;
				this->resBox4->AccessibleName = nullptr;
				resources->ApplyResources(this->resBox4, L"resBox4");
				this->resBox4->BackgroundImage = nullptr;
				this->resBox4->Name = L"resBox4";
				this->resBox4->UseVisualStyleBackColor = true;
				// 
				// resBox5
				// 
				this->resBox5->AccessibleDescription = nullptr;
				this->resBox5->AccessibleName = nullptr;
				resources->ApplyResources(this->resBox5, L"resBox5");
				this->resBox5->BackgroundImage = nullptr;
				this->resBox5->Name = L"resBox5";
				this->resBox5->UseVisualStyleBackColor = true;
				// 
				// resBox6
				// 
				this->resBox6->AccessibleDescription = nullptr;
				this->resBox6->AccessibleName = nullptr;
				resources->ApplyResources(this->resBox6, L"resBox6");
				this->resBox6->BackgroundImage = nullptr;
				this->resBox6->Name = L"resBox6";
				this->resBox6->UseVisualStyleBackColor = true;
				// 
				// groupBox_IRS
				// 
				this->groupBox_IRS->AccessibleDescription = nullptr;
				this->groupBox_IRS->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_IRS, L"groupBox_IRS");
				this->groupBox_IRS->BackColor = System::Drawing::Color::Khaki;
				this->groupBox_IRS->BackgroundImage = nullptr;
				this->groupBox_IRS->Controls->Add(this->help_IRS);
				this->groupBox_IRS->Controls->Add(this->edit_irs);
				this->groupBox_IRS->Controls->Add(this->go_IRS);
				this->groupBox_IRS->Controls->Add(this->irsBox1);
				this->groupBox_IRS->Controls->Add(this->irsBox2);
				this->groupBox_IRS->Controls->Add(this->irsBox3);
				this->groupBox_IRS->Controls->Add(this->irsBox4);
				this->groupBox_IRS->Controls->Add(this->irsBox5);
				this->groupBox_IRS->Controls->Add(this->irsBox6);
				this->groupBox_IRS->ForeColor = System::Drawing::Color::Black;
				this->groupBox_IRS->Name = L"groupBox_IRS";
				this->groupBox_IRS->TabStop = false;
				this->groupBox_IRS->MouseCaptureChanged += gcnew System::EventHandler(this, &Form1::groupBox_IRS_Enter);
				// 
				// help_IRS
				// 
				this->help_IRS->AccessibleDescription = nullptr;
				this->help_IRS->AccessibleName = nullptr;
				resources->ApplyResources(this->help_IRS, L"help_IRS");
				this->help_IRS->BackColor = System::Drawing::Color::DarkSalmon;
				this->help_IRS->Font = nullptr;
				this->help_IRS->ForeColor = System::Drawing::Color::White;
				this->help_IRS->LinkColor = System::Drawing::Color::White;
				this->help_IRS->Name = L"help_IRS";
				this->help_IRS->TabStop = true;
				this->help_IRS->VisitedLinkColor = System::Drawing::Color::White;
				this->help_IRS->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Form1::help_IRS_LinkClicked);
				// 
				// edit_irs
				// 
				this->edit_irs->AccessibleDescription = nullptr;
				this->edit_irs->AccessibleName = nullptr;
				resources->ApplyResources(this->edit_irs, L"edit_irs");
				this->edit_irs->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->edit_irs->BackgroundImage = nullptr;
				this->edit_irs->Font = nullptr;
				this->edit_irs->ForeColor = System::Drawing::Color::Black;
				this->edit_irs->Name = L"edit_irs";
				this->edit_irs->UseVisualStyleBackColor = false;
				this->edit_irs->Click += gcnew System::EventHandler(this, &Form1::edit_irs_Click);
				// 
				// go_IRS
				// 
				this->go_IRS->AccessibleDescription = nullptr;
				this->go_IRS->AccessibleName = nullptr;
				resources->ApplyResources(this->go_IRS, L"go_IRS");
				this->go_IRS->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->go_IRS->BackgroundImage = nullptr;
				this->go_IRS->Font = nullptr;
				this->go_IRS->ForeColor = System::Drawing::Color::Black;
				this->go_IRS->Name = L"go_IRS";
				this->go_IRS->UseVisualStyleBackColor = false;
				this->go_IRS->Click += gcnew System::EventHandler(this, &Form1::go_IRS_Click);
				// 
				// irsBox1
				// 
				this->irsBox1->AccessibleDescription = nullptr;
				this->irsBox1->AccessibleName = nullptr;
				resources->ApplyResources(this->irsBox1, L"irsBox1");
				this->irsBox1->BackgroundImage = nullptr;
				this->irsBox1->Name = L"irsBox1";
				this->irsBox1->UseVisualStyleBackColor = true;
				// 
				// irsBox2
				// 
				this->irsBox2->AccessibleDescription = nullptr;
				this->irsBox2->AccessibleName = nullptr;
				resources->ApplyResources(this->irsBox2, L"irsBox2");
				this->irsBox2->BackgroundImage = nullptr;
				this->irsBox2->Name = L"irsBox2";
				this->irsBox2->UseVisualStyleBackColor = true;
				// 
				// irsBox3
				// 
				this->irsBox3->AccessibleDescription = nullptr;
				this->irsBox3->AccessibleName = nullptr;
				resources->ApplyResources(this->irsBox3, L"irsBox3");
				this->irsBox3->BackgroundImage = nullptr;
				this->irsBox3->Name = L"irsBox3";
				this->irsBox3->UseVisualStyleBackColor = true;
				// 
				// irsBox4
				// 
				this->irsBox4->AccessibleDescription = nullptr;
				this->irsBox4->AccessibleName = nullptr;
				resources->ApplyResources(this->irsBox4, L"irsBox4");
				this->irsBox4->BackgroundImage = nullptr;
				this->irsBox4->Name = L"irsBox4";
				this->irsBox4->UseVisualStyleBackColor = true;
				// 
				// irsBox5
				// 
				this->irsBox5->AccessibleDescription = nullptr;
				this->irsBox5->AccessibleName = nullptr;
				resources->ApplyResources(this->irsBox5, L"irsBox5");
				this->irsBox5->BackgroundImage = nullptr;
				this->irsBox5->Name = L"irsBox5";
				this->irsBox5->UseVisualStyleBackColor = true;
				// 
				// irsBox6
				// 
				this->irsBox6->AccessibleDescription = nullptr;
				this->irsBox6->AccessibleName = nullptr;
				resources->ApplyResources(this->irsBox6, L"irsBox6");
				this->irsBox6->BackgroundImage = nullptr;
				this->irsBox6->Name = L"irsBox6";
				this->irsBox6->UseVisualStyleBackColor = true;
				// 
				// link_author
				// 
				this->link_author->AccessibleDescription = nullptr;
				this->link_author->AccessibleName = nullptr;
				resources->ApplyResources(this->link_author, L"link_author");
				this->link_author->Name = L"link_author";
				this->link_author->TabStop = true;
				// 
				// link_email
				// 
				this->link_email->AccessibleDescription = nullptr;
				this->link_email->AccessibleName = nullptr;
				resources->ApplyResources(this->link_email, L"link_email");
				this->link_email->Name = L"link_email";
				this->link_email->TabStop = true;
				// 
				// author_data
				// 
				this->author_data->AccessibleDescription = nullptr;
				this->author_data->AccessibleName = nullptr;
				resources->ApplyResources(this->author_data, L"author_data");
				this->author_data->Name = L"author_data";
				// 
				// email_data
				// 
				this->email_data->AccessibleDescription = nullptr;
				this->email_data->AccessibleName = nullptr;
				resources->ApplyResources(this->email_data, L"email_data");
				this->email_data->Name = L"email_data";
				// 
				// author
				// 
				this->author->AccessibleDescription = nullptr;
				this->author->AccessibleName = nullptr;
				resources->ApplyResources(this->author, L"author");
				this->author->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->author->BackgroundImage = nullptr;
				this->author->Controls->Add(this->link_author);
				this->author->Controls->Add(this->email_data);
				this->author->Controls->Add(this->link_email);
				this->author->Controls->Add(this->author_data);
				this->author->Font = nullptr;
				this->author->Name = L"author";
				this->author->TabStop = false;
				// 
				// LOG_Print
				// 
				this->LOG_Print->AccessibleDescription = nullptr;
				this->LOG_Print->AccessibleName = nullptr;
				resources->ApplyResources(this->LOG_Print, L"LOG_Print");
				this->LOG_Print->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->LOG_Print->BackgroundImage = nullptr;
				this->LOG_Print->Font = nullptr;
				this->LOG_Print->Name = L"LOG_Print";
				this->LOG_Print->UseVisualStyleBackColor = false;
				this->LOG_Print->Click += gcnew System::EventHandler(this, &Form1::LOG_Print_Click);
				// 
				// LOG_Clear
				// 
				this->LOG_Clear->AccessibleDescription = nullptr;
				this->LOG_Clear->AccessibleName = nullptr;
				resources->ApplyResources(this->LOG_Clear, L"LOG_Clear");
				this->LOG_Clear->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->LOG_Clear->BackgroundImage = nullptr;
				this->LOG_Clear->Font = nullptr;
				this->LOG_Clear->Name = L"LOG_Clear";
				this->LOG_Clear->UseVisualStyleBackColor = false;
				this->LOG_Clear->Click += gcnew System::EventHandler(this, &Form1::LOG_Clear_Click);
				// 
				// groupBox_INFO
				// 
				this->groupBox_INFO->AccessibleDescription = nullptr;
				this->groupBox_INFO->AccessibleName = nullptr;
				resources->ApplyResources(this->groupBox_INFO, L"groupBox_INFO");
				this->groupBox_INFO->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->groupBox_INFO->BackgroundImage = nullptr;
				this->groupBox_INFO->Controls->Add(this->LOG);
				this->groupBox_INFO->Controls->Add(this->LOG_Clear);
				this->groupBox_INFO->Controls->Add(this->LOG_Print);
				this->groupBox_INFO->ForeColor = System::Drawing::Color::ForestGreen;
				this->groupBox_INFO->Name = L"groupBox_INFO";
				this->groupBox_INFO->TabStop = false;
				// 
				// tutorial
				// 
				this->tutorial->AccessibleDescription = nullptr;
				this->tutorial->AccessibleName = nullptr;
				resources->ApplyResources(this->tutorial, L"tutorial");
				this->tutorial->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->tutorial->BackgroundImage = nullptr;
				this->tutorial->ForeColor = System::Drawing::Color::Firebrick;
				this->tutorial->Name = L"tutorial";
				this->tutorial->UseVisualStyleBackColor = false;
				this->tutorial->Click += gcnew System::EventHandler(this, &Form1::tutorial_Click);
				// 
				// PANIC
				// 
				this->PANIC->AccessibleDescription = nullptr;
				this->PANIC->AccessibleName = nullptr;
				resources->ApplyResources(this->PANIC, L"PANIC");
				this->PANIC->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->PANIC->BackgroundImage = nullptr;
				this->PANIC->ForeColor = System::Drawing::Color::Black;
				this->PANIC->Name = L"PANIC";
				this->PANIC->UseVisualStyleBackColor = false;
				this->PANIC->Click += gcnew System::EventHandler(this, &Form1::PANIC_Click);
				// 
				// label_PANIC
				// 
				this->label_PANIC->AccessibleDescription = nullptr;
				this->label_PANIC->AccessibleName = nullptr;
				resources->ApplyResources(this->label_PANIC, L"label_PANIC");
				this->label_PANIC->ForeColor = System::Drawing::Color::Red;
				this->label_PANIC->Name = L"label_PANIC";
				// 
				// label_all
				// 
				this->label_all->AccessibleDescription = nullptr;
				this->label_all->AccessibleName = nullptr;
				resources->ApplyResources(this->label_all, L"label_all");
				this->label_all->ForeColor = System::Drawing::Color::DarkSlateBlue;
				this->label_all->Name = L"label_all";
				// 
				// all
				// 
				this->all->AccessibleDescription = nullptr;
				this->all->AccessibleName = nullptr;
				resources->ApplyResources(this->all, L"all");
				this->all->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->all->BackgroundImage = nullptr;
				this->all->ForeColor = System::Drawing::Color::MidnightBlue;
				this->all->Name = L"all";
				this->all->UseVisualStyleBackColor = false;
				this->all->Click += gcnew System::EventHandler(this, &Form1::all_Click);
				// 
				// Form1
				// 
				resources->ApplyResources(this, L"$this");
				this->AccessibleRole = System::Windows::Forms::AccessibleRole::TitleBar;
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->BackColor = System::Drawing::SystemColors::ButtonFace;
				this->BackgroundImage = nullptr;
				this->Controls->Add(this->label_all);
				this->Controls->Add(this->all);
				this->Controls->Add(this->label_PANIC);
				this->Controls->Add(this->PANIC);
				this->Controls->Add(this->tutorial);
				this->Controls->Add(this->groupBox_INFO);
				this->Controls->Add(this->author);
				this->Controls->Add(this->groupBox_IRS);
				this->Controls->Add(this->groupBox_RES);
				this->Controls->Add(this->groupBox_WIR);
				this->Controls->Add(this->groupBox_Header);
				this->Controls->Add(this->groupBox_228);
				this->Controls->Add(this->groupBox_Results);
				this->Controls->Add(this->groupBox_Samples_TODO);
				this->Controls->Add(this->groupBox_ANC);
				this->Controls->Add(this->groupBox_Import);
				this->Controls->Add(this->groupBox_Samples_List);
				this->Font = nullptr;
				this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
				this->Name = L"Form1";
				this->groupBox_Samples_List->ResumeLayout(false);
				this->groupBox_Samples_List->PerformLayout();
				this->groupBox_Import->ResumeLayout(false);
				this->groupBox_Import->PerformLayout();
				this->groupBox_ANC->ResumeLayout(false);
				this->groupBox_ANC->PerformLayout();
				this->groupBox_Samples_TODO->ResumeLayout(false);
				this->groupBox_Samples_TODO->PerformLayout();
				this->groupBox_Results->ResumeLayout(false);
				this->groupBox_Results->PerformLayout();
				this->groupBox_Results_Data->ResumeLayout(false);
				this->groupBox_Results_Data->PerformLayout();
				this->groupBox_Header->ResumeLayout(false);
				this->groupBox_Header->PerformLayout();
				this->groupBox_228->ResumeLayout(false);
				this->groupBox_228->PerformLayout();
				this->groupBox_WIR->ResumeLayout(false);
				this->groupBox_WIR->PerformLayout();
				this->groupBox_RES->ResumeLayout(false);
				this->groupBox_RES->PerformLayout();
				this->groupBox_IRS->ResumeLayout(false);
				this->groupBox_IRS->PerformLayout();
				this->author->ResumeLayout(false);
				this->author->PerformLayout();
				this->groupBox_INFO->ResumeLayout(false);
				this->ResumeLayout(false);
				this->PerformLayout();

}
#pragma endregion

#pragma region Functions Optinaa

int get_Analyte(struct isodata *p)
			{
				int i=0, n_lines=0;
				string str;
				ifstream lib;
				if (p->fis=='y') lib.open("dat\\lib.fis.dat"); // open library for search fission-analyte general data


				else lib.open("dat\\lib.dat"); // open library for search analyte general data

				while (!lib.eof())
				{
					lib >> str;
					// if found analyte, copy general data
					if (str.compare(p->Iso)==0)
					{
						// copy resonance data
						lib >> str >> p->Sym >> str >> p->MD;
						lib >> str >> p->Qo1 >> str >> p->Qo2 >> str >> p->Eres;
						lib >> str >> p->T2 >> str >> p->T3 >> str >> p->T4;
						lib >> str >> p->F1 >> str >> p->F2 >> str >> p->F3;
						lib >> str >> p->F4 >> str >> p->Cd;
						lib >> str >> str >> str;
						// copy energies, k0s and codes until runs out
						for(i=0;i<ML;i++)
						{
							lib >> p->E[i];
							if (p->E[i]!=0) lib >> p->Ko[i] >> p->Code[i];
							else break;
						}
					}

				}
				lib.close();

				n_lines=i;

				for(i=0;i<n_lines;i++)
				{
					if (p->E[i]==p->Energy)
					{
						p->line=i;
						if (p->fis=='y') p->index=1;
						else p->index=2;
						break; // gamma line found from record
					}
					else
					{
						p->index=5;
						p->frq=0;
					}
				}

				//calculate lamdas
				if (p->T2!=0) p->L2=((0.693)/p->T2);
				if (p->T3!=0) p->L3=((0.693)/p->T3);
				if (p->T4!=0) p->L4=((0.693)/p->T4);

				//obtain yield data
				double energy;
				ifstream lines;
				if (p->fis=='y') lines.open("dat\\lines.fis.dat");
				else lines.open("dat\\lines.dat");
				while (!lines.eof())
				{
					lines >> str;
					if (str.compare(p->Iso)==0)
					{
						lines >> str >> energy;
						for(i=0;i<n_lines;i++)
						{
							if (p->E[i]==energy)
							{
								lines >> p->Yield[i] >> p->Code[i];
								if (p->Code[i]==5) p->Quote[i]="Single-escape line";
								else if (p->Code[i]==4) p->Quote[i]="Double-escape line";
								else if (p->Code[i]==6) p->Quote[i]="recommended line";
								else if (p->Code[i]==1) p->Quote[i]="good line";
								else if (p->Code[i]==3) p->Quote[i]="poor line";
								else if (p->Code[i]==2) p->Quote[i]="acceptable line";
								else p->Quote[i]="no quote";
							}
						}
					}
				}
				lines.close();
				return(n_lines);
			}



  int get_common(struct isodata *p)
			  {

				  get_channel_parameters(p);
				  System::Windows::Forms::Application::DoEvents();
				  get_Analyte(p);
				  System::Windows::Forms::Application::DoEvents();
				  get_Rate(p);
				  get_Temporal(p);
				  System::Windows::Forms::Application::DoEvents();
				  get_Temporal_Scheme_Correction(p);
				  p->eta=sigma58*(p->T[5]/p->T[0])*g*YTe*(p->R[2]/p->R[0]); 


				  return(0);
			  }


			  int get_Apparent_to_Uranium (int n_peaks,struct isodata *pFis[], struct isodata *pNonFis[])

			  {

				  				  
				  int j;
				  int w;

				  for (j=0;j<=n_peaks;j++)
				  {
					  if (pFis[j]->fis=='y')
					  {
						  if (pFis[j]->Iso.compare("La-140")==0)
						  {
							  pFis[j]->factor=((pNonFis[j]->R[0]*pNonFis[j]->Ko[pNonFis[j]->line]*pNonFis[j]->T[2])/(pFis[j]->T[0]*pFis[j]->R[0]*pFis[j]->Ko[pFis[j]->line]));
							  pFis[j]->ro=(pNonFis[j]->ro)*pFis[j]->factor;
						  }
						  else
						  {
							  pFis[j]->factor=((pNonFis[j]->R[0]*pNonFis[j]->Ko[pNonFis[j]->line])/(pFis[j]->R[0]*pFis[j]->Ko[pFis[j]->line]));
							  pFis[j]->ro=(pNonFis[j]->ro)*pFis[j]->factor;
						  }
					  }
					  else if (pFis[j]->fis=='n') 
					  {
						  if (pFis[j]->Energy==228.1 || pFis[j]->Energy==228.2)

						  {
							   for (w=0;w<=n_peaks;w++)

							   {
								   if (	pFis[w]->Energy==277.6 && pFis[w]->meas==pFis[j]->meas)	 pFis[j]->factor=pFis[w]->unc;

							   }
						 

						  }


						 
						  else pFis[j]->factor=pFis[j]->unc;
						 
						  
						  pFis[j]->ro=pNonFis[j]->ro;

					  }
				  }
				  for (j=0;j<=n_peaks;j++) pFis[j]->ro2=pNonFis[j]->ro;



				  return (0);

			  }

			  int get_Uranium_to_Apparent (int n_peaks,struct isodata *pFis[], struct enrichment *pR)
			  {
				  int j;
				  for (j=0;j<=n_peaks;j++)
				  {
					  if (pFis[j]->Iso.compare("Np-239")!=0 && pFis[j]->Iso.compare("U-239")!=0)
					  {
						  pFis[j]->ro=((pR->ro)/(pFis[j]->factor))*((M_nat*pR->theta5)/(theta5_nat*100*pR->M));
					  }

				  }
				  for (j=0;j<=n_peaks;j++)
				  {
					  pFis[j]->res=pFis[j]->ro2-pFis[j]->ro;
					  if ((100*(pFis[j]->res/pFis[j]->ro2))<=2*pR->k) pFis[j]->res=0;
					  if (pFis[j]->res<=0) pFis[j]->res=0;
				  }


				  return (0);

			  }

			  int get_228_Correction(struct isodata *p[],int n_peaks, struct enrichment *pR)
			  {
				  int w;

				  for(w=0;w<=n_peaks;w++)
				  {
					  if ((p[w]->Iso.compare("Np-239")==0) && (p[w]->Energy==228.2 || p[w]->Energy==228.1)) 
					  {
 //here factor is the sd experimental
	  //to wich you have to add the uncertainty from the 1st isotopic determination

						  p[w]->ro=(p[w]->ro2*(1+(ratio_nat*p[w]->eta)))/(1+(pR->ratio*p[w]->eta));
						  p[w]->unc=sqrt(pow(p[w]->factor,2) + pow((2*pR->k),2));
						  //p[w]->unc=p[w]->unc/100;
						  p[w]->index=2;
						

					  }
					 

				  }

				  return(0);
			  }


			  int get_reset_index(struct isodata *p[],int n_peaks)
			  {
				  int w;

				  for(w=0;w<=n_peaks;w++)
				  {
					 
					  if (p[w]->Iso.compare("Np-239")==0)
					  {
						  //p[w]->fis='n';
						  p[w]->index=2;
					  }
					  else p[w]->index=1;

					  p[w]->unc=p[w]->unc*100;

				  }

				  return(0);
			  }





			
  int get_Rate(struct isodata *p)
			  {

				  p->Eresfis=0.47;
				  p->Qofis=0.59;


				  p->Qo1=((p->Qo1-0.429)*pow(p->Eres,-1*p->alfa))+((0.429)/((2*p->alfa+1)*pow(0.55,p->alfa))); //Qalfa calculo 1
				  p->Qo2=((p->Qo2-0.429)*pow(p->Eres,-1*p->alfa))+((0.429)/((2*p->alfa+1)*pow(0.55,p->alfa))); //Qalfa calculo 2
				  p->Qofis=((p->Qofis-0.429)*pow(p->Eresfis,-1*p->alfa))+((0.429)/((2*p->alfa+1)*pow(0.55,p->alfa))); //Qalfa calculo 2


				  //in case analyte is La-140
				  if (p->fis=='y' && p->Iso.compare("La-140")==0) p->MD=0;

				  p->R[0]=((p->Gt*p->f)+(p->Ge*p->Qo1));
				  p->R[1]=((p->Gt*p->f)+(p->Ge*p->Qo2));
				  p->R[2]=((p->Gt*p->f)+(p->Ge*p->Qofis));

				  if (p->Iso.compare("Np-239")!=0 && p->Iso.compare("U-239")!=0 && p->fis=='y')
				  {
					  p->R[0]=p->R[2]; //fission reaction rate

				  }



				  return(0);
			  }



			  int get_Temporal(struct isodata *p)
			  {
				  p->T[0]=0;
				  p->T[1]=0;
				  p->T[2]=((1-(exp(-1*p->L2*p->ti)))*(exp(-1*p->L2*p->td))*((1-(exp(-1*p->L2*p->tc)))/(p->tc*p->L2)));
				  p->T[3]=((1-(exp(-1*p->L3*p->ti)))*(exp(-1*p->L3*p->td))*((1-(exp(-1*p->L3*p->tc)))/(p->tc*p->L3)));
				  p->T[4]=((1-(exp(-1*p->L4*p->ti)))*(exp(-1*p->L4*p->td))*((1-(exp(-1*p->L4*p->tc)))/(p->tc*p->L4)));
				  p->T[5]=((1-(exp(-1*lTe*p->ti)))*(exp(-1*lTe*p->td))*((1-(exp(-1*lTe*p->tc)))/(p->tc*lTe)));	
				  return(0);
			  }

			  int get_Frequency(struct isodata *p[],int n_peaks)
			  {


					   int n=0;
				  int w;
				  int j;

				  double band;

				  int fis=0;
				  int u=0;

				  for (w=0;w<=n_peaks;w++) p[w]->tries=p[w]->match=0;


				  for(w=0;w<=n_peaks;w++)
				  {
					  if (p[w]->index==1) fis++;
				  }
				  for(w=0;w<=n_peaks;w++)
				  {
					  if (p[w]->index==2) u++;
				  }

				  if (fis==0)
				  {
					  LOG->Text= LOG->Text->ToString() + ("FATAL ERROR!\nNo fision products identified!\nCheck the data before proceeding to Step 3!\n\t\t\t...\t");
						return(6);										 
				  }
				  if (u==0)
				  {
					  LOG->Text= LOG->Text->ToString() + ("FATAL ERROR!\nNo U-239 and/or Np-239 identified!\nCheck the data before proceeding to Step 3!\n\t\t\t...\t");
							return(6);
				  }

				  if (fis==1)
				  {
				    LOG->Text= LOG->Text->ToString() + ("WARNING!\nONLY one fission product gamma-line identified...\nThis is poor data...\nCheck the data!\t\t...\t\t");
				    for(w=0;w<=n_peaks;w++)
					  {
						  if (p[w]->index==1)
						  {
							  p[w]->frq=1;
							  p[w]->index=3;
						   
						  }
						  else if (p[w]->index!=2 && p[w]->index!=4)
						  {
							  p[w]->frq=0;
							  p[w]->index=5;
						  }
					  }
		   		  }

				  if (u==1)
				  {
				     LOG->Text= LOG->Text->ToString() + ("WARNING!\nONLY one U-238 activation product gamma-line identified...\nThis is poor data...\nCheck the data!\t\t...\t\t");
				    for(w=0;w<=n_peaks;w++)
					  {
						  if (p[w]->index==2)
						  {
							  p[w]->frq=1;
							  p[w]->index=4;
						  }
						  else if (p[w]->index!=1 && p[w]->index!=3)
						  {
							  p[w]->frq=0;
							  p[w]->index=5;
						  }

					  }

				  }

				  if (fis>1 && panic==0)

				  {
					  band=0.30;
					 
					  while(band>=0.025)
					  {
						  for(w=0;w<=n_peaks-1;w++)
						  {
							  for (j=w+1;j<=n_peaks;j++)
							  { 
								  if ((p[w]->index==1 && p[j]->index==1) && p[w]->Sym.compare(p[j]->Sym)!=0 ) // fission-to-fission and 238-to-238 comparision only
								  {
									  p[w]->tries++;
									  p[j]->tries++;

									  if (((p[w]->ro/p[j]->ro)<=(1+band)) && ((p[w]->ro/p[j]->ro)>=(1-band)))
									  {
										  p[w]->match++;
										  p[j]->match++;
									  }
									  else if (((p[j]->ro/p[w]->ro)<=(1+band)) && ((p[j]->ro/p[w]->ro)>=(1-band)))
									  {
										  p[w]->match++;
										  p[j]->match++;
									  }
								  }

							  }
						  }
						  band=band-0.025;
					  }
				  }


				  else if (fis>1 && panic==1)

				  {
					  band=0.30;
					  while(band>=0.025)
					  {
						  for(w=0;w<=n_peaks-1;w++)
						  {
							  for (j=w+1;j<=n_peaks;j++)
							  { 
								  if ((p[w]->index==1 && p[j]->index==1) ) // fission-to-fission and 238-to-238 comparision only
								  {
									  p[w]->tries++;
									  p[j]->tries++;

									  if (((p[w]->ro/p[j]->ro)<=(1+band)) && ((p[w]->ro/p[j]->ro)>=(1-band)))
									  {
										  p[w]->match++;
										  p[j]->match++;
									  }
									  else if (((p[j]->ro/p[w]->ro)<=(1+band)) && ((p[j]->ro/p[w]->ro)>=(1-band)))
									  {
										  p[w]->match++;
										  p[j]->match++;
									  }
								  }

							  }
						  }
						  band=band-0.025;
					  }
				  }






			   if (fis>1)
			   {
				   MW_Fis=0;
				   for (w=0;w<=n_peaks;w++)
					  {
						  if ((p[w]->index==1))
						  {
							  p[w]->frq=(p[w]->match/p[w]->tries);
							  if (p[w]->frq>MW_Fis) MW_Fis=p[w]->frq;
						  }
					  }

				  MW_Fis=MW_Fis*0.5;
				  double FRQ_Fis=0;
				  for(w=0;w<=n_peaks;w++)
					  {
						  if (p[w]->index==1 && p[w]->frq>=MW_Fis)
						  {
							  FRQ_Fis=FRQ_Fis+p[w]->frq;
							  p[w]->index=3;
						  }
						  else if (p[w]->index==1 && p[w]->frq < MW_Fis)
						  {
							  p[w]->index=5;
							  p[w]->frq=0;
						  }
					  }

					  fis=0;
					  int te=0;
					  int te2=0;
					  int nte=0,nte2=0;

					  for(w=0;w<=n_peaks;w++)
					  {
						  if (p[w]->index==3)
						  {
							 p[w]->frq=((p[w]->frq)/FRQ_Fis);
							 fis++;
						  }
						  if (p[w]->index==3 && p[w]->Iso.compare("I-131")==0) te++;
						  if (p[w]->index==5 && p[w]->Iso.compare("I-131")!=0 && p[w]->Iso.compare("Np-239")!=0 && p[w]->Iso.compare("U-239")!=0 ) nte2++;
						  if (p[w]->index==3 && p[w]->Iso.compare("I-131")!=0) nte++;
						  if (p[w]->index==5 && p[w]->Iso.compare("I-131")==0) te2++;
					  }

					  if (te==0 && te2>0)  LOG->Text= LOG->Text->ToString() + ("WARNING!\nI-131 from Te-131 completely rejected!\nThis isotope is a good indicator for multi-elemental samples\nPANIC won't work for this sample\t\t...\t\t");

					  if (te==0 && te2==0) LOG->Text= LOG->Text->ToString() + ("WARNING!\nI-131 from Te-131 not present!\nThis isotope is a good indicator for multi-elemental samples\nPANIC mode won't work for this sample\t\t...\t\t");

					  if (te2>0 && te2>te)	 LOG->Text= LOG->Text->ToString() + ("WARNING!\nI-131 from Te-131 was rejected several times\nThis isotope is a good indicator for multi-elemental samples\nCheck your data!\t\t...\t\t");
				   						 
					  if (nte2>nte && panic==0)  LOG->Text= LOG->Text->ToString() + ("WARNING!\nThis sample looks complicated\nMore than 50% of the data from fission products was rejected\nCheck your data!\t\t...\t\t");

					  
					  if(fis==0)
					  {
						  for(w=0;w<=n_peaks;w++)
						  {
							  if (p[w]->Iso.compare("I-131")==0)
							  {		fis++;
								  p[w]->frq=1;
								  p[w]->index=3;
							  }
						  }
						  if (fis==0)
						  {
							  LOG->Text= LOG->Text->ToString() + ("FATAL ERROR!\nNo fission products identified\nYou must check your data!\t\t...\t");
						  return(6);
						  }
						  else	  LOG->Text= LOG->Text->ToString() + ("WARNING!\nVery scarce fission products data\nI-131 will be used as default!\nYou should check your data!\t\t...\t\t");
					  
					  }

						
				  
				  }




				  if (u>1 && panic==0)

				  {

					  band=0.20;
					  while(band>=0.025)
					  {
						  for(w=0;w<=n_peaks-1;w++)
						  {
							  for (j=w+1;j<=n_peaks;j++)
							  {
								  if ((p[w]->index==2 && p[j]->index==2) && (p[w]->Energy!=p[j]->Energy))
								  {
									  p[w]->tries++;
									  p[j]->tries++;

									  if (((p[w]->ro/p[j]->ro)<=(1+band)) && ((p[w]->ro/p[j]->ro)>=(1-band)))
									  {
										  p[w]->match++;
										  p[j]->match++;
									  }
									  else if (((p[j]->ro/p[w]->ro)<=(1+band)) && ((p[j]->ro/p[w]->ro)>=(1-band)))
									  {
										  p[w]->match++;
										  p[j]->match++;
									  }

								  }
							  }
						  }
						  band=band-0.025;

					  }
				  }

				  else if (u>1 && panic==1)

				  {

					  band=0.20;
					  while(band>=0.025)
					  {
						  for(w=0;w<=n_peaks-1;w++)
						  {
							  for (j=w+1;j<=n_peaks;j++)
							  {
								  if ((p[w]->index==2 && p[j]->index==2))
								  {
									  p[w]->tries++;
									  p[j]->tries++;

									  if (((p[w]->ro/p[j]->ro)<=(1+band)) && ((p[w]->ro/p[j]->ro)>=(1-band)))
									  {
										  p[w]->match++;
										  p[j]->match++;
									  }
									  else if (((p[j]->ro/p[w]->ro)<=(1+band)) && ((p[j]->ro/p[w]->ro)>=(1-band)))
									  {
										  p[w]->match++;
										  p[j]->match++;
									  }

								  }
							  }
						  }
						  band=band-0.025;

					  }

						}

				  if (u>1)
				  {

					  MW_U=0;

					  for(w=0;w<=n_peaks;w++)
					  {
						  if ((p[w]->index==2))
						  {
							  p[w]->frq=(p[w]->match/p[w]->tries);
							  if(p[w]->frq>MW_U) MW_U=p[w]->frq;
						  }
					  }

					  MW_U=MW_U*0.5;

					  double FRQ_U=0;

					  for(w=0;w<=n_peaks;w++)
					  {
						  if ((p[w]->index==2) && p[w]->frq>=MW_U)
						  {
							  p[w]->index=4;
							  FRQ_U=FRQ_U+p[w]->frq;
						  }
						  if ((p[w]->index==2) && p[w]->frq<MW_U)
						  {
							  p[w]->index=5;
							  p[w]->frq=0;
						  }

					  }

					  u=0;

					  for(w=0;w<=n_peaks;w++)
					  {

						  if (p[w]->index==4)
						  {
							 p[w]->frq=((p[w]->frq)/FRQ_U);
							  u++;
						  }
					  }


					  if(u==0)

					  {
						  for(w=0;w<=n_peaks;w++)
						  {
							  if (p[w]->Iso.compare("Np-239")==0 || p[w]->Iso.compare("U-239")==0 )
							  {
								  u++;
								  p[w]->frq=1;
								  p[w]->index=4;
							  }

						  }
						
						if (u==0)
						{
							LOG->Text= LOG->Text->ToString() + ("FATAL ERROR!\nNp-239 and/or U-239 not present!!!\nYou must check the data!!!\t\t...\t");
						return(6);
						}
						
						else LOG->Text= LOG->Text->ToString() + ("WARNING!\nVery scarce Np-239 and/or U-239 data\nYou should check the data!\t\t...\t\t");
						

					  }

				  }

				  return(0); //if return is 6 then a fatal error occurred...
			  }

			  int get_PANIC(struct isodata *p[],int n_peaks)
			  {

				  int w;
								     			 
				  for(w=0;w<=n_peaks;w++)
				  {

					   if (p[w]->index==1)
						  
					  {

					  if (p[w]->Iso.compare("I-131")==0 && p[w]->Energy==364.5) p[w]->index=1;
					  else if (p[w]->Iso.compare("I-131")==0 && p[w]->Energy!=364.5) p[w]->index=5;
					  else
					  {
						  p[w]->frq=0;
						  p[w]->index=5;

					  }
					   }

					  if   (p[w]->index==2)
						  
					  {
					  if ( p[w]->Energy==277.6)  p[w]->index=2;
					  //else if  (p[w]->Energy==315.9 || p[w]->Energy==334.2 )   p[w]->index=2;
					  else
					  {
						  p[w]->frq=0;
						  p[w]->index=5;

					  }


					   }
					   
				  }
				  

			   

				 return(0);

				}
			  int get_recommended(struct isodata *p[],int n_peaks)
			  {

				  int w;
								     			 
				  for(w=0;w<=n_peaks;w++)
				  {
					  if (p[w]->index==1)
						  
					  {
					  
					 if (p[w]->Iso.compare("Ce-141")==0) p[w]->index=1;
					  else if (p[w]->Iso.compare("Tc-99m")==0) p[w]->index=1;
					  
					  //i-131
					  else if (p[w]->Energy==364.5) p[w]->index=1;
					
					  //nd-147
					  else if (p[w]->Energy==91.1) p[w]->index=1;
					   else if (p[w]->Energy==531.0) p[w]->index=1;
					  else if (p[w]->Energy==439.9) p[w]->index=1;
					   else if (p[w]->Energy==319.4) p[w]->index=1;

					   //ce-143
					  else if (p[w]->Energy==293.3) p[w]->index=1;
					  else if (p[w]->Energy==664.6) p[w]->index=1;
					 else if (p[w]->Energy==721.9) p[w]->index=1;
					  else if (p[w]->Energy==350.6) p[w]->index=1;

					  //ru-105
					  else if (p[w]->Energy==306.1) p[w]->index=1;
					  //ru-103
					  else if (p[w]->Energy==497.1) p[w]->index=1;
					  
					  
					  //la-140
					  else if (p[w]->Energy==815.8 || p[w]->Energy==328.8) p[w]->index=1;
					  else if (p[w]->Energy==1596.2) p[w]->index=1;
					  else if (p[w]->Energy==487.0) p[w]->index=1;
					    
					  //mo
					  else if (p[w]->Energy==739.5 || p[w]->Energy==366.4) p[w]->index=1;
					  else if (p[w]->Energy==777.9) p[w]->index=1;

					 //nbios
					  else if (p[w]->Energy==765.8 || p[w]->Energy==657.9 || p[w]->Energy==743.4) p[w]->index=1;
					  else if (p[w]->Energy==756.7) p[w]->index=1;
					  					  
					  else
					  {
						  p[w]->frq=0;
						  p[w]->index=5;

					  }
					   
				   	  }

					if  ( p[w]->index==2)

					{
					   if ( p[w]->Energy==277.6 ) p[w]->index=2;
					  // else if ( p[w]->Energy==209.8 ) p[w]->index=2;
					   else if  (p[w]->Energy==315.9 || p[w]->Energy==334.2 )   p[w]->index=2;
					   else
					  {
						  p[w]->frq=0;
						  p[w]->index=5;

					  }
					   
					   
					}



				  }
				  


				return(0);
				}



	int get_enriched(struct isodata *p[],int n_peaks)
			  {

				  int w;
								     			 
				  for(w=0;w<=n_peaks;w++)
				  {
			
					if  ( p[w]->Iso.compare("Np-239")==0) 

					{
					   if ( p[w]->Energy==277.6 ) 
					   {
						   p[w]->index=4;
						   p[w]->frq=1;
					   }
					   else
					  {
						  p[w]->frq=0;
						  p[w]->index=5;

					  }
													   
					}

					   p[w]->unc=p[w]->unc*100;



				  }
				  


				return(0);
				}






		int get_channel_parameters (struct isodata *p)
			{
				string str;
				ifstream channel;
				channel.open("dat\\channels.dat");

				while(!channel.eof())

				{
					channel >> str;
					if (str.compare(p->channel)==0)
					{
						channel >> p->f >> p->alfa;
						if (p->ENAA=='y') p->f=0;

					}

				}
				channel.close();
				return(0);
			}



			  int get_Isotopic_Ratio (struct isodata *p[],int n_peaks,const char *file)
			  {
				  string fileresults;
				  fileresults.clear();
				  fileresults.append(file);
				  fileresults.append(".irs.xls");
				  file=fileresults.data();


				  ofstream ratiodata;
				  ratiodata.open(file);
				  int j;
				  int w;

				  double ratio;
				  double sd;
				  double ro;
				  double theta5,theta8,M;
				  string str,Iso;
				  double wfactor;

				  //cout << "\n\tCalculating U-235 vs. U-238 Isotopic Ratios per gamma-lines" << endl;

				  ratiodata << "Isotope\tEnergy\tvs. Isotope\tEnergy\tRatio\tU (ppm)\tsd\tU-235 (%)\tU-238 (%)\tMolar Mass (amu)\tweight\n";

				  for(w=0;w<=n_peaks-1;w++)
				  {
					  if (p[w]->index==3) // if numerator is fission and denominator is U238
					  {
						  ro=0;
						  ratio=0;
						  sd=0;
						  wfactor=0;
						  for (j=w+1;j<=n_peaks;j++)
						  {
							  if (p[j]->index==4)
							  {
								  ro=(p[w]->ro*theta5_nat + p[j]->ro*theta8_nat); // obtain ro and sum it to the prior
								  ratio=(p[w]->ro/p[j]->ro); // obtain isotopic ratio and sum it to the prior
								  sd=sqrt(pow(p[w]->unc,2)+pow(p[j]->unc,2));
								  wfactor=sqrt(pow(p[w]->frq,2)+pow(p[j]->frq,2));
								  ratio=ratio*(theta5_nat/theta8_nat);
								  theta5=(ratio)/(ratio+1);
								  theta8=(1)/(ratio+1);
								  M=(M5*theta5)+(M8*theta8);
								  ro=ro*(M/M_nat);

								  ratiodata << p[w]->Iso <<'\t'<< p[w]->Energy << '\t'<< p[j]->Iso << '\t' << p[j]->Energy << '\t' <<ratio << '\t' <<ro << '\t' << sd*100 <<'\t' << theta5*100 <<'\t' << theta8*100 << '\t'<< M<< '\t'<< wfactor*100 << endl;
							  }

						  }
					  }
				  }

				  ratiodata.close();


				
				  return(0);

			  }



			  int get_Overall_Isotopic_Ratio (struct enrichment *pR,const char *file,int mode)
			  {

				  string fileresults;
				  fileresults.clear();
				  fileresults.append(file);
				  fileresults.append(".irs.xls");
				  file=fileresults.data();

				  ifstream ratioinput;
				  ratioinput.open(file);

				  double ratio=0;
				  double sd=0;
				  double ro=0;
				  double theta5=0,theta8=0,M=0;
				  string str,Iso;
				  double Energy;
				  double theta5_w=0,theta8_w=0,M_w=0;
				  double sd_obs_w=0;
				  double wfactor=0;

				  double ro_w=0;
				  double ratio_w=0;
				  double weight=0;
				  double sd_w=0;
				  double weight_sum=0;
				  double max=0, min=0;
				  double max2=0, min2=0;

				  pR->outlier=0;
				  pR->total=0;


				  max2=(pR->ratio+(pR->ratio*pR->conf*0.02));
				  min2=(pR->ratio-(pR->ratio*pR->conf*0.02));
				  getline(ratioinput,str,'\n');

				  while (1)
				  {
					  ratioinput >> Iso >> Energy >> Iso >> Energy >> ratio >> ro >> sd >> theta5 >> theta8 >> M >> wfactor;
					  if (ratioinput.fail()) break;

					  pR->total++;
					  if (mode==1)
					  {

						  max=(ratio+(ratio*sd*0.02));
						  min=(ratio-(ratio*sd*0.02));
						  if (max<min2 || min>max2) pR->outlier++;
						  else
						  {
							  //sd=sd*0.01;
							  wfactor=wfactor*0.01;
							  //weight=(wfactor*wfactor/(sd*sd));
							  weight=pow(sd,-2);
							  sd_w=sd_w + (pow(weight*sd,2));
							  ro_w=ro_w+(ro*weight);
							  theta5_w=theta5_w+(theta5*weight);
							  theta8_w=theta8_w+(theta8*weight);
							  M_w=M_w+(M*weight);
							  ratio_w=ratio_w+(ratio*weight);
							  weight_sum=weight_sum+weight;

						  }
					  }
					  else if (mode==0)
					  {
						  //sd=sd*0.01;
						  wfactor=wfactor*0.01;
						  //weight=(wfactor*wfactor/(sd*sd));
						 weight=pow(sd,-2);
						  sd_w=sd_w + (pow(weight*sd,2));
						  ro_w=ro_w+(ro*weight);
						  theta5_w=theta5_w+(theta5*weight);
						  theta8_w=theta8_w+(theta8*weight);
						  M_w=M_w+(M*weight);
						  ratio_w=ratio_w+(ratio*weight);
						  weight_sum=weight_sum+weight;

					  }
				  }

				  ratioinput.close();

				  sd=sqrt((sd_w/pow(weight_sum,2)));
				  ratio=(ratio_w/weight_sum);
				  theta5=(theta5_w/weight_sum);
				  theta8=(theta8_w/weight_sum);
				  M=(M_w/weight_sum);
				  ro=(ro_w/weight_sum);



				  pR->sd=sd;
				  pR->ratio=ratio;
				  pR->theta5=theta5;
				  pR->theta8=theta8;
				  pR->M=M;
				  pR->ro=ro;



				  ifstream ratioinput2;
				  ratioinput2.open(file);

				  pR->outlier=0;
				  pR->total=0;
				  sd_obs_w=0;
				  sd=0;
				  ratio=0;

				  int n=0;
				  weight=0;
				  weight_sum=0;

				  getline(ratioinput2,str,'\n');

				  while (1)
				  {
					  ratioinput2 >> Iso >> Energy >> Iso >> Energy >> ratio >> ro >> sd >> theta5 >> theta8 >> M >> wfactor;

					  if (ratioinput2.fail()) break;

					  pR->total++;

					  if (mode==1)
					  {
						  max=(ratio+(ratio*sd*0.02));
						  min=(ratio-(ratio*sd*0.02));

						  if (max<min2 || min>max2) pR->outlier++;
						  else
						  {
							  //sd=sd*0.01;
							  wfactor=wfactor*0.01;
							  //weight=(wfactor*wfactor/(sd*sd));
							  weight=pow(sd,-2);
							  weight_sum=weight_sum+weight;
							 
						 sd_obs_w=sd_obs_w + (weight*(pow((pR->ratio-ratio),2)));

					
							  
							  n++;
						  }
					  }
					  if (mode==0)
					  {
						  //sd=sd*0.01;
						  wfactor=wfactor*0.01;
						  //weight=(wfactor*wfactor/(sd*sd));
						  weight=pow(sd,-2);
						  weight_sum=weight_sum+weight;
						 sd_obs_w=sd_obs_w + (weight*(pow((pR->ratio-ratio),2)));
						  
					

						  n++;
					  }

				  }

				  ratioinput2.close();

				  n=n-1;

				  if(n!=0)
				  {

				 sd_obs_w=sqrt((sd_obs_w/(n*weight_sum)));
				
				  pR->sd_obs=100*(sd_obs_w/pR->ratio);
				  }
				  else	pR->sd_obs=0;

				  if (pR->sd_obs>pR->sd) pR->conf=pR->sd_obs;
				  else pR->conf=pR->sd;

				  
				  pR->k=sqrt(pow(pR->conf,2) + pow(3.0,2)); // U-SD (ALL) without altering conf
				  
				  show_WIR(pR);


				  return(0);

				  }



		public:		  int show_WIR(struct enrichment *pR)
				  
				  {
				  double max,min;

				  max=(pR->ratio+(pR->ratio*(2*pR->k/100)));
				  min=(pR->ratio-(pR->ratio*(2*pR->k/100)));


				  struct tm *newTime;
				  time_t szClock;

				  // Get time in seconds
				  time( &szClock );

				  // Convert time to struct tm form
				  newTime = localtime( &szClock );
				  string timestring;
				  timestring.clear();
				  pR->timestring=asctime( newTime );
				  timestring.append(pR->timestring);
				  System::Windows::Forms::Application::DoEvents();


				  System::String ^ dt = gcnew String(timestring.c_str());

				  DT->Text=	dt;

				  if ((0.007252581>max) && (0.007252581>min)) quoteU->Text="URANIUM IS DEPLETED";
				  else if ((0.007252581<max) && (0.007252581<min)) 
				  {
					  quoteU->Text="URANIUM IS ENRICHED";
					  quoteU->Font->Bold;
				  }
				  else if ((0.007252581<max) && (0.007252581>min)) quoteU->Text="URANIUM IS NATURAL";

				  WIR->Text= System::Convert::ToString((float)pR->ratio);
				
				  RO->Text = System::Convert::ToString((float)pR->ro);
				  U235->Text=System::Convert::ToString((float)pR->theta5);
				  RO5->Text=System::Convert::ToString((float)(pR->theta5*pR->ro*0.01)); 
				  U238->Text=System::Convert::ToString((float)pR->theta8);
				  RO8->Text=System::Convert::ToString((float)(pR->theta8*pR->ro*0.01)); 
				  AW->Text=System::Convert::ToString((float)pR->M);
				  SDexp->Text= System::Convert::ToString((float)(pR->sd)) ;
				  SDobs->Text= System::Convert::ToString((float)(pR->sd_obs)) ;
				  SD->Text= System::Convert::ToString((float)(2*pR->k)) ;
				  
				  return(0);

			  }



			  int get_Temporal_Scheme_Correction (struct isodata *p)
			  {
				  switch (p->MD)
				  {
				  case 2:
					  p->T[0]=((p->L3*p->T[2])-(p->L2*p->T[3]))/(p->L3-p->L2);
					  break;
				  case 1:
					  p->T[0]=p->T[2]; //normal activation
					  break;
				  case 10:
					  p->T[0]=p->T[3];
					  break;
				  case 14:
					  p->T[0]=p->T[3];
					  break;
				  case 3:
					  p->T[0]=p->T[3];
					  break;
				  case 0: // for La-140
					  p->T[0]=((p->L2*p->T[3])-(p->L3*p->T[2]))/(p->L2-p->L3);
					  break;
				  case 6:
					  p->T[2]=((p->T[2]*p->L4)/(p->L4-p->L2));
					  p->T[2]=p->T[2]*(((p->L3)/(p->L3-p->L2))+p->F2);
					  p->T[4]=((p->T[4]*p->L2)/(p->L4-p->L2));
					  p->T[4]=p->T[4]*(((p->L3)/(p->L4-p->L3))-p->F2);
					  p->T[3]=(p->T[3]*p->L2*p->L4)/((p->L4-p->L3)*(p->L3-p->L2));
					  p->T[0]=p->T[2]+p->T[4]-p->T[3];
					  break;
				  case 16:
					  p->F1=p->F1*(p->R[1]/p->R[0])*(((p->T[2]*p->L4)-(p->T[4]*p->L2))/(p->L4-p->L2));
					  p->F2=((p->T[3]*p->L4)-(p->T[4]*p->L3))/(p->L4-p->L3);
					  p->F3=p->F3*(p->R[1]/p->R[0]);
					  p->T[2]=(p->T[2]*p->L4*p->L3)/((p->L4-p->L2)*(p->L3-p->L2));
					  p->T[3]=(p->T[3]*p->L4*p->L2)/((p->L4-p->L3)*(p->L3-p->L2));
					  p->T[4]=(p->T[4]*p->L2*p->L3)/((p->L4-p->L2)*(p->L4-p->L3));
					  p->F3=p->F3*(p->T[2]-p->T[3]+p->T[4]);
					  p->T[0]=p->F1+p->F2+p->F3;
					  break;
				  case 5:
					  p->T[0]=(((p->L3*p->T[2])-(p->L2*p->T[3]))/(p->L3-p->L2)) + p->F1*p->T[2];
					  break;
				  case 19:
					  if (p->E[p->line]==1332.5 || p->E[p->line]==555.8)
					  {
						  p->T[1]=((((p->L3*p->T[2])-(p->L2*p->T[3]))/(p->L3-p->L2))+p->F1*p->T[2]);
						  p->T[0]=(p->F3*p->T[1]*(p->R[1]/p->R[0]))+p->T[3];
					  }
					  else p->T[0]=p->T[3];
					  break;
				  case 13:
					  p->T[1]=(p->F3*(p->R[1]/p->R[0])*((p->L4*p->T[2])-(p->L2*p->T[4])))/(p->L4-p->L2);
					  p->T[0]= p->T[1] + (((p->L4*p->T[3])-(p->L3*p->T[4]))/(p->L4-p->L3));
					  break;
				  case 8:
					  p->T[0]=((p->L4*p->T[2])-(p->L2*p->T[4]))/(p->L4-p->L2);
					  break;
				  }
				  return(0);
			  }

	 int write_WIR (struct enrichment *pR[], const char *file, int iter)
			{

				int j;


				string fileresults;
				string str;
				fileresults.clear();
				fileresults.append(file);
				fileresults.append(".wir.txt");
				file=fileresults.data();


				ofstream results;
				results.open(file, ios::app);

				results <<"\n";
				double max, min;

				for (j=0;j<iter;j++)

				{


					max=(pR[j]->ratio+(pR[j]->ratio*(2*pR[j]->k/100)));
					min=(pR[j]->ratio-(pR[j]->ratio*(2*pR[j]->k/100)));


					results << "ITERATION\t"<<"------------------------------\n";

					if ((0.007252581>max) && (0.007252581>min)) results << j << "\tURANIUM IS DEPLETED!!!\t\t\t" << pR[j]->timestring ;
					else if ((0.007252581<max) && (0.007252581<min)) results << j << "\tURANIUM IS ENRICHED!!!\t\t\t"<< pR[j]->timestring ;
					else if ((0.007252581<max) && (0.007252581>min)) results <<j << "\tURANIUM IS NATURAL!!!\t\t\t" << pR[j]->timestring ;

					results << j << "\tWeighted Isotopic Ratio:\t" << pR[j]->ratio << "\t+\\-\t" << pR[j]->ratio*2*pR[j]->k*0.01;
					results << "\n" << j << "\tElemental U (mg/kg):\t" << pR[j]->ro << "\t+\\-\t" << pR[j]->ro*2*pR[j]->k*0.01;
					results << "\n" << j << "\tU-235 (%):\t" << pR[j]->theta5<< "\t+\\-\t" << pR[j]->theta5*2*pR[j]->k*0.01;
					results << "\n" << j<< "\tU-235 (mg/kg):\t" << pR[j]->theta5*pR[j]->ro*0.01<< "\t+\\-\t" << pR[j]->theta5*pR[j]->ro*0.01*2*pR[j]->k*0.01;
					results << "\n" << j<< "\tU-238 (%):\t" << pR[j]->theta8<< "\t+\\-\t" << pR[j]->theta8*2*pR[j]->k*0.01;
					results << "\n" << j<< "\tU-238 (mg/kg):\t" << pR[j]->theta8*pR[j]->ro*0.01<< "\t+\\-\t" << pR[j]->theta8*pR[j]->ro*0.01*2*pR[j]->k*0.01;
					results << "\n" << j<< "\tSUM (%):\t" << pR[j]->theta8 + pR[j]->theta5;
					results << "\n" << j<< "\tMolar Mass (gr/mol):\t" << pR[j]->M << "\t+\\-\t" << pR[j]->M*2*pR[j]->k*0.01;
					results << "\n" << j<< "\tweighted SD exp (%):\t" << pR[j]->sd;
					results << "\n" << j<< "\tweighted SD obs (%):\t" << pR[j]->sd_obs;
					results << "\n" << j<< "\tTOTAL RELATIVE SD (95% conf) (%):\t" << 2*pR[j]->k;
					results << "\n" << j<< "\tOutliers:\t" << pR[j]->outlier;
					results << "\n" << j<< "\tTotal Data Points:\t" << pR[j]->total;
					results << endl;

				}

				results.close();


				return(0);
			}










  int write_RES (struct isodata *p[], int n_peaks,const char *file)
			  {

				  string fileresults;
				  fileresults.clear();
				  fileresults.append(file);
				  fileresults.append(".res.xls");

				  file=fileresults.data();

				  ofstream results;
				  results.open(file);
				  int j;
				 

				  int h;

				  results << "Element\tIsotope\tEnergy\tapparent ppm\tcorrection ppm\tresidual ppm\tindex\n";


				  for (h=3;h<=5;h++)
				  {

					  for(j=0;j<=n_peaks;j++)
					  {
						  if (p[j]->index==h)
						  {

							  results << p[j]->Sym <<'\t' << p[j]->Iso << '\t' << p[j]->Energy << '\t';
							  results << p[j]->ro2 << '\t' ; // apparent
							  results << p[j]->ro << '\t' ; // uranium
							  results << p[j]->res << '\t' ;
							  results << p[j]->index << '\n' ; // index


						  }

					  }

				  }



				  results.close();


				  return(0);

			  }
	int write_ANC (struct isodata *p[], int n_peaks,const char *file)
			{


				string fileresults;
				fileresults.clear();
				fileresults.append(file);
				fileresults.append(".anc.xls");

				file=fileresults.data();


				ofstream results;
				results.open(file);
				int j;

				int h;

				results << "Element\tIsotope\tEnergy\tapparent (ppm)\tnatural uranium (ppm)\tsd\tindex\tfrequency\tmeas\teta\tfactor\n";

				for (h=3;h<=5;h++)
				{

					for(j=0;j<=n_peaks;j++)
					{
						if (p[j]->index==h)
						{

							results << p[j]->Sym <<'\t' << p[j]->Iso << '\t' << p[j]->Energy << '\t';
							results << p[j]->ro2 << '\t' ; // apparent
							results << p[j]->ro << '\t' ; // uranium

							results << p[j]->unc << '\t' ; // standard deviation
							results << p[j]->index << '\t' ; // index
							results << p[j]->frq*100 << '\t' ; // frequency weight
							results << p[j]->meas << '\t' ; // meas
							results << p[j]->eta << '\t' ; // for correcting neptunium lines
							results << p[j]->factor << '\n';
						}
					}

				}
				results.close();


				return(0);


			}


	
 int Tools_IRS(string sample,int mode)
			{

		

				string sample2;
				const char *file,*file2;
				int j;
				int n_peaks=0;



				for (j=0;j<ML;j++) 
				{
					pF[j]=&F[j];
					}

				file=sample.data();

				n_peaks=Input_ANC (pF, file);

				if (mode==1)
				{
				// in case the sample is VERY enrich, use only the 277 keV line of Np=239
				get_enriched (pF,n_peaks);
				write_ANC(pF,n_peaks,file);
				n_peaks=Input_ANC (pF, file);
				

				}
		



sample2=sample;
				sample2.append(".irs.xls");
				file2=sample2.data();
				remove(file2);




				get_Isotopic_Ratio (pF,n_peaks,file);
		
			 

				sample2=sample;
				sample2.append(".wir.txt");
				file2=sample2.data();
				remove(file2);



				sample2=sample;
				sample2.append(".wir.xls");
				file2=sample2.data();
				remove(file2);

				sample2=sample;
				sample2.append(".res.xls");
				file2=sample2.data();
				remove(file2);




				return(0);

			}


	 int Tools_WIR(string sample)
			{



				const char *file,*file2;
				string str;
		string sample2;		
				int j;

				for (j=0;j<MR;j++) pRatio[j]=&Ratio[j];

				file=sample.data();

				WSAMPLE->Visible::set(true);

				get_Overall_Isotopic_Ratio (pRatio[0],file,0);

		


				DT->Visible::set(true);
				quoteU->Visible::set(true);

				System::Windows::Forms::Application::DoEvents();


				for (j=1;j<MR;j++)
				{

					groupBox_Results->Text= "RESULTS FROM WEIGHTING ITERATION # "+ Convert::ToString(j);
					System::Windows::Forms::Application::DoEvents();
					pRatio[j]->ratio=pRatio[j-1]->ratio;
					pRatio[j]->conf=pRatio[j-1]->conf;
					get_Overall_Isotopic_Ratio (pRatio[j],file,1);
					if(pRatio[j]->ratio==pRatio[j-1]->ratio) break;
				}







				write_WIR (pRatio,file,j);
				System::Windows::Forms::Application::DoEvents();

				struct tm *newTime;
				time_t szClock;

				// Get time in seconds
				time( &szClock );

				// Convert time to struct tm form
				newTime = localtime( &szClock );

				

				ofstream wirlog;
						
				sample2=sample;
				sample2.append(".wir.xls");
				file=sample2.data();

				wirlog.open(file,ios::out);
				wirlog << pRatio[j-1]->ratio << '\t' << pRatio[j-1]->ro << '\t' << pRatio[j-1]->theta5 << '\t' << pRatio[j-1]->theta5*pRatio[j-1]->ro*0.01 << '\t' << pRatio[j-1]->theta8 << '\t' << pRatio[j-1]->theta8*pRatio[j-1]->ro*0.01 << '\t' << pRatio[j-1]->M << '\t' << 2*pRatio[j-1]->k << '\t' << asctime( newTime ); 

				wirlog.close();

					ofstream batchlog;
						
					sample2=sample;
					sample2.resize(sample2.size()-6);
					
				sample2.append(".xls");
				file=sample2.data();

				batchlog.open(file,ios::app);
				batchlog <<"SAMPLE\tRATIO\tRO\tA U5\tRO U5\tA U8\tO U8\tM\tSD\tDATE\n";
				batchlog << sample << '\t' << pRatio[j-1]->ratio << '\t' << pRatio[j-1]->ro << '\t' << pRatio[j-1]->theta5 << '\t' << pRatio[j-1]->theta5*pRatio[j-1]->ro*0.01 << '\t' << pRatio[j-1]->theta8 << '\t' << pRatio[j-1]->theta8*pRatio[j-1]->ro*0.01 << '\t' << pRatio[j-1]->M << '\t' << 2*pRatio[j-1]->k << '\t' << asctime( newTime ); 

				batchlog.close();

				
				
				sample2=sample;
				sample2.append(".res.xls");
				file2=sample2.data();
				remove(file2);





			   if (pRatio[0]->theta5>15.0) return(1);
			   return(0);
		   

			}


	 int Tools_RES(string sample)
			{

				const char *file;
				string time;
				int j;
				int n_peaks=0;
				for (j=0;j<ML;j++) pF[j]=&F[j];
				pRat=&Rat;

				file=sample.data();
				n_peaks=Input_ANC (pF, file);

				Input_WIR(pRat,file);

				get_Uranium_to_Apparent (n_peaks,pF,pRat);

				write_RES (pF,n_peaks,file);


				return(0);


			}






 int Tools_228(string sample)
			{




string sample2;
				const char *file,*file2;
				string time;
				int j;
				int n_peaks=0;
				for (j=0;j<ML;j++) pF[j]=&F[j];
				pRat=&Rat;

				file=sample.data();
				n_peaks=Input_ANC (pF, file);
				System::Windows::Forms::Application::DoEvents();
				Input_WIR(pRat,file);


				
			    get_reset_index(pF,n_peaks);

				System::Windows::Forms::Application::DoEvents();
				
				if (panic==1) get_PANIC(pF,n_peaks);
				if (recommended==1) get_recommended(pF,n_peaks);
				
				get_228_Correction(pF,n_peaks,pRat);


				if(get_Frequency(pF,n_peaks)==0) write_ANC (pF,n_peaks,file);
				else 
				{

				sample2=sample;
				sample2.append(".anc.xls");
				file2=sample2.data();
				remove(file2);
	
				return(6);
				}

				return(0);


			}





  void MarshalString ( String ^ s, string& os ) {
				using namespace Runtime::InteropServices;
				const char* chars = 
					(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
				os = chars;
				Marshal::FreeHGlobal(IntPtr((void*)chars));
			}


  int Tools_KPG (struct isodata *p, int mode,string filename, string gth, string gepi, string enaa, string tirr)
			{

				ofstream header;
				ofstream PGout;
				ifstream PGin;
			
				stringstream(gth) >> p->Gt;
				stringstream(gepi) >> p->Ge;
				stringstream(enaa) >> p->ENAA;
				stringstream(tirr) >> p->ti;

			
				int i=0;
				int r=0;
				double Energy2=0;
				const char *file;
				const char *filen;
				const char *file2;
				string str2,str,sample,filename_dir;
				string filehead;

				string before="none";
				string tdecay;




				filehead=filename;
				filehead.resize(filehead.size()-4);
				filehead.append(".h");
				filen=filehead.data();

				header.open(filen);

				file=filename.data();
				PGin.open(file);


				while (!PGin.eof())
				{
					PGin >> str;
					if (str.compare("_________________________________________________________________")==0)
					{
						if (i==0) i=1; // it has not started, so start
						else i=2; // basic data was read, so continue with concentrations
						
						 // 1 - to read de basic data
						while (i==1) 
						{
							PGin >> str2;
							if (str2.compare("Meas.")==0) // take meas # and channel
							{
								PGin >> str >> p->ID;
								if(p->ID.find('X')==0) p->channel="BR1/Y4"; //for comparison with channel.dat
								if(p->ID.find('Z')==0) p->channel="BR1/S84"; //idem
							}
							if (str2.compare("DATA:")==0)
							{

								PGin >> p->meas; //take meas long name
								p->meas.resize(p->meas.size()-4);
								sample=p->meas; // make sample name from meas
								sample.resize(sample.size()-3); // taking first 5 letters
								if (sample.compare(before)==0)	r=0; // is the same sample so keep going
						
								else
								{
									r=1; // this is a new sample, include it in the header
									System::Windows::Forms::Application::DoEvents();

									String ^ S = gcnew String(sample.c_str());
									LOG->Text= LOG->Text->ToString() + "\t" + S + "\t\t...\t\tDONE!\n";
									header << sample << endl;
								}

								//make an excel file for storing the sample data
								before=sample;
								filename_dir=filename;
								filename_dir.resize(filename_dir.size()-4);
								filename_dir.append(".");
								filename_dir.append(sample);
								filename_dir.append(".xls");
								file2=filename_dir.data();

							}
							if (str2.compare("tm=")==0) PGin >> p->tc; //tmeas in seconds
							
							
							if (str2.compare("td=")==0) //take tdecay
							{
								PGin >> tdecay;
								int pch=tdecay.find('s');
								if(pch<=0) tdecay.append(".0s"); //for the bug
								i=3;
							}
						}



						// 2- to read the concentrations
						while (i==2) 
						{

							getline(PGin,str,'\n');
							stringstream(str)  >> p->Sym >> p->Iso >> p->Energy >> p->ro >> p->unc;


							if (p->Sym.compare("Gamma")==0)
							{
								i=0;
								p->Sym.clear();
							}

							else if (p->Sym.compare("without")!=0 && p->Iso.compare("lines") !=0)
							{


								if (p->Energy!=0 && p->ro!=0 && p->Energy!=Energy2)
								{
										if (r==0) PGout.open(file2,ios::app);

									if (r==1) //make a new excel file for the sample
									{
										remove(file2);
										PGout.open(file2,ios::app);
										PGout <<"Element\tIsotope\tEnergy\tppm\tsd\tPTF\tmeas time (s)\tirr time (m)\tdecay time\tID\tchannel\tGt\tGe\tfis\tENAA\n";
										r=0;
									}

								
									
									
									if (p->Iso.compare("U-239")==0 || p->Iso.compare("Np-239")==0)
									{
										p->fis='n';
										PGout << p->Sym << '\t'<< p->Iso << '\t'<< p->Energy << '\t'<< p->ro << '\t' << p->unc << '\t';
										PGout << p->meas << '\t' << p->tc << '\t' << p->ti << '\t' << tdecay <<'\t' << p->ID << '\t' << p->channel << '\t';
										PGout << p->Gt<< '\t'<< p->Ge << '\t' << p->fis << '\t' << p->ENAA << endl;

									}
									else
									{
										if (mode==1) p->fis='y'; // for only aquiring fission
										if (mode==0) p->fis='n';
										if (get_Analyte(p)!=0) // means that the analyte was found in the fission product library
										{
											PGout << p->Sym << '\t'<< p->Iso << '\t'<< p->Energy << '\t'<< p->ro << '\t' << p->unc << '\t';
											PGout << p->meas << '\t' << p->tc << '\t' << p->ti << '\t' << tdecay <<'\t' << p->ID << '\t' << p->channel << '\t';
											PGout << p->Gt<< '\t'<< p->Ge << '\t' << p->fis << '\t' << p->ENAA << endl;

										}
									}
									PGout.close();
									Energy2=p->Energy;
								}
							}
						}

					}
				}

				PGin.close();
				header.close();



				return(0);
			}







	int Tools_ANC(string sample)
			{
				const char *file,*file2;
string sample2;

				int j;
				int n_peaks=0;

				for (j=0;j<ML;j++) pF[j]=&F[j];
				for (j=0;j<ML;j++) pNF[j]=&NF[j];

				file=sample.data();

				n_peaks=Input_KPG(pF,file);

				System::Windows::Forms::Application::DoEvents();

				Input_KPG(pNF,file);

				

				for (j=0;j<=n_peaks;j++)
				{
					get_common(pF[j]);
					pNF[j]->fis='n';
					get_common(pNF[j]);
					System::Windows::Forms::Application::DoEvents();

				}
				
				get_Apparent_to_Uranium (n_peaks,pF,pNF);

			
				
				if (panic==1) get_PANIC(pF,n_peaks);
				
				if (recommended==1) get_recommended(pF,n_peaks);
				

				System::Windows::Forms::Application::DoEvents();


				sample2=sample;
				sample2.append(".irs.xls");
				file2=sample2.data();
				remove(file2);

				sample2=sample;
				sample2.append(".wir.txt");
				file2=sample2.data();
				remove(file2);

				sample2=sample;
				sample2.append(".wir.xls");
				file2=sample2.data();
				remove(file2);

				sample2=sample;
				sample2.append(".res.xls");
				file2=sample2.data();
				remove(file2);


				if(get_Frequency(pF,n_peaks)==0) write_ANC (pF,n_peaks,file);
				else 
				{

				sample2=sample;
				sample2.append(".anc.xls");
				file2=sample2.data();
				remove(file2);
	
				return(6);
				}

				
				return(0);

			}


	int Input_ANC (struct isodata *p[], const char *file)

			{
				string fileresults;
				fileresults.clear();
				fileresults.append(file);
				fileresults.append(".anc.xls");
				file=fileresults.data();

				ifstream inputdata1,inputdata2,inputdata3;
				
				string str;
				inputdata1.open(file);
				getline(inputdata1,str);

				int i=0;

				while (1)
				{
				
					//Isotope energy fission MEAS mass counts unc BG ti td tc channel Gt Ge geo Fc ENAA
					inputdata1 >> p[i]->Sym >> p[i]->Iso >> p[i]->Energy;
					inputdata1 >> p[i]->ro2 >> p[i]->ro >> p[i]->unc;
					inputdata1 >> p[i]->index >> p[i]->frq >> p[i]->meas >> p[i]->eta >>p[i]->factor;
					if (inputdata1.fail()) break;
					p[i]->unc=p[i]->unc/100;
					p[i]->frq=p[i]->frq/100;
					if (p[i]->index==3) i++;
				}
				inputdata1.close();

				inputdata2.open(file);
				getline(inputdata2,str);

				while (1)
				{
				
					//Isotope energy fission MEAS mass counts unc BG ti td tc channel Gt Ge geo Fc ENAA
					inputdata2 >> p[i]->Sym >> p[i]->Iso >> p[i]->Energy;
					inputdata2 >> p[i]->ro2 >> p[i]->ro >> p[i]->unc;
					inputdata2 >> p[i]->index >> p[i]->frq >> p[i]->meas >> p[i]->eta >>p[i]->factor;
					if (inputdata2.fail()) break;
					p[i]->unc=p[i]->unc/100;
					p[i]->frq=p[i]->frq/100;
					if (p[i]->index==4) i++;
				}
				inputdata2.close();

				inputdata3.open(file);
				getline(inputdata3,str);

				while (1)
				{
				
					//Isotope energy fission MEAS mass counts unc BG ti td tc channel Gt Ge geo Fc ENAA
					inputdata3 >> p[i]->Sym >> p[i]->Iso >> p[i]->Energy;
					inputdata3 >> p[i]->ro2 >> p[i]->ro >> p[i]->unc;
					inputdata3 >> p[i]->index >> p[i]->frq >> p[i]->meas >> p[i]->eta >>p[i]->factor;
					if (inputdata3.fail()) break;
					p[i]->unc=p[i]->unc/100;
					p[i]->frq=p[i]->frq/100;
				
					if (p[i]->index==5) i++;
				}
				inputdata3.close();



				return(i-1); // IMPORTANT: max number of isotopes or n_peaks in memory from excel sheet


			}


	int Input_WIR (struct enrichment *pR, const char *file)

			{
				string fileresults;
				fileresults.clear();
				fileresults.append(file);
				fileresults.append(".wir.xls");
				file=fileresults.data();


				ifstream batchlog;

				batchlog.open(file);

				batchlog >> pR->ratio >> pR->ro;
				batchlog >> pR->theta5 >> pR->ro5 >>pR->theta8 >>pR->ro8;
				batchlog >> pR->M >> pR->k  >> pR->time;

				pR->k=pR->k/2;

				batchlog.close();

				return(0); 

			}







int Input_KPG (struct isodata *p[], const char *file)
			{

				string fileresults;
				fileresults.clear();
				fileresults.append(file);
				fileresults.append(".xls");
				file=fileresults.data();

				int j=0;
				int n_peaks=0;
				ifstream input;
				input.open(file);
				string str;
				getline(input,str,'\n');
				while(1)
				{
					

					input >> p[j]->Sym >> p[j]->Iso >> p[j]->Energy >> p[j]->ro >> p[j]->unc >> p[j]->meas >> p[j]->tc >> p[j]->ti;
					if (input.fail()) break;
					
					p[j]->tc=p[j]->tc/60;
					double time=0;
					double number=0;
					char ch;
					while (1)
					{
						input >> number >> ch;
						if( ch=='d') time=time+number*1440*60;
						if( ch=='h') time=time + number*60*60;
						if( ch=='m') time=time+ number*60;
						if( ch=='s')
						{
							time=time+number;
							p[j]->td=time/60;
							break;
						}
					}
					input >> p[j]->ID >> p[j]->channel >> p[j]->Gt >> p[j]->Ge >> p[j]->fis >> p[j]->ENAA;



					j++;
				}
				input.close();

				n_peaks=j-1;


				return(n_peaks);
			}











#pragma endregion






};


}



