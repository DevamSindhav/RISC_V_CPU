# Test BLTU (Branch if Less Than Unsigned)
# Tests both taken and not-taken paths, plus the unsigned edge case

# Basic: 3 < 7 unsigned, should branch
ADDI x1, x0, 3
ADDI x2, x0, 7
BLTU x1, x2, CHECK1
JAL x0, FAIL

CHECK1:
# Not-taken: 7 < 3 unsigned is false, should fall through
BLTU x2, x1, FAIL

# Unsigned edge: 7 < 0xFFFFFFFF unsigned, should branch
ADDI x3, x0, -1
BLTU x2, x3, PASS
JAL x0, FAIL

PASS:
ADDI x31, x0, 1
ADDI x17, x0, 10
ECALL

FAIL:
ADDI x31, x0, 0
ADDI x17, x0, 10
ECALL
