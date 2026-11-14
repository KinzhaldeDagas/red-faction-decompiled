// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CAD0 rf_emitter_disable
// UNREALRED VERIFIED [mission-visibility-20261020] Disables the emitter owner by storing byte0 at this+652. Called for each entity+5144 array entry during common hide.
_BYTE *__thiscall rf_emitter_disable(_BYTE *this)
{
  *(this + 652) = 0;
  return this;
}

