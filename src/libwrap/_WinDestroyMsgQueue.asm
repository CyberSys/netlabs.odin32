        .386p
CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'

        EXTRN   WinDestroyMsgQueue:PROC
        PUBLIC  _WinDestroyMsgQueue
_WinDestroyMsgQueue PROC NEAR
    push   fs
    mov    eax, 0150bh
    mov    fs, eax
    push   dword ptr [esp+8]
    call   WinDestroyMsgQueue
    add    esp, 4
    pop    fs
    ret
_WinDestroyMsgQueue ENDP

CODE32          ENDS

                END
