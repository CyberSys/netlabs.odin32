        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_GetLastActivePopup:PROC
        PUBLIC  O32_GetLastActivePopup
O32_GetLastActivePopup PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   _O32_GetLastActivePopup
    add    esp, 4
    pop    fs
    ret
O32_GetLastActivePopup ENDP

CODE32          ENDS

                END
