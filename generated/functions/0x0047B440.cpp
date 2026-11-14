// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047B440 rf_rfl_light_allocate152
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Cdecl no arguments, allocates152-byte runtime-light record, invokes constructor47B880 if allocation nonnull, then sets renderer handleDWORD148=-1 and elapsed FLOAT140=0. Returns
// pointer EAX. AllocationNULL branch still writes through NULL+148/+140; no safe failure return. Does not load authored fields, append registry or create renderer light.
// Constructor-exception unwind raw-deletes current allocation.
int rf_rfl_light_allocate152()
{
  int v1; // [esp+4h] [ebp-1Ch]
  void *v2; // [esp+8h] [ebp-18h]

  v2 = operator new(0x98u);
  if ( v2 )
    v1 = rf_rfl_light_construct((int)v2);
  else
    v1 = 0;
  *(_DWORD *)(v1 + 148) = -1;
  *(float *)(v1 + 140) = 0.0;
  return v1;
}

