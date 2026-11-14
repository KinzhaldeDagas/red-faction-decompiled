// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A1B50 rf_multiplayer_broadcast_item_active_bitmap37
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// No-argument builder, no own runtime/authority guard. Borrows stack storage for200-bit bitset, zeros only25 serialized bytes, scans signed slot0..<78C248 without a200 clamp,
// resolves78BF28[slot], and sets bit when item exists and is not respawn-inactive (common flags+124 mask4000). Uses unchecked bit setter. Builds fixed28-byte opcode37 packet, payload
// WORD1=25 and25 raw bitmap bytes.
// Traverses circular player list87C324 via DWORD0; excludes local player unconditionally. Admits remote player when net+4608 is NULL OR net state+12 exactly2: the native null-net
// case reaches queue delegate, which may reject it. Queues unreliable data without direct flush or own state mutation. Borrowed bitset is destroyed normally/through SEH; no heap
// ownership transfer. Return EAX is cleanup artifact.
int rf_multiplayer_broadcast_item_active_bitmap37()
{
  int v1; // [esp+4h] [ebp-258h]
  int j; // [esp+10h] [ebp-24Ch]
  int v3; // [esp+14h] [ebp-248h]
  unsigned __int16 v4; // [esp+18h] [ebp-244h]
  _BYTE v5[28]; // [esp+1Ch] [ebp-240h] BYREF
  char Src; // [esp+38h] [ebp-224h] BYREF
  __int16 v7; // [esp+39h] [ebp-223h]
  int i; // [esp+23Ch] [ebp-20h]
  int v9[3]; // [esp+240h] [ebp-1Ch] BYREF
  int k; // [esp+24Ch] [ebp-10h]
  int v11; // [esp+258h] [ebp-4h]

  rf_bitset_construct_borrowed_storage(v9, (int)v5, 200);
  v11 = 0;
  for ( i = 0; i < 25; ++i )
    v5[i] = 0;
  for ( i = 0; i < dword_78C248; ++i )
  {
    v3 = rf_item_resolve_handle(dword_78BF28[i]);
    if ( v3 )
    {
      if ( !rf_object_has_respawn_inactive_flag(v3) )
        rf_bitset_set_bit_unchecked(v9, i, 1);
    }
  }
  Src = 37;
  v4 = 3;
  for ( j = 0; j < 25; ++j )
    *(&Src + v4++) = v5[j];
  v7 = v4 - 3;
  for ( k = dword_87C324; k; k = v1 )
  {
    if ( k != rf_local_fpgun_player && (!*(_DWORD *)(k + 4608) || *(_DWORD *)(*(_DWORD *)(k + 4608) + 12) == 2) )
      rf_network_queue_unreliable_player_packet(k, &Src, v4);
    if ( *(_DWORD *)k == dword_87C324 )
      v1 = 0;
    else
      v1 = *(_DWORD *)k;
  }
  v11 = -1;
  return rf_bitset_destroy(v9);
}

