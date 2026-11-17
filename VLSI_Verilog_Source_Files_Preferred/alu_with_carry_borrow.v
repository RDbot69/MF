module alu_4bit_carry (
    input  wire [3:0] A,
    input  wire [3:0] B,
    input  wire [2:0] sel,
    output reg  [3:0] Y,
    output reg        carry
);
    reg [4:0] temp;

    always @(*) begin
        Y     = 4'b0000;
        carry = 1'b0;
        temp  = 5'b00000;

        case (sel)
            3'b000: begin                    // Addition with carry
                temp  = {1'b0, A} + {1'b0, B};
                Y     = temp[3:0];
                carry = temp[4];
            end
            3'b001: begin                    // Subtraction with borrow
                Y     = A - B;
                carry = (A < B);             // 1 when borrow occurs
            end
            3'b010: Y = A & B;               // AND
            3'b011: Y = A | B;               // OR
            3'b100: Y = A ^ B;               // XOR
            3'b101: Y = ~A;                  // NOT A
            3'b110: Y = A << 1;              // Multiply by 2 (4-bit result)
            3'b111: Y = A >> 1;              // Divide by 2 (unsigned)
            default: begin
                Y = 4'b0000;
                carry = 1'b0;
            end
        endcase
    end
endmodule
