// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E22D0 rf_player_add_riotshield_impact_mesh_decal
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player view/movement/light/shield/score contracts and owned RFString native ABI): Cdecl(player,shield clutter,optional world hitpoint). Construct80-byte mesh-decal request; find first zero entry among25 decal pointers at player+4328, with no eviction. Full array, NULL hitpoint or missing first model-container from player model handle+52 skips projection; EAX then incidental, not a reliable decal pointer. Inverse-rotate(hitpoint-shield position60) by shield matrix72. Seed direction=(1,0,0), end=local point+2X, start=end-2X (separate F32 operations). Radius=random F32[0.055,0.08]; random angle0..359 multiplied by stored double radians factor then rounded F32. Normalize hint(0,-sin,cos), forward=normalize(end-start), right=cross(forward,hint),up=cross(right,forward). Owner=request0, texture4=662E34 RiotShieldHit.tga
// bitmap, radius8,start12,end24,basis36/48/60,flags72=6, selector76=662E30 loaded from riotshield1.tga. Project prism514780; store returned collection pointer orNULL into chosen slot. No normalization/finite failure guards. Sole damage caller414EF0 supplies player,clutter,point after player mask0x10 gate.
char *__cdecl rf_player_add_riotshield_impact_mesh_decal(int a1, int a2, float *source)
{
  char *result; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float v10[3]; // [esp+Ch] [ebp-100h] BYREF
  float v11[3]; // [esp+18h] [ebp-F4h] BYREF
  float v12[3]; // [esp+24h] [ebp-E8h] BYREF
  float v13[3]; // [esp+30h] [ebp-DCh] BYREF
  float v14[3]; // [esp+3Ch] [ebp-D0h] BYREF
  float v15[3]; // [esp+48h] [ebp-C4h] BYREF
  float v16[3]; // [esp+54h] [ebp-B8h] BYREF
  float out_vector[3]; // [esp+60h] [ebp-ACh] BYREF
  float v18[3]; // [esp+6Ch] [ebp-A0h] BYREF
  float scaled_result[3]; // [esp+78h] [ebp-94h] BYREF
  float copy_result[3]; // [esp+84h] [ebp-88h] BYREF
  float vector[3]; // [esp+90h] [ebp-7Ch] BYREF
  float v22; // [esp+9Ch] [ebp-70h]
  int i; // [esp+A0h] [ebp-6Ch]
  int v24; // [esp+A4h] [ebp-68h]
  float v25[3]; // [esp+A8h] [ebp-64h] BYREF
  char *v26; // [esp+B4h] [ebp-58h] BYREF
  int v27; // [esp+B8h] [ebp-54h]
  float v28; // [esp+BCh] [ebp-50h]
  float rhs[3]; // [esp+C0h] [ebp-4Ch] BYREF
  float lhs[3]; // [esp+CCh] [ebp-40h] BYREF
  float v31[3]; // [esp+D8h] [ebp-34h] BYREF
  float v32[3]; // [esp+E4h] [ebp-28h] BYREF
  float destination[5]; // [esp+F0h] [ebp-1Ch] BYREF
  float v34; // [esp+104h] [ebp-8h]
  float v35; // [esp+108h] [ebp-4h]

  result = rf_mesh_decal_request80_construct((char *)&v26);
  v24 = -1;
  for ( i = 0; i < 25; ++i )
  {
    if ( !*(_DWORD *)(a1 + 4 * i + 4328) )
    {
      result = (char *)i;
      v24 = i;
      break;
    }
    result = (char *)(i + 1);
  }
  if ( v24 >= 0 && source )
  {
    result = (char *)rf_model_handle_get_first_model_container(*(_DWORD **)(a1 + 52));
    v26 = result;
    if ( result )
    {
      rf_vector3_set_components_return_destination(vector, 1.0, 0.0, 0.0);
      v27 = dword_662E34;
      v28 = rf_random_float_range(0.055, 0.079999998);
      rf_vector_copy(lhs, copy_result, source);
      rf_vector_subtract_in_place(lhs, (float *)(a2 + 60));
      rf_matrix3_inverse_rotate_vector(lhs, (float *)(a2 + 72));
      v4 = rf_vector_multiply_scalar(vector, scaled_result, 2.0);
      rf_vector_accumulate(lhs, v4);
      v5 = rf_vector_multiply_scalar(vector, v18, 2.0);
      v6 = rf_vector_subtract(lhs, out_vector, v5);
      rf_vector_copy(rhs, v16, v6);
      LODWORD(destination[3]) = 6;
      LODWORD(destination[4]) = dword_662E30;
      v27 = dword_662E34;
      v34 = rf_random_float_range(0.0, 359.0) * 0.01745299994945526;
      v35 = rf_cos_float(v34);
      v22 = rf_sin_float(v34);
      rf_vector3_default_construct_noop(v25);
      v25[0] = 0.0;
      v25[1] = -v22;
      v25[2] = v35;
      rf_vector_normalize_reciprocal_sqrt(v25);
      v7 = rf_vector_subtract(lhs, v15, rhs);
      rf_vector_copy(destination, v14, v7);
      rf_vector_normalize_reciprocal_sqrt(destination);
      v8 = rf_vector_cross(destination, v13, v25);
      rf_vector_copy(v31, v12, v8);
      v9 = rf_vector_cross(v31, v11, destination);
      rf_vector_copy(v32, v10, v9);
      result = (char *)rf_mesh_decal_project_prism_and_collect((float *)&v26);
      *(_DWORD *)(a1 + 4 * v24 + 4328) = result;
    }
  }
  return result;
}

