// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C1580 rf_sound_resource_query_output_format
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Requires ready and unsigned index<2600. Lazy-loads the record if sample index +48 is negative. Mode 1 forwards the sample index and three output pointers to rf_sound_sample_get_output_format_fields. Failure/unavailable paths do not initialize the outputs; inferred EAX is not a uniform success boolean.
int __cdecl rf_sound_resource_query_output_format(unsigned int a1, int *a2, int *a3, _DWORD *a4)
{
  int result; // eax

  result = rf_sound_backend_ready;
  if ( rf_sound_backend_ready )
  {
    if ( a1 < 0xA28 )
    {
      if ( unk_1D85DE8[16 * a1] >= 0 || (result = rf_sound_load_entry(a1, 0, 0), result != -1) )
      {
        result = rf_sound_backend_mode;
        if ( rf_sound_backend_mode == 1 )
          return rf_sound_sample_get_output_format_fields(unk_1D85DE8[16 * a1], a2, a3, a4);
      }
    }
  }
  return result;
}

