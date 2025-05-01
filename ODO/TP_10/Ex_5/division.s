.intel_syntax noprefix
.data
printdata: .asciz "%u\n"
.text
.data global division
.type division, @function

division:   PUSH RBP
            MOV RBP, RSP
            MOV RAX, 0
loop:       SUB RDI, RSI
            INC RAX
            CMP RSI, RDI
            JBE loop
            POP RBP
            ;MOV EAX, EDI pour retoruner le reste
            RET

.text
.global factoriser
.type factoriser, @function

factoriser: PUSH RBP
            MOV RBP, RSP
            MOV R9D, EDI
            MOV R8D, 0x1
loop_inc:   INC R8D
loop_2:       CMP R9D, 0x1
            JE loop_end
            MOV EDI, R9D
            MOV ESI, R8D
            CALL division

            CMP EDI, 0
            JNE loop_inc
            MOV R9, RAX

            MOV RDI, offset flat:printdata
            MOV ESI, R8D
            CALL printf
            JMP loop_2
loop_end:   POP RBP
            RET
