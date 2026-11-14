// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589E40 rf_v3c_mesh_metadata100_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Deleting-destructor adapter for100-byte mesh metadata records allocated alongside144-byte meshes. Bit2 destroys array via cookie[this-4] and stride100 with destructor unknown_libname_45; otherwise destroys one. Bit1 frees array cookie base or scalar allocation. Returns base even if freed. Distinct record family from auxiliary transform100 records, despite same byte size.
char *__thiscall rf_v3c_mesh_metadata100_deleting_destructor(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(this, 0x64u, *((_DWORD *)this - 1), rf_v3c_mesh_metadata100_destruct_noop);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_v3c_mesh_metadata100_destruct_noop(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

