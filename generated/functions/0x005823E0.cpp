// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005823E0 rf_short_quaternion_set_components
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall destination,then four signed16 values in four stack slots(callee pops16). Stores all fourWORD components0/2/4/6 and returns destination. No scale,clamp,normalization or buffer validation;higher integer arguments are narrowed to16bits by callers.
_WORD *__thiscall rf_short_quaternion_set_components(_WORD *this, __int16 a2, __int16 a3, __int16 a4, __int16 a5)
{
  *this = a2;
  *(this + 1) = a3;
  *(this + 2) = a4;
  *(this + 3) = a5;
  return this;
}

