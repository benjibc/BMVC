#ifndef BHMVC_MODULE_HELLO
#define BHMVC_MODULE_HELLO

#include "../../../bmvc/controllers.h"
#include "../view/.tem.index.htm.h"
#include "../view/.tem.index.html.h"
#include "../model/SoundFileReader.h"
#include <fstream>

using bhmvc::Controller;
using bhmvc::JSON;

class Welcome : public Controller
{
    public:
    Welcome() : Controller(__FILE__) {}
    void WelcomeMsg()
    {
       this->output().setOutput("Hello world!");
       JSON curJSON;
       curJSON["firstName"] = "Benny";
       curJSON["lastName"] = "Chen";
       //render("index.htm", curJSON);
       this->output().appendOutput("Second part of output!");
       char * url[] = {(char*)"Waveform", (char*)"values"};
       this->route(2, url);
    }
    void values()
    {
       float * buffer;
       int bufferSize;
       float sampleRate = 1/0.6;
       
       SoundFileReader * sndreader = new SoundFileReader();
       sndreader->loadMusicFile("A.wav",BasicSoundInfo()); 
       buffer = sndreader->outputNormalizedAverageToBuffer(bufferSize,sampleRate);
 
       JSON output = JSON();
       for (int i = 0; i < bufferSize; i++)
       {
          output[i]  = buffer[i];
       }
       delete [] buffer;
       
       string curOutput = output.json_encode();
       this->output().setOutput(curOutput);
    }

    void index()
    {
        this->loadFile("index.html");
    }
};

#endif
