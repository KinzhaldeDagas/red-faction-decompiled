// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00549090 rf_geomod_regular_polygon_face_create
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl signed sideCount,radius,Y plane. Initializes default6-DWORD metadata and allocates standalone face,not yet linked to a solid. For i=0..sideCount-1 computes float angle=(float2pi/sideCount)*i using literal6.283185482025146,position(cos(angle)*radius,Y,sin(angle)*radius),allocates/copies geomod vertex and appends corner with all4 UV values0. Finalizes face with args0,0 and returns face pointer. No minimum3-side check,radius/finite/allocation test or generated-UV projection. Nonpositive sideCount skips per-vertex loop but still finalizes empty face;division occurs inside loop,not before it. Positive angular order is literal;normal follows finalizer convention.
float *__cdecl rf_geomod_regular_polygon_face_create(int a1, float a2, float a3)
{
  float v4; // [esp+10h] [ebp-3Ch]
  float v5; // [esp+14h] [ebp-38h]
  float v6; // [esp+18h] [ebp-34h]
  float *v7; // [esp+1Ch] [ebp-30h]
  float v8[3]; // [esp+20h] [ebp-2Ch] BYREF
  float *v9; // [esp+2Ch] [ebp-20h]
  int i; // [esp+30h] [ebp-1Ch]
  _DWORD v11[6]; // [esp+34h] [ebp-18h] BYREF

  rf_vector3_default_construct_noop(v8);
  rf_geomod_face_metadata_init(v11);
  v9 = (float *)rf_geomod_face_allocate(v11);
  for ( i = 0; i < a1; ++i )
  {
    v6 = 6.283185482025146 / (double)a1 * (double)i;
    v5 = rf_sin_float(v6) * a2;
    v4 = rf_cos_float(v6) * a2;
    rf_vector3_set_components_thiscall(v8, v4, a3, v5);
    v7 = rf_geomod_vertex_copy_allocate(v8);
    rf_geomod_face_corner_append(v9, (int)v7, 0.0, 0.0, 0.0, 0.0);
  }
  rf_geomod_face_finalize_geometry((int)v9, nullptr, 0);
  return v9;
}

