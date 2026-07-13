ADDI x1, x0, 1
ADDI x2, x0, 10
LOOP:
    ADDI x1, x1, 1
    BNE x1, x2, LOOP
EBREAK