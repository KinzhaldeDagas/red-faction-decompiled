// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562050 rf_model_handle_get_node_transform
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): ECX handle plus outPositionXYZ,outMatrix3,index, RET12. Tag2 reads character node affine then copies rotation/translation; tag1 delegates hierarchy helper5B9840 with index validation. Tag3 index-1 reads FIRST runtime mesh position80/matrix92 from instance array20 without count check. Otherwise decoded kind0 uses runtime mesh152*local+80/92,kind2 point60*local+12 and identity orientation,kind3 dummy40*local+12/quaternion24,kind4 effect164*local+92/quaternion104. Kind1/unknown leaves outputs untouched. No uniform success return: many paths return low byte of copy destination/pointer or kind, unlike tag1 boolean. No index/instance checks added here.
char __thiscall rf_model_handle_get_node_transform(_DWORD *this, float *destination, float *a3, int a4)
{
  char result; // al
  float v6[3]; // [esp+8h] [ebp-78h] BYREF
  float v7[3]; // [esp+14h] [ebp-6Ch] BYREF
  float v8[3]; // [esp+20h] [ebp-60h] BYREF
  float v9[3]; // [esp+2Ch] [ebp-54h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-48h] BYREF
  int v11; // [esp+44h] [ebp-3Ch] BYREF
  int v12; // [esp+48h] [ebp-38h] BYREF
  int v13; // [esp+4Ch] [ebp-34h] BYREF
  float v14[12]; // [esp+50h] [ebp-30h] BYREF

  if ( *this == 2 )
  {
    rf_character_instance_get_node_transform((void *)*(this + 1), v14, a4);
    rf_affine48_copy_rotation_return_self(v14, a3);
    return (unsigned __int8)rf_affine48_copy_translation_return_self(v14, destination);
  }
  else
  {
    result = (char)this;
    if ( *this == 1 )
    {
      return rf_mesh_get_hierarchy_node_transform((_DWORD *)*(this + 1), a4, destination, (int)a3);
    }
    else if ( *this == 3 )
    {
      if ( a4 == -1 )
      {
        rf_vector_copy(destination, copy_result, (const float *)(*(_DWORD *)(*(this + 1) + 20) + 80));
        return rf_matrix3_copy(a3, (const float *)(*(_DWORD *)(*(this + 1) + 20) + 92));
      }
      else
      {
        rf_scene_definition_decode_flat_object_index((_DWORD *)*(this + 2), a4, &v13, &v12, &v11);
        result = v13;
        switch ( v13 )
        {
          case 0:
            rf_vector_copy(destination, v9, (const float *)(*(_DWORD *)(*(this + 1) + 20) + 152 * v12 + 80));
            result = rf_matrix3_copy(a3, (const float *)(*(_DWORD *)(*(this + 1) + 20) + 152 * v12 + 92));
            break;
          case 2:
            rf_vector_copy(destination, v8, (const float *)(*(_DWORD *)(*(this + 1) + 24) + 60 * v12 + 12));
            result = (unsigned __int8)rf_identity_orientation_matrix(a3);
            break;
          case 3:
            rf_vector_copy(destination, v7, (const float *)(*(_DWORD *)(*(this + 1) + 32) + 40 * v12 + 12));
            result = (unsigned __int8)rf_quaternion_to_matrix3_rows(
                                        (float *)(*(_DWORD *)(*(this + 1) + 32) + 40 * v12 + 24),
                                        a3);
            break;
          case 4:
            rf_vector_copy(destination, v6, (const float *)(*(_DWORD *)(*(this + 1) + 28) + 164 * v12 + 92));
            result = (unsigned __int8)rf_quaternion_to_matrix3_rows(
                                        (float *)(*(_DWORD *)(*(this + 1) + 28) + 164 * v12 + 104),
                                        a3);
            break;
          default:
            return result;
        }
      }
    }
  }
  return result;
}

