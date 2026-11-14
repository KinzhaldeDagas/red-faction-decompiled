// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00489940 rf_mover_debug_draw_keys
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl mover pointer. Iterates key-pointer vector668; draws wire sphere at key.position4 radius binary32(0.1), backend flags global187CC5C. Color priority: index==targetDWORD764
// yellow,else index==currentDWORD760 blue,else green,all alpha255. After first key, draws magenta line from current key.position to previous saved position; copies every current
// position to scratch for next row. Does not close final-to-first segment.
// After loop draws cyan sphere at mover.current228 radius binary32(0.4),formats common authored idDWORD32 as decimal to local32-byte buffer,and draws world-oriented text at common
// position60/orientation72,scale binary32(0.04),length-1,font187CD38. Then UNCONDITIONALLY accesses key index0 twice and draws its RGB basis using position4,matrix16,scale1 AND
// native FOURTH argument global182ABA0 (may be hidden by pseudocode). Empty-key array has no local safety guard. No previous render-color restore, key edit or mover activation.
// Return register is delegate artifact.
int __cdecl rf_mover_debug_draw_keys(_DWORD *a1)
{
  int first_dword; // eax
  _DWORD *v2; // eax
  _DWORD *v3; // eax
  int v4; // eax
  _DWORD *v5; // eax
  int v7; // [esp+4h] [ebp-50h]
  int v8; // [esp+Ch] [ebp-48h]
  int v9; // [esp+Ch] [ebp-48h]
  float copy_result[3]; // [esp+10h] [ebp-44h] BYREF
  float destination[3]; // [esp+1Ch] [ebp-38h] BYREF
  char Buffer[32]; // [esp+28h] [ebp-2Ch] BYREF
  char v13; // [esp+4Fh] [ebp-5h]
  int i; // [esp+50h] [ebp-4h]

  rf_vector3_default_construct_noop(destination);
  v13 = 1;
  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword(a1 + 167);
    if ( i >= first_dword )
      break;
    if ( i == a1[191] )
    {
      rf_render_color_set_rgba8(255, 255, 0, 255);
    }
    else if ( i == a1[190] )
    {
      rf_render_color_set_rgba8(0, 0, 255, 255);
    }
    else
    {
      rf_render_color_set_rgba8(0, 255, 0, 255);
    }
    v8 = dword_187CC5C;
    v2 = (_DWORD *)sub_552200(a1 + 167, i);
    rf_debug_draw_wire_sphere_backend_dispatch(*v2 + 4, 0.1, v8);
    if ( v13 == 1 )
    {
      v13 = 0;
    }
    else
    {
      rf_render_color_set_rgba8(255, 0, 255, 255);
      v9 = dword_187CC5C;
      v3 = (_DWORD *)sub_552200(a1 + 167, i);
      rf_debug_draw_world_line_backend_dispatch(*v3 + 4, (int)destination, v9);
    }
    v4 = sub_552200(a1 + 167, i);
    rf_vector_copy(destination, copy_result, (const float *)(*(_DWORD *)v4 + 4));
  }
  rf_render_color_set_rgba8(0, 255, 255, 255);
  rf_debug_draw_wire_sphere_backend_dispatch((int)(a1 + 57), 0.40000001, dword_187CC5C);
  sprintf(Buffer, "%d", a1[8]);
  rf_font_draw_text_world_oriented((int)(a1 + 15), (int)(a1 + 18), 0.039999999, Buffer, -1, unk_187CD38);
  v7 = *(_DWORD *)sub_552200(a1 + 167, 0) + 16;
  v5 = (_DWORD *)sub_552200(a1 + 167, 0);
  return rf_renderer_draw_debug_rgb_basis(*v5 + 4, v7, 1.0);
}

