module pipo_register (
    input  wire       clk,
    input  wire       rst_n,
    input  wire [3:0] d,
    output reg  [3:0] q
);
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            q <= 4'b0000;
        else
            q <= d;
    end
endmodule
