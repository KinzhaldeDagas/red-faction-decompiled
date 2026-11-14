// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A580 rf_hud_layout_profile_select_width
// UNREALRED VERIFIED [hud-viewport-20261027] This selector has only exact pixel-width cases 640/800/1024/1280 and no height/aspect/DPI input. Unsupported widths preserve the active coordinates. Modern proportional fitting must be an explicitly isolated host policy; it cannot be labeled decoded RF widescreen behavior.
int __cdecl rf_hud_layout_profile_select_width(int a1)
{
  int result; // eax

  result = a1;
  if ( a1 > 1024 )
  {
    if ( a1 == 1280 )
      qmemcpy(&rf_hud_active_layout_coordinates, &rf_hud_layout_coordinates_1280x1024, 0x180u);
  }
  else
  {
    switch ( a1 )
    {
      case 1024:
        qmemcpy(&rf_hud_active_layout_coordinates, &rf_hud_layout_coordinates_1024x768, 0x180u);
        break;
      case 640:
        qmemcpy(&rf_hud_active_layout_coordinates, &rf_hud_layout_coordinates_640x480, 0x180u);
        break;
      case 800:
        qmemcpy(&rf_hud_active_layout_coordinates, &rf_hud_layout_coordinates_800x600, 0x180u);
        break;
    }
  }
  return result;
}

