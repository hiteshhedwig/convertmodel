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

    fromonnx->SetValue(true);
      Bind(wxEVT_RADIOBUTTON, [&](wxCommandEvent& event) {
        staticText1->SetLabel(wxString::Format("frommnn state = %s", frommnn->GetValue() ? "true" : "false"));
      });
      
      staticText1->SetLabel(wxString::Format("frommnn state = %s", frommnn->GetValue() ? "true" : "false"));

    // button->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {

    //     wxFileDialog openFileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "Text Files (*.txt)|*.txt|All Files (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    //     openFileDialog.SetFilterIndex(0);
    //     if (openFileDialog.ShowModal() == wxID_OK) {
    //       label->SetLabelText(wxString::Format("File = %s",  openFileDialog.GetPath()));
    //     }
    //   });
  }

  private:
    static wxString ToString(wxCheckBoxState state) {
        if (state == wxCHK_UNCHECKED) return "Unchecked";
        if (state == wxCHK_CHECKED) return "Checked";
        return "Indeterminate";
      }


    //wxStaticText* welcometext = new wxStaticText(this, wxID_ANY, wxEmptyString, {190,10}, wxDefaultSize, wxALIGN_CENTER);
    // wxGenericStaticText* infotext = new wxGenericStaticText(this, wxID_ANY, "from ", {50,50}, wxDefaultSize, wxALIGN_CENTER);
    

    wxPanel* panel = new wxPanel(this);
    wxRadioButton* fromonnx = new wxRadioButton(panel, wxID_ANY, "ONNX", {30, 30});
    wxRadioButton* fromncnn = new wxRadioButton(panel, wxID_ANY, "NCNN", {30, 60});
    wxRadioButton* frommnn = new wxRadioButton(panel, wxID_ANY, "MNN", {30, 90});
    wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, wxEmptyString, {30, 150});

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