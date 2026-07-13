# Test I-Type Immediate Boundary Values
# I-Type immediate range: -2048 to 2047 (12-bit signed)
# Verify the CPU handles the extreme edges correctly

# Max positive: 2047
ADDI x1, x0, 2047
# Min negative: -2048
ADDI x2, x0, -2048

# Verify: 2047 + (-2048) should equal -1
ADD x3, x1, x2
ADDI x4, x0, -1
BNE x3, x4, FAIL

# Verify: 2047 + 1 = 2048
ADDI x5, x1, 1
# Build 2048 manually: LUI loads upper 20 bits, but 2048 = 0x800
# Easier: check 2048 - 2047 = 1
SUB x6, x5, x1
ADDI x7, x0, 1
BNE x6, x7, FAIL

# Verify: -2048 - 1 = -2049
ADDI x8, x2, -1
# Check: -2049 + 2049 should equal 0
# Build 2049: 2047 + 2
ADDI x9, x1, 2
ADD x10, x8, x9
BNE x10, x0, FAIL

ADDI x31, x0, 1
ADDI x17, x0, 10
ECALL

FAIL:
ADDI x31, x0, 0
ADDI x17, x0, 10
ECALL
