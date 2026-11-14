// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A4120 rf_packed_state_word_equal
// UNREALRED VERIFIED [face-batch-20261028]: Returns bool(*caller_argument==*this),one32-bit word equality. No field masks,normalization or multiword comparison. Used to compare packed render-state descriptors.
bool __thiscall rf_packed_state_word_equal(_DWORD *this, _DWORD *a2)
{
  return *a2 == *this;
}

