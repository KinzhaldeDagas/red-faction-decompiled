// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061694E __ffexpm1
// UNREALRED VERIFIED (2026-11-13; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Internal exp reduction helper: live extended ST0 x,
// EBP runtime frame, CH sign/context; no ordinary stack arguments. FLD x/FABS then original80-bit665C9E=32767.5 and FCOMPP test C0/C3 through frameWORD-0xA0: finite |x|<32767.5
// admitted, equality/larger/unordered exits range path. Admitted: duplicate x,FRNDINT ->n, FTST n; write status frame-0xA0 and copy highBYTE to DL. FXCH,FSUB ->fraction f=x-n; FTST f
// writes status again, FABS,F2XM1. Normal RET leaves ST0=(2^abs(f)-1), ST1=n, original lower stack retained; net x87 depth+1. Additional ST1/DL/status outputs are not a lone scalar C
// return; no own CW change. Original integer GPR writes only DL on normal-return path. Out-of-range entry616900 POP EAX discards helper return-PC (one extra nonlocal return level).
// FTST original x: negative (or unordered C0) ->frame errorBYTE-0x90=4, jump shared60DDC6 FSTP x/FLDZ/RET one level higher. Nonnegative ->drop x/load +infinity665C80, FCHS iff CH
// nonzero, sharedRET616922 one level higher; does NOT set errorBYTE in this path. Original intermediate FP state/exception masks apply; no general expm1 result or FP-environment
// save. Old void-only CH/EBP prototype omitted numeric input/output; corrected visible ST0 channel with secondary outputs/nonlocal exits documented, no ordinary standalone-C claim.
// positive sp value has been detected, the output may be wrong!
long double __usercall __spoils<dl> _ffexpm1@<st0>(
        long double x@<st0>,
        void *frame@<ebp>,
        unsigned __int8 signContext@<ch>)
{
  __asm
  {
    fld     st
    fabs
    fld     tbyte_665C9E; UNREALRED VERIFIED: Original80-bit threshold32767.5; equality and unordered join range exit.
    fcompp
    fstsw   word ptr [ebp-0A0h]
  }
  if ( (*((char *)frame - 159) & 0x41) != 0 )
  {
    __asm
    {
      ftst
      fstsw   word ptr [ebp-0A0h]
    }
    if ( (*((char *)frame - 159) & 1) != 0 )
    {
      *((char *)frame - 144) = 4;
      __asm
      {
        fstp    st
        fldz
      }
    }
    else
    {
      __asm
      {
        fstp    st
        fld     tbyte_665C80; UNREALRED VERIFIED: Positive range path loads +Inf then optional CH sign; errorBYTE is not assigned here.
      }
      if ( signContext )
        __asm { fchs }
      expbigret();
    }
  }
  else
  {
    __asm
    {
      fld     st
      frndint
      ftst
      fstsw   word ptr [ebp-0A0h]
    }
    __asm
    {
      fxch    st(1)
      fsub    st, st(1)
      ftst
      fstsw   word ptr [ebp-0A0h]; UNREALRED VERIFIED: Frame status now records signed fraction BEFORE FABS/F2XM1.
      fabs
      f2xm1
    }
  }
  return x;
}

