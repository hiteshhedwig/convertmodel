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
#include "ncnnreader.h"
#include <algorithm>
#include <map>
#include <set>
#include <vector>

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
    choice1->SetSelection(01);
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

    button->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event) {
        staticText1->SetLabel(wxString::Format("Converted clicked %d times", ++button1Clicked));
        optimizer.storage_type = 0;
        optimizer.load_param("/home/eulermotors/ncnn/tools/tools/onnx/conv/ncnn.param");
        optimizer.load_model("/home/eulermotors/ncnn/tools/tools/onnx/conv/ncnn.bin");
        optimizer.fuse_batchnorm_scale();
        optimizer.fuse_convolution_batchnorm();
        optimizer.fuse_convolution_mul();
        optimizer.fuse_convolution_add();
        optimizer.fuse_convolutiondepthwise_batchnorm();
        optimizer.fuse_convolutiondepthwise_mul();
        optimizer.fuse_convolutiondepthwise_add();
        optimizer.fuse_deconvolution_batchnorm();
        optimizer.fuse_deconvolution_mul();
        optimizer.fuse_deconvolution_add();
        optimizer.fuse_deconvolutiondepthwise_batchnorm();
        optimizer.fuse_innerproduct_batchnorm();
        optimizer.fuse_innerproduct_add();
        optimizer.fuse_innerproduct_dropout();

        optimizer.replace_reduction_with_global_pooling();
        optimizer.replace_prelu_with_leaky_relu();

        optimizer.fuse_convolution_activation();
        optimizer.fuse_convolutiondepthwise_activation();
        optimizer.fuse_deconvolution_activation();
        optimizer.fuse_deconvolutiondepthwise_activation();
        optimizer.fuse_innerproduct_activation();
        optimizer.fuse_memorydata_binaryop();
        optimizer.fuse_binaryop_eltwise();

        optimizer.eliminate_dropout();
        optimizer.eliminate_pooling1x1();
        optimizer.eliminate_noop();
        optimizer.eliminate_split();
        optimizer.eliminate_flatten_after_global_pooling();
        optimizer.eliminate_reshape_after_global_pooling();
        optimizer.eliminate_reshape_before_binaryop();

        optimizer.replace_convolution_with_innerproduct_after_global_pooling();
        optimizer.replace_convolution_with_innerproduct_after_innerproduct();

        optimizer.eliminate_flatten_after_innerproduct();
        optimizer.eliminate_orphaned_memorydata();

        optimizer.shape_inference();

        optimizer.estimate_memory_footprint();

        optimizer.save("test.param", "test.bin");
    });
  }

  private:
    void OnChoicClick(wxCommandEvent& e) {
      choice1->SetSelection(static_cast<wxChoice*>(e.GetEventObject())->GetSelection());
      std::cout << choice1->GetSelection() << std::endl;
      if (choice1->GetSelection() == 0) {
          wxChoice* choice2 = new wxChoice(panel, wxID_ANY, {400, 60});
          choice2->Append("ONNX-sim");
          choice2->Append("NCNN");
          choice2->SetSelection(0);
          choice2->Bind(wxEVT_CHOICE, &Frame::OnChoicClick2, this);
      } else {
          wxChoice* choice2 = new wxChoice(panel, wxID_ANY, {400, 60});
          choice2->Append({"ONNX-sim", "NCNN", "MNN", "PNNX"});
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
    wxButton* button = new wxButton(panel, wxID_ANY, "Convert", {200, 260});
    // wxStaticText* label = new wxStaticText(panel, wxID_ANY, "", {10, 300});
    wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, "button1 clicked 0 times", {50, 150}, {200, 20});
    int button1Clicked = 0;
    NetOptimize optimizer ;


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