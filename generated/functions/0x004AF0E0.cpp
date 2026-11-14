// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AF0E0 rf_splitscreen_render_player_respawn_fade
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, split-match render/update/pause gates, score comparisons, announcer policy, ignored extra audio arguments and
// x87 fade thresholds): Recovered4AF0E0..4AF20C, lastRET4AF20B. Cdecl player. If first-phase BYTE4592 nonzero compute float ratio=elapsed4596/float662D04 (original PE0.15000000596).
// Only ordered ratio>1 calls splitscreen_player_entity_create(player), ignores result, forces local ratio1; equal1/unordered do NOT spawn. Fresh-entity helper separately
// switches4592off/4593on and resets elapsed, but this invocation continues first-phase drawing. Set whiteRGB and alpha=trunc_towardzero(signed DWORD662C7C * ratio); factor default165
// in original PE, not255. Fill current viewport rectangle(0,0,width,height,clip182ABB8). Else if BYTE4593 nonzero compute float ratio=elapsed4596/float662D08 (original0.5). Only
// ordered>1 clears BYTE4593 and draws NOTHING. Equal1/unordered enters drawing: round float(1-ratio), square/round float, multiply by signed alpha factor, truncate via ftol2; set
// whiteRGB/draw viewport rectangle. First-phase byte takes precedence when both set. No elapsed advance, pause/runtime/death/entity/player NULL guard, clamp0..1, fade-duration
// validation or previous color restoration; NaNs/negative times follow native x87/conversion semantics. At exact first duration white alpha165 but no respawn until strictly later;
// exact second duration draws alpha0 before clearing on a later call.
void __cdecl rf_splitscreen_render_player_respawn_fade(int player)
{
  int viewport_width; // eax
  int v2; // eax
  int viewport_height; // [esp-8h] [ebp-10h]
  int v4; // [esp-8h] [ebp-10h]
  int v5; // [esp-4h] [ebp-Ch]
  int v6; // [esp-4h] [ebp-Ch]
  float v7; // [esp+0h] [ebp-8h]
  float v8; // [esp+0h] [ebp-8h]
  float v9; // [esp+0h] [ebp-8h]
  float v10; // [esp+4h] [ebp-4h]

  if ( *(_BYTE *)(player + 4592) )
  {
    v10 = *(float *)(player + 4596) / flt_662D04;
    if ( v10 > 1.0 )
    {
      rf_splitscreen_player_entity_create(player);
      v10 = 1.0;
    }
    rf_render_color_set_rgba8(255, 255, 255, (int)((double)dword_662C7C * v10));
    v5 = dword_182ABB8;
    viewport_height = rf_renderer_get_viewport_height();
    viewport_width = rf_renderer_get_viewport_width();
    rf_renderer_fill_rectangle_clipped(0, 0, viewport_width, viewport_height, v5);
  }
  else if ( *(_BYTE *)(player + 4593) )
  {
    v7 = *(float *)(player + 4596) / flt_662D08;
    if ( v7 <= 1.0 )
    {
      v8 = 1.0 - v7;
      v9 = v8 * v8;
      rf_render_color_set_rgba8(255, 255, 255, (int)((double)dword_662C7C * v9));
      v6 = dword_182ABB8;
      v4 = rf_renderer_get_viewport_height();
      v2 = rf_renderer_get_viewport_width();
      rf_renderer_fill_rectangle_clipped(0, 0, v2, v4, v6);
    }
    else
    {
      *(_BYTE *)(player + 4593) = 0;
    }
  }
}

