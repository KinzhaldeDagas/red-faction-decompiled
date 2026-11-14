// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005396D0 rf_dual_array28_vector_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Microsoft deleting adapter for28-byte objects destroyed by5397A0. Flag02:cookie count at this-4,vector destructor iterator stride28,optional delete(cookie) if01,returns cookie address. Otherwise destroys one object,optional delete(this) if01,returns original address. Flag02 selects array cleanup even without free;does not deep-delete member pointer elements.
char *__thiscall rf_dual_array28_vector_deleting_destructor(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(
      this,
      0x1Cu,
      *((_DWORD *)this - 1),
      (void (__thiscall *)(void *))rf_dual_array28_destroy_members);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_dual_array28_destroy_members((void **)this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

