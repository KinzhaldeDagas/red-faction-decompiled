// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617F4C AugmentSinCos
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal inverse-trig augmentation: EBP runtime
// frame and one extended ST0 x, no stack arguments. FABS x then duplicates/FLD1/FSUBRP/FXCH/FLD1/FADDP/FMULP form radicand r=(1-|x|)*(1+|x|), leaving |x| beneath r. FTST r; waiting
// FSTSW to frameWORD-0xA0/FWAIT, test C0 through highBYTE. Ordered nonnegative ->XOR CH,CH then FSQRT, RET: ST0=sqrt(r),ST1=|x|, net numeric depth+1; CL preserved, CH0, other GPRs
// preserved on OWN returning path. Explicit spoils<ch> retains CL sign needed by fFASN. Negative OR unordered C0 ->POP EAX discards own return-PC and JMP shared60DE66: pop BOTH r and
// |x|, load original negative quiet NaN665090; if existing signed frame errorBYTE>0 preserve it and enter60DE80 OR CL/RET, otherwise60DE79 sets error1 then OR CL/RET. Thus failure
// returns one caller level higher, bypassing asin/acos continuation; not an ordinary void result or independent C exception. Original CW/precision/status govern intermediate
// multiply/sqrt and traps; no own restoration, errno, size validation or SEH.
// positive sp value has been detected, the output may be wrong!
long double __usercall __spoils<ch> AugmentSinCos@<st0>(long double x@<st0>, void *frame@<ebp>)
{
  long double result; // st7
  __int16 v3; // fps
  long double v4; // st6
  bool v5; // c0
  char v6; // c2
  bool v7; // c3

  result = fabs(x);
  v4 = (1.0 - result) * (result + 1.0);
  v5 = v4 < 0.0;
  v6 = 0;
  v7 = v4 == 0.0;
  *((_WORD *)frame - 80) = v3;
  if ( (*((char *)frame - 159) & 1) != 0 )
  {
    result = *(double *)&tbyte_665090;
    if ( *((char *)frame - 144) > 0 )
      JUMPOUT(0x60DE80);
    _rttosnpopde((int)frame);
  }
  return result;
}

