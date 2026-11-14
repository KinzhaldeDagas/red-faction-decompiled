// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E88C ___AdjustPointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw object pointer,const PMD*), return
// adjusted raw pointer in EAX, no writes. Read signed mdisp=PMD+0 and initialize result=object+mdisp modulo32. If signed pdisp=PMD+4<0 return immediately, never read vdisp or object
// memory. Otherwise load vdisp DWORD+8, dereference DWORD vbtablePointer at ORIGINAL object+pdisp (not object+mdisp), read signed/raw32 vbtable displacement at vbtablePointer+vdisp,
// add pdisp+displacement to preliminary result modulo32. No NULL-special case: NULL object may return nonNULL arithmetic value on negative pdisp, or fault on nonnegative pdisp. No
// bounds/alignment/table validity, range/overflow checks, allocation, dynamic RTTI search or errno. Preserve ESI. Native callers pass catchable.thisDisplacement at+8; existing PMD
// layout {int mdisp,int pdisp,int vdisp} retained and raw-int return corrected to void*.
void *__cdecl __AdjustPointer(void *a1, const PMD *a2)
{
  void *result; // eax

  result = (char *)a1 + a2->mdisp;
  if ( a2->pdisp >= 0 )
    return (char *)result + a2->pdisp + *(_DWORD *)(*(_DWORD *)((char *)a1 + a2->pdisp) + a2->vdisp);
  return result;
}

