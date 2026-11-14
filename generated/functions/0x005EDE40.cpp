// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EDE40 rf_feedback_xor_state_set_nonzero_seeds
// UNREALRED VERIFIED [wave-codec-20261028]: Copies three32-bit seed words into this state. Replaces zero first seed with unsigned representation of-1994492286,zero second with1816682354,zero third with1540656698. Nonzero seed values copied unchanged. No allocation or entropy generation. Returns source pointer if third seed nonzero,otherwise this; not a consistent chaining pointer.
_DWORD *__thiscall rf_feedback_xor_state_set_nonzero_seeds(_DWORD *this, _DWORD *a2)
{
  _DWORD *result; // eax

  *this = *a2;
  if ( !*this )
    *this = -1994492286;
  *(this + 1) = a2[1];
  if ( !*(this + 1) )
    *(this + 1) = 1816682354;
  result = a2;
  *(this + 2) = a2[2];
  if ( !*(this + 2) )
  {
    *(this + 2) = 1540656698;
    return this;
  }
  return result;
}

