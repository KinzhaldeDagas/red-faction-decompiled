// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051CED0 rf_solid_extrude_one_face_by_vector
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall solid,face,translation3f,RET8. For each circular corner,allocates/appends NEW vertex=old position+translation,removes face from old vertex incident-face array32,uniquely appends face to new incident list,stores old vertex pointer at new+28,and replaces corner vertex. Finalizes moving face and generates UVs. Then each edge creates linked quad using copied metadata face+40:current new,current old,next old,next new. Primary UVs copied from corresponding moving corners;secondary UVs0. Finalizes/projects each side. Old vertices remain in solid;does not clone moving cap or delete old ring,rebuild bounds/room tree,select new faces,validate ring/allocation or roll
// back partial extrusion. Normal ordinary return0 after iterator ends;no success status established.
int __thiscall rf_solid_extrude_one_face_by_vector(_DWORD *this, int a2, float *rhs)
{
  int result; // eax
  int v4; // [esp+10h] [ebp-28h]
  int v5; // [esp+14h] [ebp-24h]
  unsigned int *link; // [esp+1Ch] [ebp-1Ch]
  float *v8; // [esp+20h] [ebp-18h]
  float sum_result[3]; // [esp+24h] [ebp-14h] BYREF
  float *lhs; // [esp+30h] [ebp-8h]
  int i; // [esp+34h] [ebp-4h]

  for ( i = *(_DWORD *)(a2 + 64); i; i = v5 )
  {
    lhs = *(float **)i;
    rf_vector_add(lhs, sum_result, rhs);
    v8 = rf_solid_vertex_copy_append(this, sum_result);
    rf_pointer_array_remove_first((int *)lhs + 8, a2);
    rf_pointer_array_append_unique((_DWORD *)v8 + 8, a2);
    *((_DWORD *)v8 + 7) = lhs;
    *(_DWORD *)i = v8;
    if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a2 + 64) )
      v5 = 0;
    else
      v5 = *(_DWORD *)(i + 20);
  }
  rf_geomod_face_finalize_geometry(a2, 0, 0);
  rf_geomod_generated_uv_project(a2);
  result = *(_DWORD *)(a2 + 64);
  for ( i = result; i; i = v4 )
  {
    link = rf_solid_face_allocate_link(this, (const unsigned int *)(a2 + 40));
    rf_geomod_face_corner_append(link, *(_DWORD *)i, *(float *)(i + 4), *(float *)(i + 8), 0.0, 0.0);
    rf_geomod_face_corner_append(link, *(_DWORD *)(*(_DWORD *)i + 28), *(float *)(i + 4), *(float *)(i + 8), 0.0, 0.0);
    rf_geomod_face_corner_append(
      link,
      *(_DWORD *)(**(_DWORD **)(i + 20) + 28),
      *(float *)(*(_DWORD *)(i + 20) + 4),
      *(float *)(*(_DWORD *)(i + 20) + 8),
      0.0,
      0.0);
    rf_geomod_face_corner_append(
      link,
      **(_DWORD **)(i + 20),
      *(float *)(*(_DWORD *)(i + 20) + 4),
      *(float *)(*(_DWORD *)(i + 20) + 8),
      0.0,
      0.0);
    rf_geomod_face_finalize_geometry((int)link, 0, 0);
    rf_geomod_generated_uv_project((int)link);
    if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a2 + 64) )
      v4 = 0;
    else
      v4 = *(_DWORD *)(i + 20);
    result = v4;
  }
  return result;
}

