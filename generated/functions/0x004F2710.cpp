// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F2710 rf_uint32_clamp_in_place
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Uses UNSIGNED comparisons to clamp *value to [minimum,maximum]. Does not validate minimum<=maximum. EAX is incidental: low-clamp path leaves the minimum scalar in EAX, other paths leave a pointer. The old pointer-return inference does not describe a consistent return contract.
unsigned int *__cdecl rf_uint32_clamp_in_place(unsigned int *a1, unsigned int a2, unsigned int a3)
{
  unsigned int *result; // eax

  result = a1;
  if ( *a1 >= a2 )
  {
    if ( *a1 > a3 )
    {
      *a1 = a3;
      return a1;
    }
  }
  else
  {
    *a1 = a2;
    return (unsigned int *)a2;
  }
  return result;
}

