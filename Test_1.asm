Data1 Segment
    Vb     db 1010011b
    String db "String test - new"
    Vw     dw 4567d
    Vd     dd 0d7856dh
Data1 ends
Data2 Segment
    Doublesg dw 678
    QWERTY   dd 67ff89h
    Zxcv     dd 89h
Data2 Ends

Assume cs:Code,ds:Data1,gs:Data2
Code Segment
    nop
    nop
    jmp label2
label1:
    adc vw[bp+di],ax
    jc label2
    sub ax, vw[eax+edx]

    shr ax,1
    not vB[eax+edx]
    Sub ax,vw[bp+di]
    Adc zXcV[eax+edx],ebx
    Jc label1
    jmp label1
label2:
Code ends