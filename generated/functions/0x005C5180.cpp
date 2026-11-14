// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5180 rf_renderer_pop_instance_transform
// UNREALRED VERIFIED [character-pipeline-20261029]: Decrements depth0x18CD388 FIRST,then restores view origin,view matrix,instance matrix,instance origin from96-byte stack record at0x18CD600+96*depth. Returns last vector-copy helper result. No underflow,capacity or matching-push check in body; does not restore material or texture state.
float *rf_renderer_pop_instance_transform()
{
  float v1[3]; // [esp+0h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-Ch] BYREF

  --unk_18CD388;
  rf_vector_copy(&flt_18CD5E8, copy_result, (const float *)&unk_18CD624 + 24 * unk_18CD388);
  rf_matrix3_copy(&flt_18CD4B4, (const float *)&unk_18CD600 + 24 * unk_18CD388);
  rf_matrix3_copy(&flt_18CD5B8, (const float *)&unk_18CD630 + 24 * unk_18CD388);
  return rf_vector_copy(unk_18CD804, v1, &flt_18CD654[24 * unk_18CD388]);
}

