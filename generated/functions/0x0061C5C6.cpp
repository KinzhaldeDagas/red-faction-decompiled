// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061C5C6 crt_x87_fprem_block_step_restore_quotient_flags
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime x87 remainder support, KEEP library flag. Private ABI: B=entryESP+4 points to caller block containing divisorD80 at+0, original divisor
// save80 at+12, dividendN80 at+24, CW word+36, workCW DWORD+40,status word+44. EDX bits0/1 are flags; no conventional __int128 argument semantics. PUSH/POP preserves FULL incoming
// EAX,EBX,ECX, and EDX is not modified. Useful results are x87 stack/status/block mutation, NOT pseudocode unsignedEAX result.  For STABLE caller block the software reduction region
// is UNREACHABLE from entry: first overlapping DWORD[B+6] XOR0x700/TEST0x700 requires(DWORD[B+4]&0x07000000)==0x07000000; later DWORD[B+4] doubled/JNZ-default admits continuation
// only for0 or0x80000000, both contradict that mask. There are no intervening calls or block writes. Additional gates (classification table665F0C, exponent/sig tests) do not remove
// contradiction. This is a literal proof about stable private input, not arbitrary asynchronous memory mutation. Ordinary entry therefore loads80-bit D thenN and executes EXACTLY ONE
// hardware FPREM at61C768, leaving[remainderStep,D,...]. It does not loop untilC2 clears, promise a complete fmod result, clamp/validate inputs or software-normalize NaNs; hardware
// exceptions/partial-reduction status remain.  Then EDX&3==0 returns with those two pushed x87 entries, no environment rewrite. For nonzero flags save status word toB+44. If EDXbit0
// set, saveCW toB+36, load(oldCW|0x0300) extended precision with original rounding/masks, multiply top remainder by DOUBLE665F2C=2^-64, restore savedCW. In either nonzero-flag case
// FXCH/discard current divisor entry, FLD80 ORIGINAL saved divisorB+12, FXCH back to[remainder,originalD,...]. Extract saved status bits0x4300 (C0,C1,C3 ONLY; C2 is NOT included).
// FNSTENV into temporary28-byte stack area, AND statusDWORD atenv+4 with0x0000BCFF thenOR those bits, FLDENV and discard area. Preserve other stored low-status fields/native
// environment behavior, no blanket exception/status rollback. Caller must have seeded+12 when flags require it.  Dead region is still retained as native evidence:
// table-pattern/exponent tests, exponent-gap small reduction using FPREM, large-gap compare/subtract/half-scale loop, original ten-byte665F44 seed, temporary CW and sign restoration.
// At61C6AE its original-divisor-copy decision tests EDXbit1. No claim that this dead algorithm is a normal caller path; early contradiction is the reason, not a familiar CRT label.
unsigned int __usercall crt_x87_fprem_block_step_restore_quotient_flags@<eax>(
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
    __asm { fnstenv [esp+28h+var_28]; UNREALRED VERIFIED: FNSTENV28B;statusDWORD&0000BCFF |saved4300;FLDENV, notblanketstatus/exceptionrollback. }
    __asm { fldenv  [esp+28h+var_28] }
    return v13 & 0x4300;
  }
  return result;
}

