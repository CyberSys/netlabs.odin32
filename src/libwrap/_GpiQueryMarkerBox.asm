        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   GpiQueryMarkerBox:PROC
        PUBLIC  _GpiQueryMarkerBox
_GpiQueryMarkerBox PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+12]
    push   dword ptr [esp+12]
    call   GpiQueryMarkerBox
    add    esp, 8
    pop    fs
    ret
_GpiQueryMarkerBox ENDP

CODE32          ENDS

                END
