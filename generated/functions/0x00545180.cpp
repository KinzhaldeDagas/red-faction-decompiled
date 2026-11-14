// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00545180 rf_solid_import_first_mesh_batch_triangles
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl mesh filename. Loads cached .v3m resource through5B7F80;NULL returnsNULL. Selects FIRST mesh pointer from resource metadata84+4,then geometry pointer140,LOD pointer+4,and FIRST batch pointer+8. No positive mesh/LOD/batch-count or nested-pointer validation;ignores other batches/LODs/materials. Allocates888-byte solid519240 and temporary DWORD vertex-pointer array sized4*unsignedWORD batch40. Copies each12-byte position from batch+4 through51A170 with optional argumentNULL; no normals/UVs/materials/remap transform copied. For each unsignedWORD face count42,reads8-byte record at batch+20,uses3 SIGNED16 vertex indices without bounds checks,creates linked face from
// default24-byte metadata,appends3 corners with all4 UV floats0,finalizes geometry. Walks every face edge and calls53AB70 to count incident uses;tracks min/max locally but NEVER tests/publishes those values,so no closedness/manifold rejection occurs. Recomputes bounds,allocates460-byte room using solid and bounds+72/+84,attaches every face,rebuilds room face tree,frees temporary vertex-pointer array,returns solid. No generated-UV projection call in this importer,no cached resource release,no centralized allocation/error rollback. Corrected19FF0 thiscall prototype exposes actual ECX solid receiver at face creation.
_DWORD *__cdecl rf_solid_import_first_mesh_batch_triangles(char *Str)
{
  float *v2; // eax
  int *v3; // [esp+14h] [ebp-88h]
  int v4; // [esp+18h] [ebp-84h]
  void **v5; // [esp+1Ch] [ebp-80h]
  void *room; // [esp+24h] [ebp-78h]
  void **v7; // [esp+30h] [ebp-6Ch]
  int v8; // [esp+38h] [ebp-64h]
  int k; // [esp+3Ch] [ebp-60h]
  float *link; // [esp+40h] [ebp-5Ch]
  __int16 *v11; // [esp+44h] [ebp-58h]
  unsigned int metadata[6]; // [esp+48h] [ebp-54h] BYREF
  float v13[3]; // [esp+60h] [ebp-3Ch] BYREF
  int v14; // [esp+6Ch] [ebp-30h]
  int v15; // [esp+70h] [ebp-2Ch]
  float *v16; // [esp+74h] [ebp-28h]
  int v17; // [esp+78h] [ebp-24h]
  int j; // [esp+7Ch] [ebp-20h]
  void *solid; // [esp+80h] [ebp-1Ch]
  _DWORD *v20; // [esp+84h] [ebp-18h]
  int i; // [esp+88h] [ebp-14h]
  char *v22; // [esp+8Ch] [ebp-10h]
  int v23; // [esp+98h] [ebp-4h]

  v22 = sub_5B7F80(Str, 0, (int)byte_98967F);
  if ( !v22 )
    return nullptr;
  v17 = *(_DWORD *)(*((_DWORD *)v22 + 21) + 4);
  v7 = (void **)operator new(0x378u);
  v23 = 0;
  if ( v7 )
    v5 = rf_solid888_construct(v7);
  else
    v5 = nullptr;
  v23 = -1;
  solid = v5;
  v20 = operator new(4 * *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v17 + 140) + 4) + 8) + 40));
  for ( i = 0; i < *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v17 + 140) + 4) + 8) + 40); ++i )
  {
    rf_vector3_default_construct_noop(v13);
    v13[0] = *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v17 + 140) + 4) + 8) + 4) + 12 * i);
    v13[1] = *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v17 + 140) + 4) + 8) + 4) + 12 * i + 4);
    v13[2] = *(float *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v17 + 140) + 4) + 8) + 4) + 12 * i + 8);
    v2 = rf_solid_vertex_find_or_copy_append(solid, v13, nullptr);
    v20[i] = v2;
  }
  for ( i = 0; i < *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v17 + 140) + 4) + 8) + 42); ++i )
  {
    v11 = (__int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v17 + 140) + 4) + 8) + 20) + 8 * i);
    rf_geomod_face_metadata_init(metadata);
    link = (float *)rf_solid_face_allocate_link(solid, metadata);
    rf_geomod_face_corner_append(link, v20[*v11], 0.0, 0.0, 0.0, 0.0);
    rf_geomod_face_corner_append(link, v20[v11[1]], 0.0, 0.0, 0.0, 0.0);
    rf_geomod_face_corner_append(link, v20[v11[2]], 0.0, 0.0, 0.0, 0.0);
    rf_geomod_face_finalize_geometry((int)link, nullptr, 0);
  }
  v14 = -1;
  v15 = -1;
  for ( j = rf_receiver_get_first_dword((char *)solid + 112); j; j = rf_solid_face_next_link(j) )
  {
    for ( k = *(_DWORD *)(j + 64); k; k = v4 )
    {
      v8 = rf_geomod_count_incident_edge_uses((int)solid, *(_DWORD *)k, **(_DWORD **)(k + 20));
      if ( v14 == -1 || v8 < v14 )
        v14 = v8;
      if ( v15 == -1 || v8 > v15 )
        v15 = v8;
      if ( *(_DWORD *)(k + 20) == *(_DWORD *)(j + 64) )
        v4 = 0;
      else
        v4 = *(_DWORD *)(k + 20);
    }
  }
  rf_solid_finalize_bounds((float *)solid);
  room = operator new(0x1CCu);
  v23 = 1;
  if ( room )
    v3 = (int *)rf_room460_construct_register(room, solid, (const float *)solid + 18, (const float *)solid + 21);
  else
    v3 = nullptr;
  v23 = -1;
  v16 = (float *)v3;
  for ( j = rf_receiver_get_first_dword((char *)solid + 112); j; j = rf_solid_face_next_link(j) )
    rf_geomod_room_face_attach(v16, j);
  rf_room_face_spatial_tree_rebuild((int *)v16);
  operator delete(v20);
  return solid;
}

