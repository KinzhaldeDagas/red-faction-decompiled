// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00554A60 rf_solid_duplicate_face_with_new_vertices
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Allocates face using source metadata40, clears new corner head64, then duplicates EACH source corner vertex into the solid and copies all four UV floats into corresponding new corner. Writes each original vertex+28 scratch DWORD to its new vertex pointer, overwriting it for repeated source vertices. Finalizes new face ignoring status and returns it; no explicit room attachment or selection append.
unsigned int *__thiscall rf_solid_duplicate_face_with_new_vertices(_DWORD *this, int a2)
{
  int v3; // [esp+10h] [ebp-14h]
  float *v5; // [esp+18h] [ebp-Ch]
  int i; // [esp+1Ch] [ebp-8h]
  unsigned int *link; // [esp+20h] [ebp-4h]

  link = rf_solid_face_allocate_link(this, (const unsigned int *)(a2 + 40));
  link[16] = 0;
  for ( i = *(_DWORD *)(a2 + 64); i; i = v3 )
  {
    v5 = rf_solid_vertex_copy_append(this, *(float **)i);
    rf_geomod_face_corner_append(
      (float *)link,
      (int)v5,
      *(float *)(i + 4),
      *(float *)(i + 8),
      *(float *)(i + 12),
      *(float *)(i + 16));
    *(_DWORD *)(*(_DWORD *)i + 28) = v5;
    if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a2 + 64) )
      v3 = 0;
    else
      v3 = *(_DWORD *)(i + 20);
  }
  rf_geomod_face_finalize_geometry((int)link, nullptr, 0);
  return link;
}

