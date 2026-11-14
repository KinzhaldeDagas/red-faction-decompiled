// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00440010 rf_particle_emitter_definition_assign132
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Thiscall destination,source pointer RET4 returns destination. Sequential assignment of132B emitter definition: x87 FLD/FSTP floats28..48,56..96,124/128; RAW DWORD MOV at0
// and100..120; vec3 helper copies at4/16; WORD52 raw copy. Bytes54..55 padding NOT assigned. Not memcpy: floating loads/stores can quiet signaling NaNs, and source/destination
// overlap follows sequential field writes rather than whole-record snapshot. No allocation, validation, defaults, normalization, pointer ownership or source mutation in
// nonoverlapping case. Used by firing ring to make local definition overrides without editing global prototype.
float *__thiscall rf_particle_emitter_definition_assign132(float *this, int a2)
{
  float v4[3]; // [esp+4h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-Ch] BYREF

  *this = *(float *)a2;
  rf_vector_copy(this + 1, copy_result, (const float *)(a2 + 4));
  rf_vector_copy(this + 4, v4, (const float *)(a2 + 16));
  *(this + 7) = *(float *)(a2 + 28);
  *(this + 8) = *(float *)(a2 + 32);
  *(this + 9) = *(float *)(a2 + 36);
  *(this + 10) = *(float *)(a2 + 40);
  *(this + 11) = *(float *)(a2 + 44);
  *(this + 12) = *(float *)(a2 + 48);
  *((_WORD *)this + 26) = *(_WORD *)(a2 + 52);
  *(this + 14) = *(float *)(a2 + 56);
  *(this + 15) = *(float *)(a2 + 60);
  *(this + 16) = *(float *)(a2 + 64);
  *(this + 17) = *(float *)(a2 + 68);
  *(this + 18) = *(float *)(a2 + 72);
  *(this + 19) = *(float *)(a2 + 76);
  *(this + 20) = *(float *)(a2 + 80);
  *(this + 21) = *(float *)(a2 + 84);
  *(this + 22) = *(float *)(a2 + 88);
  *(this + 23) = *(float *)(a2 + 92);
  *(this + 24) = *(float *)(a2 + 96);
  *(this + 25) = *(float *)(a2 + 100);
  *(this + 26) = *(float *)(a2 + 104);
  *(this + 27) = *(float *)(a2 + 108);
  *(this + 28) = *(float *)(a2 + 112);
  *(this + 29) = *(float *)(a2 + 116);
  *(this + 30) = *(float *)(a2 + 120);
  *(this + 31) = *(float *)(a2 + 124);
  *(this + 32) = *(float *)(a2 + 128);
  return this;
}

