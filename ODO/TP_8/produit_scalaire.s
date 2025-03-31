.intel_syntax noprefix
.text
.global produit_scalaire
.type produit_scalaire , @function
; convention pour définir une fonction

produit_scalaire:
                     PUSH RBP
                     MOV RBP , RSP
                     ;MOV RAX , 0
                     ;RAX ne peut pas etre utilise car
                     ;la multiplication va modifier la valeur de RAX et RDX
                     ;on va utiliser R12
                     PUSH R12 ; tmp = 0
                     MOV R12 , 0 ; tmp = 0
                     MOV R8 , RDX ; pour la MUL aussi
                     MOV RCX , 0 ; i = 0
                     

loop:                MOV RAX , 0
                     MOV AL , byte ptr[ RDI + RCX ]
                     IMUL byte ptr[ RSI + RCX ]
                     ADD R12W , AX
                     INC RCX
                     CMP RCX , R8 ; i<n
                     JL loop
                     POP R12
                     MOV AL , R12B
                     POP RBP
                     RET