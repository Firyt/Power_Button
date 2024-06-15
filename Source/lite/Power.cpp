#include "Power.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Buat dan jalankan form Power
    lite::Power form;
    Application::Run(% form);
    return 0;
}
