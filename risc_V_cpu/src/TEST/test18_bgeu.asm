# Test BGEU (Branch if Greater Than or Equal Unsigned)
# Tests taken (greater), taken (equal), and not-taken paths

# Greater: 10 >= 5 unsigned, should branch
ADDI x1, x0, 10
ADDI x2, x0, 5
BGEU x1, x2, CHECK1
JAL x0, FAIL

CHECK1:
# Equal: 10 >= 10 unsigned, should branch
ADDI x3, x0, 10
BGEU x1, x3, CHECK2
JAL x0, FAIL

CHECK2:
# Not-taken: 5 >= 10 unsigned is false, should fall through
BGEU x2, x1, FAIL

# Unsigned edge: 0xFFFFFFFF >= 1, should branch
ADDI x4, x0, -1
ADDI x5, x0, 1
BGEU x4, x5, PASS
JAL x0, FAIL

PASS:
ADDI x31, x0, 1
ADDI x17, x0, 10
ECALL

FAIL:
ADDI x31, x0, 0
ADDI x17, x0, 10
ECALL
