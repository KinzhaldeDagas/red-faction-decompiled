// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054A180 rf_world_packet_group_reorder_faces_and_vertices
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Cdecl group. For each face exceptlast,selects later face with greatest54A0E0 shared-index pair score,first winner on ties,best initialized-1 so even zero score qualifies;swaps into next slot using28-byte copy helpers. Then initializes remap[0..vertexCount)=-1,assigns new vertex IDs in first-reference order across reordered face indices,permutes local->global WORD map and4-float UV entries through global scratch,rewrites all face indices. Returns signed face count at loop exit;not boolean. Assumes every declared vertex referenced:unused remap stays-1 and is used as scratch destination index without check. No capacity/negative-index guards;global scratch nonreentrant.
int __cdecl rf_world_packet_group_reorder_faces_and_vertices(int a1)
{
  int result; // eax
  __int16 *v2; // [esp+0h] [ebp-50h]
  int v3; // [esp+4h] [ebp-4Ch]
  int v4; // [esp+8h] [ebp-48h]
  __int16 *v5; // [esp+Ch] [ebp-44h]
  char destination[28]; // [esp+10h] [ebp-40h] BYREF
  int v7; // [esp+2Ch] [ebp-24h]
  int v8; // [esp+30h] [ebp-20h]
  int v9; // [esp+34h] [ebp-1Ch]
  int j; // [esp+38h] [ebp-18h]
  int v11; // [esp+3Ch] [ebp-14h]
  int i; // [esp+40h] [ebp-10h]
  int v13; // [esp+44h] [ebp-Ch]
  int v14; // [esp+48h] [ebp-8h]
  int k; // [esp+4Ch] [ebp-4h]

  v13 = 0;
  v11 = 0;
  for ( i = 0; i < *(__int16 *)(a1 + 74) - 1; ++i )
  {
    v8 = -1;
    v9 = -1;
    for ( j = i + 1; j < *(__int16 *)(a1 + 74); ++j )
    {
      v7 = rf_world_packet_face_shared_index_pair_score(a1, i, j);
      if ( v7 > v9 )
      {
        v8 = j;
        v9 = v7;
      }
    }
    if ( v8 == -1 )
    {
      ++v11;
    }
    else
    {
      ++v13;
      if ( v8 != i + 1 )
      {
        rf_world_packet_face28_copy_54cb80(destination, (const void *)(*(_DWORD *)(a1 + 48) + 28 * (i + 1)));
        rf_world_packet_face28_assign((void *)(*(_DWORD *)(a1 + 48) + 28 * (i + 1)), *(_DWORD *)(a1 + 48) + 28 * v8);
        rf_world_packet_face28_assign((void *)(*(_DWORD *)(a1 + 48) + 28 * v8), (int)destination);
      }
    }
  }
  v14 = 0;
  for ( i = 0; i < *(__int16 *)(a1 + 72); ++i )
    unk_1436C78[i] = -1;
  for ( i = 0; i < *(__int16 *)(a1 + 74); ++i )
  {
    v5 = (__int16 *)(*(_DWORD *)(a1 + 48) + 28 * i);
    for ( k = 0; k < *v5; ++k )
    {
      v4 = *(__int16 *)(*((_DWORD *)v5 + 1) + 2 * k);
      if ( unk_1436C78[v4] < 0 )
        unk_1436C78[v4] = v14++;
    }
  }
  for ( i = 0; i < *(__int16 *)(a1 + 72); ++i )
  {
    v3 = unk_1436C78[i];
    unk_145E180[v3] = *(_WORD *)(*(_DWORD *)(a1 + 40) + 2 * i);
    unk_143E980[4 * v3] = *(float *)(*(_DWORD *)(a1 + 44) + 16 * i);
    unk_143E984[4 * v3] = *(float *)(*(_DWORD *)(a1 + 44) + 16 * i + 4);
    unk_143E988[4 * v3] = *(float *)(*(_DWORD *)(a1 + 44) + 16 * i + 8);
    unk_143E98C[4 * v3] = *(float *)(*(_DWORD *)(a1 + 44) + 16 * i + 12);
  }
  memcpy(*(void **)(a1 + 40), unk_145E180, 2 * *(__int16 *)(a1 + 72));
  memcpy(*(void **)(a1 + 44), unk_143E980, 16 * *(__int16 *)(a1 + 72));
  for ( i = 0; ; ++i )
  {
    result = *(__int16 *)(a1 + 74);
    if ( i >= result )
      break;
    v2 = (__int16 *)(*(_DWORD *)(a1 + 48) + 28 * i);
    for ( k = 0; k < *v2; ++k )
      *(_WORD *)(*((_DWORD *)v2 + 1) + 2 * k) = unk_1436C78[*(__int16 *)(*((_DWORD *)v2 + 1) + 2 * k)];
  }
  return result;
}

