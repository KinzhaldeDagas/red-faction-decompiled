// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00468960 rf_controls_draw_action_binding_row
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl(actionIndex,visibleOrdinal),unchecked player/index. Y=pixelRowHeight*ordinal+trunc(absListY*scaleY). Default color;selected action fills scaled list
// width662018/raw pixel rowheight and changes color. Action label is RFString atplayer252+28*index. ColumnsX=trunc((panelX6F6338+offset662000/662004)*scaleX),sum before conversion.
// Current keyboardWORD260 and mouseWORD264 loaded SIGNED:keyboard>=0 wins and indexes direct keyNames662020;else mouse>=0 uses doubly dereferenced localized6F69BC[mouse];bothnegative
// ->localized None88E110. Unbounded copy label into stack buffer,no trim/width/table upper-bound/pointer guard,so invalid nonnegative indices can index beyond256/5. No bindings/state
// mutation except render color;return final draw residue.
int __cdecl rf_controls_draw_action_binding_row(int a1, int a2)
{
  unsigned __int8 *v2; // eax
  int v4; // [esp-8h] [ebp-E4h]
  int v5; // [esp-4h] [ebp-E0h]
  unsigned __int8 v6; // [esp+7h] [ebp-D5h]
  unsigned __int8 *v7; // [esp+Ch] [ebp-D0h]
  unsigned __int8 *v8; // [esp+10h] [ebp-CCh]
  unsigned __int8 v9; // [esp+1Bh] [ebp-C1h]
  unsigned __int8 *v10; // [esp+20h] [ebp-BCh]
  unsigned __int8 *v11; // [esp+24h] [ebp-B8h]
  unsigned __int8 v12; // [esp+2Bh] [ebp-B1h]
  unsigned __int8 *v13; // [esp+30h] [ebp-ACh]
  unsigned __int8 *v14; // [esp+34h] [ebp-A8h]
  __int16 v15; // [esp+44h] [ebp-98h]
  __int16 v16; // [esp+48h] [ebp-94h]
  unsigned __int8 v17[132]; // [esp+4Ch] [ebp-90h] BYREF
  int v18; // [esp+D4h] [ebp-8h]
  int v19; // [esp+D8h] [ebp-4h]

  v18 = dword_6F299C * a2 + (int)((double)rf_ui_control_absolute_y(&dword_6F62C0) * rf_ui_scale_y);
  rf_render_color_set_packed_rgba8(byte_6F29D0);
  if ( a1 == dword_6F62BC )
  {
    v19 = (int)((double)rf_ui_control_absolute_x(&dword_6F62C0) * rf_ui_scale_x);
    rf_renderer_fill_rectangle_clipped(
      v19,
      v18,
      (int)((double)dword_662018 * rf_ui_scale_x),
      dword_6F299C,
      dword_182ABB8);
    rf_render_color_set_packed_rgba8(byte_6F29CC);
  }
  v19 = (int)((double)(dword_662000 + unk_6F6338) * rf_ui_scale_x);
  v5 = dword_182ABBC;
  v4 = dword_6F29B4;
  v2 = (unsigned __int8 *)rf_string_object_c_str_or_empty((const void *)(rf_local_fpgun_player + 28 * a1 + 252));
  rf_font_draw_text_screen(v19, v18, v2, v4, v5);
  v15 = *(_WORD *)(rf_local_fpgun_player + 28 * a1 + 260);
  v16 = *(_WORD *)(rf_local_fpgun_player + 28 * a1 + 264);
  if ( v15 < 0 )
  {
    if ( v16 < 0 )
    {
      v8 = (unsigned __int8 *)unk_88E110;
      v7 = v17;
      do
      {
        v6 = *v8;
        *v7++ = *v8++;
      }
      while ( v6 );
    }
    else
    {
      v11 = *(unsigned __int8 **)dword_6F69BC[v16];
      v10 = v17;
      do
      {
        v9 = *v11;
        *v10++ = *v11++;
      }
      while ( v9 );
    }
  }
  else
  {
    v14 = (unsigned __int8 *)*(&off_662020 + v15);
    v13 = v17;
    do
    {
      v12 = *v14;
      *v13++ = *v14++;
    }
    while ( v12 );
  }
  return rf_font_draw_text_screen(
           (int)((double)(dword_662004 + unk_6F6338) * rf_ui_scale_x),
           v18,
           v17,
           dword_6F29B4,
           dword_182ABBC);
}

