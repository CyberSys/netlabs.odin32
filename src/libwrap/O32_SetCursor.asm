        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_SetCursor:PROC
        PUBLIC  O32_SetCursor
O32_SetCursor PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   _O32_SetCursor
    add    esp, 4
    pop    fs
    ret
O32_SetCursor ENDP

CODE32          ENDS

                END
