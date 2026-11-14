// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507790 rf_vclip_effect_submit_callbacks_for_room
// UNREALRED VERIFIED [impact-callbacks-20261028]: Traverses circular active VClip list sentinel0x90B838 via next+0. Records whose room pointer+68 equals caller submit callback0x507740 with record payload,position+12 stored/cullcenter,radius+64,sort1,optional pointers0,lighting bytes0/1. Does not check active byte separately or handle submission failure. Return AL incidental last pointer/helper value.
char __cdecl rf_vclip_effect_submit_callbacks_for_room(int a1)
{
  char result; // al
  int i; // [esp+20h] [ebp-4h]

  result = dword_90B838;
  for ( i = dword_90B838; (_DWORD *)i != &dword_90B838; i = *(_DWORD *)i )
  {
    result = i;
    if ( *(_DWORD *)(i + 68) == a1 )
      result = rf_world_submit_render_callback_entry(
                 i,
                 i + 12,
                 i + 12,
                 *(float *)(i + 64),
                 (int)rf_vclip_effect_render_callback,
                 1,
                 0,
                 0,
                 0,
                 0,
                 1);
  }
  return result;
}

