#ifndef SCREEN3VIEW_HPP
#define SCREEN3VIEW_HPP

#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>
#include <gui/common/CustomKeyboard.hpp>

class Screen3View : public Screen3ViewBase
{
public:
    Screen3View();
    virtual ~Screen3View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void NameClicked();
    virtual void MdpClicked();
    virtual void OkClicked();
    virtual void ExitClicked();
    virtual void IdClicked();
    virtual void SendClicked();




protected:
    CustomKeyboard keyboard;
    int okmod;
    int nomod;
    int ermod;
    int idmod;
    int namemod;
    int mdpmod;
    char dataBuf[100];
    char idBuf[TEXTAREAID_SIZE];
    char nameBuf[TEXTAREANAME_SIZE];
    char mdpBuf[TEXTAREAMDP_SIZE];
    //char ID[30];
};

#endif // SCREEN3VIEW_HPP
