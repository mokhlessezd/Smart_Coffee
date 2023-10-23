#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void updateTextInTextArea(const char* text); // Ajout de la fonction pour mettre à jour le textArea2

    void appendToHistory(const char* entry);
protected:
};

#endif // SCREEN2VIEW_HPP
