// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C8220 rf_clip_line_vertex48_outcode_planes
// UNREALRED VERIFIED [renderer-helpers-20261028]: Arguments addresses of two endpoint pointers and combined outcode byte. Iterates bits1..64; skips0x80. For selected bit,if first endpoint outside swaps endpoint pointers,then replaces second endpoint with0x5C7740 intersection(attribute mask0). Recomputes OR from both endpoint outcodes; recycles replaced second endpoint if flags+25 bit4. Mutates caller pointer variables,can swap endpoint order. No initial shared-AND rejection,allocation-null guard or both-outside guard; caller0x5D9620 performs initial AND rejection. Mask0 leaves UV/colors in generated scratch vertices stale.
void __cdecl rf_clip_line_vertex48_outcode_planes(int *a1, float **a2, unsigned __int8 a3)
{
  int v3; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int v5; // [esp+8h] [ebp-4h]

  for ( i = 1; i <= 64; i *= 2 )
  {
    if ( ((unsigned __int8)i & a3) != 0 )
    {
      if ( ((unsigned __int8)i & *(_BYTE *)(*a1 + 24)) != 0 )
      {
        v3 = *a1;
        *a1 = (int)*a2;
        *a2 = (float *)v3;
      }
      v5 = (int)*a2;
      *a2 = rf_clip_make_intersection_vertex_48(i, (float *)*a1, *a2, 0);
      a3 = *((_BYTE *)*a2 + 24) | *(_BYTE *)(*a1 + 24);
      if ( (*(_BYTE *)(v5 + 25) & 4) != 0 )
        rf_clip_vertex48_pool_release(v5);
    }
  }
}

