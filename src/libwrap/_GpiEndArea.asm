        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   GpiEndArea:PROC
        PUBLIC  _GpiEndArea
_GpiEndArea PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   GpiEndArea
    add    esp, 4
    pop    fs
    ret
_GpiEndArea ENDP

CODE32          ENDS

                END
