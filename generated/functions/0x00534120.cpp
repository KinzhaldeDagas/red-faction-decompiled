// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00534120 rf_geomod_face_split_between_intersection_vertices
// UNREALRED VERIFIED [finite-split-20261028] Divides both circular boundary arcs between nonadjacent shared endpoint pointers. Every intermediate sorted finite intersection record is inserted into BOTH new cut boundaries in opposite scalar orders, interpolating all four corner floats +4/+8/+12/+16 by scalar ratio before finalize/ownership transfer. Paired records must survive pre-triangulation division; inserting only cutter-edge points after triangulation cannot replace this contract.
// UNREALRED VERIFIED [ordered-boundary-20261028] Exact pointer membership is checked separately in output A at0x534336 and output B at0x5344CA. Intermediate shared records are inserted unless already present in THAT loop. Each output is independently finalized (0x5345BD /0x534634); a zero-area output is destroyed/cleared at0x5345D4 /0x53464B while the other continues. This is local face disposal, not permission to relax host transaction seam gates. Finalization retains all collinear corner IDs.
// UNREALRED VERIFIED [combat-native-query-20261104]: Valid split children append to global active list, copy parent spatial-node owner and append child0 thenchild1 to that node face list, then attach to parent room tail. Caller removes parent separately. Preserve independent global, room and node ordering; inherited node bounds remain conservative. Child planes copy parent, and intermediate shared vertex IDs remain in both cut boundaries.
char __thiscall rf_geomod_face_split_between_intersection_vertices(
        int this,
        void *solid,
        int a3,
        int a4,
        int a5,
        int *a6,
        int *a7)
{
  int v8; // [esp+10h] [ebp-64h]
  int v9; // [esp+14h] [ebp-60h]
  float v11; // [esp+1Ch] [ebp-58h]
  float v12; // [esp+20h] [ebp-54h]
  float v13; // [esp+24h] [ebp-50h]
  float v14; // [esp+28h] [ebp-4Ch]
  float v15; // [esp+2Ch] [ebp-48h]
  float v16; // [esp+30h] [ebp-44h]
  float v17; // [esp+34h] [ebp-40h]
  float v18; // [esp+38h] [ebp-3Ch]
  float v19; // [esp+3Ch] [ebp-38h]
  float v20; // [esp+40h] [ebp-34h]
  int i; // [esp+44h] [ebp-30h]
  int j; // [esp+44h] [ebp-30h]
  _DWORD *k; // [esp+44h] [ebp-30h]
  int v24; // [esp+48h] [ebp-2Ch]
  int v25; // [esp+48h] [ebp-2Ch]
  float *v26; // [esp+50h] [ebp-24h]
  int v27; // [esp+54h] [ebp-20h]
  int v28; // [esp+58h] [ebp-1Ch]
  int v29; // [esp+58h] [ebp-1Ch]
  int v30; // [esp+5Ch] [ebp-18h]
  float *v31; // [esp+60h] [ebp-14h]
  _DWORD *v32; // [esp+64h] [ebp-10h]
  _DWORD *v33; // [esp+64h] [ebp-10h]
  int m; // [esp+68h] [ebp-Ch]
  int n; // [esp+68h] [ebp-Ch]

  v30 = **(_DWORD **)(a5 + 4 * a3);
  v27 = **(_DWORD **)(a5 + 4 * a4);
  for ( i = *(_DWORD *)(this + 64); i; i = v9 )
  {
    if ( *(_DWORD *)i == v30 )
    {
      if ( **(_DWORD **)(i + 24) == v27 || **(_DWORD **)(i + 20) == v27 )
        return 0;
      break;
    }
    if ( *(_DWORD *)(i + 20) == *(_DWORD *)(this + 64) )
      v9 = 0;
    else
      v9 = *(_DWORD *)(i + 20);
  }
  *a6 = (int)rf_solid_face_allocate_link(solid, (const unsigned int *)(this + 40));
  *a7 = (int)rf_solid_face_allocate_link(solid, (const unsigned int *)(this + 40));
  v28 = 0;
  for ( j = *(_DWORD *)(this + 64); j && *(_DWORD *)j != v30; j = v8 )
  {
    if ( *(_DWORD *)(j + 20) == *(_DWORD *)(this + 64) )
      v8 = 0;
    else
      v8 = *(_DWORD *)(j + 20);
  }
  v26 = rf_geomod_face_corner_append(
          (float *)*a6,
          *(_DWORD *)j,
          *(float *)(j + 4),
          *(float *)(j + 8),
          *(float *)(j + 12),
          *(float *)(j + 16));
  v24 = 1;
  for ( k = *(_DWORD **)(j + 20); *k != v27; k = v32 )
  {
    v32 = (_DWORD *)k[5];
    rf_geomod_face_corner_move((_DWORD *)*a6, this, k);
    ++v24;
  }
  v31 = rf_geomod_face_corner_append(
          (float *)*a6,
          *k,
          *((float *)k + 1),
          *((float *)k + 2),
          *((float *)k + 3),
          *((float *)k + 4));
  v25 = v24 + 1;
  for ( m = a4 - 1; m > a3; --m )
  {
    if ( !rf_geomod_face_contains_shared_vertex((_DWORD *)*a6, **(_DWORD **)(a5 + 4 * m)) )
    {
      v17 = (*(float *)(*(_DWORD *)(a5 + 4 * m) + 20) - *(float *)(*(_DWORD *)(a5 + 4 * a4) + 20))
          / (*(float *)(*(_DWORD *)(a5 + 4 * a3) + 20) - *(float *)(*(_DWORD *)(a5 + 4 * a4) + 20));
      v18 = (v26[1] - v31[1]) * v17 + v31[1];
      v20 = (v26[2] - v31[2]) * v17 + v31[2];
      v16 = (v26[3] - v31[3]) * v17 + v31[3];
      v19 = (v26[4] - v31[4]) * v17 + v31[4];
      rf_geomod_face_corner_append((float *)*a6, **(_DWORD **)(a5 + 4 * m), v18, v20, v16, v19);
      ++v25;
    }
  }
  do
  {
    v33 = (_DWORD *)k[5];
    rf_geomod_face_corner_move((_DWORD *)*a7, this, k);
    ++v28;
    k = v33;
  }
  while ( *v33 != v30 );
  rf_geomod_face_corner_move((_DWORD *)*a7, this, v33);
  v29 = v28 + 1;
  for ( n = a3 + 1; n < a4; ++n )
  {
    if ( !rf_geomod_face_contains_shared_vertex((_DWORD *)*a7, **(_DWORD **)(a5 + 4 * n)) )
    {
      v12 = (*(float *)(*(_DWORD *)(a5 + 4 * n) + 20) - *(float *)(*(_DWORD *)(a5 + 4 * a3) + 20))
          / (*(float *)(*(_DWORD *)(a5 + 4 * a4) + 20) - *(float *)(*(_DWORD *)(a5 + 4 * a3) + 20));
      v13 = (v31[1] - v26[1]) * v12 + v26[1];
      v15 = (v31[2] - v26[2]) * v12 + v26[2];
      v11 = (v31[3] - v26[3]) * v12 + v26[3];
      v14 = (v31[4] - v26[4]) * v12 + v26[4];
      rf_geomod_face_corner_append((float *)*a7, **(_DWORD **)(a5 + 4 * n), v13, v15, v11, v14);
      ++v29;
    }
  }
  if ( rf_geomod_face_finalize_geometry(*a6, (float *)this, 0) )
  {
    *(_DWORD *)(*a6 + 72) = *(_DWORD *)(this + 72);
    if ( *(_DWORD *)(this + 72) )
      rf_geomod_spatial_node_face_list_append((int *)(*(_DWORD *)(this + 72) + 24), *a6);
    if ( *(_DWORD *)(this + 68) )
      rf_geomod_room_face_attach(*(float **)(this + 68), *a6);
  }
  else
  {
    rf_solid_face_remove_destroy((int *)solid, (_DWORD *)*a6, 0);
    *a6 = 0;
  }
  if ( rf_geomod_face_finalize_geometry(*a7, (float *)this, 0) )
  {
    *(_DWORD *)(*a7 + 72) = *(_DWORD *)(this + 72);
    if ( *(_DWORD *)(this + 72) )
      rf_geomod_spatial_node_face_list_append((int *)(*(_DWORD *)(this + 72) + 24), *a7);
    if ( *(_DWORD *)(this + 68) )
      rf_geomod_room_face_attach(*(float **)(this + 68), *a7);
  }
  else
  {
    rf_solid_face_remove_destroy((int *)solid, (_DWORD *)*a7, 0);
    *a7 = 0;
  }
  return 1;
}

