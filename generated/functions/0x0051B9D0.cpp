// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051B9D0 rf_geomod_split_vertex_on_first_face_edge
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Cdecl solid(unused directly),existing split vertex,face; three stack args caller pop12, AL bool. Reject if face already contains vertex pointer or plane-classification530740 !=2. Iterate ORIGINAL circular edges in order; normalize(next.position-current.position), store returned length F32, project split-current onto direction and store scalar F32. Require ORDERED scalar>double epsilon and scalar<length-epsilon, strict both; then build projected point via F32 vector helpers and require ORDERED F32 distance(split,projected)<same epsilon. Epsilon PE double0.00009999999747378752. First qualifying edge invokes51AAA0 on current,next,split and returns1 UNCONDITIONALLY, even if common-incidence/bit8 guards
// cause zero actual insertions. No endpoint welding or vertex allocation; plane classifier NaN can report2 but ordered edge tests reject unordered scalar/distance. Return0 if no edge qualifies. Solid argument only forwarded as ECX to propagation; no direct solid use.
char __cdecl rf_geomod_split_vertex_on_first_face_edge(int a1, float *a2, _DWORD *a3)
{
  float *v4; // eax
  int v5; // [esp+4h] [ebp-60h]
  float scaled_result[3]; // [esp+8h] [ebp-5Ch] BYREF
  float sum_result[3]; // [esp+14h] [ebp-50h] BYREF
  float v8; // [esp+20h] [ebp-44h]
  float v9[3]; // [esp+24h] [ebp-40h] BYREF
  float v10[3]; // [esp+30h] [ebp-34h] BYREF
  float scalar; // [esp+3Ch] [ebp-28h]
  float out_vector[3]; // [esp+40h] [ebp-24h] BYREF
  float *lhs; // [esp+4Ch] [ebp-18h]
  float *rhs; // [esp+50h] [ebp-14h]
  int v15; // [esp+54h] [ebp-10h]
  float length; // [esp+58h] [ebp-Ch]
  int v17; // [esp+5Ch] [ebp-8h]
  int i; // [esp+60h] [ebp-4h]

  if ( rf_geomod_face_contains_shared_vertex(a3, (int)a2) )
    return 0;
  v17 = rf_geomod_point_classify_against_face_plane(a2, a3);
  if ( v17 != 2 )
    return 0;
  for ( i = a3[16]; i; i = v15 )
  {
    if ( *(_DWORD *)(i + 20) == a3[16] )
      v5 = 0;
    else
      v5 = *(_DWORD *)(i + 20);
    v15 = v5;
    rhs = *(float **)i;
    lhs = **(float ***)(i + 20);
    rf_vector_subtract(lhs, out_vector, rhs);
    length = rf_vector_normalize_get_length(out_vector);
    rf_vector_subtract(a2, v10, rhs);
    scalar = rf_vector_dot(out_vector, v10);
    if ( scalar > 0.00009999999747378752 && scalar < length - 0.00009999999747378752 )
    {
      v4 = rf_vector_multiply_scalar(out_vector, scaled_result, scalar);
      rf_vector_add(rhs, sum_result, v4);
      rf_vector_subtract(a2, v9, sum_result);
      v8 = rf_vector3_length(v9);
      if ( v8 < 0.00009999999747378752 )
      {
        rf_geomod_split_vertex_propagate_to_incident_faces(rhs, lhs, a2);
        return 1;
      }
    }
  }
  return 0;
}

