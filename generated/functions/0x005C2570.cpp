// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C2570 rf_d3d8_begin_scene_reset_batch_counts
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Always clears batch counters18CCFBC/18CCFC0. If scene-use flag1DAEDCC is nonzero and scene-active1DAEDC8 is zero, sets active=1 before calling BeginScene(vtable+136). HRESULT unchecked; failure still leaves active set.
void rf_d3d8_begin_scene_reset_batch_counts()
{
  unk_18CCFBC = 0;
  unk_18CCFC0 = 0;
  if ( unk_1DAEDCC )
  {
    if ( !unk_1DAEDC8 )
    {
      unk_1DAEDC8 = 1;
      (*(void (__thiscall **)(int, int))(*(_DWORD *)dword_1DAEDC4 + 136))(dword_1DAEDC4, dword_1DAEDC4);
    }
  }
}

