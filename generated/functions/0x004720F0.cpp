// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004720F0 rf_ui_meta_control_add_child_and_expand_bounds
// UNREALRED VERIFIED [cutscene-ui-20261028]: When signed child count+168<32, appends supplied child at+40+4*count and increments count, copies group bytes+8/+9 to child, expands integer x/y/width/height bounds(+12/+16/+20/+24) to include child using recursive absolute coordinates. When moving origin left/up, preserves existing extent only if dimension>0, otherwise takes child dimension. Parent-relative origin is recomputed using group parent+4. Does not assign child parent pointer, null-check child, reject duplicate children or guard negative count. Full group silently unchanged; return incidental coordinate, not success status.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): ABI refinement: ECX receiver plus ONE stack child pointer, RET4. Entry EDX is never read; apparent third fastcall argument is spurious. Fresh457860 callsites
// push only child, move group into ECX. Preserve existing bounds/ownership contract: signed count+168<32 appends at+40+4*oldcount and increments; copies bytes+8/+9;
// absolute-coordinate expansion of+12/+16/+20/+24; recomputes origin relative to group parent+4, never assigns child parent. Negative count/null/duplicates/cycles/overflow unguarded;
// count>=32 no mutation; incidental return, not success.
int __thiscall rf_ui_meta_control_add_child_and_expand_bounds(void *self, void *child)
{
  int result; // eax
  int v3; // esi
  int v4; // esi
  int v5; // esi
  int v6; // esi
  int v7; // esi
  int v8; // esi
  int v9; // esi
  int v10; // esi
  int v11; // esi
  int v12; // esi

  result = (int)self;
  if ( *((int *)self + 42) < 32 )
  {
    *((_DWORD *)self + (*((_DWORD *)self + 42))++ + 10) = child;
    *((_BYTE *)child + 8) = *((_BYTE *)self + 8);
    *((_BYTE *)child + 9) = *((_BYTE *)self + 9);
    v3 = rf_ui_control_absolute_x(child);
    if ( v3 < rf_ui_control_absolute_x(self) )
    {
      if ( *((int *)self + 5) <= 0 )
      {
        *((_DWORD *)self + 5) = *((_DWORD *)child + 5);
      }
      else
      {
        v4 = rf_ui_control_absolute_x(self);
        *((_DWORD *)self + 5) += v4 - rf_ui_control_absolute_x(child);
      }
      if ( *((_DWORD *)self + 1) )
      {
        v5 = rf_ui_control_absolute_x(child);
        *((_DWORD *)self + 3) = v5 - rf_ui_control_absolute_x(*((_DWORD **)self + 1));
      }
      else
      {
        *((_DWORD *)self + 3) = rf_ui_control_absolute_x(child);
      }
    }
    v6 = *((_DWORD *)self + 5) + rf_ui_control_absolute_x(self);
    if ( v6 < *((_DWORD *)child + 5) + rf_ui_control_absolute_x(child) )
    {
      v7 = *((_DWORD *)child + 5) + rf_ui_control_absolute_x(child);
      *((_DWORD *)self + 5) = v7 - rf_ui_control_absolute_x(self);
    }
    v8 = rf_ui_control_absolute_y(child);
    if ( v8 < rf_ui_control_absolute_y(self) )
    {
      if ( *((int *)self + 6) <= 0 )
      {
        *((_DWORD *)self + 6) = *((_DWORD *)child + 6);
      }
      else
      {
        v9 = rf_ui_control_absolute_y(self);
        *((_DWORD *)self + 6) += v9 - rf_ui_control_absolute_y(child);
      }
      if ( *((_DWORD *)self + 1) )
      {
        v10 = rf_ui_control_absolute_y(child);
        *((_DWORD *)self + 4) = v10 - rf_ui_control_absolute_y(*((_DWORD **)self + 1));
      }
      else
      {
        *((_DWORD *)self + 4) = rf_ui_control_absolute_y(child);
      }
    }
    v11 = *((_DWORD *)self + 6) + rf_ui_control_absolute_y(self);
    result = *((_DWORD *)child + 6) + rf_ui_control_absolute_y(child);
    if ( v11 < result )
    {
      v12 = *((_DWORD *)child + 6) + rf_ui_control_absolute_y(child);
      result = rf_ui_control_absolute_y(self);
      *((_DWORD *)self + 6) = v12 - result;
    }
  }
  return result;
}

