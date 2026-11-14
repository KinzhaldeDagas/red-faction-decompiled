// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061CA84 crt_x87_fprem1_step_with_denormal_divisor_scaling
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Genuine runtime x87 remainder adapter, KEEP library flag. OriginalST0=N dividend,ST1=D divisor. SaveEDX/reserve48bytes, FSTP80 N toB24,D toB0, EDX0. Nonzero
// raw divisor exponent calls61C87E, whose stable-block normal operation is one hardwareFPREM1 step. Exponent0 reloadsD,N and checks rawD significand. ZERO significand explicitly
// executes FPREM(D9F8) at61CB32, NOT FPREM1, returnsEAX0 and preserves incomingEDX; retain this opcode distinction even where masked invalid zero-divisor outcomes coincide.  Nonzero
// exponent0 divisor follows same scaling transaction as61C7CC: save originalD80 toB12,setEDX2; saveCW B36,load oldCW|033F preservingrounding. Raw numerator exponent<=7FBE setsEDX3
// and scales BOTH80-bit inputs by DOUBLE2^64, restores ORIGINALCW then calls61C87E; flag3 suffix unscales result by2^-64, restores original divisor and onlyC0/C1/C3. Exponent>7FBE
// RE-SAVES alreadymodifiedCW over original at61CB04, loadsworking|0300, discards numerator register, scales divisorONLY, restores that overwritten workingCW and callscoreEDX2. This
// branch retains callerCW bits OR033F; do not assert fullCW restoration. Core61C966 EBX-vs-EDX distinction remains in its provably dead software branch.  Normal result is x87 partial
// remainder step plus original divisor (two originalinputs->two outputs), deeper stack retained. Restore incomingEDX/ESP. EAX is inspected/raw scratch residue except explicit
// zero-significand path0, no meaningful integer result; no stack input arguments, RF state, general NaN/finite policy, complete-C2 reduction loop or rollback.
int __usercall __spoils<ecx,st0> crt_x87_fprem1_step_with_denormal_divisor_scaling@<eax>(
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
    return crt_x87_fprem1_block_step_restore_quotient_flags(0, *(__int128 *)v4, *(int *)&v4[16], v5, v6);
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
    return crt_x87_fprem1_block_step_restore_quotient_flags(
             v3,
             *(__int128 *)v4,
             HIDWORD(*(unsigned __int64 *)&a2),
             v5,
             v6);
  }
  return result;
}

