        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_BringWindowToTop:PROC
        PUBLIC  O32_BringWindowToTop
O32_BringWindowToTop PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   _O32_BringWindowToTop
    add    esp, 4
    pop    fs
    ret
O32_BringWindowToTop ENDP

CODE32          ENDS

                END
