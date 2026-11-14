// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E43C0 rf_renderer_unbind_texture_stage
// UNREALRED VERIFIED [general-gap-20260830]: Binds a null texture to the cached stage index at record +0x04 and records cached handle -1 at +0x08.
_DWORD *__thiscall rf_renderer_unbind_texture_stage(_DWORD *this)
{
  (*(void (__thiscall **)(int, int, _DWORD, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 244))(
    dword_1DAEDC4,
    dword_1DAEDC4,
    *(this + 1),
    0);
  *(this + 2) = -1;
  return this;
}

