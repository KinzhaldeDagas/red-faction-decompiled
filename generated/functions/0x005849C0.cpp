// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005849C0 rf_short_quaternion_add_to_destination
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall sourceA inECX,args destination,sourceB. Writes four componentwise A+B via16-bit constructor0x5823E0,returns destination. Results narrow/wrap16bits,no saturation/normalization;sum squared norm used for hemisphere choice.
_WORD *__thiscall rf_short_quaternion_add_to_destination(_WORD *this, _WORD *a2, _WORD *a3)
{
  rf_short_quaternion_set_components(a2, *a3 + *this, a3[1] + *(this + 1), a3[2] + *(this + 2), a3[3] + *(this + 3));
  return a2;
}

