// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DF35 __fload_withFB
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Native x87 loader with EDX pointer to binary64; no
// ECX input/ordinary stack slots. Mask highDWORD exponent0x7FF00000 and CMP. Finite exponent: FLD qword[EDX], RET; EAX is masked exponent and EFLAGS from CMP (ZF0). All-ones
// exponent: reserve10 bytes, construct extended image: low64=(original64<<11) with truncation, topWORD=originalTopWORD|0x7FFF. Overlapping DWORD stores ensure complete10-byte image;
// explicit integer bit copied from original exponent into bit63, fraction bits shifted11. FLD tbyte image, reclaim10 bytes, TEST EAX,0 establishes ZF1/CF0, then MOV EAX original
// highDWORD without altering flags. Thus ST0 carries native extended value, EAX/flags are additional protocol outputs; callers use JZ immediately after CALL to detect
// exponent-all-ones. EDX preserved, EAX/ECX clobbered; finite path leaves ECX untouched. No numeric conversion of NaN payload via ordinary FLD64 on special path, but extended FLD
// itself can quiet/trap signaling NaNs. No CW/status save, NULL check or own SEH. Old decompiler QWORD-leftshift return omits ten-byte exponent/sign and flag protocol.
long double __usercall __spoils<eax,ecx> _fload_withFB@<st0>(const double *a1@<edx>)
{
  long double result; // st7

  if ( (*((_DWORD *)a1 + 1) & 0x7FF00000) != 0x7FF00000 )
    return *a1;
  *(_QWORD *)&result = *(_QWORD *)a1 << 11;
  return result;
}

