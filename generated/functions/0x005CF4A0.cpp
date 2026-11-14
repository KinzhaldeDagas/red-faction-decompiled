// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CF4A0 rf_v3c_asset_collide_all_static_meshes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Optional reset only byte EXACT1 initializes hit fraction1/tag0. If query flags2 clear,mutates input start48 by subtracting reference position0 and row-transforming through matrix12;row-transforms delta60,sets flags2. Walks mesh count at asset+72 via5B8D70,invokes static per-mesh collision with reset0,ORs hits. Query flag1 returns on FIRST accepted hit in mesh/triangle traversal,not guaranteed global nearest. Otherwise shared fraction limits later candidates. Does not restore original start/delta/flag or transform hit back to world coordinates;no count/index/pointer guards.
char __thiscall rf_v3c_asset_collide_all_static_meshes(void *this, void *rhs, void *a3, unsigned __int8 a4)
{
  float *v4; // eax
  float *v5; // eax
  int mesh_count; // eax
  char v7; // bl
  float v10[3]; // [esp+8h] [ebp-38h] BYREF
  float v11[3]; // [esp+14h] [ebp-2Ch] BYREF
  float copy_result[3]; // [esp+20h] [ebp-20h] BYREF
  float out_vector[3]; // [esp+2Ch] [ebp-14h] BYREF
  int i; // [esp+38h] [ebp-8h]
  char v15; // [esp+3Fh] [ebp-1h]

  v15 = 0;
  if ( a4 == 1 )
  {
    *(float *)a3 = 1.0;
    *((_DWORD *)a3 + 7) = 0;
  }
  if ( (*((_DWORD *)rhs + 19) & 2) == 0 )
  {
    v4 = rf_vector_subtract((const float *)rhs + 12, out_vector, (const float *)rhs);
    rf_vector_copy((float *)rhs + 12, copy_result, v4);
    rf_matrix3_inverse_rotate_vector((float *)rhs + 12, (float *)rhs + 3);
    v5 = rf_vector3_transform_by_matrix_rows((float *)rhs + 15, v11, (float *)rhs + 3);
    rf_vector_copy((float *)rhs + 15, v10, v5);
    *((_DWORD *)rhs + 19) |= 2u;
  }
  for ( i = 0; ; ++i )
  {
    mesh_count = rf_v3c_asset_get_mesh_count(this);
    if ( i >= mesh_count )
      break;
    v7 = v15;
    v15 = rf_v3c_asset_collide_static_mesh(this, i, rhs, a3, 0) | v7;
    if ( v15 && (*((_DWORD *)rhs + 19) & 1) != 0 )
      return 1;
  }
  return v15;
}

