// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4BE0 rf_vani_player_cache_loaded_animation
// UNREALRED VERIFIED [texture-conversion-20261028]: Emptynamefataldiagnostic anim.cpp425. Ifloadedflag0x20clearreturns-1. Streamingflag0x10selects0x5E4670userbitmapcache,else0x5E46C0VBMsequencecache. Convertsnonzerocalleeresultto-1,zero0. Streamingcalleealwaysreturns0evencreationfailure; no checkof resultinghandlehere.
int __thiscall rf_vani_player_cache_loaded_animation(int this)
{
  int v2; // [esp+14h] [ebp-4h]

  if ( !strlen((const char *)this) )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\bmpman\\anim.cpp",
      425,
      "Trying to cache an anim without a name");
  if ( (*(_DWORD *)(this + 404) & 0x20) == 0 )
    return -1;
  if ( (*(_DWORD *)(this + 404) & 0x10) != 0 )
    v2 = rf_vani_player_cache_user_bitmap(this);
  else
    v2 = rf_vani_player_cache_vbm_sequence(this);
  if ( v2 )
    return -1;
  else
    return 0;
}

