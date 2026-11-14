// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004170B0 rf_clutter_skin_record_at_index
// UNREALRED VERIFIED [switch-clutter-reset] Returns ordered 108-byte clutter skin record index from the class skin vector.
int __thiscall rf_clutter_skin_record_at_index(_DWORD *this, int a2)
{
  return *(this + 2) + 108 * a2;
}

