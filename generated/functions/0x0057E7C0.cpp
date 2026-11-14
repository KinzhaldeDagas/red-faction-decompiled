// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E7C0 rf_renderer_clip_polygon_to_screen_xy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Cdecl count,input clip48-vertex pointers,output contiguous floatXY pairs. Copies pointers to global18CD040,computes outcode+24 OR/AND;nonzero AND returns0 (including count<=0 because AND startsFF). If OR nonzero,clips through5C86D0 using alternate global18CD108,mutable count/OR/AND,mode0. No vertex-count/output-capacity checks;global scratch nonreentrant. Projects each surviving vertex unless flags+25 bit01 already set;flags02 rejected path returns0 IMMEDIATELY,can leave partial output pairs and bypass final temporary-pool cleanup. Success writes screenX+12,Y+16 into output8-byte strides. If clipping attempted,normal cleanup releases surviving flags04 vertices through5C76E0;clipped-away lifetime follows clipper. If
// clipper zeroes count or sets AND,sets count0,so final cleanup iterates none. No clipping means no pool releases. Returns final count;does not draw polygon. Clipper handles bits01..40,not80.
int __cdecl rf_renderer_clip_polygon_to_screen_xy(int a1, int a2, int a3)
{
  int v4; // [esp+4h] [ebp-18h]
  int v5; // [esp+8h] [ebp-14h]
  _DWORD *v6; // [esp+Ch] [ebp-10h]
  char v7; // [esp+13h] [ebp-9h]
  int i; // [esp+14h] [ebp-8h]
  int j; // [esp+14h] [ebp-8h]
  int k; // [esp+14h] [ebp-8h]
  char v11; // [esp+18h] [ebp-4h] BYREF
  char v12; // [esp+19h] [ebp-3h]

  v11 = 0;
  v12 = -1;
  v6 = unk_18CD040;
  for ( i = 0; i < a1; ++i )
  {
    unk_18CD040[i] = *(_DWORD *)(a2 + 4 * i);
    v5 = unk_18CD040[i];
    v12 &= *(_BYTE *)(v5 + 24);
    v11 |= *(_BYTE *)(v5 + 24);
  }
  if ( v12 )
    return 0;
  v7 = 0;
  if ( v11
    && ((v7 = 1, v6 = (_DWORD *)rf_clip_polygon_outcode_planes_48((int)unk_18CD040, (int)unk_18CD108, &a1, &v11, 0), !a1)
     || v12) )
  {
    a1 = 0;
  }
  else
  {
    for ( j = 0; j < a1; ++j )
    {
      v4 = v6[j];
      if ( (*(_BYTE *)(v4 + 25) & 1) == 0 )
        rf_renderer_project_clip_vertex_backend_wrapper(v4);
      if ( (*(_BYTE *)(v4 + 25) & 2) != 0 )
        return 0;
      *(float *)(a3 + 8 * j) = *(float *)(v4 + 12);
      *(float *)(a3 + 8 * j + 4) = *(float *)(v4 + 16);
    }
  }
  if ( v7 )
  {
    for ( k = 0; k < a1; ++k )
    {
      if ( (*(_BYTE *)(v6[k] + 25) & 4) != 0 )
        rf_clip_vertex48_pool_release(v6[k]);
    }
  }
  return a1;
}

