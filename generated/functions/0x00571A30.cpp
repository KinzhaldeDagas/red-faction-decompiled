// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571A30 rf_renderer_set_viewport_and_relative_clip
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Calls legacy no-op5738C0, stores viewport origin187CCBC/CCC0, initializes inclusive relative clip bounds [0,width-1] and [0,height-1], then clamps each absolute origin+bound against the physical screen [0,screenDimension-1]. Stores effective width/height as right-left+1 and bottom-top+1. For backend102 applies viewport through rf_renderer_apply_viewport_rectangle; otherwise EAX is effective width. Does not validate positive requested dimensions, normalize reversed bounds or change physical screen size. Clipping coordinates remain relative to stored origin.
int __cdecl rf_renderer_set_viewport_and_relative_clip(int a1, int a2, int a3, int a4)
{
  int result; // eax

  rf_renderer_reserved_noop_5738C0();
  unk_187CCBC = a1;
  unk_187CCC0 = a2;
  unk_187CCD4 = 0;
  unk_187CCD8 = a3 - 1;
  unk_187CCDC = 0;
  unk_187CCE0 = a4 - 1;
  if ( a1 >= 0 )
  {
    if ( a1 + unk_187CCD4 > dword_187CC94 - 1 )
      unk_187CCD4 = dword_187CC94 - 1 - a1;
  }
  else
  {
    unk_187CCD4 = -a1;
  }
  if ( a1 + unk_187CCD8 >= 0 )
  {
    if ( a1 + unk_187CCD8 >= dword_187CC94 - 1 )
      unk_187CCD8 = dword_187CC94 - 1 - a1;
  }
  else
  {
    unk_187CCD8 = -a1;
  }
  if ( a2 + unk_187CCDC >= 0 )
  {
    if ( a2 + unk_187CCDC > dword_187CC98 - 1 )
      unk_187CCDC = dword_187CC98 - 1 - a2;
  }
  else
  {
    unk_187CCDC = -a2;
  }
  if ( a2 + unk_187CCE0 >= 0 )
  {
    if ( a2 + unk_187CCE0 > dword_187CC98 - 1 )
      unk_187CCE0 = dword_187CC98 - 1 - a2;
  }
  else
  {
    unk_187CCE0 = -a2;
  }
  result = unk_187CCD8 - unk_187CCD4 + 1;
  unk_187CCC4 = result;
  unk_187CCC8 = unk_187CCE0 - unk_187CCDC + 1;
  if ( dword_187CC9C == 102 )
    return rf_renderer_apply_viewport_rectangle();
  return result;
}

