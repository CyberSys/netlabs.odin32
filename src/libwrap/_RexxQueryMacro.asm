        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   RexxQueryMacro:PROC
        PUBLIC  _RexxQueryMacro
_RexxQueryMacro PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+12]
    push   dword ptr [esp+12]
    call   RexxQueryMacro
    add    esp, 8
    pop    fs
    ret
_RexxQueryMacro ENDP

CODE32          ENDS

                END
