        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   DdfEndList:PROC
        PUBLIC  _DdfEndList
_DdfEndList PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   DdfEndList
    add    esp, 4
    pop    fs
    ret
_DdfEndList ENDP

CODE32          ENDS

                END
