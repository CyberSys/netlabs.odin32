        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   _O32_RegCreateKeyEx:PROC
        PUBLIC  O32_RegCreateKeyEx
O32_RegCreateKeyEx PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+40]
    push   dword ptr [esp+40]
    push   dword ptr [esp+40]
    push   dword ptr [esp+40]
    push   dword ptr [esp+40]
    push   dword ptr [esp+40]
    push   dword ptr [esp+40]
    push   dword ptr [esp+40]
    push   dword ptr [esp+40]
    call   _O32_RegCreateKeyEx
    add    esp, 36
    pop    fs
    ret
O32_RegCreateKeyEx ENDP

CODE32          ENDS

                END
