// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C84F0 rf_clip_polygon_extended_uv_one_plane
// UNREALRED VERIFIED [extended-clip-20261028]: Arguments plane bit,input pointer array,output pointer array,input count pointer,OR/AND bytes,attribute mask. Writes input[count]=input[0] and input[count+1]=input[1],requiring two spare pointer slots. Walks indices1..count; inside vertex is copied,while outside vertex generates intersections from each inside neighbor through0x5C7CA0. Recycles discarded temporary vertex when flags+25 bit4set through0x5C7710. Accumulates complete output outcodes into flags[0] OR and flags[1] AND,initialized0/255; empty output leaves AND255. Returns output count without updating input count itself. All-inside polygon is rotated one pointer position. No count,output-capacity or allocation-failure guard.
int __cdecl rf_clip_polygon_extended_uv_one_plane(unsigned __int8 a1, _DWORD *a2, int a3, int *a4, _BYTE *a5, char a6)
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
        *(_DWORD *)a3 = rf_clip_make_intersection_vertex_extended_uv(a1, (float *)a2[i - 1], (float *)a2[i], a6);
        *a5 |= *(_BYTE *)(*(_DWORD *)a3 + 24);
        a5[1] &= *(_BYTE *)(*(_DWORD *)a3 + 24);
        a3 += 4;
      }
      if ( (a1 & *(_BYTE *)(a2[i + 1] + 24)) == 0 )
      {
        *(_DWORD *)a3 = rf_clip_make_intersection_vertex_extended_uv(a1, (float *)a2[i + 1], (float *)a2[i], a6);
        *a5 |= *(_BYTE *)(*(_DWORD *)a3 + 24);
        a5[1] &= *(_BYTE *)(*(_DWORD *)a3 + 24);
        a3 += 4;
      }
      if ( (*(_BYTE *)(a2[i] + 25) & 4) != 0 )
        rf_clip_extended_vertex_pool_release(a2[i]);
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

