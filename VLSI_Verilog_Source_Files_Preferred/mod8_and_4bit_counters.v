module mod8_counter (
    input  wire       clk,
    input  wire       rst,
    output reg  [2:0] count
);
    always @(posedge clk or posedge rst) begin
        if (rst)
            count <= 3'b000;
        else
            count <= count + 1'b1;
    end
endmodule

module binary4_counter (
    input  wire       clk,
    input  wire       rst,
    output reg  [3:0] count
);
    always @(posedge clk or posedge rst) begin
        if (rst)
            count <= 4'b0000;
        else
            count <= count + 1'b1;
    end
endmodule
