; crt_cos_x87_core -- native analysis retained, C pseudocode unavailable
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
; write, full FP/SSE save, finite-only input validation or SEH; live x87 loads/stores/arithmetic can trap. Finite FCOS; waiting status+SAHF tests C2 via PF. If range reduction
; required, load original extended constant648FBA (significand C90FDAA22168C235, exponent403E, approximately pi*2^62, NOT ordinary2*pi), FXCH, loop FPREM1 until C2 clear, discard
; divisor via FSTP ST1, then FCOS. No bounded iteration or large-argument numerical accuracy guarantee. Infinity ->negative quiet NaN/type1. NaN ->convertTOStoQNaN. Operation18/name
; cos.
0x00606268 push    edx
0x00606269 fstcw   [esp+4+var_4]; UNREALRED VERIFIED: Waiting FSTCW writes lowWORD of the core-owned CW slot; incoming ZF from exponent loader remains live across PUSH/FSTCW/MOV.
0x0060626D jz      short inf_or_nan_0
0x0060626F cmp     [esp+4+var_4], 27Fh
0x00606275 jz      short CW_is_set_to_default_0
0x00606277 fldcw   ds:word_648FB8
0x0060627D fcos
0x0060627F fstsw   ax
0x00606282 sahf
0x00606283 jp      short reduce_arg
0x00606285 cmp     dword ptr unk_2021334, 0
0x0060628C jnz     __fast_exit
0x00606292 mov     edx, 12h
0x00606297 lea     ecx, off_664C20
0x0060629D jmp     __math_exit
0x006062A2 fld     ds:tbyte_648FBA
0x006062A8 fxch    st(1)
0x006062AA fprem1; UNREALRED VERIFIED: Reduce modulo original huge80-bit divisor ~pi*2^62, repeat until C2 clear; not ordinary2*pi.
0x006062AC fstsw   ax
0x006062AF sahf
0x006062B0 jp      short redux_loop
0x006062B2 fstp    st(1)
0x006062B4 fcos
0x006062B6 jmp     short exit_0
0x006062B8 call    __convertTOStoQNaN
0x006062BD jmp     short _Error_handling_0
0x006062BF test    eax, 0FFFFFh
0x006062C4 jnz     short not_infinity_0
0x006062C6 cmp     dword ptr [esp+4+original], 0
0x006062CB jnz     short not_infinity_0
0x006062CD fstp    st
0x006062CF fld     tbyte_665090
0x006062D5 mov     eax, 1
0x006062DA cmp     dword ptr unk_2021334, 0
0x006062E1 jnz     __fast_exit
0x006062E7 mov     edx, 12h
0x006062EC lea     ecx, off_664C20
0x006062F2 call    __startOneArgErrorHandling; UNREALRED VERIFIED: No PUSHed C argument block: borrow CW at caller ESP, ignore outer return-PC gap, read original DOUBLE at caller ESP+8.
0x006062F7 pop     edx
0x006062F8 retn
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
