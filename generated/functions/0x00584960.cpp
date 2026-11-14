// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00584960 rf_short_quaternion_subtract_to_destination
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall sourceA inECX,args destination,sourceB. Writes four componentwise A-B results via16-bit constructor0x5823E0;returns destination. Arithmetic narrows/wraps to16bits,no saturation or normalization. Interpolator uses resulting squared scaled dot to choose hemisphere.
_WORD *__thiscall rf_short_quaternion_subtract_to_destination(_WORD *this, _WORD *a2, _WORD *a3)
{
  rf_short_quaternion_set_components(a2, *this - *a3, *(this + 1) - a3[1], *(this + 2) - a3[2], *(this + 3) - a3[3]);
  return a2;
}

