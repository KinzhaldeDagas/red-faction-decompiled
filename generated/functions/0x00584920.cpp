// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00584920 rf_short_quaternion_negate_to_destination
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall source inECX,one destination pointer arg. Negates all four16-bit words through16-bit component constructor0x5823E0,returns destination. Negation wraps16bits (0x8000 remains0x8000). No normalization,allocation or NULL check;used to select quaternion hemisphere.
_WORD *__thiscall rf_short_quaternion_negate_to_destination(_WORD *this, _WORD *a2)
{
  rf_short_quaternion_set_components(a2, -*this, -*(this + 1), -*(this + 2), -*(this + 3));
  return a2;
}

