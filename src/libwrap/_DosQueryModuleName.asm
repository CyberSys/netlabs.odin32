        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   DosQueryModuleName:PROC
        PUBLIC  _DosQueryModuleName
_DosQueryModuleName PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    push   dword ptr [esp+16]
    call   DosQueryModuleName
    add    esp, 12
    pop    fs
    ret
_DosQueryModuleName ENDP

CODE32          ENDS

                END
