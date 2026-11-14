// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00617F10 fFASN
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Multi-entry x87 inverse-trig helper block; EBP
// runtime frame and CL/CH sign context, not uniform two-input C function. PRIMARY617F10 (asin): one extended ST0 input, CL original sign. CALL AugmentSinCos
// ->ST0=sqrt((1-|x|)*(1+|x|)),ST1=|x|, CH=0; XCHG CH,CL ->CL0/CHoriginalSign; common FPATAN computes atan2(|x|,root), apply CH sign. SECONDARY617F19 (acos): same single input/CL
// sign, CALL Augment, FXCH ->FPATAN atan2(root,|x|); CLnegative original x applies pi-angle, CH0. SECONDARY617F22 (atan): FABS x,FLD1,CH=CL,CL=0 ->FPATAN atan2(|x|,1),apply CH sign.
// SECONDARY617F2C (atan2): two operands denominator ST0,numerator ST1; set frame errorBYTE-0x90=-2, FABS both, common FPATAN. CL indicates denominator sign (pi-angle correction),CH
// numerator sign (final FCHS). Raw DEE1 FSUBRP computes pi-angle, not angle-pi. Common617F3B path needs two live FP operands, no caller stack args; normal RET returns one extended
// ST0. Primary normal return consumes one numeric input, no semantic incoming ST1; corrected primary ABI includes frame/CL. Augment domain failure discards its return-PC and returns
// one level higher, skipping this block's FPATAN/sign continuation. No independent errno/CW/MXCSR restore or input/FP-stack-capacity guard; shared runtime frame owns error handling.
long double __usercall fFASN@<st0>(long double x@<st0>, void *frame@<ebp>, unsigned __int8 originalSign@<cl>)
{
  long double result; // st7
  char v4; // ch

  result = AugmentSinCos(x, frame);
  __asm { fpatan }
  if ( v4 )
  {
    __asm
    {
      fldpi
      fsubrp  st(1), st; UNREALRED VERIFIED: FSUBRP forms pi-angle; CH applies final numerator sign below.
    }
  }
  if ( originalSign )
    __asm { fchs }
  return result;
}

