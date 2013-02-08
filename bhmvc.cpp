#include <v8.h>
#include <node.h>
#include <array>
#include "./bmvc/controllers.h"
#include "./bmvc/output.h"
#include "./bmvc/router.h"
#include "./bmvc/config.h"

using namespace node;
using namespace v8;
using bhmvc::Output;
using std::array;
static int counter = 0;

static Handle<Value> foo(const Arguments& args)
{
    Output curOutput;
    counter++;
    if(args[0]->IsString())
    {
        String::AsciiValue val(args[0]->ToString());
        int argc1 = 1;
        char * argv1[] = {*val};
        cout<<"counter "<<counter<<endl;
        return String::New(router.routeRequest(NULL, argc1, argv1)->content());
    }
    cout<<"In foo, not a string"<<endl;
    return String::New(curOutput.getOutput().c_str());
}

extern "C" void init(Handle<Object> target)
{
  NODE_SET_METHOD(target, "foo", foo);
}
