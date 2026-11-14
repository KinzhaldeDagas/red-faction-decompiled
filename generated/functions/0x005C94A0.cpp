// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C94A0 rf_material200_destroy_owned_float_arrays
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): If material flags DWORD4&1 set, deletes each nonnull array pointer128,188,196 independently;counts not consulted. Then runs two texture-layer destructors at16,stride52 via unknown_libname_53. Does not free material object,clear pointers/counts/flags,or guard repeated destruction. This ownership bit is set by private-material cloning5657D0.
void __thiscall rf_material200_destroy_owned_float_arrays(void *this)
{
  if ( (*((_DWORD *)this + 1) & 1) != 0 )
  {
    if ( *((_DWORD *)this + 32) )
      operator delete(*((void **)this + 32));
    if ( *((_DWORD *)this + 47) )
      operator delete(*((void **)this + 47));
    if ( *((_DWORD *)this + 49) )
      operator delete(*((void **)this + 49));
  }
  `eh vector destructor iterator'((char *)this + 16, 0x34u, 2, rf_saved_receiver_noop_5C90E0);
}

