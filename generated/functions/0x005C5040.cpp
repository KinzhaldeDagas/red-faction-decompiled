// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5040 rf_renderer_push_instance_transform
// UNREALRED VERIFIED [character-pipeline-20261029]: cdecl position3f,orientation3x3. Calls0x581740 first. Saves view matrix at stack record0,view origin at+36,instance matrix at+48,instance origin at+84; stack base0x18CD600,stride96,index0x18CD388,then increments depth. Converts camera origin to instance coordinates (subtract position,inverse-rotate),composes active view/instance matrices and translates instance origin through existing instance rotation plus previous origin. Updates globals used by CPU projection. No stack limit or pointer test in this body; return is final matrix-copy helper result,not pushed index. Uses global mutable state; paired pop0x5C5180 restores saved4 blocks.
int __cdecl rf_renderer_push_instance_transform(float *a1, float *a2)
{
  const float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float v7[9]; // [esp+0h] [ebp-CCh] BYREF
  float v8[3]; // [esp+24h] [ebp-A8h] BYREF
  float v9[3]; // [esp+30h] [ebp-9Ch] BYREF
  float v10[9]; // [esp+3Ch] [ebp-90h] BYREF
  _BYTE v11[36]; // [esp+60h] [ebp-6Ch] BYREF
  float v12[3]; // [esp+84h] [ebp-48h] BYREF
  float copy_result[3]; // [esp+90h] [ebp-3Ch] BYREF
  float v14[3]; // [esp+9Ch] [ebp-30h] BYREF
  float v15[9]; // [esp+A8h] [ebp-24h] BYREF

  rf_clip_outcode_enable_all_bits();
  rf_matrix3_copy((float *)&unk_18CD600 + 24 * unk_18CD388, &flt_18CD4B4);
  rf_vector_copy((float *)&unk_18CD624 + 24 * unk_18CD388, copy_result, &flt_18CD5E8);
  rf_matrix3_copy((float *)&unk_18CD630 + 24 * unk_18CD388, &flt_18CD5B8);
  rf_vector_copy(&flt_18CD654[24 * unk_18CD388], v12, unk_18CD804);
  ++unk_18CD388;
  rf_vector_subtract_in_place(&flt_18CD5E8, a1);
  rf_matrix3_inverse_rotate_vector(&flt_18CD5E8, a2);
  v2 = (const float *)rf_matrix3_transpose_to_output(a2, (int)v11);
  v3 = rf_matrix3_argument_times_receiver_to_output(v2, v10, &flt_18CD4B4);
  rf_matrix3_copy(&flt_18CD4B4, v3);
  rf_matrix3_copy_construct((int)v15, &flt_18CD5B8);
  rf_vector3_copy_return_destination(v14, unk_18CD804);
  v4 = rf_matrix3_rotate_vector(a1, v9, v15);
  rf_vector_copy(unk_18CD804, v8, v4);
  rf_vector_accumulate(unk_18CD804, v14);
  v5 = rf_matrix3_argument_times_receiver_to_output(v15, v7, a2);
  return rf_matrix3_copy(&flt_18CD5B8, v5);
}

