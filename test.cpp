#include <wx/wx.h>
#include <wx/artprov.h>
#include <map>
#include <stdexcept>
#include <wx/app.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/generic/stattextg.h>

namespace Examples {

  class Frame : public wxFrame {
  public:
  Frame() : wxFrame(nullptr, wxID_ANY, "savior") {
    SetClientSize(640, 480);

    // welcometext->SetLabel("Convert Models Quick");
    // welcometext->SetFont({15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD});
    // welcometext->SetForegroundColour(wxTheColourDatabase->Find("Black"));

    // infotext->SetFont({8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT});
    // infotext->SetForegroundColour(wxTheColourDatabase->Find("White"));


    

    choice1->Append({"ONNX", "NCNN", "MNN", "PNNX"});
    choice1->SetSelection(0);
    choice1->Bind(wxEVT_CHOICE, &Frame::OnChoicClick, this);


    choice2->Append({"ONNX", "NCNN", "MNN", "PNNX"});
    choice2->SetSelection(0);
    choice2->Bind(wxEVT_CHOICE, &Frame::OnChoicClick2, this);

    

    // button->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {

    //     wxFileDialog openFileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "Text Files (*.txt)|*.txt|All Files (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    //     openFileDialog.SetFilterIndex(0);
    //     if (openFileDialog.ShowModal() == wxID_OK) {
    //       label->SetLabelText(wxString::Format("File = %s",  openFileDialog.GetPath()));
    //     }
    //   });
  }

  private:
    void OnChoicClick(wxCommandEvent& e) {
      choice1->SetSelection(static_cast<wxChoice*>(e.GetEventObject())->GetSelection());
      std::cout << choice1->GetSelection() << std::endl;
      if (choice1->GetSelection() == 3) {
          wxChoice* choice2 = new wxChoice(panel, wxID_ANY, {400, 60});
          choice2->Append("ONNX");
          choice2->SetSelection(0);
          choice2->Bind(wxEVT_CHOICE, &Frame::OnChoicClick2, this);
      }
    }
    void OnChoicClick2(wxCommandEvent& e) {
      choice2->SetSelection(static_cast<wxChoice*>(e.GetEventObject())->GetSelection());
    }

    //wxStaticText* welcometext = new wxStaticText(this, wxID_ANY, wxEmptyString, {190,10}, wxDefaultSize, wxALIGN_CENTER);
    // wxGenericStaticText* infotext = new wxGenericStaticText(this, wxID_ANY, "from ", {50,50}, wxDefaultSize, wxALIGN_CENTER);


    wxPanel* panel = new wxPanel(this);
    wxChoice* choice1 = new wxChoice(panel, wxID_ANY, {25, 60});
    wxChoice* choice2 = new wxChoice(panel, wxID_ANY, {400, 60});
    // wxButton* button = new wxButton(panel, wxID_ANY, "Open...", {10, 260});
    // wxStaticText* label = new wxStaticText(panel, wxID_ANY, "", {10, 300});
  
    };

  class Application : public wxApp {
    bool OnInit() override {
      (new Frame())->Show();
      return true;
    }
  };
}

int main(int argc, char* argv[]) {
  wxDISABLE_DEBUG_SUPPORT();
  new Examples::Application();
  return wxEntry(argc, argv);
}