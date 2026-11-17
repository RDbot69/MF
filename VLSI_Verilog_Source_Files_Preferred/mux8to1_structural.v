module mux2to1 (
    input  wire I0,
    input  wire I1,
    input  wire S,
    output wire Y
);
    assign Y = S ? I1 : I0;
endmodule

module mux4to1_structural (
    input  wire [3:0] I,
    input  wire [1:0] S,
    output wire Y
);
    wire y0, y1;

    mux2to1 M0 (.I0(I[0]), .I1(I[1]), .S(S[0]), .Y(y0));
    mux2to1 M1 (.I0(I[2]), .I1(I[3]), .S(S[0]), .Y(y1));
    mux2to1 M2 (.I0(y0),   .I1(y1),   .S(S[1]), .Y(Y));
endmodule

module mux8to1_structural (
    input  wire [7:0] I,
    input  wire [2:0] S,
    output wire Y
);
    wire y_low, y_high;

    mux4to1_structural M0 (
        .I(I[3:0]), .S(S[1:0]), .Y(y_low)
    );
    mux4to1_structural M1 (
        .I(I[7:4]), .S(S[1:0]), .Y(y_high)
    );
    mux2to1 M2 (
        .I0(y_low), .I1(y_high), .S(S[2]), .Y(Y)
    );
endmodule
