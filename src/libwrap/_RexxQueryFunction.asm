        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   RexxQueryFunction:PROC
        PUBLIC  _RexxQueryFunction
_RexxQueryFunction PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   RexxQueryFunction
    add    esp, 4
    pop    fs
    ret
_RexxQueryFunction ENDP

CODE32          ENDS

                END
