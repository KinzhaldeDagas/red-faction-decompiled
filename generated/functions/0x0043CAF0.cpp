// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CAF0 rf_emitter_enable
// UNREALRED VERIFIED [mission-visibility-20261020] Enables the emitter owner by storing byte1 at this+652. Called for each entity+5144 array entry during common reactivation.
_BYTE *__thiscall rf_emitter_enable(_BYTE *this)
{
  *(this + 652) = 1;
  return this;
}

