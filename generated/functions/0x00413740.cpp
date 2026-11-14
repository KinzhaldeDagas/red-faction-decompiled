// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413740 rf_record24_copy_six_floats
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native aggregate constructors, vector/matrix/24-byte array ownership, by-value stack arguments, contact copies and packed network messages): ECX destination24-byte record plus source pointer stackarg,RET4,returns destinationEAX. Copies first3 floats via vector-copy,then offsets12,16,20 individually through x87 FLD/FSTP. No omitted tail words or default initialization. Used for physics sphere records but original generic record identity not restricted here;not a raw memcpy because float loads/stores can affect signaling NaNs/exceptions. Exact self-copy works;arbitrary partial overlap not staged as a full six-float snapshot. No pointer/finite/size guard.
float *__thiscall rf_record24_copy_six_floats(float *this, float *source)
{
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector_copy(this, copy_result, source);
  *(this + 3) = source[3];
  *(this + 4) = source[4];
  *(this + 5) = source[5];
  return this;
}

