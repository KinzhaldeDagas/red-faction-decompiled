// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573420 rf_renderer_compatibility_zero_two_dword_outputs
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): cdecl(firstOutput,secondOutput),both valid DWORD pointers required. Unconditionally writes32bit0 to each,in order,then returns with EAX holding first pointer (incidental). No backend/capability query,physical/texture dimension computation or global state mutation. Output aliasing simply writes same zero twice;semantic names for outputs unproven.
unsigned int *__cdecl rf_renderer_compatibility_zero_two_dword_outputs(unsigned int *first, unsigned int *second)
{
  *first = 0;
  *second = 0;
  return first;
}

