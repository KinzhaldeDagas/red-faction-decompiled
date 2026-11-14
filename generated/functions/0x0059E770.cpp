// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059E770 rf_vpackfile_set_loading_user_maps
// UNREALRED VERIFIED [vpp-streaming] Sets the VPP entry-parser mode that neutralizes .tbl members while user-map archives are loading.
char __cdecl rf_vpackfile_set_loading_user_maps(char a1)
{
  rf_vpackfile_loading_user_maps = a1;
  return a1;
}

