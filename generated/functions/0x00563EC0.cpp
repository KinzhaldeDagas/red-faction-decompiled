// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00563EC0 rf_model_handle_load_v3m_mode1
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(filename,cacheByte,limitWord). Normalizes limit bits-1 to decimal9999999 (IDA offset label98967F is scalar literal), allocates initialized88byte handle, calls type1V3M loader with mode1 and limit. That loader ignores its mode argument, stores shared cached asset in handle4. Success sets material pointer80=0 and returns handle; reported load failure releases handle and returnsNULL. No allocation-null guard. Equivalent to564050 for same effective inputs because mode unused.
_DWORD *__cdecl rf_model_handle_load_v3m_mode1(char *a1, unsigned __int8 a2, char *a3)
{
  _DWORD *initialized; // [esp+0h] [ebp-4h]

  if ( a3 == (char *)-1 )
    a3 = byte_98967F;
  initialized = rf_model_handle_allocate_initialized();
  if ( rf_vmesh_type1_v3m_load(initialized, a1, a2, 1, (int)a3) )
  {
    initialized[20] = 0;
  }
  else
  {
    rf_model_handle_destroy_and_release_to_pool(initialized);
    return nullptr;
  }
  return initialized;
}

