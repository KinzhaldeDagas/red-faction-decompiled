// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CEDB0 rf_scene_vector_key40_construct_from_affine
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Writes firstDWORD0,invokes no-op vectors+4,+16,+28,extracts affine-template translation floats[9..11] through55E0B0 and copies them to vector+4. Second stack integer argument unused,so nonzero input would still store0 in firstDWORD. Returns receiver;vectors+16/+28 remain untouched;no rotation/keyframe sampling or allocation.
float *__thiscall rf_scene_vector_key40_construct_from_affine(float *this, int a2, float *a3)
{
  float *translation; // eax
  float copy_result[3]; // [esp+4h] [ebp-18h] BYREF
  float v7[3]; // [esp+10h] [ebp-Ch] BYREF

  rf_scene_key_set_first_dword(this, 0);
  rf_vector3_default_construct_noop(this + 1);
  rf_vector3_default_construct_noop(this + 4);
  rf_vector3_default_construct_noop(this + 7);
  translation = rf_affine3x4_get_translation(a3, v7);
  rf_vector_copy(this + 1, copy_result, translation);
  return this;
}

