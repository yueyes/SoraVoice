#include "asm_callee.h"
#include <SVData.h>

void text() {
	_asm {
		push    eax
		
		cmp     dword ptr [sv.sora], 0
		jne     text_sora
		cmp     dword ptr [sv.tits], 0
		je      text_start
		
		mov     eax, ebx //tits
		jmp     short text_start
	text_sora:
		mov     eax, edx //sora

	text_start:
		cmp     byte ptr [eax], 0x20
		jb      jcode

		cmp     byte ptr [eax], '#'
		jnz     short checkcode

		push    eax
	loopstart:
		inc     eax
		cmp     byte ptr [eax], '0'
		jb      short loopend
		cmp     byte ptr [eax], '9'
		jbe     short loopstart

	loopend:
		cmp     byte ptr [eax], 'A'
		jnz     checkV
		mov     dword ptr [sv.status.scode], 0
		pop     eax
		jmp     short text_return

	checkV:
		cmp     byte ptr [eax], 'v'
		pop     eax
		jnz     short text_return

		push    ecx
		push    edx
		push    eax
		call    ASM::Play
		pop     edx
		pop     ecx

	text_return:
		pop     eax
		push    dword ptr [sv.jcs.text.to]
		ret     4

	checkcode:
		mov     eax, dword ptr [sv.status.scode]
		cmp     eax, dword ptr [sv.scode.TEXT]
		je      checkwait
		cmp     eax, dword ptr [sv.scode.SAY]
		je      checkwait
		cmp     eax, dword ptr [sv.scode.TALK]
		jne     short text_return

	checkwait:
		cmp     dword ptr [sv.status.wait], 0
		je      count
		mov     dword ptr [sv.status.wait], 0
		mov     dword ptr [sv.rcd.count_ch], 0
	count:
		add     dword ptr [sv.rcd.count_ch], 1
		cmp     dword ptr [sv.rcd.count_ch], 1
		jne     short text_return
		mov     eax, dword ptr [sv.rcd.now]
		mov     dword ptr [sv.rcd.time_textbeg], eax
		jmp     short text_return

	jcode:
		cmp     byte ptr [eax], 2
		jne     short text_returnb
		cmp     dword ptr [sv.rcd.count_ch], 0
		je      short text_returnb
		mov     dword ptr [sv.status.wait], 1

	text_returnb:
		pop     eax
		ret
	}
}