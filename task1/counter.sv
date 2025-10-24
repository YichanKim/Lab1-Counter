module counter #( //file name and module name must be the same
    parameter WIDTH = 8 // specify counter bit width
)(
    //interface signals
    input logic                 clk, //clock
    input logic                 rst, //reset
    input logic                en,  //counter enable
    output logic [WIDTH-1:0]   count  //count output
);

always_ff @ (posedge clk, posedge rst) //always_ff specifies a clocked circuit. This is an asynchronous reset
    if (rst) count <= {WIDTH{1'b0}}; //non-blocking assignment (asynchronous). {} is used to from WIDTH bits of 0
    else count <= count + {{WIDTH-1{1'b0}}, en};

endmodule
