// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005324F0 rf_geomod_component_shell_validate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shared-edge insertion,component classification/extraction,finite epsilon tests,original ECX/stack flow and PE bytes): Thiscall solid,label RET4 bool. Build epsilon-expanded bounds via51B250(label) then F32-accumulate scalar=(maxX-minX)+0,(maxY-minY)+scalar,(maxZ-minZ)+scalar; L1 extent, not Euclidean diagonal. Iterate solid faces112; seed eligible when label<=-1 OR exact face44 match (different from bounds helper whose wildcard is only==-1). Compute corner centroid, origin=centroid+faceNormal*scalar, direction=-faceNormal (no normalization here), begin60-byte ray context flag0,maxDistance=float(scalar+1),last0. Iterate same label selection and call face ray accumulator; any true return marks seed ambiguous and tries next seed. On FIRST seed with no accumulator true, IMMEDIATELY return(class_get==1), including false for
// another class; does NOT continue after unambiguous non-class1. If no seeds or all ambiguous return0. This verifies engine ray classification policy, not a general mathematical proof of watertightness; no edge-manifold enumeration. No matching bounds leaves no-op-constructed vector contents uninitialized before expansion. No geometry changes.
bool __thiscall rf_geomod_component_shell_validate(char *this, int a2)
{
  float *v2; // eax
  float *v3; // eax
  float v5; // [esp+8h] [ebp-B8h]
  float copy_result[3]; // [esp+10h] [ebp-B0h] BYREF
  float v8[3]; // [esp+1Ch] [ebp-A4h] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-98h] BYREF
  float lhs[3]; // [esp+38h] [ebp-88h] BYREF
  char v11; // [esp+47h] [ebp-79h]
  int i; // [esp+48h] [ebp-78h]
  char v13[60]; // [esp+4Ch] [ebp-74h] BYREF
  float sum_result[3]; // [esp+88h] [ebp-38h] BYREF
  float *vector; // [esp+94h] [ebp-2Ch]
  float v16[3]; // [esp+98h] [ebp-28h] BYREF
  float destination[3]; // [esp+A4h] [ebp-1Ch] BYREF
  float scalar; // [esp+B0h] [ebp-10h]
  float v19[3]; // [esp+B4h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v19);
  rf_vector3_default_construct_noop(v16);
  rf_geomod_component_bounds_build(this, a2, v19, v16);
  scalar = v16[0] - v19[0] + (float)0.0;
  scalar = v16[1] - v19[1] + scalar;
  scalar = v16[2] - v19[2] + scalar;
  rf_vector3_default_construct_noop(destination);
  for ( vector = (float *)rf_receiver_get_first_dword(this + 112);
        vector;
        vector = (float *)rf_solid_face_next_link((int)vector) )
  {
    if ( a2 <= -1 || *((_DWORD *)vector + 11) == a2 )
    {
      rf_vector3_default_construct_noop(lhs);
      rf_geomod_face_centroid(vector, lhs);
      v2 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
      rf_vector_add(lhs, sum_result, v2);
      rf_geomod_face_ray_query_init(v13);
      v3 = rf_vector_negate(vector, v8);
      rf_vector_copy(destination, copy_result, v3);
      v5 = scalar + 1.0;
      rf_geomod_face_ray_query_begin((int)v13, 0, sum_result, destination, v5, 0);
      v11 = 1;
      for ( i = rf_receiver_get_first_dword(this + 112); i; i = rf_solid_face_next_link(i) )
      {
        if ( (a2 <= -1 || *(_DWORD *)(i + 44) == a2) && rf_geomod_face_ray_query_accumulate((int)v13, i) )
        {
          v11 = 0;
          break;
        }
      }
      if ( v11 )
        return rf_geomod_face_ray_query_class_get((int)v13) == 1;
    }
  }
  return 0;
}

