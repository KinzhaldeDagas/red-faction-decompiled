// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B742 _test_whether_TOS_is_int
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal x87 classifier consumes original ST0, returns classification in CL:0 noninteger,1 odd integer,2 even integer. FLD/FRNDINT/FCOMP against original
// under CURRENT CW; JNZ tests ZF only. Integer-admitted path multiplies original by verified DOUBLE0.5, setsCL1, compares rounded half with half via FCOMPP and incrementsCL to2 on
// equality. Noninteger path FSTP pops original; integer path FCOMPP pops both temporary/original-half values, net consumes one input in all paths. NaN unordered givesZF1 and
// proceeds/even2; infinity also follows equality route. AX/flags reflect x87 status, no PF guard and no stack args.
unsigned __int8 __usercall test_whether_TOS_is_int@<cl>(long double value@<st0>)
{
  unsigned __int8 result; // cl
  long double v4; // st7

  _ST6 = value;
  __asm { frndint }
  result = 0;
  if ( _ST6 == value )
  {
    v4 = value * dbl_664D80;
    result = 1;
    _ST6 = v4;
    __asm { frndint }
    if ( _ST6 == v4 )
      return 2;
  }
  return result;
}

