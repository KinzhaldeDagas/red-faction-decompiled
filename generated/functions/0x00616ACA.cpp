// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00616ACA cintrinexit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Shared INTERNAL x87 exit, EBP caller-owned runtime frame, live ST0 input/output. If global2021334 nonzero, immediately FLDCW savedWORD[frame-164],FWAIT,RET
// preserving ST0. Otherwise FST QWORD[frame-720] without popping, inspect signed errorBYTE[frame-144]. Zero checks inexact: if originalCW masks inexact or current status has none,
// restoreCW/RET; otherwise errorDWORD[frame-142]=8. Error-1 checks stored result exponent for overflow; error-2 checks underflow/overflow; other nonzero sign-extended byte becomes
// errorDWORD. Underflow stores4 and rescales ST0 using original constants64C8A8/64C898/64C8B8; overflow stores3 and rescales using64C8A0/64C890/64C8B0, preserving native
// strict/unordered x87 flags. Error route sets name pointer=stored descriptor+1, conditionally copies first/second original stack doubles into frame according to BYTE[frame-712]&1
// and descriptorBYTE+12, FSTP QWORD result[frame-118], calls __87except(descriptorBYTE+14,&errorRecord,&savedCW), then FLD QWORD result and restoreCW/FWAIT/RET. No independent
// frame/argument stack teardown or EAX numeric promise. Existing long-double ST0 ABI retained; all shared native bytes captured, no function-boundary merge or code patch.
long double __usercall cintrinexit@<st0>(long double *a1@<ebp>, long double result@<st0>)
{
  char v2; // fps
  char v3; // al
  __int16 v4; // ax
  int v5; // ebx

  if ( unk_2021334 )
    return result;
  *(a1 - 90) = result;
  v3 = *((_BYTE *)a1 - 144);
  switch ( v3 )
  {
    case 0:
      goto checkinexact;
    case -1:
      if ( (*((_WORD *)a1 - 357) & 0x7FF0) != 0x7FF0 )
        goto checkinexact;
      goto haveoverflow_0;
    case -2:
      v4 = *((_WORD *)a1 - 357) & 0x7FF0;
      if ( !v4 )
      {
        *(_DWORD *)((char *)a1 - 142) = 4;
        result = __FSCALE__(result, 1536.0);
        if ( fabs(result) < 2.225073858507201e-308 )
          result = result * 0.0;
        goto haveerror;
      }
      if ( v4 != 32752 )
      {
checkinexact:
        if ( (*((_WORD *)a1 - 82) & 0x20) != 0 || (v2 & 0x20) == 0 )
          return result;
        *(_DWORD *)((char *)a1 - 142) = 8;
        goto haveerror;
      }
haveoverflow_0:
      *(_DWORD *)((char *)a1 - 142) = 3;
      result = __FSCALE__(result, -1536.0);
      if ( fabs(result) > 1.797693134862316e308 )
        result = result * INFINITY;
      goto haveerror;
  }
  *(_DWORD *)((char *)a1 - 142) = v3;
haveerror:
  v5 = *((_DWORD *)a1 - 37) + 1;
  *(_DWORD *)((char *)a1 - 138) = v5;
  if ( (*(_BYTE *)(a1 - 89) & 1) == 0 )
  {
    *(long double *)((char *)a1 - 134) = a1[1];
    if ( *(_BYTE *)(v5 + 12) != 1 )
      *(long double *)((char *)a1 - 126) = a1[2];
  }
  *(long double *)((char *)a1 - 118) = result;
  _87except(*(char *)(*((_DWORD *)a1 - 37) + 14), (long double *)((char *)a1 - 142), (const unsigned __int16 *)a1 - 82);
  return *(long double *)((char *)a1 - 118);
}

