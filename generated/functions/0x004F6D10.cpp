// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6D10 rf_quicksave_notification_update
// UNREALRED VERIFIED [save-validation-20261028]: When notification float0x894D30<=0, checks pending quickload byte0x894D2A and clears it if quicksav.svl fails header validation. Positive timer branch initializes/positions UI element0x90B010 when byte0x894D28 is clear, assigns RGB240 and alpha=int(timer*255), subtracts frame delta seconds, and renders through0x4703F0. Does not execute a save/load in positive branch; timer is not clamped to zero here.
void rf_quicksave_notification_update()
{
  CHAR v0; // dl
  char *v2; // [esp+8h] [ebp-140h]
  char *v3; // [esp+14h] [ebp-134h]
  CHAR *v4; // [esp+18h] [ebp-130h]
  int v5; // [esp+1Ch] [ebp-12Ch] BYREF
  char FileName[260]; // [esp+20h] [ebp-128h] BYREF
  int v7[8]; // [esp+124h] [ebp-24h] BYREF

  if ( unk_894D30 <= 0.0 )
  {
    if ( unk_894D2A )
    {
      v4 = MEMORY[0x88E7D0];
      v3 = FileName;
      do
      {
        v0 = *v4;
        *v3++ = *v4++;
      }
      while ( v0 );
      v2 = (char *)&v5 + 3;
      while ( *++v2 )
        ;
      strcpy(v2, "quicksav.svl");
      if ( !rf_savegame_validate_headers_and_read_info(FileName, v7, nullptr, nullptr) )
        unk_894D2A = 0;
    }
  }
  else
  {
    if ( !unk_894D28 )
    {
      rf_ui_label_initialize_measured_text(unk_90B010, 0, 0, 0, unk_88E354, rf_pause_font);
      unk_90B01C = (640 - unk_90B024) / 2;
      unk_90B020 = (480 - unk_90B028) / 2 - 64;
      rf_ui_button_set_focus(unk_90B010);
    }
    rf_ui_button_clear_focus(unk_90B010);
    rf_color4_set_bytes_return_destination(unk_90B038, 240, 240, 240, (int)(unk_894D30 * 255.0));
    unk_894D30 = unk_894D30 - rf_frame_delta_seconds / 1.0;
    rf_ui_label_render((int)unk_90B010);
  }
}

