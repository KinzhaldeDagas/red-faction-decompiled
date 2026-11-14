// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005076A0 rf_vclip_effect_update_all
// UNREALRED VERIFIED [resource-pools-20261028]: First traverses circular active list sentinel0x90B838 saving next before mutation; calls rf_vfx_get_remaining_time(instance+8,0) and destroys record only when floating result equals0.0 exactly. Second traversal updates surviving instances through rf_vfx_update_instance(instance,frame_delta,0,record+12,record+24,1). No <=0 lifetime check. Current decompiler x87 argument is an analysis artifact around floating returns; types preserved.
int rf_vclip_effect_update_all()
{
  int result; // eax
  int *i; // [esp+14h] [ebp-8h]
  int j; // [esp+14h] [ebp-8h]
  int v3; // [esp+18h] [ebp-4h]

  result = dword_90B838;
  for ( i = (int *)dword_90B838; i != &dword_90B838; i = (int *)v3 )
  {
    v3 = *i;
    if ( rf_vfx_get_remaining_time((const void *)i[2], 0) == 0.0 )
      rf_vclip_effect_destroy_runtime_record((int)i);
    result = v3;
  }
  for ( j = dword_90B838; (_DWORD *)j != &dword_90B838; j = *(_DWORD *)j )
  {
    rf_vfx_update_instance(*(int **)(j + 8), rf_frame_delta_seconds, 0, j + 12, j + 24, 1);
    result = *(_DWORD *)j;
  }
  return result;
}

