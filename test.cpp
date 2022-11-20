#include <wx/wx.h>
#include <wx/artprov.h>
#include <map>
#include <stdexcept>
#include <wx/app.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/stattext.h>

namespace Examples {

  class Frame : public wxFrame {
  public:
  Frame() : wxFrame(nullptr, wxID_ANY, "savior") {
    SetClientSize(640, 480);

    button->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {

        wxFileDialog openFileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "Text Files (*.txt)|*.txt|All Files (*.*)|*.*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        openFileDialog.SetFilterIndex(0);
        if (openFileDialog.ShowModal() == wxID_OK) {
          label->SetLabelText(wxString::Format("File = %s",  openFileDialog.GetPath()));
        }



      });
  }

  private:
    wxPanel* panel = new wxPanel(this);
    wxButton* button = new wxButton(panel, wxID_ANY, "Open...", {10, 60});
    wxStaticText* label = new wxStaticText(panel, wxID_ANY, "", {10, 100});
    // wxPanel* panel = new wxPanel(this);
    // wxButton* button1 = new wxButton(panel, wxID_ANY, "button1", {50, 10});
    // wxButton* button2 = new wxButton(panel, wxID_ANY, "button2", {50, 60}, {200, 75}, wxBORDER_SIMPLE);
    // wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, "button1 clicked 0 times", {50, 150}, {200, 20});
    // wxStaticText* staticText2 = new wxStaticText(panel, wxID_ANY, "button2 clicked 0 times", {50, 180}, {200, 20});
    // int button1Clicked = 0;
    // int button2Clicked = 0;
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