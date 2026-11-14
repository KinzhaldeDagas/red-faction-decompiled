// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573D20 rf_bitmap_texture_release_reference_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): cdecl(unsigned bitmapHandle). Loads backend selector187CC9C;for102 calls5E42D0 and returns cache-entry pointer bits as incidentalEAX. Other selectors return selector unchanged,not a normalized success flag. Callee binds warmup texture FIRST,resolves16B entry,decrements8bit reference with wrap,and releases tiles/clears handle only when new refbyte0;ref0 wraps255 and retains tiles. Wrapper adds no validation,underflow/ownership guard or alternative backend release.
int __cdecl rf_bitmap_texture_release_reference_backend_dispatch(unsigned int a1)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_bitmap_texture_release_reference(a1);
  return result;
}

