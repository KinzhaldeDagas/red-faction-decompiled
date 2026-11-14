// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C990 rf_float6_vector3_dword40_assign
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Thiscall destination ECX, one stack source pointer, RET4, EAX original destination. Sequentially
// x87-load/store FLOAT32 fields0,4,8,12,16,20; call40CE30 vector3 assignment at destination/source+24; finally copy raw DWORD36 verbatim. Exactly40 bytes covered. Last field is a
// DWORD transfer despite inferred float-pointer spelling, and this is not a memcpy/snapshot: partial overlap can observe preceding writes, and x87 float transfers retain native
// floating-environment behavior. No allocation, NULL/size/range/finite check, initialization or write beyond40 bytes.
float *__thiscall rf_float6_vector3_dword40_assign(float *this, float *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = a2[3];
  *(this + 4) = a2[4];
  *(this + 5) = a2[5];
  rf_vector3_copy_return_destination(this + 6, a2 + 6);
  *(this + 9) = a2[9];
  return this;
}

