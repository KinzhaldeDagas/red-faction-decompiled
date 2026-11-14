// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044D9A0 rf_hud_directional_damage_render
// UNREALRED VERIFIED [ingame-hud-layers] Draws four front/left/back/right alphas at table coordinates using rotations 0, 3pi/2, pi, and pi/2; chooses on-foot or vehicle art from the controlled entity attachment.
int __cdecl rf_hud_directional_damage_render(int a1)
{
  int result; // eax
  float v2; // [esp+0h] [ebp-3Ch]
  float v3; // [esp+4h] [ebp-38h]
  int v4; // [esp+14h] [ebp-28h]
  int v5; // [esp+18h] [ebp-24h]
  int v6; // [esp+1Ch] [ebp-20h]
  float v7[4]; // [esp+20h] [ebp-1Ch]
  int v8; // [esp+30h] [ebp-Ch]
  int i; // [esp+34h] [ebp-8h]
  int v10; // [esp+38h] [ebp-4h]

  result = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  v10 = result;
  if ( result )
  {
    v7[0] = 0.0;
    v7[1] = 4.712389;
    v7[2] = 3.1415927;
    v7[3] = 1.5707964;
    v8 = -1;
    result = rf_entity_has_attached_use_vehicle(v10);
    if ( (_BYTE)result )
      v8 = rf_hud_damage_indicator_vehicle_bitmap;
    else
      v8 = rf_hud_damage_indicator_on_foot_bitmap;
    for ( i = 0; i < 4; ++i )
    {
      v4 = unk_6EDFB0[2 * i];
      v5 = unk_6EDFB4[2 * i];
      v6 = (int)(*(float *)(a1 + 4 * i + 4576) * 255.0);
      if ( v6 > 0 )
      {
        rf_render_color_set_rgba8(255, 255, 255, v6);
        v3 = (float)v5;
        v2 = (float)v4;
        rf_bitmap_draw_rotated_screen_quad(v8, v2, v3, 1.0, v7[i], unk_187CD34);
      }
      result = i + 1;
    }
  }
  return result;
}

