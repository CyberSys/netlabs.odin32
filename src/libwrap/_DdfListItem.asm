        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   DdfListItem:PROC
        PUBLIC  _DdfListItem
_DdfListItem PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    call   DdfListItem
    add    esp, 12
    pop    fs
    ret
_DdfListItem ENDP

CODE32          ENDS

                END
