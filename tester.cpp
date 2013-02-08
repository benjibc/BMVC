#include "./bmvc/router.h"
#include "./bmvc/controllers.h"
#include "./bmvc/config.h"
#include <stdio.h>
#include <welcome/controller/welcome.h>
using std::cout;
using std::endl;

//test for router
int main(int argc, char * argv[])
{
    bhmvc::Output curOutput;// = router.routeRequest(NULL, argc, argv);
    const char * request = "GET /Welcome/WelcomeMsg/seg3/seg4 HTTP/1.1\r\n"
    "Host: www.facebook.com\r\n"
    "Connection: keep-alive\r\n"
    "Cache-Control: max-age=0\r\n"
    "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.4 "
    "(KHTML, like Gecko) Chrome/22.0.1229.94 Safari/537.4\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;"
    "q=0.9,*/*;q=0.8\r\n"
    "Accept-Encoding: gzip,deflate,sdch\r\n"
    "Accept-Language: en-US,en;q=0.8,zh;q=0.6\r\n"
    "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.3\r\n"
    "Cookie: datr=NsMoUGQj1PtT5NBxZBt1eBz4; lu=ThlgM-3DtgWToioApbWvlL8w;" 
    "act=1353141401681%2F1%3A0; sub=1024; p=121; c_user=1131512639; "
    "fr=09VP5qkVASxeX8AFe.AWWjLsYaZq9BVoymFJCcXfijN-Y.BQKMM2.Q4.AWVp5_21; "
    "xs=5%3ApOj3NaIq7Ukqpw%3A0%3A1345359394; "
    "presence=EM353141402EuserFA21131512639A2EstateFDsb2F0Et2F_5b_5dElm2Fn"
    "ullEuct2F1353208198BEtrFA2loadA2EtwF511347691EatF1353141402356G353139"
    "144611CEchFDp_5f1131512639F1CC";
    //int argc1 = 1;
    //char * strArg = (char*)"/Welcome/WelcomeMsg";
    //char * argv1[] = {strArg};
    bhmvc::MinimalCtrllr *curCtrllr = router.route(request);
    //curCtrllr->swapOutput(curOutput);
    //cout<<curOutput.getOutput()<<endl;
    //delete curCtrllr;
    return 0;
}
