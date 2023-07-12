#include "SettingsForm.h"
#include "RootForm.h"
#include "Main.h"

using namespace System;
using namespace System::Text;
using namespace Windows::Forms;
using namespace System::Collections;

KeyboardAudio::SettingsForm::SettingsForm(void)
{
	InitializeComponent();
	//
	//TODO: Add the constructor code here
	//
}

KeyboardAudio::SettingsForm::SettingsForm(Form^ form)
{
	InitializeComponent();
	rootForm = form;

	tmpKeyToAudioDict = gcnew Dictionary<String^, String^>(((RootForm^)rootForm)->keyToAudioDict);
	tmpMouseToAudioDict = gcnew Dictionary<String^, String^>(((RootForm^)rootForm)->mouseToAudioDict);

	for each (Control ^ cont in Btn_groupBox->Controls)
		if ((Button^)cont)
			if (cont->Tag)
				((Button^)cont)->Click += gcnew System::EventHandler(this, &SettingsForm::KeyClick); // bind click event

	ResetSelected(false);
}

KeyboardAudio::SettingsForm::~SettingsForm()
{
	if (components)
	{
		delete components;
	}
}

System::Void KeyboardAudio::SettingsForm::ResetSelected(bool isReset)
{
	// finding key in UI, and show
	for each (Control ^ cont in Btn_groupBox->Controls)
	{
		if ((Button^)cont)
		{
			cont->BackColor = SystemColors::Control;
			if (cont->Tag)
			{
				if (!isReset)
				{
					if (!String::IsNullOrEmpty(tmpKeyToAudioDict[cont->Tag->ToString()]))
					{
						cont->BackColor = Color::Aqua; // already has audio's key set to aqua color
					}
				}
				else
				{
					if (!String::IsNullOrEmpty(((RootForm^)rootForm)->keyToAudioDict[cont->Tag->ToString()]))
					{
						cont->BackColor = Color::Aqua; // already has audio's key set to aqua color (reset)
					}
				}
			}
		}
	}
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::SelectedKey(String^ key)
{
	KeyName_Label->Text = key;
	AudioPath_Label->Text = tmpKeyToAudioDict[key];

	ResetSelected(false);

	// finding key in UI, and show
	for each (Control ^ cont in Btn_groupBox->Controls)
	{
		if ((Button^)cont)
		{
			if (cont->Tag)
			{
				if (cont->Tag->ToString() == key)
				{
					selectedKey_Btn = (Button^)cont;
					selectedKey_Btn->BackColor = Color::Yellow; // selected key set to yellow
				}
			}
		}
	}

	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::KeyClick(System::Object^ sender, System::EventArgs^ e)
{
	SelectedKey(((Button^)sender)->Tag->ToString());
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::ReloadForm()
{
	// Lang init
	if (Main::lang == "zh-TW")
	{
		this->Text = "�]�w";
		this->Size = System::Drawing::Size(1275, 660);
		SelectedKeyLabel_label->Text = "�{��ܤ�����G";
		SelectedKeyLabel_label->Location = Point(6, 18);
		SelectedKeyLabel_label->Size = System::Drawing::Size(197, 29);
		KeyName_Label->Location = Point(209, 24);
		AudioPathLabel_label->Text = "���ɸ��|�G";
		AudioPathLabel_label->Location = Point(6, 50);
		AudioPathLabel_label->Size = System::Drawing::Size(197, 29);
		AudioPath_Label->Location = Point(209, 60);
		SelectAudio_Btn->Text = "��ܭ���";
		SelectAudio_Btn->Size = System::Drawing::Size(197, 32);
		ResetAll_Btn->Text = "���]�Ҧ�����";
		Reset_Btn->Text = "���]�{��ܤ�����";
		Back_Btn->Text = "��^";
		Save_Btn->Text = "�x�s�ê�^";
		Description1_label->Text = "* �]�w���t�m�ϥ�100%����108����L�]�`�W�^�C";
		Description1_label->Location = Point(9, 530);
		Description2_label->Text = "* �A����L�W�i��S���Y�ǫ���C�B�Y�A����L���S�W�A�h�]�w���t�m�i��S���A�Q�n������C";
		Description2_label->Location = Point(9, 555);
		Description3_label->Text = "* �A�����ܤW��ӧO����ӳ]�w�C�]����������A��L������ӿ�ܨó]�w�C�]�]�w�b��ܭ��ɫ�N�|���Ȧs�^";
		Description3_label->Location = Point(9, 580);
		Annotation1_label->Text = "�{���";
		Annotation2_label->Text = "�w�]�w";
	}
	else
	{
		this->Text = "Settings";
		this->Size = System::Drawing::Size(1275, 680);
		SelectedKeyLabel_label->Text = "Selected Key:";
		SelectedKeyLabel_label->Size = System::Drawing::Size(156, 29);
		KeyName_Label->Location = Point(168, 24);
		AudioPathLabel_label->Text = "Audio Path:";
		AudioPathLabel_label->Size = System::Drawing::Size(156, 29);
		AudioPath_Label->Location = Point(168, 60);
		SelectAudio_Btn->Text = "Select Audio";
		SelectAudio_Btn->Size = System::Drawing::Size(156, 32);
		ResetAll_Btn->Text = "Reset All";
		Reset_Btn->Text = "Reset Selected Key";
		Back_Btn->Text = "Back";
		Save_Btn->Text = "Save and Exit";
		Description1_label->Text = "* The configuration is for 100% full-size 108-key keyboard (standard).";
		Description1_label->Location = Point(9, 530);
		Description2_label->Text = "* It's possible that certain keys may be missing on your keyboard. \r\n"
			+ "* Additionally, if your keyboard is non-standard, the configured setup may not have the specific keys you desire.";
		Description2_label->Location = Point(9, 555);
		Description3_label->Text = "* You can select each keys above to configure them. You can also directly press the keys on your keyboard to select and configure them. \r\n"
			+ "(The configuration will be temporarily stored after selecting an audio file.)";
		Description3_label->Location = Point(9, 596);
		Annotation1_label->Text = "Now Selected";
		Annotation2_label->Text = "Already Set";
	}
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::Back_Btn_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::Windows::Forms::DialogResult result = MessageBox::Show("�T�w���s�����}�ܡH", "", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (result == System::Windows::Forms::DialogResult::Yes) this->Close();
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::SettingsForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
{
	((RootForm^)rootForm)->ReloadForm();
	rootForm->Show();
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::ResetAll_Btn_Click(System::Object^ sender, System::EventArgs^ e)
{
	ResetSelected(true);
	KeyName_Label->Text = "";
	AudioPath_Label->Text = "";
	SelectAudio_Btn->Enabled = false;
	Reset_Btn->Enabled = false;
	tmpKeyToAudioDict = gcnew Dictionary<String^, String^>(((RootForm^)rootForm)->keyToAudioDict);
	tmpMouseToAudioDict = gcnew Dictionary<String^, String^>(((RootForm^)rootForm)->mouseToAudioDict);
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::Reset_Btn_Click(System::Object^ sender, System::EventArgs^ e)
{
	AudioPath_Label->Text = "";
	tmpKeyToAudioDict[selectedKey_Btn->Tag->ToString()] = String::Empty;
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::SelectAudio_Btn_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Title = "�п�ܱ��]�w������";
	ofd->Filter = "Audio File (*.wav;*.mp3;*.ogg)|*.wav;*.mp3;*.ogg";
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		AudioPath_Label->Text = ofd->FileName;
		tmpKeyToAudioDict[selectedKey_Btn->Tag->ToString()] = ofd->FileName;
	}
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::Save_Btn_Click(System::Object^ sender, System::EventArgs^ e)
{
	((RootForm^)rootForm)->keyToAudioDict = tmpKeyToAudioDict;
	((RootForm^)rootForm)->mouseToAudioDict = tmpMouseToAudioDict;
	Main::CreateNewIniFile(Main::iniPath, tmpKeyToAudioDict, tmpMouseToAudioDict);
	this->Close();
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::KeyName_Label_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (!String::IsNullOrEmpty(KeyName_Label->Text))
	{
		SelectAudio_Btn->Enabled = true;
		Reset_Btn->Enabled = true;
	}
	return System::Void();
}

bool KeyboardAudio::SettingsForm::ProcessDialogKey(System::Windows::Forms::Keys keyData)
{
	return false;
}

System::Void KeyboardAudio::SettingsForm::SettingsForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	e->Handled = true;
	Keys key = (Keys)e->KeyCode;

	if (key == Keys::ShiftKey)
		if (GetAsyncKeyState((int)Keys::LShiftKey)) key = Keys::LShiftKey;
		else key = Keys::RShiftKey;
	if (key == Keys::ControlKey)
		if (GetAsyncKeyState((int)Keys::LControlKey)) key = Keys::LControlKey;
		else key = Keys::RControlKey;
	if (key == Keys::Menu)
		if (GetAsyncKeyState((int)Keys::LMenu)) key = Keys::LMenu;
		else key = Keys::RMenu;

	SelectedKey(key.ToString());

	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::zhTWToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Main::UpdateIniFileLang(Main::iniPath, "zh-TW");
	ReloadForm();
	return System::Void();
}

System::Void KeyboardAudio::SettingsForm::englishToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Main::UpdateIniFileLang(Main::iniPath, "en");
	ReloadForm();
	return System::Void();
}
