// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449D90 rf_geomod_operation100_assign
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Thiscall(destination100,source100), RET4, returns destination. Fieldwise copies raw DWORD cutter0,room4,flags56; vector position8; matrix20; FLOAT scale60 via FLD/FSTP; vectors
// normal64,constraints76/88. No normalization, constructor, region application or pointer ownership. Not a generic memcpy contract: float/vector helpers use their native floating
// stores, and aliases are not guarded. Surrounding node links and smoke slots are untouched.
float *__thiscall rf_geomod_operation100_assign(float *this, float *a2)
{
  float v4[3]; // [esp+4h] [ebp-30h] BYREF
  float v5[3]; // [esp+10h] [ebp-24h] BYREF
  float v6[3]; // [esp+1Ch] [ebp-18h] BYREF
  float copy_result[3]; // [esp+28h] [ebp-Ch] BYREF

  *this = *a2;
  *(this + 1) = a2[1];
  rf_vector_copy(this + 2, copy_result, a2 + 2);
  rf_matrix3_copy(this + 5, a2 + 5);
  *(this + 14) = a2[14];
  *(this + 15) = a2[15];
  rf_vector_copy(this + 16, v6, a2 + 16);
  rf_vector_copy(this + 19, v5, a2 + 19);
  rf_vector_copy(this + 22, v4, a2 + 22);
  return this;
}

