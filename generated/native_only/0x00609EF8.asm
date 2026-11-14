; crt_log_x87_core -- native analysis retained, C pseudocode unavailable
; UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal x87 unary core, not an ordinary stack-only
; C entry: live extended ST0 plus incoming ZF from exponent classifier, original binary64 image at entryESP+4/+8; EAX classifier/highWORD data also required except sqrt which reloads
; original highDWORD before branch. PUSH one DWORD, waiting FSTCW writes its lowWORD while preserving incoming integer flags. ZF1 selects exponent-all-ones route before any own CW
; comparison. Finite-path working CW: cos/sin/atan/log/tan explicitly load0x027F if savedCW differs; sqrt/acos/asin call load_CW, which preserves original lowWORD and writes
; (savedCW&0x300)|0x7F to upperWORD, retaining precision but forcing nearest/all masks. Original CW restored on returning paths unless already0x027F. Live global0x02021334 nonzero
; bypasses math/error notification, using shared fast exit0x60DF8E. Normal mode uses operation/name and shared math exit0x60DF9B: savedCW==0x027F skips notification; otherwise raw
; savedCW bit0x20 must be SET and current status bit0x20 SET to call unary error adapter with type8. Note this mask polarity is opposite the range-exit tail, whose inexact route
; requires bit0x20 CLEAR. Shared exits pop the core-owned CW DWORD and RET. Error route CALLs adapter with EAX type,EDX operation,ECX name,ST0 result WITHOUT pushing a normal C
; argument block: adapter borrows savedCW at callerESP, caller return-PC in ignored gap, and original argument beyond it. Sparse stack ABI documents the hole; Hex-Rays still reports
; call-analysis failure at this genuine frame-borrowing call. Native CFG/stack paths and constants verified independently; do not substitute incomplete pseudocode. No own errno
; write, full FP/SSE save, finite-only input validation or SEH; live x87 loads/stores/arithmetic can trap. Finite branch reloads original highDWORD. Positive normal or positive
; subnormal: FLDLN2,FXCH,FYL2X ->ln(input). Negative nonzero ->negative quiet NaN/type1. Both signed exact zeros ->original -infinity665C8A/type2. +infinity preserved; -infinity
; domain/type1. NaN uses convertTOStoQNaN. Integer tests include both fraction DWORD parts; no denormal flush in own path. Operation26/name log.
0x00609EF8 push    edx
0x00609EF9 fstcw   [esp+4+var_4]; UNREALRED VERIFIED: Waiting FSTCW writes lowWORD of the core-owned CW slot; incoming ZF from exponent loader remains live across PUSH/FSTCW/MOV.
0x00609EFD jz      short inf_or_nan_4
0x00609EFF mov     eax, dword ptr [esp+4+original+4]
0x00609F03 cmp     [esp+4+var_4], 27Fh
0x00609F09 jz      short CW_is_set_to_default_4
0x00609F0B fldcw   ds:word_648FB8
0x00609F11 test    eax, 7FF00000h
0x00609F16 jz      short test_if_x_zero_0
0x00609F18 test    eax, 80000000h
0x00609F1D jnz     short negative_x_0
0x00609F1F fldln2
0x00609F21 fxch    st(1)
0x00609F23 fyl2x
0x00609F25 cmp     dword ptr unk_2021334, 0
0x00609F2C jnz     __fast_exit
0x00609F32 lea     ecx, off_664D40
0x00609F38 mov     edx, 1Ah
0x00609F3D jmp     __math_exit
0x00609F42 test    eax, 80000000h
0x00609F47 jnz     short negative_x_0
0x00609F49 jmp     short normal
0x00609F4B test    eax, 0FFFFFh
0x00609F50 jnz     short not_infinity_4
0x00609F52 cmp     dword ptr [esp+4+original], 0
0x00609F57 jnz     short not_infinity_4
0x00609F59 and     eax, 80000000h
0x00609F5E jz      short exit_4
0x00609F60 fstp    st
0x00609F62 fld     tbyte_665090
0x00609F68 mov     eax, 1
0x00609F6D jmp     short _ErrorHandling
0x00609F6F call    __convertTOStoQNaN
0x00609F74 jmp     short _ErrorHandling
0x00609F76 test    eax, 0FFFFFh
0x00609F7B jnz     short x_is_denormal_0
0x00609F7D cmp     dword ptr [esp+4+original], 0
0x00609F82 jnz     short x_is_denormal_0
0x00609F84 fstp    st
0x00609F86 fld     tbyte_665C8A
0x00609F8C mov     eax, 2
0x00609F91 cmp     dword ptr unk_2021334, 0
0x00609F98 jnz     __fast_exit
0x00609F9E lea     ecx, off_664D40
0x00609FA4 mov     edx, 1Ah
0x00609FA9 call    __startOneArgErrorHandling; UNREALRED VERIFIED: No PUSHed C argument block: borrow CW at caller ESP, ignore outer return-PC gap, read original DOUBLE at caller ESP+8.
0x00609FAE pop     edx
0x00609FAF retn
0x0060DF8E cmp     [esp+4+var_4], 27Fh; UNREALRED VERIFIED: Shared fast exit: restore originalCW unless0x027F, pop outer core CW DWORD, RET.
0x0060DF94 jz      short fast_exit_CW_is_restored
0x0060DF96 fldcw   [esp+4+var_4]
0x0060DF99 pop     edx
0x0060DF9A retn
0x0060DF9B mov     ax, [esp+4+var_4]
0x0060DF9F cmp     ax, 27Fh
0x0060DFA3 jz      short CW_is_restored_0
0x0060DFA5 and     ax, 20h
0x0060DFA9 jz      short restore_CW; UNREALRED VERIFIED: Native unary math exit: CW inexact mask bit CLEAR skips handler; SET proceeds to status check. Preserve observed polarity.
0x0060DFAB fstsw   ax
0x0060DFAE and     ax, 20h
0x0060DFB2 jz      short restore_CW
0x0060DFB4 mov     eax, 8
0x0060DFB9 call    __startOneArgErrorHandling; UNREALRED VERIFIED: Borrowed-frame unary error call for type8; no freshly pushed stack args.
0x0060DFBE pop     edx
0x0060DFBF retn
0x0060DFC0 fldcw   [esp+4+var_4]
0x0060DFC3 pop     edx
0x0060DFC4 retn
