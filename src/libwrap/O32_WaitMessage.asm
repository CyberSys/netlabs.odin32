        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_WaitMessage:PROC
        PUBLIC  O32_WaitMessage
O32_WaitMessage PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    call   _O32_WaitMessage
    pop    fs
    ret
O32_WaitMessage ENDP

CODE32          ENDS

                END
