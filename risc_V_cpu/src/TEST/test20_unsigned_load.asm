# Test LBU (Load Byte Unsigned) and LHU (Load Halfword Unsigned)
# These should ZERO-extend, not sign-extend
# This is the critical difference from LB and LH

ADDI x1, x0, 200

# Store 0xFF byte (looks like -1 signed, but 255 unsigned)
ADDI x2, x0, -1
SB x2, 0(x1)

# LB should sign-extend 0xFF to 0xFFFFFFFF (-1)
LB x3, 0(x1)
ADDI x4, x0, -1
BNE x3, x4, FAIL

# LBU should zero-extend 0xFF to 0x000000FF (255)
LBU x5, 0(x1)
ADDI x6, x0, 255
BNE x5, x6, FAIL

# Store 0xFFFF halfword
SH x2, 2(x1)

# LH should sign-extend to 0xFFFFFFFF (-1)
LH x7, 2(x1)
BNE x7, x4, FAIL

# LHU should zero-extend to 0x0000FFFF (65535)
# We cannot load 65535 into a register with ADDI, so verify
# the upper 16 bits are zero by shifting right 16
LHU x8, 2(x1)
SRLI x9, x8, 16
# x9 should be 0 if LHU zero-extended correctly
BNE x9, x0, FAIL
# Also verify x8 != -1 (would mean sign extension happened)
BEQ x8, x4, FAIL

ADDI x31, x0, 1
ADDI x17, x0, 10
ECALL

FAIL:
ADDI x31, x0, 0
ADDI x17, x0, 10
ECALL
