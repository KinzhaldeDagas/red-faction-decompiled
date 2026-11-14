// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00580880 rf_volume_prepare_visible_for_view
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Copies current renderer view state to front-end camera globals,clears active pointer-list count18CD030,iterates owned volumes18CCFF4. Sphere tag1:skip frustum-rejected sphere;cache72=strength*255/(2*radius),76=center-camera,88=length(center-camera),append active. Box tag2:local bounds92=-dimensions/2,104=dimensions/2;reject through transformed-box clip planes581E10. If visible cache72=strength*255,rebuild same bounds,116=-1/dimensions.y,120=maxBound.y/dimensions.y,124=inverseRotate(camera-center,orientation24),append active. Unknown tags ignored. No zero radius/dimension guards or allocations of volume objects;active list borrows owned pointers. Returns owned-list count at loop exit,not active count.
int rf_volume_prepare_visible_for_view()
{
  int result; // eax
  float *v1; // eax
  double v2; // st7
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float v8[3]; // [esp+8h] [ebp-98h] BYREF
  float v9[3]; // [esp+14h] [ebp-8Ch] BYREF
  float v10[3]; // [esp+20h] [ebp-80h] BYREF
  float v11[3]; // [esp+2Ch] [ebp-74h] BYREF
  float v12[3]; // [esp+38h] [ebp-68h] BYREF
  float v13[3]; // [esp+44h] [ebp-5Ch] BYREF
  float v14[3]; // [esp+50h] [ebp-50h] BYREF
  float v15[3]; // [esp+5Ch] [ebp-44h] BYREF
  float v16[3]; // [esp+68h] [ebp-38h] BYREF
  float scaled_result[3]; // [esp+74h] [ebp-2Ch] BYREF
  float copy_result[3]; // [esp+80h] [ebp-20h] BYREF
  float out_vector[3]; // [esp+8Ch] [ebp-14h] BYREF
  int v20; // [esp+98h] [ebp-8h]
  int i; // [esp+9Ch] [ebp-4h]

  rf_renderer_copy_current_view_transform(&flt_18CD000, &flt_18CD00C);
  rf_pointer_array_clear_count_keep_storage(unk_18CD030);
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_18CCFF4);
    if ( i >= result )
      break;
    v20 = *(_DWORD *)sub_552200(unk_18CCFF4, i);
    if ( *(_BYTE *)v20 == 1 )
    {
      if ( !rf_frustum_reject_sphere((float *)(v20 + 8), *(float *)(v20 + 20)) )
      {
        *(float *)(v20 + 72) = *(float *)(v20 + 4) * 255.0 / (*(float *)(v20 + 20) + *(float *)(v20 + 20));
        v1 = rf_vector_subtract((const float *)(v20 + 8), out_vector, &flt_18CD000);
        rf_vector_copy((float *)(v20 + 76), copy_result, v1);
        v2 = rf_vector3_length((float *)(v20 + 76));
        *(float *)(v20 + 88) = v2;
        rf_pointer_array_append_dword(unk_18CD030, v20);
      }
    }
    else if ( *(_BYTE *)v20 == 2 )
    {
      v3 = rf_vector_multiply_scalar((const float *)(v20 + 60), scaled_result, -0.5);
      rf_vector_copy((float *)(v20 + 92), v16, v3);
      v4 = rf_vector_multiply_scalar((const float *)(v20 + 60), v15, 0.5);
      rf_vector_copy((float *)(v20 + 104), v14, v4);
      if ( !rf_frustum_reject_transformed_aabb_legacy_plane(
              v20 + 24,
              (float *)(v20 + 8),
              (float *)(v20 + 92),
              (float *)(v20 + 104)) )
      {
        *(float *)(v20 + 72) = *(float *)(v20 + 4) * 255.0;
        v5 = rf_vector_multiply_scalar((const float *)(v20 + 60), v13, -0.5);
        rf_vector_copy((float *)(v20 + 92), v12, v5);
        v6 = rf_vector_multiply_scalar((const float *)(v20 + 60), v11, 0.5);
        rf_vector_copy((float *)(v20 + 104), v10, v6);
        *(float *)(v20 + 116) = -1.0 / *(float *)(v20 + 64);
        *(float *)(v20 + 120) = *(float *)(v20 + 108) / *(float *)(v20 + 64);
        v7 = rf_vector_subtract(&flt_18CD000, v9, (const float *)(v20 + 8));
        rf_vector_copy((float *)(v20 + 124), v8, v7);
        rf_matrix3_inverse_rotate_vector((float *)(v20 + 124), (float *)(v20 + 24));
        rf_pointer_array_append_dword(unk_18CD030, v20);
      }
    }
  }
  return result;
}

