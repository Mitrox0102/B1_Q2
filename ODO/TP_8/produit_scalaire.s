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
                     MOV R8 , RDX ; pour la MUL aussi
                     