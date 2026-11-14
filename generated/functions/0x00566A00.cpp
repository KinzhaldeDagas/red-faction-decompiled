// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00566A00 rf_material200_vector_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): ECX material element plus flags. flags&2(array mode) reads element count from DWORD at this-4, destroys elements via runtime iterator stride200 and5C94A0, then flags&1 frees cookie pointer this-4;returns cookie address. Scalar mode destroys one through5C94A0,flags&1 frees this,returns this. No flag/layout/count validation; flags3 used by handle material cleanup.
char *__thiscall rf_material200_vector_deleting_destructor(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(this, 0xC8u, *((_DWORD *)this - 1), rf_material200_destroy_owned_float_arrays);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_material200_destroy_owned_float_arrays(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

