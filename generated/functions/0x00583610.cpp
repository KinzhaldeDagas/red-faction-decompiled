// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583610 rf_quaternion_s16_conjugate_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Outputs low16bits of(-x,-y,-z,w) through component setter,returns output. Signed source words;negating -32768 produces32768 then wraps back to0x8000 on16-bit store. No saturation,normalization or squared-norm divide;not general inverse. Arguments evaluated before setter writes,allowing exact alias.
_WORD *__thiscall rf_quaternion_s16_conjugate_to_destination(__int16 *this, _WORD *a2)
{
  rf_short_quaternion_set_components(a2, -*this, -*(this + 1), -*(this + 2), *(this + 3));
  return a2;
}

