        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_ResetEvent:PROC
        PUBLIC  O32_ResetEvent
O32_ResetEvent PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   _O32_ResetEvent
    add    esp, 4
    pop    fs
    ret
O32_ResetEvent ENDP

CODE32          ENDS

                END
