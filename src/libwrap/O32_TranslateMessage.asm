        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_TranslateMessage:PROC
        PUBLIC  O32_TranslateMessage
O32_TranslateMessage PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   _O32_TranslateMessage
    add    esp, 4
    pop    fs
    ret
O32_TranslateMessage ENDP

CODE32          ENDS

                END
