        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   DosSetFHState:PROC
        PUBLIC  _DosSetFHState
_DosSetFHState PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+12]
    push   dword ptr [esp+12]
    call   DosSetFHState
    add    esp, 8
    pop    fs
    ret
_DosSetFHState ENDP

CODE32          ENDS

                END
