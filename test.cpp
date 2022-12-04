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
#include "layer.h"
#include "layer_type.h"
#include "net.h"
#include "ncnnoptimize.h"
#include <string.h>
#include "optimizer.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>


namespace Examples {

  class Frame : public wxFrame {
  public:
  std::string current_conversion = "onnx2ncnn";
  std::string paramPath ;
  std::string binPath   ;
  std::string onnxPath  ;

  void updateButtonBin() {
    buttonfile_bin->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        wxFileDialog openFileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "BIN Files (*.bin)|*.bin", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        openFileDialog.SetFilterIndex(0);
        if (openFileDialog.ShowModal() == wxID_OK) {
          label_bin->SetLabelText(wxString::Format("File = %s",  openFileDialog.GetPath()));
          std::cout << openFileDialog.GetPath() << std::endl;
          binPath = openFileDialog.GetPath();
        }
      });
  }

  void updateButtonParam() {
    buttonfile_param->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        wxFileDialog openFileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "PARAM Files (*.param)|*.param", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        openFileDialog.SetFilterIndex(0);
        if (openFileDialog.ShowModal() == wxID_OK) {
          label_param->SetLabelText(wxString::Format("File = %s",  openFileDialog.GetPath()));
          std::cout << openFileDialog.GetPath() << std::endl;
          paramPath = openFileDialog.GetPath();
        }
      });
  }

  void updateOnnx() {
    buttonOnnx->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        wxFileDialog openFileDialog(this, wxEmptyString, wxEmptyString, wxEmptyString, "ONNX Files (*.onnx)|*.onnx", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        openFileDialog.SetFilterIndex(0);
        if (openFileDialog.ShowModal() == wxID_OK) {
          label_onnx->SetLabelText(wxString::Format("File = %s",  openFileDialog.GetPath()));
          std::cout << openFileDialog.GetPath() << std::endl;
          onnxPath = openFileDialog.GetPath();
        }
      });
  }

  void removeNCNNOptimButton() {
    removeButtonBin();
    removeButtonParam();
  }

  void removeButtonParam() {
    buttonfile_param->Destroy();
  }

  void removeButtonBin() {
    buttonfile_bin->Destroy();
  }


  Frame() : wxFrame(nullptr, wxID_ANY, "savior") {
    SetClientSize(640, 480);   

    choice1->Append({"ONNX", "NCNN", "MNN", "PNNX"});
    choice1->SetSelection(0);
    choice1->Bind(wxEVT_CHOICE, &Frame::OnChoicClick, this);


    choice2->Append({"NCNN", "ONNX", "NCNN-optimized", "MNN", "PNNX"});
    choice2->SetSelection(0);
    choice2->Bind(wxEVT_CHOICE, &Frame::OnChoicClick2, this);

    button->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        if (current_conversion == "NCNN-optimized") {
          if (binPath.empty()) {
              std::cout << "bin path not specified" << binPath << std::endl;
              wxMessageDialog(nullptr, ".bin path not loaded").ShowModal();
              return;
          } 
          if (paramPath.empty()) {
              std::cout << "param path not specified" << paramPath << std::endl;
              wxMessageDialog(nullptr, ".param path not loaded").ShowModal();
              return;
          }
          optimizer.ncnnOptimize(
            false,
            nullptr,
            paramPath.c_str(),
            binPath.c_str()
          );

          optimizer.saveOptimized(
            "ncnn_optimized.param",
            "ncnn_optimized.bin"
          );

          wxMessageDialog(nullptr, "Converted ! ").ShowModal();
        } 

        if (current_conversion == "onnx2ncnn") {
          if (onnxPath.empty()) {
              std::cout << "onnx path not specified" << binPath << std::endl;
              wxMessageDialog(nullptr, ".onnx path not loaded").ShowModal();
              return;
          }
          optimizer.convertFromOnnx2Ncnn(onnxPath.c_str());
          wxMessageDialog(nullptr, "Saved!!" ).ShowModal();
          return;
        }
    });
  }

  private:
    void OnChoicClick(wxCommandEvent& e) {
      choice1->SetSelection(static_cast<wxChoice*>(e.GetEventObject())->GetSelection());
      std::cout << choice1->GetSelection() << std::endl;
      if (choice1->GetSelection() == 0) {
          wxChoice* choice2 = new wxChoice(panel, wxID_ANY, {400, 60});
          //choice2->Append("ONNX-sim");
          choice2->Append("NCNN");
          choice2->SetSelection(0);
          choice2->Bind(wxEVT_CHOICE, &Frame::OnChoicClick2, this);
          buttonOnnx   = new wxButton(panel, wxID_ANY, "Load ONNX", {35, 150});
          current_conversion = "onnx2ncnn" ;
          updateOnnx();
      }   
      if (choice1->GetSelection() == 1) {
          wxChoice* choice2 = new wxChoice(panel, wxID_ANY, {400, 60});
          choice2->Append("NCNN-optimized");
          choice2->SetSelection(0);
          choice2->Bind(wxEVT_CHOICE, &Frame::OnChoicClick2, this);
          current_conversion = "NCNN-optimized";

          buttonfile_bin   = new wxButton(panel, wxID_ANY, "Load BIN", {35, 150});
          buttonfile_param = new wxButton(panel, wxID_ANY, "Load PARAM", {35, 230});
          updateButtonBin();
          updateButtonParam();
      } else {
          removeNCNNOptimButton();
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
    wxButton* button = new wxButton(panel, wxID_ANY, "Convert", {260, 300});
    wxButton* buttonfile_bin   = new wxButton() ;//= new wxButton(panel, wxID_ANY, "Load BIN", {35, 150});
    wxButton* buttonfile_param = new wxButton(); //= new wxButton(panel, wxID_ANY, "Load PARAM", {35, 230});
    wxButton* buttonOnnx       = new wxButton(); 


    wxStaticText* label_bin = new wxStaticText(panel, wxID_ANY, "", {35, 200});
    wxStaticText* label_param = new wxStaticText(panel, wxID_ANY, "", {35, 270});
    wxStaticText* label_onnx = new wxStaticText(panel, wxID_ANY, "", {35, 200});

    //wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, "button1 clicked 0 times", {50, 150}, {200, 20});
    int button1Clicked = 0;
    Optimizer optimizer;
    //NetOptimize optimizer;

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