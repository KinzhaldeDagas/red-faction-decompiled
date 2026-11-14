// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005326D0 rf_geomod_room_first_unambiguous_ray_is_class1
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, face query setup/classification,corner-limit splitting and pool lifecycle,original ECX/stack flow and PE bytes): Cdecl room pointer, caller pops4. Compute F32 scale as sequential sum of room AABB extents(max20-min8,max24-min12,max28-min16). Iterate room face-list40 through face+92. For each face, start=arithmetic corner centroid+face normal*scale; direction=-face normal, query scalar=F32(scale+double1), source=NULL, flagLOWBYTE0. No normal normalization. Accumulate ALL room faces until first AL nonzero retry request; that seed is abandoned and next outer face tried. For first seed with no retry, return query class EXACTLY1 immediately, even if class2/no hit or3/4 would make result false; does not seek a later favorable seed. Empty list or all ambiguous seeds return AL0. Does not alter room geometry or prove
// manifoldness. In caller516170 this predicate is applied only when room BYTE0 is zero before changing room classification.
bool __cdecl rf_geomod_room_first_unambiguous_ray_is_class1(float *a1)
{
  float *v1; // eax
  float *v2; // eax
  float v4; // [esp+8h] [ebp-9Ch]
  float copy_result[3]; // [esp+Ch] [ebp-98h] BYREF
  float v6[3]; // [esp+18h] [ebp-8Ch] BYREF
  float scaled_result[3]; // [esp+24h] [ebp-80h] BYREF
  float lhs[3]; // [esp+34h] [ebp-70h] BYREF
  char v9; // [esp+43h] [ebp-61h]
  int i; // [esp+44h] [ebp-60h]
  char v11[60]; // [esp+48h] [ebp-5Ch] BYREF
  float sum_result[3]; // [esp+84h] [ebp-20h] BYREF
  float *vector; // [esp+90h] [ebp-14h]
  float destination[3]; // [esp+94h] [ebp-10h] BYREF
  float scalar; // [esp+A0h] [ebp-4h]

  scalar = 0.0;
  scalar = a1[5] - a1[2] + (float)0.0;
  scalar = a1[6] - a1[3] + scalar;
  scalar = a1[7] - a1[4] + scalar;
  rf_vector3_default_construct_noop(destination);
  for ( vector = (float *)rf_receiver_get_first_dword(a1 + 10);
        vector;
        vector = (float *)rf_face_next_room_link((int)vector) )
  {
    rf_vector3_default_construct_noop(lhs);
    rf_geomod_face_centroid(vector, lhs);
    v1 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
    rf_vector_add(lhs, sum_result, v1);
    rf_geomod_face_ray_query_init(v11);
    v2 = rf_vector_negate(vector, v6);
    rf_vector_copy(destination, copy_result, v2);
    v4 = scalar + 1.0;
    rf_geomod_face_ray_query_begin((int)v11, 0, sum_result, destination, v4, 0);
    v9 = 1;
    for ( i = rf_receiver_get_first_dword(a1 + 10); i; i = rf_face_next_room_link(i) )
    {
      if ( rf_geomod_face_ray_query_accumulate((int)v11, i) )
      {
        v9 = 0;
        break;
      }
    }
    if ( v9 )
      return rf_geomod_face_ray_query_class_get((int)v11) == 1;
  }
  return 0;
}

