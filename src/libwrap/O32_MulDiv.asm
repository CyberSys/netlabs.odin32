        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_MulDiv:PROC
        PUBLIC  O32_MulDiv
O32_MulDiv PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    call   _O32_MulDiv
    add    esp, 12
    pop    fs
    ret
O32_MulDiv ENDP

CODE32          ENDS

                END
