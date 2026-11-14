// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044F4A0 rf_bomb_defuse_panel_initialize_or_resume
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(entryCode), one DWORD. EXACT entryCode2 skips all initialization below; otherwise difficulty
// helper449550 selects FLOAT32 field6EFDBC for0/1/2/3 from PE constants62.34000015258789/46.77000045776367/41.029998779296875/30.260000228881836. Native unsigned switch default
// retains prior value, while verified helper maps invalid difficulty to0. Clears BYTE6EFDA5, DWORD6EFDA0, BYTE6EFDA7, FLOAT6EFD88, BYTE6EFDA6/A4, BYTE6EFE34 and BYTE6EFE78, in that
// order. Loads29 bitmaps with requested handle-1, storing every result without a failure gate or previous-handle release: red/green glow66191C/661918,door661920,small digits0..9
// at6EFDC0+4*n,colon6EFDFC,period6EFE10,background6EFE14,dull up/right/left/down6EFE00/04/08/0C,bright up/right/left/down6EFDA8/AC/B0/B4,bomb
// up/right/left/down6EFD8C/90/94/98,paused66195C. Only BOMBBACKGROUND.tga uses mipmap flag1; all others0. Reseeds CRT rand with raw DWORD18092E0, then takes ELEVEN ordered567730 unit
// samples: multiply each x87 result by DOUBLE100, truncate toward0 through605F00, compute native SIGNED remainder4, and store first4 at6EFDEC..6EFDF8 and next7 at6EFE18..6EFE30; no
// intermediate FLOAT32 product store. Sets FLOAT6EFDB8=193.0. For three16-byte records661960+16*i loads L20S3_PAA_02.wav,L20S3_PAA_03.wav,atomic.wav with FLOAT(5,1,1), stores
// resource ID, calls568050 only if signed ID>=0 and ignores its result, then writes record+4=-1 and BYTE+8=0, leaving other bytes. Plays event55 with args(55,0,FLOAT0,FLOAT1), stores
// voice66199C, ignoring prior voice ownership. Computes FLOAT32 Xscale6EFD9C=signed viewportWidth/DOUBLE640 and Yscale6EFDE8=signed viewportHeight/DOUBLE448. Every following product
// re-reads stored scale and rounds FLOAT32:50=X*373 then40=50;54=X*427 then44=54;38=Y*320;3C=Y*340;48=Y*377;4C=Y*396;68=Y*340 then58=68;6C=Y*377
// then5C=6C;60=X*345;64=X*373;70=X*427;74=X*456 (suffixes are offsets from6EFE00). After initialization/skip, EXACT entryCode2 AND LIVE BYTE6EFE78==0 plays/stores the same event55
// again. ALL entries finally arm deadline6EFE7C for10000 milliseconds through55EF80 and forward EAX. No own rendering, success normalization, resource rollback, finite/viewport guard
// or RNG-state restoration; resume2 retains assets/random/layout/state and still re-arms deadline.
int __cdecl rf_bomb_defuse_panel_initialize_or_resume(int a1)
{
  int i; // [esp+1Ch] [ebp-4h]

  if ( a1 != 2 )
  {
    switch ( rf_ai_difficulty_get_with_zero_fallback() )
    {
      case 0:
        unk_6EFDBC = 62.34;
        break;
      case 1:
        unk_6EFDBC = 46.77;
        break;
      case 2:
        unk_6EFDBC = 41.029999;
        break;
      case 3:
        unk_6EFDBC = 30.26;
        break;
      default:
        break;
    }
    unk_6EFDA5 = 0;
    unk_6EFDA0 = 0;
    unk_6EFDA7 = 0;
    unk_6EFD88 = 0.0;
    unk_6EFDA6 = 0;
    unk_6EFDA4 = 0;
    unk_6EFE34 = 0;
    unk_6EFE78 = 0;
    dword_66191C = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_red_glow.tga", (void *)0xFFFFFFFF, 0);
    dword_661918 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_green_glow.tga", (void *)0xFFFFFFFF, 0);
    dword_661920 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_door.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDC0[0] = rf_bitmap_load_with_optional_mipmap_generation(
                      "bomb_defuse_digit_small_0.tga",
                      (void *)0xFFFFFFFF,
                      0);
    unk_6EFDC4 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_small_1.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDC8 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_small_2.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDCC = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_small_3.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDD0 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_small_4.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDD4 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_small_5.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDD8 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_small_6.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDDC = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_small_7.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDE0 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_small_8.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDE4 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_small_9.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDFC = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_colon.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFE10 = rf_bitmap_load_with_optional_mipmap_generation("bomb_defuse_digit_period.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFE14 = rf_bitmap_load_with_optional_mipmap_generation("BOMBBACKGROUND.tga", (void *)0xFFFFFFFF, 1);
    unk_6EFE00[0] = rf_bitmap_load_with_optional_mipmap_generation("updull.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFE0C = rf_bitmap_load_with_optional_mipmap_generation("downdull.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFE04 = rf_bitmap_load_with_optional_mipmap_generation("rightdull.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFE08 = rf_bitmap_load_with_optional_mipmap_generation("leftdull.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDA8[0] = rf_bitmap_load_with_optional_mipmap_generation("upbright.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDB4 = rf_bitmap_load_with_optional_mipmap_generation("downbright.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDAC = rf_bitmap_load_with_optional_mipmap_generation("rightbright.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFDB0 = rf_bitmap_load_with_optional_mipmap_generation("leftbright.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFD8C = rf_bitmap_load_with_optional_mipmap_generation("bomb_up.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFD98 = rf_bitmap_load_with_optional_mipmap_generation("bomb_down.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFD90 = rf_bitmap_load_with_optional_mipmap_generation("bomb_right.tga", (void *)0xFFFFFFFF, 0);
    unk_6EFD94 = rf_bitmap_load_with_optional_mipmap_generation("bomb_left.tga", (void *)0xFFFFFFFF, 0);
    dword_66195C = rf_bitmap_load_with_optional_mipmap_generation("paused.tga", (void *)0xFFFFFFFF, 0);
    srand(LODWORD(flt_18092A0[16]));
    unk_6EFDEC[0] = (int)(sub_567730() * 100.0) % 4;
    unk_6EFDF0 = (int)(sub_567730() * 100.0) % 4;
    unk_6EFDF4 = (int)(sub_567730() * 100.0) % 4;
    unk_6EFDF8 = (int)(sub_567730() * 100.0) % 4;
    unk_6EFE18[0] = (int)(sub_567730() * 100.0) % 4;
    unk_6EFE1C = (int)(sub_567730() * 100.0) % 4;
    unk_6EFE20 = (int)(sub_567730() * 100.0) % 4;
    unk_6EFE24 = (int)(sub_567730() * 100.0) % 4;
    unk_6EFE28 = (int)(sub_567730() * 100.0) % 4;
    unk_6EFE2C = (int)(sub_567730() * 100.0) % 4;
    unk_6EFE30 = (int)(sub_567730() * 100.0) % 4;
    unk_6EFDB8 = 193.0;
    for ( i = 0; i < 3; ++i )
    {
      dword_661960[4 * i] = rf_sound_resource_load((&filename)[i], 5.0, 1.0, 1.0);
      if ( dword_661960[4 * i] >= 0 )
        rf_gamesound_resolve_and_load(dword_661960[4 * i]);
      dword_661964[4 * i] = -1;
      byte_661968[16 * i] = 0;
    }
    dword_66199C = rf_gamesound_play_event(55, 0, 0.0, 1.0);
    unk_6EFD9C = (double)rf_renderer_get_viewport_width() / 640.0;
    unk_6EFDE8 = (double)rf_renderer_get_viewport_height() / 448.0;
    unk_6EFE50 = unk_6EFD9C * 373.0;
    unk_6EFE40 = unk_6EFE50;
    unk_6EFE54 = unk_6EFD9C * 427.0;
    unk_6EFE44 = unk_6EFE54;
    unk_6EFE38 = unk_6EFDE8 * 320.0;
    unk_6EFE3C = unk_6EFDE8 * 340.0;
    unk_6EFE48 = unk_6EFDE8 * 377.0;
    unk_6EFE4C = unk_6EFDE8 * 396.0;
    unk_6EFE68 = unk_6EFDE8 * 340.0;
    unk_6EFE58 = unk_6EFE68;
    unk_6EFE6C = unk_6EFDE8 * 377.0;
    unk_6EFE5C = unk_6EFE6C;
    unk_6EFE60 = unk_6EFD9C * 345.0;
    unk_6EFE64 = unk_6EFD9C * 373.0;
    unk_6EFE70 = unk_6EFD9C * 427.0;
    unk_6EFE74 = unk_6EFD9C * 456.0;
  }
  if ( a1 == 2 && !unk_6EFE78 )
    dword_66199C = rf_gamesound_play_event(55, 0, 0.0, 1.0);
  return rf_replicator_arm_milliseconds(&unk_6EFE7C, 10000);
}

