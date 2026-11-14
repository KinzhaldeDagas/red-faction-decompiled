// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573500 rf_renderer_get_auxiliary_capability_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fog output widths, channel-sum color filtering, backend dispatch, byte/int return distinctions and context startup): No args,returnsBYTE. Backend selector187CC9C==102 calls5D4260,which returns raw capability byte1DAEDAD without normalization/device query. Selector104 explicitly returnsAL0;all other selectors alsoAL0. No renderer-ready gate,state writes or higher24EAX return guarantee.
unsigned __int8 __cdecl rf_renderer_get_auxiliary_capability_backend_dispatch()
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_get_auxiliary_capability_byte();
  else
    return 0;
}

