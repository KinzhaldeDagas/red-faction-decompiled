// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005369D0 rf_lightmap_inset_cell_inside_polygon_halfplanes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, lightmap clusters, tile mapping, atlas placement, seam blend snapshots, recovered halfplanes and original PE bytes): Recovered cdecl integer cellX,cellY,signed vertexCount,contiguous floatXY polygon. Tests four inset-cell corners(x,y+S),(x,y),(x+S,y+S),(x+S,y),S=exact PE double0.9999989867210388,rounding each coordinate tofloat. For each polygon vertex,current and previous(wrapped),normalizes previous-current and corner-current through558B00;positive ordered cross(edge,toCorner) rejects immediately,otherwise continues. All tests pass returnsAL1. Intended convex CCW halfplanes,but no convexity/winding checks. count<=0 vacuously returns1 with no polygon read. Cross0 accepted,UNORDERED not rejected;coincident/zero vectors substituted(1,0) by normalizer,so vertex-boundary/degenerate cases differ from plain cross-product
// containment. Does not test a full exact1x1 square,clip polygon or allocate.
unsigned __int8 __cdecl rf_lightmap_inset_cell_inside_polygon_halfplanes(int a1, int a2, int a3, const float *a4)
{
  float v4; // ecx
  float v5; // edx
  float *v6; // eax
  float v8; // [esp+8h] [ebp-5Ch]
  float v9; // [esp+Ch] [ebp-58h]
  int v10; // [esp+10h] [ebp-54h]
  float v11; // [esp+14h] [ebp-50h]
  float v12; // [esp+18h] [ebp-4Ch]
  float v13[3]; // [esp+1Ch] [ebp-48h] BYREF
  float v14; // [esp+28h] [ebp-3Ch]
  float v15; // [esp+2Ch] [ebp-38h] BYREF
  float v16; // [esp+30h] [ebp-34h]
  float v17; // [esp+34h] [ebp-30h] BYREF
  float v18; // [esp+38h] [ebp-2Ch]
  float v19[2]; // [esp+3Ch] [ebp-28h] BYREF
  int j; // [esp+44h] [ebp-20h]
  float v21; // [esp+48h] [ebp-1Ch]
  float v22; // [esp+4Ch] [ebp-18h]
  int i; // [esp+50h] [ebp-14h]
  float v24; // [esp+54h] [ebp-10h]
  float v25; // [esp+58h] [ebp-Ch]
  float v26; // [esp+5Ch] [ebp-8h]
  float v27; // [esp+60h] [ebp-4h]

  v24 = (float)a1;
  v26 = (double)a1 + 0.9999989867210388;
  v25 = (float)a2;
  v27 = (double)a2 + 0.9999989867210388;
  for ( i = 0; i < 4; ++i )
  {
    if ( i >= 2 )
      v12 = v26;
    else
      v12 = v24;
    v21 = v12;
    if ( (i & 1) != 0 )
      v11 = v25;
    else
      v11 = v27;
    v22 = v11;
    for ( j = 0; j < a3; ++j )
    {
      if ( j )
        v10 = j - 1;
      else
        v10 = a3 - 1;
      LODWORD(v13[2]) = v10;
      v4 = a4[2 * j + 1];
      v17 = a4[2 * j];
      v18 = v4;
      v5 = a4[2 * v10 + 1];
      v15 = a4[2 * v10];
      v16 = v5;
      v6 = rf_vector2_subtract_to_output(&v15, v13, &v17);
      rf_vector2_copy_return_source(&v15, v6);
      rf_vector2_normalize_length_or_unit_x(&v15);
      v9 = v22 - v18;
      v8 = v21 - v17;
      rf_vector2_assign_components(v19, v8, v9);
      rf_vector2_normalize_length_or_unit_x(v19);
      v14 = v15 * v19[1] - v16 * v19[0];
      if ( v14 > 0.0 )
        return 0;
    }
  }
  return 1;
}

