// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EAD50 rf_fpgun_shutdown_presentation_assets
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): No args. Global wrapper87C6F0 nonzero: destroy then0. Global87C6F4 SIGNED>0: destroy then0; zero/negative unchanged. For signed type count87C6D8 assign empty CString to modelRFString+8 and nameRFString+0 in52-byte type records87C798. For exactly64 weapon records stride1360, nonzero wrapperDWORD1264 and1280 each destroy then0. Finally call4ED6B0 cycle-slot model-cache release, return its EAX. Does not itself reset type count, release nine type bitmap slots, clear every weapon cache or invoke action-sound replacement cleanup. Existing shutdown name retained; tests are not a uniform valid-handle predicate.
int rf_fpgun_shutdown_presentation_assets()
{
  char *v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  if ( dword_87C6F0 )
  {
    rf_model_handle_destroy_cdecl_adapter(dword_87C6F0);
    dword_87C6F0 = nullptr;
  }
  if ( dword_87C6F4 > 0 )
  {
    rf_model_handle_destroy_cdecl_adapter((_DWORD *)dword_87C6F4);
    dword_87C6F4 = 0;
  }
  for ( i = 0; i < dword_87C6D8; ++i )
  {
    rf_string_assign_from_cstr(&dword_87C7A0[13 * i], (char *)&byte_63CB19);
    rf_string_assign_from_cstr(&byte_87C798[52 * i], (char *)byte_63CB1A);
  }
  for ( j = 0; j < 64; ++j )
  {
    v1 = (char *)&rf_weapon_records + 1360 * j;
    if ( *((_DWORD *)v1 + 316) )
    {
      rf_model_handle_destroy_cdecl_adapter(*((_DWORD **)v1 + 316));
      *((_DWORD *)v1 + 316) = 0;
    }
    if ( *((_DWORD *)v1 + 320) )
    {
      rf_model_handle_destroy_cdecl_adapter(*((_DWORD **)v1 + 320));
      *((_DWORD *)v1 + 320) = 0;
    }
  }
  return rf_fpgun_release_cycle_slot_model_cache();
}

