// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055E160 rf_affine3x4_set_quaternion_translation
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This destination affine48bytes,args quaternion float4,translation float3. Calls0x582CD0(source quaternion,destination) to write rotation andzero translation,then0x55E080(destination,translation). Returns TRANSLATION SOURCE pointer from final helper,not destination. No normalization or alias staging;source translation overlapping overwritten matrix can be changed before final copy.
float *__thiscall rf_affine3x4_set_quaternion_translation(float *this, float *a2, float *a3)
{
  rf_quaternion_to_affine3x4_zero_translation(a2, this);
  return rf_affine3x4_set_translation_return_source(this, a3);
}

