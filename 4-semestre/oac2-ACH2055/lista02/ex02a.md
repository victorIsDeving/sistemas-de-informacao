$t1 = 0 e $s2 = 0
    `slt $t2, $0, $t1` -> $t2 = 0 ( 0 < 0 )
    `beq $t2, $0, DONE` -> true, segue para _DONE_
Então $s2 termina com o valor que começou, `0`