// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E3D60 rf_d3d8_bitmap_mark_dirty_invalidate_stage_bindings
// UNREALRED VERIFIED [texture-upload-20261028]: Resolvesbitmapindex,sets cachebyte+11=1,then calls0x5E4500 fortwostagecaches0x1E01550 stride24 withthatindex. Doesnotupload/freeimmediately. Returnsloopartifact2. No invalidresolverguard.
int __cdecl rf_d3d8_bitmap_mark_dirty_invalidate_stage_bindings(unsigned int a1)
{
  int result; // eax
  int v2; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  result = rf_bitmap_resolve_current_frame_slot(a1);
  v2 = result;
  *((_BYTE *)dword_1E01548 + 16 * result + 11) = 1;
  for ( i = 0; i < 2; ++i )
  {
    rf_d3d8_texture_stage_unbind_if_bitmap_index(&unk_1E01550[6 * i], v2);
    result = i + 1;
  }
  return result;
}

