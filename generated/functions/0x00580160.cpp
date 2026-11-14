// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580160 rf_model_instance_render_with_lod_translation
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Reads selected mesh through instance+144. If flags DWORD bit0x40 set,uses supplied position unchanged;otherwise reads selected mesh LOD-table translation,rotates by supplied orientation,adds supplied position. Calls model renderer on mesh+140 with resulting position,orientation,second DWORD argument,and flags pointer. No NULL/selected mesh validation or stored instance-position mutation.
void __cdecl rf_model_instance_render_with_lod_translation(int a1, int a2, float *source, float *a4, _DWORD *a5)
{
  float *lod_table_translation; // eax
  float v6[3]; // [esp+0h] [ebp-30h] BYREF
  float v7[3]; // [esp+Ch] [ebp-24h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-18h] BYREF
  float destination[3]; // [esp+24h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  if ( (*a5 & 0x40) != 0 )
  {
    rf_vector_copy(destination, copy_result, source);
  }
  else
  {
    lod_table_translation = rf_model_mesh144_get_lod_table_translation(*(_DWORD **)(a1 + 144), v7);
    rf_vector_copy(destination, v6, lod_table_translation);
    rf_vector_rotate_by_matrix3(destination, a4);
    rf_vector_accumulate(destination, source);
  }
  rf_model_render_select_lod_and_skin(*(int **)(*(_DWORD *)(a1 + 144) + 140), (int)destination, (int)a4, a2, (int)a5);
}

