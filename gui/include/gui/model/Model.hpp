#ifndef MODEL_HPP
#define MODEL_HPP
class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
    void saveButton(int counterValue);
    int getCounterValue() const;
    const char* getTextFromBuffer();
    void sendData (char *data);
    void sendDateTime(); // Ajoutez cette déclaration
    void saveText(const char* text);
    void getText(char* textBuffer, int bufferSize) const;

    virtual void updateTextFromBuffer(const char* texte) {}
protected:
    ModelListener* modelListener;
    bool button_State;
    int counterValue;
    char data[50];
    char savedText[30];


};

#endif // MODEL_HPP
