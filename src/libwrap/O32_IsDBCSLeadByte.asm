        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_IsDBCSLeadByte:PROC
        PUBLIC  O32_IsDBCSLeadByte
O32_IsDBCSLeadByte PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   _O32_IsDBCSLeadByte
    add    esp, 4
    pop    fs
    ret
O32_IsDBCSLeadByte ENDP

CODE32          ENDS

                END
