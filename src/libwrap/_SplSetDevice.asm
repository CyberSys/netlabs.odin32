        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   SplSetDevice:PROC
        PUBLIC  _SplSetDevice
_SplSetDevice PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    push   dword ptr [esp+28]
    call   SplSetDevice
    add    esp, 24
    pop    fs
    ret
_SplSetDevice ENDP

CODE32          ENDS

                END
