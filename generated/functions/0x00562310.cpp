// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562310 rf_model_handle_get_named_sphere_position_radius
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag1/2 only, returns byte0 on index<0 or index>=count96. Sphere record44 bytes:name at0,bone/node index24,local XYZ28,radius40. Tag1 copies XYZ/radius directly from record array100. Tag2 obtains character node affine for sphere node24 and transforms local center into animated coordinates; radius copied unchanged, not scaled by affine. Unsupported tags/failure leave outputs untouched; no null/output validation.
char __thiscall rf_model_handle_get_named_sphere_position_radius(_DWORD *this, int a2, float *destination, float *a4)
{
  float *v4; // eax
  float v7[3]; // [esp+8h] [ebp-58h] BYREF
  float copy_result[3]; // [esp+14h] [ebp-4Ch] BYREF
  float v9[3]; // [esp+20h] [ebp-40h] BYREF
  float v10[12]; // [esp+2Ch] [ebp-34h] BYREF
  _DWORD *v11; // [esp+5Ch] [ebp-4h]

  v11 = nullptr;
  if ( *this == 1 )
  {
    v11 = (_DWORD *)*(this + 1);
    if ( a2 >= 0 && a2 < v11[24] )
    {
      rf_vector_copy(destination, v7, (const float *)(v11[25] + 44 * a2 + 28));
      *a4 = *(float *)(v11[25] + 44 * a2 + 40);
      return 1;
    }
  }
  else if ( *this == 2 )
  {
    v11 = rf_vector3_default_construct_noop((void *)(*(this + 2) + 6592));
    if ( a2 >= 0 && a2 < v11[24] )
    {
      rf_character_instance_get_node_transform((void *)*(this + 1), v10, *(_DWORD *)(v11[25] + 44 * a2 + 24));
      v4 = rf_affine3x4_transform_point(v10, v9, (float *)(v11[25] + 44 * a2 + 28));
      rf_vector_copy(destination, copy_result, v4);
      *a4 = *(float *)(v11[25] + 44 * a2 + 40);
      return 1;
    }
  }
  return 0;
}

