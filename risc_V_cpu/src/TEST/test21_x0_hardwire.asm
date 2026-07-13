# Test x0 Hardwire-to-Zero
# In RISC-V, register x0 is physically wired to always read as 0
# Any attempt to write to x0 must be silently discarded by the CPU

# Attempt to write 42 into x0
ADDI x0, x0, 42

# Use x0 in an operation: if x0 is still 0, result is 0
ADD x1, x0, x0
# x1 should be 0 (0 + 0)
BNE x1, x0, FAIL

# Try harder: use x0 as rd in an ADD
ADDI x2, x0, 100
ADD x0, x2, x2
# x0 should STILL be 0
ADD x3, x0, x0
BNE x3, x0, FAIL

ADDI x31, x0, 1
ADDI x17, x0, 10
ECALL

FAIL:
ADDI x31, x0, 0
ADDI x17, x0, 10
ECALL
