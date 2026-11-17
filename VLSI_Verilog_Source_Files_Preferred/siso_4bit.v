module siso_4bit (
    input  wire clk,
    input  wire rst,
    input  wire serial_in,
    output wire serial_out
);
    reg [3:0] shift_reg;

    always @(posedge clk or posedge rst) begin
        if (rst)
            shift_reg <= 4'b0000;
        else
            shift_reg <= {shift_reg[2:0], serial_in};
    end

    assign serial_out = shift_reg[3];
endmodule
