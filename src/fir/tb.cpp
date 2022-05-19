#include    "tb.hpp"

void tb::source() {
    //Reset
    inp.write(0);
    inp_vld.write(0);
    rst.write(1);
    wait();
    rst.write(0);
    wait();

    sc_int<16>  tmp;

    //send stimlus to FIR
    for(int i=0;i<64;i++) {
        if (i > 23 && i < 29)
            tmp = 256;
        else
            tmp = 0;
        
        inp_vld.write(1);
        inp.write(tmp);

        do {
            wait();
        } while ( !inp_rdy.read() );
        inp_vld.write(0);
        start_time[i] = sc_time_stamp();
    }

    //simulation hanging gard
    wait(10000);
    printf("Hanging simulation stopped by TB source thread. \n");
    sc_stop();
}

void tb::sink() {
    sc_int<16>      indata;

    //Extract clock period
    //sc_clock *clk_p = DCAST<sc_clock*>(clk.get_interface());
    //clock_period = clk_p->period();
    //clock_period = 10 SC_NS;

    //Open simulation output results file
    char output_file[256];
    
    sprintf( output_file, "./output.dat");
    outfp = fopen(output_file, "wb");

    if (outfp == NULL)
    {
        printf("Couldn't open output.dat for writing. \n");
        exit(0);
    }

    //Initialize port
    outp_rdy.write(0);

    double total_cycles = 0;


    //Read output comming from DUT
    for(int i = 0; i < 64; i++) {
        outp_rdy.write(1);
        do {
            wait();
        } while (!outp_vld.read());
        indata = outp.read();
        end_time[i] = sc_time_stamp();
        //total_cycles += (end_time[i] - start_time[i]) / clock_period;
        //total_cycles += (int)((end_time[i] - start_time[i])) / 10;
        outp_rdy.write(0);

        fprintf(outfp, "%d\n", (int)indata);
        cout << i << " :\t" << indata.to_double() << endl;
    }
    
    //print latency
    //double total_throughput = (start_time[63] - start_time[0])/clock_period;
    //double total_throughput = (int)((start_time[63] - start_time[0]))/10;
    //printf("Average latency is %g cycles. \n", (double)(total_cycles/64) );
    //printf("Average throughput is %g cycles per input. \n", (double)(total_throughput/63) );

    //End simulation:w
    sc_stop();
}
