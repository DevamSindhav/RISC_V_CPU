# JAL jumps to TARGET, saves return address in x5
JAL x5, TARGET
# JALR returns HERE (address 0x04), then we jump to PASS
JAL x0, PASS

TARGET:
# Return to caller using the saved address in x5
JALR x0, x5, 0

FAIL:
ADDI x31, x0, 0
ADDI x17, x0, 10
ECALL

PASS:
ADDI x31, x0, 1
ADDI x17, x0, 10
ECALL