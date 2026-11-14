// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DBBE0 sub_4DBBE0
// UNREALRED VERIFIED [lan-body-credit-20261029] Multiplayer-only fallback: scan exactly64 slots from0x87C328, stride8, comparing full source handle dword; return matching slot+4 network-id byte (first match) or0xFF. No live object resolution and no time-based expiry occur here. This allows a destroyed old body to identify its player until ring eviction/reset.
char __cdecl sub_4DBBE0(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  if ( !rf_multiplayer_runtime_mode )
    return -1;
  for ( i = 0; i < 64; ++i )
  {
    if ( unk_87C328[2 * i] == a1 )
      return unk_87C32C[8 * i];
  }
  return -1;
}

