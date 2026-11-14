// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C82E0 rf_clip_polygon_one_plane_48
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, complete skinned draw path, clipping control flow, buffer limits, original x87/integer operations and caller arguments): Cdecl plane mask,input vertex-pointer array,output vertex-pointer array,count pointer,two BYTE OR/AND output,attribute mask. Writes input[count]=input[0] and input[count+1]=input[1] BEFORE any count validation; requires2 writable closure slots. Initializes OR0/ANDFF. Iterates i=1 through original count,using previous/current/next input pointers. Inside current vertex is retained; outside current vertex creates intersection from previous inside to current and/or next inside to current,then releases current vertex through5C76E0 if flags BYTE25 has4. Every emitted pointer updates OR/AND using vertex outcode BYTE24. Retained cyclic order is rotated by one slot because iteration begins1 and closure[count]
// repeats0. On failed intersection allocation sets ANDFF and returns0 immediately; already emitted pointers/intersections are not rolled back or freed in that branch. Otherwise returns emitted pointer count ((outputEnd-outputStart)/4); does not itself update *count. Zero count still writes both closure entries,returns0 with OR0/ANDFF. No source/destination capacity,index,alias or positive-count guard. Full wrapper5C86D0 owns count update/buffer swap; caller resets shared pool before a triangle.
int __cdecl rf_clip_polygon_one_plane_48(unsigned __int8 a1, _DWORD *a2, int a3, int *a4, _BYTE *a5, char a6)
{
  int v7; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  v7 = a3;
  a2[*a4] = *a2;
  a2[*a4 + 1] = a2[1];
  a5[1] = -1;
  *a5 = 0;
  for ( i = 1; i <= *a4; ++i )
  {
    if ( (a1 & *(_BYTE *)(a2[i] + 24)) != 0 )
    {
      if ( (a1 & *(_BYTE *)(a2[i - 1] + 24)) == 0 )
      {
        *(_DWORD *)a3 = rf_clip_make_intersection_vertex_48(a1, (float *)a2[i - 1], (float *)a2[i], a6);
        if ( !*(_DWORD *)a3 )
        {
          a5[1] = -1;
          return 0;
        }
        *a5 |= *(_BYTE *)(*(_DWORD *)a3 + 24);
        a5[1] &= *(_BYTE *)(*(_DWORD *)a3 + 24);
        a3 += 4;
      }
      if ( (a1 & *(_BYTE *)(a2[i + 1] + 24)) == 0 )
      {
        *(_DWORD *)a3 = rf_clip_make_intersection_vertex_48(a1, (float *)a2[i + 1], (float *)a2[i], a6);
        if ( !*(_DWORD *)a3 )
        {
          a5[1] = -1;
          return 0;
        }
        *a5 |= *(_BYTE *)(*(_DWORD *)a3 + 24);
        a5[1] &= *(_BYTE *)(*(_DWORD *)a3 + 24);
        a3 += 4;
      }
      if ( (*(_BYTE *)(a2[i] + 25) & 4) != 0 )
        rf_clip_vertex48_pool_release(a2[i]);
    }
    else
    {
      *(_DWORD *)a3 = a2[i];
      a3 += 4;
      *a5 |= *(_BYTE *)(a2[i] + 24);
      a5[1] &= *(_BYTE *)(a2[i] + 24);
    }
  }
  return (a3 - v7) >> 2;
}

