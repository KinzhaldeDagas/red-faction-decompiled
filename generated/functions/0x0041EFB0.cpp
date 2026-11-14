// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041EFB0 rf_physics_hit_record68_copy_fields
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX destination68-byte physics contact plus source stackpointer,RET4,returns destinationEAX. Copies vectors at0(point),12(normal),36(other vector) through vector helper;fraction24 and scalar32 through x87 FLD/FSTP;material28 and DWORD48(UID)/52(raw material)/56(liquid)/60(face)/64(extra) through integer MOV. ALL17 DWORD slots covered,including optional metadata;raw UID/material/face words preserved as integer bits,not float NaNs. Not an atomic/blob memcpy:scalar/vector float paths retain native floating behavior and no full68-byte staging. Exact alias works,arbitrary partial overlap not protected. No NULL,finite,material/index or pointer validation;does not allocate/retain
// referenced objects.
float *__thiscall rf_physics_hit_record68_copy_fields(float *this, float *source)
{
  float v4[3]; // [esp+4h] [ebp-24h] BYREF
  float v5[3]; // [esp+10h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-Ch] BYREF

  rf_vector_copy(this, copy_result, source);
  rf_vector_copy(this + 3, v5, source + 3);
  *(this + 6) = source[6];
  *(this + 7) = source[7];
  *(this + 8) = source[8];
  rf_vector_copy(this + 9, v4, source + 9);
  *(this + 12) = source[12];
  *(this + 13) = source[13];
  *(this + 14) = source[14];
  *(this + 15) = source[15];
  *(this + 16) = source[16];
  return this;
}

