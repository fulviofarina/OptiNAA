#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace optinaa {

	/// <summary>
	/// Summary for gammas
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class gammas : public System::Windows::Forms::Form
	{
	public:
		gammas(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~gammas()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ToolStrip^  La_140_1596;
	private: System::Windows::Forms::Timer^  timer1;






	private: System::ComponentModel::IContainer^  components;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->La_140_1596 = (gcnew System::Windows::Forms::ToolStrip());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// La_140_1596
			// 
			this->La_140_1596->Location = System::Drawing::Point(0, 0);
			this->La_140_1596->Name = L"La_140_1596";
			this->La_140_1596->Size = System::Drawing::Size(543, 25);
			this->La_140_1596->TabIndex = 0;
			this->La_140_1596->Text = L"toolStrip1";
			// 
			// gammas
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(543, 377);
			this->Controls->Add(this->La_140_1596);
			this->Name = L"gammas";
			this->Text = L"gammas";
			this->ResumeLayout(false);
			this->PerformLayout();

			
		}
#pragma endregion
	};
}
