module sipo_reg (
    input  wire       clk,
    input  wire       rst,
    input  wire       mode,          // 0 = SIPO, 1 = PISO
    input  wire       load,          // Parallel load in PISO mode
    input  wire       serial_in,
    input  wire [3:0] parallel_in,
    output reg  [3:0] parallel_out,
    output wire       serial_out
);
    reg [3:0] shift_reg;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            shift_reg    <= 4'b0000;
            parallel_out <= 4'b0000;
        end
        else if (mode == 1'b0) begin
            shift_reg    <= {shift_reg[2:0], serial_in};
            parallel_out <= {shift_reg[2:0], serial_in};
        end
        else begin
            if (load)
                shift_reg <= parallel_in;
            else
                shift_reg <= {1'b0, shift_reg[3:1]};
        end
    end

    assign serial_out = shift_reg[0];
endmodule
