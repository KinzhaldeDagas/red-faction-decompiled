// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EDEB0 rf_feedback_xor_state_copy_out
// UNREALRED VERIFIED [wave-codec-20261028]: Writes three state DWORDs to caller array; returns third DWORD value (32 bits),not output pointer. Does not advance generator or transform data.
int __thiscall rf_feedback_xor_state_copy_out(_DWORD *this, _DWORD *a2)
{
  int result; // eax

  *a2 = *this;
  a2[1] = *(this + 1);
  result = *(this + 2);
  a2[2] = result;
  return result;
}

