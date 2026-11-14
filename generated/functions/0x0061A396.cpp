// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A396 __powhlp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl int(double base,double
// exponent,double*result),20 caller stack bytes; selected infinite cases only, no general pow calculation or ST0 numeric return. x87 comparisons use abs(base). Exponent exactly
// +infinity: |base|>1 ->+infinity, |base|<1 ->+0, |base|==1 ->1. Exponent exactly -infinity: |base|>1 ->+0, |base|<1 ->+infinity, |base|==1 ->original negative quiet NaN665DB8 and
// return1 (observed legacy policy). Other written cases return0. Finite exponent with base exactly +infinity: positive ->+infinity, negative ->+0, zero ->1. Base exactly -infinity:
// call d_inttype(exponent); positive ->-infinity iff odd1 else +infinity; negative ->original -0 constant665DD0 iff odd1 else +0; zero ->1. Unhandled other inputs return0 WITHOUT
// writing output, so0 is not universal initialized-success. Native raw high/low DWORD equality identifies infinities; no own NaN validation, errno, CW change, SEH or NULL checks.
// Caller filters NaNs/infinite admission and wraps this helper in FSAVE/FRSTOR; own x87 operations can trap and follow live environment. Unordered comparisons use exact native TEST
// AH,5/41 parity/zero branches, not additional finite guards; stated numeric matrix applies to non-NaN admission. All actual comparisons/pops/output writes and integer return paths
// reviewed.
int __cdecl _powhlp(double a1, double a2, double *a3)
{
  double v3; // st7
  int v4; // esi
  double v5; // st6
  double *v6; // eax
  int v7; // eax

  v3 = 0.0;
  v4 = 0;
  v5 = a1;
  if ( a1 < 0.0 )
    v5 = -a1;
  if ( HIDWORD(a2) == 2146435072 )
  {
    if ( !LODWORD(a2) )
    {
      if ( v5 <= 1.0 )
      {
        v6 = a3;
        if ( v5 >= 1.0 )
          v3 = 1.0;
        goto LABEL_28;
      }
      goto LABEL_6;
    }
  }
  else if ( a2 == -INFINITY )
  {
    if ( v5 > 1.0 )
      goto LABEL_27;
    v6 = a3;
    if ( v5 < 1.0 )
    {
      v3 = dbl_665DB0;
LABEL_28:
      *v6 = v3;
      return v4;
    }
    *a3 = dbl_665DB8;
    return 1;
  }
  if ( HIDWORD(a1) == 2146435072 )
  {
    if ( !LODWORD(a1) )
    {
      if ( a2 <= 0.0 )
      {
        v6 = a3;
        if ( a2 >= 0.0 )
          v3 = 1.0;
        goto LABEL_28;
      }
LABEL_6:
      v3 = dbl_665DB0;
LABEL_27:
      v6 = a3;
      goto LABEL_28;
    }
  }
  else if ( a1 == -INFINITY )
  {
    v7 = _d_inttype(a2);
    v3 = 0.0;
    if ( a2 <= 0.0 )
    {
      if ( a2 >= 0.0 )
      {
        v3 = 1.0;
      }
      else if ( v7 == 1 )
      {
        v3 = dbl_665DD0;
      }
    }
    else
    {
      v3 = dbl_665DB0;
      if ( v7 == 1 )
        v3 = -dbl_665DB0;
    }
    goto LABEL_27;
  }
  return v4;
}

