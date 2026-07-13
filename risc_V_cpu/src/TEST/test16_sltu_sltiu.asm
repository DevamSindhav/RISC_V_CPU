# Test SLTU (Set Less Than Unsigned) and SLTIU
# Unsigned comparison catches the case where -1 (0xFFFFFFFF) is the LARGEST number, not the smallest

# Basic unsigned: 5 < 10 = true
ADDI x1, x0, 5
ADDI x2, x0, 10
SLTU x3, x1, x2
# x3 should be 1
BEQ x3, x0, FAIL

# Tricky case: -1 as unsigned is 0xFFFFFFFF (huge!)
# So 1 < 0xFFFFFFFF unsigned = true
ADDI x4, x0, -1
ADDI x5, x0, 1
SLTU x6, x5, x4
# x6 should be 1
BEQ x6, x0, FAIL

# Reverse: 0xFFFFFFFF < 1 unsigned = false
SLTU x7, x4, x5
# x7 should be 0
BNE x7, x0, FAIL

# SLTIU: 1 < 0xFFFFFFFF (sign-extended -1) unsigned = true
SLTIU x8, x5, -1
# x8 should be 1
BEQ x8, x0, FAIL

ADDI x31, x0, 1
ADDI x17, x0, 10
ECALL

FAIL:
ADDI x31, x0, 0
ADDI x17, x0, 10
ECALL
