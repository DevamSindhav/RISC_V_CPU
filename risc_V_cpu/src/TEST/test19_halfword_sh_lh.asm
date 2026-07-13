# Test SH (Store Halfword) and LH (Load Halfword with sign extension)
# Store a 16-bit value, load it back, verify it matches

# Use address 200 (safely past instruction memory, aligned to 2)
ADDI x1, x0, 200
ADDI x2, x0, 1234
SH x2, 0(x1)
LH x3, 0(x1)
BNE x2, x3, FAIL

# Test sign extension: store 0xFFFF (-1 as halfword), load with LH
# LH should sign-extend to 0xFFFFFFFF
ADDI x4, x0, -1
SH x4, 2(x1)
LH x5, 2(x1)
ADDI x6, x0, -1
BNE x5, x6, FAIL

ADDI x31, x0, 1
ADDI x17, x0, 10
ECALL

FAIL:
ADDI x31, x0, 0
ADDI x17, x0, 10
ECALL
