// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00495C70 rf_player_pose60_assign
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scoreboard snapshot ordering and Player ownership, native packet layouts/audiences, inline string-record lifecycle, unreliable queue semantics and false SDK classification): 
// Thiscall60-byte embedded pose(Player4244),source stack,RET4,returns receiver. Copies vector0,matrix12,RAW DWORD48,then FLOAT52/FLOAT56. Source decompiler types may label48 as float
// but native uses integer MOV there. No normalization,allocation,padding fill or position publication; all60 bytes represented by listed fields.
float *__thiscall rf_player_pose60_assign(float *this, float *source)
{
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector_copy(this, copy_result, source);
  rf_matrix3_copy(this + 3, source + 3);
  *(this + 12) = source[12];
  *(this + 13) = source[13];
  *(this + 14) = source[14];
  return this;
}

