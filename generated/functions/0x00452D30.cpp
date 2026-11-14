// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00452D30 rf_credits_panel_initialize_scroll_fade_and_cached_bitmap
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Native no-argument entry; extra dispatcher payload is ignored. Capture effective viewport
// width571C00 toDWORD6EFEAC then height571C10 to6EFE9C. ONLY cached bitmapDWORD6EFEA8==EXACT0 loads 'demo-gameover.tga' via574E90(name,-1,0), stores raw result,
// then576450(handle,&width6EFE98,&height6EFEA0), ignoring dimension status. Every other raw handle, including negative, skips load and dimension refresh. Store
// scrollY6EFEB4=F32(SIGNED cached viewport height6EFE9C). Set mouse centering permission rawBYTE1 via58AD90. If BYTE6EDD38 ANYnonzero, get global RFString6F2C78 Cstring and
// call568A20(filename,FLOAT1), ignored; no own music-stop branch.  Then BYTE6EFEB2=1, exitDWORD6F1504=0. Measure PREEXISTING credits text6EFEC0
// using58C130(widthOut6F1500,heightOut6EFEBC,text6EFEC0,maxBytes-1,fontDWORD663048). Does not call452980 or clear/load text/budget here. Finally fadeFLOAT6EFEA4=+0,
// fade-inBYTE6EFEB1=1, fade-outBYTE6EFEB0=0. No own handle success/NULL, screen-size, authority or pause checks, old bitmap release, state rollback or normalized return. Final EAX is
// measure-helper residue; later final stores do not change it. Global render-font selection effects belong to measure helper.
_DWORD *rf_credits_panel_initialize_scroll_fade_and_cached_bitmap()
{
  const char *v0; // eax
  _DWORD *result; // eax

  unk_6EFEAC = rf_renderer_get_viewport_width();
  dword_6EFE9C = rf_renderer_get_viewport_height();
  if ( !dword_6EFEA8 )
  {
    dword_6EFEA8 = rf_bitmap_load_with_optional_mipmap_generation("demo-gameover.tga", (void *)0xFFFFFFFF, 0);
    rf_bitmap_get_resolved_dimensions(dword_6EFEA8, &dword_6EFE98, &dword_6EFEA0);
  }
  unk_6EFEB4 = (float)dword_6EFE9C;
  rf_mouse_set_centering_permission_byte(1);
  if ( unk_6EDD38 )
  {
    v0 = rf_string_object_c_str_or_empty(unk_6F2C78);
    rf_music_play_owned_filename((int)v0, 1.0);
  }
  unk_6EFEB2 = 1;
  unk_6F1504 = 0;
  result = rf_font_measure_text_extent(
             &dword_6F1500,
             dword_6EFEBC,
             (unsigned __int8 *)&dword_6EFEBC[1],
             -1,
             dword_663048);
  unk_6EFEA4 = 0.0;
  unk_6EFEB1 = 1;
  unk_6EFEB0 = 0;
  return result;
}

