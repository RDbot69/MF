module clock_divider_1hz #(
    parameter integer HALF_PERIOD = 50000000
) (
    input  wire clk_100MHz,
    input  wire rst,
    output reg  clk_1Hz
);
    reg [31:0] counter;

    always @(posedge clk_100MHz or posedge rst) begin
        if (rst) begin
            counter <= 32'd0;
            clk_1Hz <= 1'b0;
        end
        else if (counter == HALF_PERIOD - 1) begin
            counter <= 32'd0;
            clk_1Hz <= ~clk_1Hz;
        end
        else begin
            counter <= counter + 1'b1;
        end
    end
endmodule
