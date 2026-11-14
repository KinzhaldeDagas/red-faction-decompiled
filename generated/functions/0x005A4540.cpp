// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4540 rf_cubic_bezier_construct_embedded_controls
// UNREALRED VERIFIED [character-pipeline-20261029]: Thiscall64-byte object. Calls vector default constructor on4 embedded12-byte points at+0,+12,+24,+36,then sets pointer table DWORDs+48,+52,+56,+60 to those points. No explicit coordinate assignment,allocation or external pointer ownership; vector default constructor does not initialize components. Returns this.
_DWORD *__thiscall rf_cubic_bezier_construct_embedded_controls(_DWORD *this)
{
  rf_vector3_default_construct_noop(this);
  rf_vector3_default_construct_noop(this + 3);
  rf_vector3_default_construct_noop(this + 6);
  rf_vector3_default_construct_noop(this + 9);
  *(this + 12) = this;
  *(this + 13) = this + 3;
  *(this + 14) = this + 6;
  *(this + 15) = this + 9;
  return this;
}

