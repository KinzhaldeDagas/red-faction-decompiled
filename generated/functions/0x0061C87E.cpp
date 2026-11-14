// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061C87E crt_x87_fprem1_block_step_restore_quotient_flags
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime nearest-quotient remainder support, KEEP library flag. SAME privateB=entryESP+4 map as61C5C6:
// D80+0,originalD80+12,N80+24,CWword36,workDWORD40,statusword44; EDX bits0/1 flags. FULL EAX,EBX,ECX preserved byPUSH/POP, EDX unchanged; inferred unsignedEAX result is false.
// Stable-block gates have SAME impossible overlap: first requires DWORD[B+4]&07000000==07000000, later doubled-same-DWORD JNZ-default allows only0/80000000. No calls/writes between
// gates, so software-reduction block is unreachable from ordinary stable entry.  Normal path FLD80 D,FLD80 N then exactly ONE FPREM1 at61CA20: output[remainderStep,D,...], can be
// partial withC2 set, not a promised full IEEE remainder routine. Flags0 returns directly. Flags&3 nonzero saves status atB+44; flagbit0 temporarily sets CWold|0300, scales top
// result by DOUBLE2^-64, restoresCW. Both flag1/2 paths then replace retained divisor with original80-bitB+12 and patch saved C0/C1/C3 bits0x4300 into FNSTENV/FLDENV status image; C2
// is NOT restored by that mask. No custom NaN/zero clamp, game state or conventional stack-argument return status.  Literal DEAD-code differences from61C5C6 matter:61C966 tests
// EBXbit1, NOT EDXbit1, before possibly copying original divisor. Its internal intermediate reduction at61C95C still uses FPREM, while seed-status operation61CA00 and ordinary61CA20
// use FPREM1. Remaining dead exponent-gap/compare/subtract/half-scale paths are not substituted for reachable behavior. Native whole environment/masks/status semantics preserved;
// caller seeds originalD slot whenever flags require replacement.
unsigned int __usercall crt_x87_fprem1_block_step_restore_quotient_flags@<eax>(
        char a1@<dl>,
        __int128 a2,
        int a3,
        int a4,
        __int128 a5)
{
  unsigned int result; // eax
  int v6; // ecx
  double v7; // st7
  __int16 v8; // fps
  double v9; // st6
  bool v10; // c0
  char v11; // c2
  bool v12; // c3
  __int16 v13; // fps

  result = *(_DWORD *)((char *)&a2 + 6) ^ 0x700;
  if ( ((*(_DWORD *)((char *)&a2 + 6) ^ 0x700) & 0x700) == 0 )
  {
    result = (result >> 11) & 0xF;
    if ( byte_665F0C[result] )
    {
      result = *(_DWORD *)((_BYTE *)&a2 + 6) & 0x7FFF0000;
      if ( (*(_DWORD *)((_BYTE *)&a2 + 6) & 0x7FFF0000) != 0x7FFF0000 )
      {
        result = *(_DWORD *)((_BYTE *)&a5 + 6) & 0x7FFF0000;
        if ( (*(_DWORD *)((_BYTE *)&a5 + 6) & 0x7FFF0000) != 0 && result != 2147418112 )
        {
          result = 2 * DWORD1(a5);
          if ( !(2 * DWORD1(a5)) )
          {
            result = 2 * DWORD1(a2);
            if ( !(2 * DWORD1(a2)) )
            {
              if ( (WORD4(a5) & 0x7FFFu) > (WORD4(a2) & 0x7FFFu) + 63 )
              {
                v6 = ((BYTE8(a5) - BYTE8(a2)) & 0x3F | 0x20) + 1;
                v7 = fabs(*(long double *)&a2);
                v9 = fabs(*(long double *)&a5);
                do
                {
                  v10 = v9 < v7;
                  v11 = 0;
                  v12 = v9 == v7;
                  result = v8 & 0x100;
                  if ( (v8 & 0x100) == 0 )
                    v9 = v9 - v7;
                  v7 = v7 * dbl_665F3C;
                  --v6;
                }
                while ( v6 );
              }
              else
              {
                while ( 1 )
                {
                  result = (WORD4(a2) & 0x7FFF) + 10;
                  if ( (int)((WORD4(a5) & 0x7FFF) - result) < 0 )
                    break;
                  *(double *)&a5 = __FPREM__(*(long double *)&a5, *(long double *)&a2);
                }
              }
            }
          }
        }
      }
    }
  }
  if ( (a1 & 3) != 0 )
  {
    __asm { fnstenv [esp+28h+var_28] }
    __asm { fldenv  [esp+28h+var_28] }
    return v13 & 0x4300;
  }
  return result;
}

