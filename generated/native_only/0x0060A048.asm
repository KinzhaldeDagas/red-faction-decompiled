; crt_tan_x87_core -- native analysis retained, C pseudocode unavailable
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
; write, full FP/SSE save, finite-only input validation or SEH; live x87 loads/stores/arithmetic can trap. Finite FPTAN; status+SAHF C2/PF chooses reduction. Successful FPTAN leaves
; auxiliary1 at ST0, explicitly popped to return tangent. Reduction uses original huge divisor648FBA, FPREM1 until C2 clear, discards divisor, FPTAN then pops auxiliary1. Infinity
; ->negative quiet NaN/type1; NaN ->convertTOStoQNaN. No iteration bound or numerical-error guarantee. Operation32/name tan.
0x0060A048 push    edx
0x0060A049 fstcw   [esp+4+var_4]; UNREALRED VERIFIED: Waiting FSTCW writes lowWORD of the core-owned CW slot; incoming ZF from exponent loader remains live across PUSH/FSTCW/MOV.
0x0060A04D jz      short inf_or_nan_5
0x0060A04F cmp     [esp+4+var_4], 27Fh
0x0060A055 jz      short CW_is_set_to_default_5
0x0060A057 fldcw   ds:word_648FB8
0x0060A05D fptan
0x0060A05F fstsw   ax
0x0060A062 sahf
0x0060A063 jp      short reduce_arg_1
0x0060A065 fstp    st
0x0060A067 cmp     dword ptr unk_2021334, 0
0x0060A06E jnz     __fast_exit
0x0060A074 mov     edx, 20h ; ' '
0x0060A079 lea     ecx, off_664D50
0x0060A07F jmp     __math_exit
0x0060A084 fld     ds:tbyte_648FBA
0x0060A08A fxch    st(1)
0x0060A08C fprem1; UNREALRED VERIFIED: Reduce modulo original huge80-bit divisor ~pi*2^62, repeat until C2 clear; not ordinary2*pi.
0x0060A08E fstsw   ax
0x0060A091 sahf
0x0060A092 jp      short redux_loop_1
0x0060A094 fstp    st(1)
0x0060A096 fptan
0x0060A098 fstp    st
0x0060A09A jmp     short exit_5
0x0060A09C call    __convertTOStoQNaN
0x0060A0A1 jmp     short _Error_handling_4
0x0060A0A3 test    eax, 0FFFFFh
0x0060A0A8 jnz     short not_infinity_5
0x0060A0AA cmp     dword ptr [esp+4+original], 0
0x0060A0AF jnz     short not_infinity_5
0x0060A0B1 fstp    st
0x0060A0B3 fld     tbyte_665090
0x0060A0B9 mov     eax, 1
0x0060A0BE cmp     dword ptr unk_2021334, 0
0x0060A0C5 jnz     __fast_exit
0x0060A0CB mov     edx, 20h ; ' '
0x0060A0D0 lea     ecx, off_664D50
0x0060A0D6 call    __startOneArgErrorHandling; UNREALRED VERIFIED: No PUSHed C argument block: borrow CW at caller ESP, ignore outer return-PC gap, read original DOUBLE at caller ESP+8.
0x0060A0DB pop     edx
0x0060A0DC retn
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
