// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061031A ___libm_error_support
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl void libm error support
// (double*arg1,double*arg2,double*result,int selector),16 caller stack bytes. Select callback BEFORE selector validation: if live DWORD0x020216F4 nonzero, decode live slot0x02021F5C
// via decode_pointer; otherwise fixed zero stub0x61D8D7. These absolute slots are not file-backed initial values; do not infer runtime contents. Selected pointer called directly
// without NULL validation. Local C math record is32 bytes {type,name,arg1,arg2,retval}; callback receives one pointer and its retval edits copy back to *result. Exact selector
// matrix:2 log/type2,8 log10/type2,14 exp/type3,24 pow/type3,27 pow/type2,166 exp10/type3 -> callback, errno34 only if callback returns0. Selectors15 exp/type4,25 pow/type4 ->
// callback with NO own errno write regardless return. Selectors3 log,9 log10,28 pow,58 acos,61 asin -> type1 callback, errno33 if0. Selector29 pow and1000 log,1001 log10,1002
// exp,1003 atan,1004 ceil,1005 floor,1007 modf first write *result=*arg1, then form type1 record/callback/errno33 if0. Selector1006 pow uses existing result. Selectors1008 acos/1009
// asin use existing result. Selectors1010 sin/1011 cos/1012 tan first compute *arg1 times local +0.0, FST result before loading argument fields, then type1 callback/errno33 if0.
// Selector26 stores1.0 without callback; all other selectors leave result unchanged after initial callback-selection work. All memory reads/writes preserve native alias order:
// transformed-result stores precede subsequent arg1/arg2 loads. No semantic returned function pointer; EAX is incidental callback/address/errno state. No own CW restoration,
// synchronization, SEH, allocation or pointer/buffer checks; callbacks/FP conversions may throw/trap.
void __cdecl __libm_error_support(double *a1, double *a2, double *a3, int a4)
{
  int (__cdecl *v4)(int *); // eax
  double v5; // st7
  double v6; // st7
  double v7; // st7
  int v8; // [esp+Ch] [ebp-28h] BYREF
  const char *v9; // [esp+10h] [ebp-24h]
  double v10; // [esp+14h] [ebp-20h]
  double v11; // [esp+1Ch] [ebp-18h]
  double v12; // [esp+24h] [ebp-10h]
  double v13; // [esp+2Ch] [ebp-8h]

  v13 = 0.0;
  if ( unk_20216F4 )
    v4 = (int (__cdecl *)(int *))_decode_pointer(unk_2021F5C);
  else
    v4 = (int (__cdecl *)(int *))crt_return_zero_0061d8d7;
  if ( a4 > 166 )
  {
    switch ( a4 )
    {
      case 1000:
        v9 = (const char *)&off_64BAEC;
        goto LABEL_37;
      case 1001:
        v9 = "log10";
        goto LABEL_37;
      case 1002:
        v9 = (const char *)&off_64BAF8;
        goto LABEL_37;
      case 1003:
        v9 = "atan";
        goto LABEL_37;
      case 1004:
        v9 = "ceil";
        goto LABEL_37;
      case 1005:
        v9 = "floor";
        goto LABEL_37;
      case 1006:
        goto LABEL_38;
      case 1007:
        v9 = "modf";
        goto LABEL_37;
      case 1008:
        goto LABEL_35;
      case 1009:
        goto LABEL_34;
      case 1010:
        v9 = (const char *)&off_64BAB0;
        goto LABEL_53;
      case 1011:
        v9 = (const char *)&off_64BAAC;
        goto LABEL_53;
      case 1012:
        v9 = (const char *)&off_64BAA8;
LABEL_53:
        v6 = *a1 * v13;
        *a3 = v6;
        v10 = *a1;
        v11 = *a2;
        goto LABEL_54;
      default:
        return;
    }
  }
  if ( a4 == 166 )
  {
    v8 = 3;
    v9 = "exp10";
    goto LABEL_17;
  }
  if ( a4 <= 25 )
  {
    switch ( a4 )
    {
      case 25:
        v9 = (const char *)&off_64BAFC;
        goto LABEL_20;
      case 2:
        v8 = 2;
        v9 = (const char *)&off_64BAEC;
        goto LABEL_17;
      case 3:
        v9 = (const char *)&off_64BAEC;
        break;
      case 8:
        v8 = 2;
        v9 = "log10";
        goto LABEL_17;
      case 9:
        v9 = "log10";
        break;
      case 14:
        v8 = 3;
        v9 = (const char *)&off_64BAF8;
LABEL_17:
        v10 = *a1;
        v11 = *a2;
        v12 = *a3;
        if ( !v4(&v8) )
          *_errno() = 34;
        goto LABEL_56;
      case 15:
        v9 = (const char *)&off_64BAF8;
LABEL_20:
        v10 = *a1;
        v5 = *a2;
        v8 = 4;
        v11 = v5;
        v12 = *a3;
        v4(&v8);
LABEL_56:
        v7 = v12;
        goto LABEL_57;
      case 24:
        v8 = 3;
        goto LABEL_16;
      default:
        return;
    }
LABEL_23:
    v10 = *a1;
    v11 = *a2;
    v6 = *a3;
LABEL_54:
    v12 = v6;
    v8 = 1;
    if ( !v4(&v8) )
      *_errno() = 33;
    goto LABEL_56;
  }
  if ( a4 != 26 )
  {
    switch ( a4 )
    {
      case 27:
        v8 = 2;
LABEL_16:
        v9 = (const char *)&off_64BAFC;
        goto LABEL_17;
      case 28:
LABEL_38:
        v9 = (const char *)&off_64BAFC;
        break;
      case 29:
        v9 = (const char *)&off_64BAFC;
LABEL_37:
        *a3 = *a1;
        break;
      case 58:
LABEL_35:
        v9 = "acos";
        break;
      case 61:
LABEL_34:
        v9 = "asin";
        break;
      default:
        return;
    }
    goto LABEL_23;
  }
  v7 = 1.0;
LABEL_57:
  *a3 = v7;
}

