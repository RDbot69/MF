module sync_up_down_counter (
    input  wire       clk,
    input  wire       rst,
    input  wire       up_down,
    output reg  [2:0] count
);
    always @(posedge clk or posedge rst) begin
        if (rst)
            count <= 3'b000;
        else if (up_down)
            count <= count + 1'b1;
        else
            count <= count - 1'b1;
    end
endmodule
