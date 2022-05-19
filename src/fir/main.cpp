#include    <systemc.h>
#include    "fir.hpp"
#include    "tb.hpp"

SC_MODULE(SYSTEM) {
    //MODULE declarations
    tb      *tb0;
    fir     *fir0;

    //Local signal declaration
    sc_signal< sc_int<16> >     inp_sig;
    sc_signal< bool >           inp_vld_sig;
    sc_signal< bool >           inp_rdy_sig;

    sc_signal< sc_int<16> >     outp_sig;
    sc_signal< bool >           outp_vld_sig;
    sc_signal< bool >           outp_rdy_sig;

    sc_signal< bool >           rst_sig;

    sc_clock                    clk_sig;

    
    SC_CTOR(SYSTEM) : clk_sig ("clk_sig", 10, SC_NS)
    {
        
        //Module instance signal connections
        tb0 = new tb("tb0");
        tb0->clk(clk_sig);
        tb0->rst(rst_sig);
        tb0->inp(inp_sig);
        tb0->inp_vld(inp_vld_sig);
        tb0->inp_rdy(inp_rdy_sig);
        tb0->outp(outp_sig);
        tb0->outp_vld(outp_vld_sig);
        tb0->outp_rdy(outp_rdy_sig);
        

        fir0 = new fir("fir0");
        fir0->clk(clk_sig);
        fir0->rst(rst_sig);
        fir0->inp(inp_sig);
        fir0->inp_vld(inp_vld_sig);
        fir0->inp_rdy(inp_rdy_sig);
        fir0->outp(outp_sig);
        fir0->outp_vld(outp_vld_sig);
        fir0->outp_rdy(outp_rdy_sig);
 
 
    }

    ~SYSTEM() {
        //Destructor
        delete tb0;
        delete fir0;
    }
};


SYSTEM *top = NULL;

int sc_main( int argc, char* argv[] ) {
    top = new SYSTEM( "top" );
    sc_start();
    return 0;
}
