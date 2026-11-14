// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00458BE0 rf_ui_hit_test_enabled_buttons
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl signed physicalX,physicalY,pointer-to-control-pointer array,signed count. Scan signed index0..<count, first matching control wins; count<=0 returns-1
// without array dereference. For each entry ONLY nonzero BYTE+9 enables testing; BYTE+8,callbacks,selection and parent visibility not tested. Re-fetch entry and recursively resolve
// absoluteX46FC70 twice, absoluteY46FCA0 twice; receiver parent+4 contributes local+12/+16 with wrap, no snapshot/cycle guard. Physical left/top truncate(absCoord*FLOATscaleX/Y);
// right/bottom first ADD signed width+20/height+24 with32-bit wrap to freshly resolved coordinate, THEN FILD/multiply/truncate. Four signed comparisons are INCLUSIVE
// >=left,<=right,>=top,<=bottom; no half-open edge. No normalized/reordered negative rectangle, zero/nonfinite-scale, NULL array/entry, capacity or overflow validation. Returns first
// signed index or-1, no side effects/sounds/callback dispatch in own body.
int __cdecl rf_ui_hit_test_enabled_buttons(int physical_x, int physical_y, void *const *controls, int count)
{
  int v5; // [esp+10h] [ebp-14h]
  int v6; // [esp+14h] [ebp-10h]
  int v7; // [esp+18h] [ebp-Ch]
  int v8; // [esp+1Ch] [ebp-8h]
  int i; // [esp+20h] [ebp-4h]

  for ( i = 0; i < count; ++i )
  {
    if ( *((_BYTE *)controls[i] + 9) )
    {
      v6 = (int)((double)rf_ui_control_absolute_x((_DWORD *)controls[i]) * rf_ui_scale_x);
      v7 = (int)((double)(*((_DWORD *)controls[i] + 5) + rf_ui_control_absolute_x((_DWORD *)controls[i])) * rf_ui_scale_x);
      v8 = (int)((double)rf_ui_control_absolute_y((_DWORD *)controls[i]) * rf_ui_scale_y);
      v5 = (int)((double)(*((_DWORD *)controls[i] + 6) + rf_ui_control_absolute_y((_DWORD *)controls[i])) * rf_ui_scale_y);
      if ( physical_x >= v6 && physical_x <= v7 && physical_y >= v8 && physical_y <= v5 )
        return i;
    }
  }
  return -1;
}

