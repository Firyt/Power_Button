#pragma once
#include <Windows.h> // Untuk fungsi Windows API
#include <Winbase.h> // Untuk InitiateSystemShutdownEx
#include <Lmcons.h> // Untuk MAX_COMPUTERNAME_LENGTH
#include <PowrProf.h> // Untuk SetSuspendState
#include <cstdlib> // Untuk std::system
#include <string> // Untuk std::to_string
#pragma comment(lib, "PowrProf.lib") // Link library PowrProf

namespace lite {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Power : public System::Windows::Forms::Form
    {
    public:
        Power(void)
        {
            InitializeComponent();
        }

    protected:
        ~Power()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Button^ buttonShutdown;
    private: System::Windows::Forms::Button^ buttonRestart;
    private: System::Windows::Forms::Button^ buttonSleep;
    private: System::Windows::Forms::Timer^ countdownTimer;
    private: int countdown;
    private: bool isShutdown;
    private: System::Windows::Forms::Form^ countdownForm;
    private: System::Windows::Forms::Label^ countdownLabel;
    private: System::ComponentModel::IContainer^ components;

    protected:

    private:


#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Power::typeid));
            this->buttonShutdown = (gcnew System::Windows::Forms::Button());
            this->buttonRestart = (gcnew System::Windows::Forms::Button());
            this->buttonSleep = (gcnew System::Windows::Forms::Button());
            this->countdownTimer = (gcnew System::Windows::Forms::Timer(this->components));
            this->SuspendLayout();
            // 
            // buttonShutdown
            // 
            this->buttonShutdown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->buttonShutdown->Location = System::Drawing::Point(16, 25);
            this->buttonShutdown->Name = L"buttonShutdown";
            this->buttonShutdown->Size = System::Drawing::Size(173, 83);
            this->buttonShutdown->TabIndex = 0;
            this->buttonShutdown->Text = L"Shutdown";
            this->buttonShutdown->UseVisualStyleBackColor = true;
            this->buttonShutdown->Click += gcnew System::EventHandler(this, &Power::buttonShutdown_Click);
            // 
            // buttonRestart
            // 
            this->buttonRestart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->buttonRestart->Location = System::Drawing::Point(231, 25);
            this->buttonRestart->Name = L"buttonRestart";
            this->buttonRestart->Size = System::Drawing::Size(176, 83);
            this->buttonRestart->TabIndex = 1;
            this->buttonRestart->Text = L"Restart";
            this->buttonRestart->UseVisualStyleBackColor = true;
            this->buttonRestart->Click += gcnew System::EventHandler(this, &Power::buttonRestart_Click);
            // 
            // buttonSleep
            // 
            this->buttonSleep->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->buttonSleep->Location = System::Drawing::Point(16, 114);
            this->buttonSleep->Name = L"buttonSleep";
            this->buttonSleep->Size = System::Drawing::Size(391, 62);
            this->buttonSleep->TabIndex = 2;
            this->buttonSleep->Text = L"Sleep";
            this->buttonSleep->UseVisualStyleBackColor = true;
            this->buttonSleep->Click += gcnew System::EventHandler(this, &Power::buttonSleep_Click);
            // 
            // countdownTimer
            // 
            this->countdownTimer->Interval = 1000;
            this->countdownTimer->Tick += gcnew System::EventHandler(this, &Power::countdownTimer_Tick);
            // 
            // Power
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(424, 213);
            this->Controls->Add(this->buttonSleep);
            this->Controls->Add(this->buttonRestart);
            this->Controls->Add(this->buttonShutdown);
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"Power";
            this->Text = L"Power Switch";
            this->Load += gcnew System::EventHandler(this, &Power::Power_Load);
            this->ResumeLayout(false);

        }
#pragma endregion

    private: System::Void buttonShutdown_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::DialogResult result = MessageBox::Show("Yakin lu mau Matiin?", "Konfirmasi.", System::Windows::Forms::MessageBoxButtons::YesNo, System::Windows::Forms::MessageBoxIcon::Question);

        if (result == System::Windows::Forms::DialogResult::Yes) {
            countdown = 10; // Set countdown to 15 seconds
            isShutdown = true;
            ShowCountdownForm();
            countdownTimer->Start();
        }
    }

    private: System::Void buttonRestart_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::DialogResult result = MessageBox::Show("Yakin lu mau Restart?", "Konfirmasi", System::Windows::Forms::MessageBoxButtons::YesNo, System::Windows::Forms::MessageBoxIcon::Question);

        if (result == System::Windows::Forms::DialogResult::Yes) {
            countdown = 10; // Set countdown to 15 seconds
            isShutdown = false;
            ShowCountdownForm();
            countdownTimer->Start();
        }
    }

    private: System::Void countdownTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
        countdown--;
        countdownLabel->Text = "Komputer akan " + (isShutdown ? "mati" : "restart") + " dalam " + countdown.ToString() + " detik. \n\nSAVE DAN TUTUP APLIKASI!!!";
        if (countdown <= 0) {
            countdownTimer->Stop();
            countdownForm->Close();
            if (isShutdown) {
                std::system("shutdown /s /t 0");
            }
            else {
                std::system("shutdown /r /t 0");
            }
        }
    }

    private: System::Void buttonSleep_Click(System::Object^ sender, System::EventArgs^ e) {
        System::Windows::Forms::DialogResult result = MessageBox::Show("Yakin Mau tidur?", "Konfirmasi", System::Windows::Forms::MessageBoxButtons::YesNo, System::Windows::Forms::MessageBoxIcon::Question);

        if (result == System::Windows::Forms::DialogResult::Yes) {
            SetSuspendState(FALSE, FALSE, FALSE);
        }
    }

    private: System::Void ShowCountdownForm() {
        countdownForm = gcnew System::Windows::Forms::Form();
        countdownLabel = gcnew System::Windows::Forms::Label();
        countdownLabel->Text = "Komputer akan " + (isShutdown ? "mati" : "restart") + " dalam " + countdown.ToString() + " detik. \n\nSAVE DAN TUTUP APLIKASI!!!";
        countdownLabel->Dock = DockStyle::Fill;
        countdownLabel->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 14);
        countdownLabel->TextAlign = ContentAlignment::MiddleCenter;
        countdownForm->Controls->Add(countdownLabel);
        countdownForm->Size = System::Drawing::Size(400, 150);
        countdownForm->Icon = gcnew System::Drawing::Icon(L"Power.ico");
        countdownForm->Show();
    }
    private: System::Void Power_Load(System::Object^ sender, System::EventArgs^ e) {
    }
};
}
