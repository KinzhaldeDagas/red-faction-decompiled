// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BFDD0 rf_particle36_vector_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): MSVC particle36 deletion adapter falsely named/typed as Concurrency::GlobalCore. Flag2: reads count DWORD at this-4,calls no-op5BDED0 for each36-byte element,flag1 frees cookie base(this-4),returns cookie base even after free. Without flag2 destroys one no-op element,optionally frees receiver for flag1,returns receiver. No count/allocation validity check; no GlobalCore behavior.
void *__thiscall rf_particle36_vector_deleting_destructor(void *this, unsigned __int8 a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'((char *)this, 0x24u, *((_DWORD *)this - 1), rf_particle36_destroy_noop);
    if ( (a2 & 1) != 0 )
      operator delete((char *)this - 4);
    return (char *)this - 4;
  }
  else
  {
    rf_particle36_destroy_noop(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

