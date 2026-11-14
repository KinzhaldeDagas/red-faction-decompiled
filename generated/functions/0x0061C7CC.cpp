// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061C7CC crt_x87_fprem_step_with_denormal_divisor_scaling
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime x87 FPREM entry adapter, KEEP library flag. Inputs originalST0 dividendN,ST1 divisorD; saveEDX and reserve48-byte blockB. FSTP80 N toB+24
// thenD toB+0, removing originals; EDX=0. Raw divisor exponent WORD[B+8]&7FFF nonzero calls61C5C6 immediately, whose stable-block entry takes one hardwareFPREM step. Divisor
// exponent0 reloads D thenN; raw significance DWORD[D]|DWORD[D+4]==0 takes direct ONE FPREM at61C877, returnsEAX0, leaves[N step D,D,...], restoresEDX. No software zero/NaN result or
// complete-reduction loop.  Nonzero significand/exponent0: preserve originalD80 atB+12, reload to restore[N,D,...], setEDXbit1 (value2). Save originalCW atB+36, load oldCW|0x033F
// (all exception masks/extended precision, KEEP original rounding-control bits). If raw numerator exponent<=0x7FBE, setEDXbit0 (value3), multiply BOTH N andD by DOUBLE665F24=2^64 and
// FSTP80 back toB+24/B+0; restore originalCW andcall61C5C6. Its flag3 suffix unscales result by2^-64, restores original divisor, and patches C0/C1/C3 from saved remainder status. No
// clamp/iteration untilC2clear.  Numerator exponent>0x7FBE instead RE-SAVES currentCW to SAME B+36 AFTER oldCW|033F was loaded, overwriting original savedCW. Load this
// workingCW|0300, discard numerator register without scaling its memory, scale ONLY divisor by2^64 toB+0, then FLDCW from OVERWRITTEN B+36 and callcore withEDX2. Thus high-exponent
// branch leaves original exception-mask/precision bits OR033F set; do NOT promise universal caller-control-word restoration. Core replaces scaled divisor register with originalB+12
// and restores quotient bits, without unscale. Restore incomingEDX and blockESP on normal exit; EAX is path-dependent raw inspected fields/core-preserved residue, not bool or
// remainder. No game state, stack-argument interface, input validation, asynchronous memory protection or exception catch/rollback.
int __usercall __spoils<ecx,st0> crt_x87_fprem_step_with_denormal_divisor_scaling@<eax>(
        double a1@<st1>,
        double a2@<st0>)
{
  int result; // eax
  char v3; // dl
  _BYTE v4[20]; // [esp+0h] [ebp-34h]
  int v5; // [esp+14h] [ebp-20h]
  __int128 v6; // [esp+18h] [ebp-1Ch]

  *(double *)&v6 = a1;
  *(double *)v4 = a2;
  if ( (*(_DWORD *)&v4[6] & 0x7FFF0000) != 0 )
    return crt_x87_fprem_block_step_restore_quotient_flags(0, *(__int128 *)v4, *(int *)&v4[16], v5, v6);
  result = *(_DWORD *)&v4[4] | *(_DWORD *)v4;
  if ( a2 != 0.0 )
  {
    *(double *)&v4[12] = a2;
    v3 = 2;
    if ( (WORD4(v6) & 0x7FFFu) <= 0x7FBE )
    {
      v3 = 3;
      *(double *)&v6 = a1 * dbl_665F24;
    }
    *(double *)v4 = a2 * dbl_665F24;
    return crt_x87_fprem_block_step_restore_quotient_flags(
             v3,
             *(__int128 *)v4,
             HIDWORD(*(unsigned __int64 *)&a2),
             v5,
             v6);
  }
  return result;
}

