; crt_acos_x87_core -- native analysis retained, C pseudocode unavailable
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
; write, full FP/SSE save, finite-only input validation or SEH; live x87 loads/stores/arithmetic can trap. Finite unsigned EAX exponent comparison against0x3FF00000 admits |x|<1.
; Compute sqrt((1+x)*(1-x)) with explicit x87 stack operations, FXCH then FPATAN ->atan2(root,x). At equal exponent inspect all fraction bits to admit ONLY exact +/-1: +1 pops
; operand/FLDZ(+0), -1 pops operand/FLDPI. Larger magnitude, infinity, or nonzero fraction at exponent1 ->negative quiet NaN/type1. NaNs use convertTOStoQNaN. Operation13/name acos.
0x006064C8 push    edx
0x006064C9 fstcw   [esp+4+var_4]; UNREALRED VERIFIED: Waiting FSTCW writes lowWORD of the core-owned CW slot; incoming ZF from exponent loader remains live across PUSH/FSTCW/MOV.
0x006064CD jz      short inf_or_nan_2
0x006064CF cmp     [esp+4+var_4], 27Fh
0x006064D5 jz      short CW_is_set_to_default_2
0x006064D7 call    __load_CW
0x006064DC cmp     eax, 3FF00000h
0x006064E1 jnb     short x_huge
0x006064E3 fld1
0x006064E5 fadd    st, st(1)
0x006064E7 fld1
0x006064E9 fsub    st, st(2)
0x006064EB fmulp   st(1), st
0x006064ED fsqrt
0x006064EF fxch    st(1)
0x006064F1 fpatan
0x006064F3 cmp     dword ptr unk_2021334, 0
0x006064FA jnz     __fast_exit
0x00606500 mov     edx, 0Dh
0x00606505 lea     ecx, aAcos
0x0060650B jmp     __math_exit
0x00606510 ja      short not_in_range
0x00606512 mov     eax, dword ptr [esp+4+original+4]
0x00606516 mov     ecx, eax
0x00606518 and     eax, 0FFFFFh
0x0060651D or      eax, dword ptr [esp+4+original]
0x00606521 jnz     short not_in_range
0x00606523 and     ecx, 80000000h
0x00606529 fstp    st
0x0060652B jz      short ret_zero
0x0060652D fldpi
0x0060652F jmp     short exit_2
0x00606531 fldz
0x00606533 jmp     short exit_2
0x00606535 call    __convertTOStoQNaN
0x0060653A jmp     short _Error_handling_2
0x0060653C test    eax, 0FFFFFh
0x00606541 jnz     short not_infinity_2
0x00606543 cmp     dword ptr [esp+4+original], 0
0x00606548 jnz     short not_infinity_2
0x0060654A fstp    st
0x0060654C fld     tbyte_665090
0x00606552 mov     eax, 1
0x00606557 cmp     dword ptr unk_2021334, 0
0x0060655E jnz     __fast_exit
0x00606564 mov     edx, 0Dh
0x00606569 lea     ecx, aAcos
0x0060656F call    __startOneArgErrorHandling; UNREALRED VERIFIED: No PUSHed C argument block: borrow CW at caller ESP, ignore outer return-PC gap, read original DOUBLE at caller ESP+8.
0x00606574 pop     edx
0x00606575 retn
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
