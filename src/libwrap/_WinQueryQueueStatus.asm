        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinQueryQueueStatus:PROC
        PUBLIC  _WinQueryQueueStatus
_WinQueryQueueStatus PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   WinQueryQueueStatus
    add    esp, 4
    pop    fs
    ret
_WinQueryQueueStatus ENDP

CODE32          ENDS

                END
