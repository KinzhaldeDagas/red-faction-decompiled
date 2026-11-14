// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005559D0 rf_solid_subdivide_face_centroid_fan
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Thiscall solid,face,keepOriginalByte,selectDerivedByte. If count>=3,averages ALL corner worldXYZ equally (arithmetic vertex centroid,not area-weighted),appends new solid vertex,then for each source edge allocates triangle(centroid,current,next). Supplies ZERO for all4 UV components of every new corner before finalization. Calls51D300(new,source,selectDerived);if keepOriginal==0 removes original,else retains it. No convexity/centroid-inside guarantee,UV interpolation or rollback/unused-centroid cleanup on derived failure. EAX incidental helper/iterator result,not new vertex/face count.
float *__thiscall rf_solid_subdivide_face_centroid_fan(_DWORD *this, int a2, char a3, char a4)
{
  float *result; // eax
  float *v5; // eax
  int v6; // [esp+10h] [ebp-44h]
  float scalar; // [esp+14h] [ebp-40h]
  int v8; // [esp+18h] [ebp-3Ch]
  float copy_result[3]; // [esp+20h] [ebp-34h] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-28h] BYREF
  float *link; // [esp+38h] [ebp-1Ch]
  int v13; // [esp+3Ch] [ebp-18h]
  float destination[3]; // [esp+40h] [ebp-14h] BYREF
  int v15; // [esp+4Ch] [ebp-8h]
  int i; // [esp+50h] [ebp-4h]

  result = (float *)rf_geomod_face_corner_count((_DWORD *)a2);
  v13 = (int)result;
  if ( (int)result >= 3 )
  {
    rf_vector3_default_construct_noop(destination);
    rf_vector3_zero_return_destination(destination);
    for ( i = *(_DWORD *)(a2 + 64); i; i = v8 )
    {
      rf_vector_accumulate(destination, *(float **)i);
      if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a2 + 64) )
        v8 = 0;
      else
        v8 = *(_DWORD *)(i + 20);
    }
    scalar = 1.0 / (double)v13;
    v5 = rf_vector_multiply_scalar(destination, scaled_result, scalar);
    rf_vector_copy(destination, copy_result, v5);
    result = rf_solid_vertex_copy_append(this, destination);
    v15 = (int)result;
    for ( i = *(_DWORD *)(a2 + 64); i; i = v6 )
    {
      link = (float *)rf_solid_face_allocate_link(this, (const unsigned int *)(a2 + 40));
      rf_geomod_face_corner_append(link, v15, 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_corner_append(link, *(_DWORD *)i, 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_corner_append(link, **(_DWORD **)(i + 20), 0.0, 0.0, 0.0, 0.0);
      rf_solid_finalize_derived_face_attach_and_select(this, link, a2, a4);
      result = (float *)i;
      if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a2 + 64) )
      {
        v6 = 0;
      }
      else
      {
        result = (float *)i;
        v6 = *(_DWORD *)(i + 20);
      }
    }
    if ( !a3 )
      return (float *)rf_solid_face_remove_destroy(this, (_DWORD *)a2, 0);
  }
  return result;
}

