        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   DrgQueryTrueType:PROC
        PUBLIC  _DrgQueryTrueType
_DrgQueryTrueType PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    call   DrgQueryTrueType
    add    esp, 12
    pop    fs
    ret
_DrgQueryTrueType ENDP

CODE32          ENDS

                END
