// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606065 ___onexitinit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs initialization: calloc_crt(32,4), encode
// result even when NULL, publish same encoded pointer to begin2022F90 and end2022F8C. NULL allocation returns24. Success additionally writes raw DWORD0 to first slot and returns0;
// calloc zeroes all128 bytes, rather than filling with encoded_null. No once guard, prior-array free, lock, callback execution, or rollback of already published globals.
int __onexitinit()
{
  _DWORD *v0; // esi

  v0 = (_DWORD *)_calloc_crt(0x20u, 4);
  dword_2022F90 = _encode_pointer(v0);
  dword_2022F8C = dword_2022F90;
  if ( !v0 )
    return 24;
  *v0 = 0;
  return 0;
}

