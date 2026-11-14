// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B57D crt_pow_x87_core
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal pow core: incoming ST0 EXPONENT, EAX
// exponent classifier/highDWORD, original stack binary64 BASE at entryESP+4 and EXPONENT+12; NO semantic incoming ST1. Save EAX to ECX, PUSH CW DWORD/FSTCW; load_CW only if original
// !=0x027F, preserving ECX/EAX. Load BASE through fload_withFB, which preserves EDX and gives EAX/ZF classification, so x87 stack becomes base/exponent. Finite nonzero positive base
// ->FYL2X then twoToTOS; CL odd-parity1 optionally negates result. For negative base duplicate exponent, integer classifier consumes duplicate and yields CL0 noninteger/1 odd/2 even,
// FCHS base before normal computation; CL0 pops both and returns original negative quiet NaN/type1. twoToTOS native preserves all GPRs, especially CL. Normal computed result:
// global02021334 nonzero fast exit; otherwise operation29/name pow tail-JMP check_range_exit (CW slot still on stack). Zero base drops base; exact +/-0 exponent drops exponent and
// returns1 directly. Otherwise classifier consumes exponent: positive exponent ->+0 or -0 for negative base and odd exponent; negative exponent ->+/-infinity/type2. Native exponent
// sign TEST is unaligned DWORD[CW-ESP+0x17]&0x80, reads three following padding/caller bytes but masks them out. Special exponent/base classify original fraction bits; raw bit0x08 in
// argument byte6 SET selects FADDP/type1; clear selects FADDP/type7 after NaN tally. Preserve this native branch sense rather than trusting SNaN/QNaN labels. Non-NaN infinite cases
// allocate116-byte scratch (8 result+108 x87 save), push result pointer and two binary64 args, pop both x87 operands to argument image, waiting FSAVE at scratch+8 resets x87, call
// powhlp(base,exponent,scratch), reclaim20 argument bytes, FRSTOR prior x87, load result64, reclaim116. powhlp0 returns through fast CW exit; nonzero becomes type1. Error mode0 calls
// two-argument adapter using borrowed caller frame (no new argument pushes), then pops CW/RET; nonzero mode skips notification. Shared fast/unary math exits remain original chunks;
// preserve ownership. No own errno/SEH/SSE save or public numerical accuracy guarantee. Existing pseudocode allocation warning is not proof of correct mixed x87/GPR/borrowed-stack
// modeling.
// local variable allocation has failed, the output may be wrong!
long double __usercall crt_pow_x87_core@<st0>(
        long double exponent@<st0>,
        unsigned int exponentClassification@<eax>,
        double baseImage,
        double exponentImage)
{
  int v4; // eax
  double v5; // st6
  char v6; // zf
  char is_int; // cl
  long double result; // st7
  int v9; // ecx
  int v10; // ecx
  int v11; // eax
  unsigned __int8 v13; // cl
  unsigned __int8 v14; // ch
  double *v15; // [esp+10h] [ebp-7Ch]
  long double *v16; // [esp+10h] [ebp-7Ch]
  double v17[14]; // [esp+14h] [ebp-78h] BYREF
  unsigned int v18; // [esp+88h] [ebp-4h]

  v18 = exponentClassification;
  if ( (_WORD)exponentClassification != 639 )
    _load_CW(v18);
  if ( (exponentClassification & 0x7FF00000) == 0x7FF00000 )
  {
    if ( LODWORD(exponentImage) | exponentClassification & 0xFFFFF )
    {
      v5 = _fload_withFB(&baseImage);
      if ( (BYTE6(exponentImage) & 8) != 0 )
        goto SNaN_detected;
      v10 = v9 + 1;
    }
    else
    {
      v5 = _fload_withFB(&baseImage);
    }
test_base:
    if ( (HIDWORD(baseImage) & 0x7FF00000) != 0x7FF00000 || !(LODWORD(baseImage) | HIDWORD(baseImage) & 0xFFFFF) )
    {
      if ( !v10 )
      {
        v15 = v17;
        __asm { fsave   byte ptr [ecx+8]; UNREALRED VERIFIED: Waiting FSAVE resets x87 after copying base/exponent to args; scratch+8 is108-byte environment/state image. }
        v11 = _powhlp(v5, exponent, v17);
        _ECX = v16;
        __asm { frstor  byte ptr [ecx+8]; UNREALRED VERIFIED: FRSTOR original saved x87 before FLD result; helper result/error EAX remains live. }
        result = *v16;
        if ( !v11 )
          return result;
        goto _ErrorHandling_0;
      }
      goto one_of_args_is_QNaN;
    }
    if ( (BYTE6(baseImage) & 8) == 0 )
    {
one_of_args_is_QNaN:
      result = exponent + v5;
      goto _ErrorHandling_0;
    }
SNaN_detected:
    result = exponent + v5;
    goto _ErrorHandling_0;
  }
  v5 = _fload_withFB(&baseImage);
  if ( v6 )
  {
    v10 = 0;
    goto test_base;
  }
  if ( (v4 & 0x7FF00000) != 0 || LODWORD(baseImage) | HIDWORD(baseImage) & 0xFFFFF )
  {
    is_int = HIBYTE(baseImage) & 0x80;
    if ( baseImage >= 0.0 || (is_int = test_whether_TOS_is_int(exponent), v5 = -v5, is_int) )
    {
      result = _twoToTOS(__FYL2X__(v5, exponent));
      if ( is_int == 1 )
        result = -result;
      if ( !unk_2021334 )
        _check_range_exit(&off_664D88, 29);
      return result;
    }
    result = *(double *)&tbyte_665090;
_ErrorHandling_0:
    if ( !unk_2021334 )
      _startTwoArgErrorHandling();
    return result;
  }
  if ( !(LODWORD(exponentImage) | HIDWORD(exponentImage) & 0x7FFFFFFF) )
    return 1.0;
  v13 = test_whether_TOS_is_int(exponent);
  v14 = HIBYTE(baseImage) >> 7;
  if ( (HIBYTE(exponentImage) & 0x80) != 0 )
  {
    result = *(double *)&tbyte_665C80;
    if ( (v13 & v14) != 0 )
      result = -*(double *)&tbyte_665C80;
    goto _ErrorHandling_0;
  }
  result = 0.0;
  if ( (v13 & v14) != 0 )
    return -0.0;
  return result;
}

