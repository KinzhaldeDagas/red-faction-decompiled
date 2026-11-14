// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004175A0 rf_clutter_skin_array_initialize_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Writes zero to count/capacity/base at +0/+4/+8 before processing requested capacity. Any nonzero value, including a negative signed value, delegates to verified allocator 0x4171A0. No release of old storage, sign validation or null receiver guard. Thiscall with one DWORD argument, RET 4.
char *__thiscall rf_clutter_skin_array_initialize_capacity(char *this, int a2)
{
  char *result; // eax

  result = this;
  *(_DWORD *)this = 0;
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 2) = 0;
  if ( a2 )
    return rf_clutter_skin_array_reallocate_capacity(this, a2);
  return result;
}

