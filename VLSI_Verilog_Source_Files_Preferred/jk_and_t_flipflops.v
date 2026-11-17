module jk_flip_flop (
    input  wire clk,
    input  wire rst_n,
    input  wire j,
    input  wire k,
    output reg  q,
    output wire q_bar
);
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            q <= 1'b0;
        else begin
            case ({j, k})
                2'b00: q <= q;       // Hold
                2'b01: q <= 1'b0;    // Reset
                2'b10: q <= 1'b1;    // Set
                2'b11: q <= ~q;      // Toggle
            endcase
        end
    end
    assign q_bar = ~q;
endmodule

module t_flip_flop (
    input  wire clk,
    input  wire rst_n,
    input  wire t,
    output reg  q,
    output wire q_bar
);
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            q <= 1'b0;
        else if (t)
            q <= ~q;
        else
            q <= q;
    end
    assign q_bar = ~q;
endmodule
