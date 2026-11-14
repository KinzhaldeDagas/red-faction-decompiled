; __check_range_exit -- native analysis retained, C pseudocode unavailable
; UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Shared TAIL-ENTERED result/range block, not an
; independently callable ordinary fastcall function. Native entry stack contains CW DWORD at ESP, caller return-PC at ESP+4, original argument image ESP+8; ECX name,EDX
; operation,live extended ST0 result. Entered by JMP with outer core's CW slot still allocated. FST binary64 temporary WITHOUT pop; inspect exponent field only
; (normal/subnormal-or-zero/all-ones), release8 temporary bytes. Normal field: originalCW0x027F ->pop CW/RET; otherwise savedCW inexact bit0x20 SET ->restore CW/pop/RET. Only if bit
; CLEAR and waiting current status bit0x20 SET use type8 error. This polarity differs from shared unary math exit0x60DF9B. Exponent0 ->load original double+1536,FXCH,FSCALE,FSTP ST1;
; compare abs(scaledResult) against minNormal2^-1022. If native JNB succeeds retain scaled result; otherwise multiply original+0.0. Type4 underflow. Exponent0x7FF (including NaN; no
; separate test) ->scale by2^-1536, compare abs against maxFinite; JBE retains scaled value, otherwise multiply original+infinity. Type3 overflow. SAHF strict/unordered flags govern
; comparisons: unordered follows carry-set branch (underflow multiplies0, overflow skips infinity multiply). Error path operation29 uses two-arg adapter; all others unary adapter;
; both borrow savedCW/return-PC gap/original argument image rather than receiving freshly pushed C args. Then pop CW/RET. Normal restore path FLDCW original savedWORD except
; already0x027F. No own global bypass, errno, SSE handling or SEH. Native CFG proves all tail paths reclaim exactly outer CW DWORD; historical stored fastcall type does not model
; shifted return address. Hex-Rays call-analysis failure retained explicitly, no fabricated C prototype or code patch.
0x0060DFD9 sub     esp, 8; UNREALRED VERIFIED: Tail-entry ESP points to outer CW slot, NOT own return-PC; true return-PC at ESP+4.
0x0060DFDC fst     [esp+8+var_8]
0x0060DFDF mov     eax, dword ptr [esp+8+var_8+4]
0x0060DFE3 add     esp, 8
0x0060DFE6 and     eax, 7FF00000h
0x0060DFEB jz      short haveunderflow
0x0060DFED cmp     eax, 7FF00000h
0x0060DFF2 jz      short haveoverflow
0x0060DFF4 mov     ax, [esp+0]
0x0060DFF8 cmp     ax, 27Fh
0x0060DFFC jz      short loc_60E028
0x0060DFFE and     ax, 20h
0x0060E002 jnz     short loc_60E025; UNREALRED VERIFIED: Range-exit inexact mask polarity: SET restores CW, CLEAR permits current-status check (opposite unary exit).
0x0060E004 fstsw   ax
0x0060E007 and     ax, 20h
0x0060E00B jz      short loc_60E025
0x0060E00D mov     eax, 8
0x0060E012 cmp     edx, 1Dh
0x0060E015 jz      short have_error_in_pow
0x0060E017 call    __startOneArgErrorHandling; UNREALRED VERIFIED: Borrowed unary-frame helper call; recorded Hex-Rays call-analysis limitation.
0x0060E01C pop     edx
0x0060E01D retn
0x0060E01E call    __startTwoArgErrorHandling
0x0060E023 pop     edx
0x0060E024 retn
0x0060E025 fldcw   word ptr [esp+0]
0x0060E028 pop     edx
0x0060E029 retn
0x0060E02A fld     ds:dbl_648FDC; UNREALRED VERIFIED: Underflow bucket includes binary64 zero/subnormal; scale originalST0 by2^1536.
0x0060E030 fxch    st(1)
0x0060E032 fscale
0x0060E034 fstp    st(1)
0x0060E036 fld     st
0x0060E038 fabs
0x0060E03A fcomp   ds:dbl_648FCC
0x0060E040 fstsw   ax
0x0060E043 sahf
0x0060E044 mov     eax, 4
0x0060E049 jnb     short have_error; UNREALRED VERIFIED: JNB includes ordered equal/greater; unordered takes multiply+0 path.
0x0060E04B fmul    ds:dbl_648FEC
0x0060E051 jmp     short have_error
0x0060E053 fld     ds:dbl_648FD4; UNREALRED VERIFIED: All-ones binary64 exponent bucket includes NaN; scale originalST0 by2^-1536.
0x0060E059 fxch    st(1)
0x0060E05B fscale
0x0060E05D fstp    st(1)
0x0060E05F fld     st
0x0060E061 fabs
0x0060E063 fcomp   ds:dbl_648FC4
0x0060E069 fstsw   ax
0x0060E06C sahf
0x0060E06D mov     eax, 3
0x0060E072 jbe     short have_error; UNREALRED VERIFIED: JBE includes unordered carry-set case; skips multiply+infinity then sends type3.
0x0060E074 fmul    ds:dbl_648FE4
0x0060E07A jmp     short have_error
