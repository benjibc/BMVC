#ifndef _MODULE_WAVEFORM_CONTROLLER_WAVEFORM_H
#define _MODULE_WAVEFORM_CONTROLLER_WAVEFORM_H

#include "../../../bmvc/controllers.h"
#include "../model/SoundFileReader.h"

class Waveform: public Controller
{
    public:
    Waveform() : Controller(__FILE__) {}

    void values()
    {
       this->output().setOutput("This is the second example where you"
       "can route different things at the same place");
    }
};

#endif
