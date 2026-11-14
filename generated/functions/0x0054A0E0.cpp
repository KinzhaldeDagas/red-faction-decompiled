// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054A0E0 rf_world_packet_face_shared_index_pair_score
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Cdecl(group,faceIndexA,faceIndexB). Finds28-byte records through group+48,compares EVERY signedWORD index of A with every index of B,increments for each equal pair,returns count. Duplicates count multiplicatively;not unique set intersection,edge adjacency or geometric distance. No face/index bounds or allocation.
int __cdecl rf_world_packet_face_shared_index_pair_score(int a1, int a2, int a3)
{
  int j; // [esp+0h] [ebp-14h]
  __int16 *v5; // [esp+4h] [ebp-10h]
  int v6; // [esp+8h] [ebp-Ch]
  __int16 *v7; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  v6 = 0;
  v5 = (__int16 *)(*(_DWORD *)(a1 + 48) + 28 * a2);
  v7 = (__int16 *)(*(_DWORD *)(a1 + 48) + 28 * a3);
  for ( i = 0; i < *v5; ++i )
  {
    for ( j = 0; j < *v7; ++j )
    {
      if ( *(__int16 *)(*((_DWORD *)v5 + 1) + 2 * i) == *(__int16 *)(*((_DWORD *)v7 + 1) + 2 * j) )
        ++v6;
    }
  }
  return v6;
}

