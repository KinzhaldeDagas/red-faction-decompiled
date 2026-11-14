// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C25F0 rf_d3d8_end_scene_if_active
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): If scene-use flag1DAEDCC is nonzero and active1DAEDC8==1, clears active before calling EndScene(vtable+140). Does not flush immediate buffers or present; HRESULT unchecked.
void rf_d3d8_end_scene_if_active()
{
  if ( unk_1DAEDCC )
  {
    if ( unk_1DAEDC8 == 1 )
    {
      unk_1DAEDC8 = 0;
      (*(void (__thiscall **)(int, int))(*(_DWORD *)dword_1DAEDC4 + 140))(dword_1DAEDC4, dword_1DAEDC4);
    }
  }
}

