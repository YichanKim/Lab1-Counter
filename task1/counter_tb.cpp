/*
Mandatory header files.
Note the name Vcounter.h is for the module counter
*/

#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i; // coutns the number of clock cycles to simulate
    int clk; //clk is the module clock signal


Verilated::commandArgs(argc, argv);
    Vcounter* top = new Vcounter; // Instantiate the counter module as Vcounter. This is the DUT

    /*
    initialise trace dump
    Turn on signal tracing, and tell verilator to dump the waveform data
    to counter.vcd file
    */
    
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    /*
    Initialise simulation inputs
    Sets initial signal values before simulation
    Top is the name of the top-level entity
    Only the top-level signals are visible
    */
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    /*
    run simulation for many clock cycles
    
    The for loop is where the simulation happens
    i counts the clock cycles
    */
    for (i=0; i<300; i++){
        
        top ->rst = (i < 2) | (i==15); //change rst and en signls during simulation. rst = 1 for i = 0, 1, 15. rst = 0 for all other cycles
        top -> en = (i > 4); //en turns on from i = 5 onwards
        
        //dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++){
            tfp->dump(2*i+clk); //time is in ps. tfp is responsible for for recording all values during the simulation
            top->clk = !top->clk; //toggle clock
            top->eval(); //evaluate model again with new clock value
        }
        
        /*
        shifted by 1 as rst and en code block is after the for loop.
        Therefore, evaluation of the clock is done before the reset and enable is evaluated again
        */
        
        
        if (Verilated::gotFinish()) exit(0); //exit if finish signal received

    }

    tfp -> close(); //close VCD file
    exit(0); //exit program
}