        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_SetLocalTime:PROC
        PUBLIC  O32_SetLocalTime
O32_SetLocalTime PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   _O32_SetLocalTime
    add    esp, 4
    pop    fs
    ret
O32_SetLocalTime ENDP

CODE32          ENDS

                END
