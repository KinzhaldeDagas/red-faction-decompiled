// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AD50 rf_mouse_get_relative_deltas
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Arguments3 DWORD output pointers. Copies globals0x193A070,+074,+078 (X,Y,wheel deltas),returns Y value. NO enabled check,locking or clearing;disabled state can still expose stored values. Return is not success status.
int __cdecl rf_mouse_get_relative_deltas(_DWORD *a1, _DWORD *a2, _DWORD *a3)
{
  int result; // eax

  *a1 = unk_193A070;
  result = unk_193A074;
  *a2 = unk_193A074;
  *a3 = unk_193A078;
  return result;
}

