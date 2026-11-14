// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051B250 rf_geomod_component_bounds_build
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Thiscall solid,label,outMin,outMax RET12. Iterate face list112, include every face if label==-1 otherwise exact DWORD44 match. First included face copies bounds16/28 to outputs; subsequent faces union componentwise. ALWAYS subtract F32 epsilon0.000099999997 from each min and add to each max after traversal. If none matched, incoming output contents are expanded without initialization, not a zero/empty sentinel. Returns outMax through final in-place-add helper. Reads face AABBs, does not recompute from corners or change stored solid bounds.
float *__thiscall rf_geomod_component_bounds_build(char *this, int a2, float *destination, float *a4)
{
  float v5[3]; // [esp+8h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+14h] [ebp-14h] BYREF
  char v7; // [esp+23h] [ebp-5h]
  int i; // [esp+24h] [ebp-4h]

  v7 = 0;
  for ( i = rf_receiver_get_first_dword(this + 112); i; i = rf_solid_face_next_link(i) )
  {
    if ( a2 == -1 || *(_DWORD *)(i + 44) == a2 )
    {
      if ( v7 )
      {
        rf_aabb_union_componentwise_in_place(destination, a4, (const float *)(i + 16), (const float *)(i + 28));
      }
      else
      {
        v7 = 1;
        rf_vector_copy(destination, copy_result, (const float *)(i + 16));
        rf_vector_copy(a4, v5, (const float *)(i + 28));
      }
    }
  }
  rf_vector3_subtract_scalar_in_place(destination, 0.000099999997);
  return rf_vector3_add_scalar_in_place(a4, 0.000099999997);
}

