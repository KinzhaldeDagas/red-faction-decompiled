// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565F00 rf_model_handle_sample_geometry_aabb_sparse
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): cdecl(handle,outMin,outMax), no default zeroing. Tag1 follows first mesh LOD hierarchy batches56bytes,tag2 uses definition reference-mesh pointer at6736 and its batches. Inner index starts0,increments3 while<batchWORD40,reads XYZ at batch.positionPointer4 +12*index. Initializes outputs only on first batch index0; later first nonempty batch does not initialize. Thus does not visit every count index; lighting566470 instead uses source+36*i with i increment1 over same count. Tag3 uses runtime mesh vertex pointer128:initializes from first mesh vertex0, then for EACH mesh includes only vertices1..definitionMesh DWORD176-1,omitting vertex0 of later meshes. Uses min-ELSE-max point helper. No
// empty/finite/index checks; unsupported/empty paths can leave outputs unchanged, raw return incidental.
int __cdecl rf_model_handle_sample_geometry_aabb_sparse(const void *a1, float *destination, float *a3)
{
  int result; // eax
  int v4; // [esp+Ch] [ebp-9Ch]
  float v5[3]; // [esp+10h] [ebp-98h] BYREF
  float v6[3]; // [esp+1Ch] [ebp-8Ch] BYREF
  float v7[3]; // [esp+28h] [ebp-80h] BYREF
  float v8[3]; // [esp+34h] [ebp-74h] BYREF
  float v9[3]; // [esp+40h] [ebp-68h] BYREF
  float copy_result[3]; // [esp+4Ch] [ebp-5Ch] BYREF
  int j; // [esp+58h] [ebp-50h]
  int v12; // [esp+5Ch] [ebp-4Ch]
  int i; // [esp+60h] [ebp-48h]
  float v14[3]; // [esp+64h] [ebp-44h] BYREF
  int v15; // [esp+70h] [ebp-38h]
  int v16; // [esp+74h] [ebp-34h]
  int ii; // [esp+78h] [ebp-30h]
  int n; // [esp+7Ch] [ebp-2Ch]
  int v19; // [esp+80h] [ebp-28h]
  int m; // [esp+84h] [ebp-24h]
  int v21; // [esp+88h] [ebp-20h]
  int k; // [esp+8Ch] [ebp-1Ch]
  float source[3]; // [esp+90h] [ebp-18h] BYREF
  int definition_pointer; // [esp+9Ch] [ebp-Ch]
  int v25; // [esp+A0h] [ebp-8h]
  const void *v26; // [esp+A4h] [ebp-4h]

  result = (int)a1;
  v26 = a1;
  v4 = *(_DWORD *)a1;
  if ( *(_DWORD *)a1 == 1 )
  {
    v15 = *((_DWORD *)a1 + 1);
    rf_vector3_default_construct_noop(v14);
    result = *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v15 + 76) + 140) + 4) + 12);
    v16 = result;
    for ( i = 0; i < v16; ++i )
    {
      v12 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v15 + 76) + 140) + 4) + 8) + 56 * i;
      for ( j = 0; ; j += 3 )
      {
        result = v12;
        if ( j >= *(unsigned __int16 *)(v12 + 40) )
          break;
        rf_vector3_set_components_thiscall(
          v14,
          *(float *)(*(_DWORD *)(v12 + 4) + 12 * j),
          *(float *)(*(_DWORD *)(v12 + 4) + 12 * j + 4),
          *(float *)(*(_DWORD *)(v12 + 4) + 12 * j + 8));
        if ( !i && !j )
        {
          rf_vector_copy(destination, v6, v14);
          rf_vector_copy(a3, v5, v14);
        }
        rf_aabb_include_point_min_else_max(destination, a3, v14);
      }
    }
  }
  else if ( v4 == 2 )
  {
    definition_pointer = rf_model_handle_get_definition_pointer((int)a1);
    rf_vector3_default_construct_noop(source);
    result = *(_DWORD *)(*(_DWORD *)(definition_pointer + 6736) + 140);
    v25 = *(unsigned __int16 *)(*(_DWORD *)(result + 4) + 12);
    for ( k = 0; k < v25; ++k )
    {
      v21 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(definition_pointer + 6736) + 140) + 4) + 8) + 56 * k;
      for ( m = 0; m < *(unsigned __int16 *)(v21 + 40); m += 3 )
      {
        rf_vector3_set_components_thiscall(
          source,
          *(float *)(*(_DWORD *)(v21 + 4) + 12 * m),
          *(float *)(*(_DWORD *)(v21 + 4) + 12 * m + 4),
          *(float *)(*(_DWORD *)(v21 + 4) + 12 * m + 8));
        if ( !k && !m )
        {
          rf_vector_copy(destination, copy_result, source);
          rf_vector_copy(a3, v9, source);
        }
        rf_aabb_include_point_min_else_max(destination, a3, source);
      }
      result = k + 1;
    }
  }
  else if ( v4 == 3 )
  {
    result = *((_DWORD *)a1 + 1);
    v19 = result;
    if ( *(_DWORD *)(result + 20) )
    {
      for ( n = 0; ; ++n )
      {
        result = v19;
        if ( n >= *(_DWORD *)(*(_DWORD *)(v19 + 8) + 76) )
          break;
        if ( !n )
        {
          rf_vector_copy(destination, v8, *(const float **)(*(_DWORD *)(v19 + 20) + 128));
          rf_vector_copy(a3, v7, *(const float **)(*(_DWORD *)(v19 + 20) + 152 * n + 128));
        }
        if ( *(int *)(*(_DWORD *)(*(_DWORD *)(v19 + 20) + 152 * n) + 176) > 1 )
        {
          for ( ii = 1; ii < *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v19 + 20) + 152 * n) + 176); ++ii )
            rf_aabb_include_point_min_else_max(
              destination,
              a3,
              (float *)(*(_DWORD *)(*(_DWORD *)(v19 + 20) + 152 * n + 128) + 12 * ii));
        }
      }
    }
  }
  return result;
}

