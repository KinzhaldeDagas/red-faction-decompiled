// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00492250 rf_multiplayer_full_scoreboard_render
// UNREALRED VERIFIED [multiplayer-hud] Draws the held full score screen in a centered 572x370 panel, sets the shared full-score active byte, and selects DM, CTF, or team layouts with score-logo and flag art.
// UNREALRED VERIFIED [hud-score-feed] Draws exact Player/Frags/Ping DM and TDM rows, adds Caps in CTF, splits Deathmatch above 16 players, and reads ping from Player+0x1200+0x5AC.
void __cdecl rf_multiplayer_full_scoreboard_render(char a1)
{
  unsigned __int8 *v1; // eax
  _WORD *v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  unsigned __int8 *v10; // eax
  unsigned __int8 *v11; // eax
  unsigned __int8 *v12; // eax
  unsigned __int8 *v13; // eax
  unsigned __int8 *v14; // eax
  int v15; // [esp-Ch] [ebp-444h] BYREF
  int v16; // [esp-8h] [ebp-440h]
  int v17; // [esp-4h] [ebp-43Ch]
  std::exception *v18; // [esp+Ch] [ebp-42Ch]
  std::exception *v19; // [esp+10h] [ebp-428h]
  _DWORD *v20; // [esp+14h] [ebp-424h]
  std::exception *v21; // [esp+18h] [ebp-420h]
  std::exception *v22; // [esp+1Ch] [ebp-41Ch]
  std::exception *v23; // [esp+20h] [ebp-418h]
  std::exception *v24; // [esp+24h] [ebp-414h]
  char v25; // [esp+2Bh] [ebp-40Dh]
  char *v26; // [esp+2Ch] [ebp-40Ch]
  char *v27; // [esp+30h] [ebp-408h]
  const char *v28; // [esp+34h] [ebp-404h]
  std::exception *v29; // [esp+38h] [ebp-400h]
  std::exception *v30; // [esp+3Ch] [ebp-3FCh]
  int v31; // [esp+40h] [ebp-3F8h]
  char v32; // [esp+47h] [ebp-3F1h]
  char *v33; // [esp+48h] [ebp-3F0h]
  char *v34; // [esp+4Ch] [ebp-3ECh]
  const char *v35; // [esp+50h] [ebp-3E8h]
  std::exception *v36; // [esp+54h] [ebp-3E4h]
  std::exception *v37; // [esp+58h] [ebp-3E0h]
  int v38; // [esp+5Ch] [ebp-3DCh]
  int v39; // [esp+60h] [ebp-3D8h]
  unsigned __int8 *v40; // [esp+64h] [ebp-3D4h]
  unsigned __int8 *v41; // [esp+68h] [ebp-3D0h]
  int v42; // [esp+6Ch] [ebp-3CCh]
  unsigned __int8 *v43; // [esp+70h] [ebp-3C8h]
  unsigned __int8 *v44; // [esp+74h] [ebp-3C4h]
  unsigned __int8 *v45; // [esp+78h] [ebp-3C0h]
  char v46; // [esp+7Fh] [ebp-3B9h]
  char *v47; // [esp+80h] [ebp-3B8h]
  char *v48; // [esp+84h] [ebp-3B4h]
  const char *v49; // [esp+88h] [ebp-3B0h]
  std::exception *v50; // [esp+8Ch] [ebp-3ACh]
  std::exception *v51; // [esp+90h] [ebp-3A8h]
  int v52; // [esp+94h] [ebp-3A4h]
  char v53; // [esp+9Bh] [ebp-39Dh]
  char *v54; // [esp+9Ch] [ebp-39Ch]
  char *v55; // [esp+A0h] [ebp-398h]
  const char *v56; // [esp+A4h] [ebp-394h]
  std::exception *v57; // [esp+A8h] [ebp-390h]
  std::exception *appended; // [esp+ACh] [ebp-38Ch]
  int v59; // [esp+B0h] [ebp-388h]
  int v60; // [esp+B4h] [ebp-384h]
  int v61; // [esp+B8h] [ebp-380h]
  unsigned __int8 *v62; // [esp+BCh] [ebp-37Ch]
  unsigned __int8 *v63; // [esp+C0h] [ebp-378h]
  int v64; // [esp+C4h] [ebp-374h]
  int v65; // [esp+C8h] [ebp-370h]
  unsigned __int8 *v66; // [esp+CCh] [ebp-36Ch]
  unsigned __int8 *v67; // [esp+D0h] [ebp-368h]
  unsigned __int8 *v68; // [esp+D4h] [ebp-364h]
  char v69; // [esp+DBh] [ebp-35Dh]
  char *v70; // [esp+DCh] [ebp-35Ch]
  char *v71; // [esp+E0h] [ebp-358h]
  const char *v72; // [esp+E4h] [ebp-354h]
  std::exception *v73; // [esp+E8h] [ebp-350h]
  std::exception *v74; // [esp+ECh] [ebp-34Ch]
  int v75; // [esp+F0h] [ebp-348h]
  char v76; // [esp+F7h] [ebp-341h]
  char *v77; // [esp+F8h] [ebp-340h]
  char *v78; // [esp+FCh] [ebp-33Ch]
  const char *v79; // [esp+100h] [ebp-338h]
  std::exception *v80; // [esp+104h] [ebp-334h]
  std::exception *v81; // [esp+108h] [ebp-330h]
  int v82; // [esp+10Ch] [ebp-32Ch]
  int v83; // [esp+110h] [ebp-328h]
  unsigned __int8 *v84; // [esp+114h] [ebp-324h]
  unsigned __int8 *v85; // [esp+118h] [ebp-320h]
  int v86; // [esp+11Ch] [ebp-31Ch]
  unsigned __int8 *v87; // [esp+120h] [ebp-318h]
  unsigned __int8 *v88; // [esp+124h] [ebp-314h]
  char v89; // [esp+12Bh] [ebp-30Dh]
  char *v90; // [esp+12Ch] [ebp-30Ch]
  char *v91; // [esp+130h] [ebp-308h]
  const char *v92; // [esp+134h] [ebp-304h]
  std::exception *v93; // [esp+138h] [ebp-300h]
  std::exception *v94; // [esp+13Ch] [ebp-2FCh]
  int v95; // [esp+140h] [ebp-2F8h]
  int v96; // [esp+144h] [ebp-2F4h]
  unsigned __int8 *v97; // [esp+148h] [ebp-2F0h]
  unsigned __int8 *v98; // [esp+14Ch] [ebp-2ECh]
  unsigned __int8 *v99; // [esp+150h] [ebp-2E8h]
  int v100; // [esp+154h] [ebp-2E4h]
  char v101; // [esp+15Bh] [ebp-2DDh]
  _WORD *v102; // [esp+15Ch] [ebp-2DCh]
  char *v104; // [esp+164h] [ebp-2D4h]
  unsigned int v105; // [esp+168h] [ebp-2D0h]
  char *v106; // [esp+16Ch] [ebp-2CCh]
  char *v107; // [esp+174h] [ebp-2C4h]
  char *v108; // [esp+178h] [ebp-2C0h]
  char v109; // [esp+17Fh] [ebp-2B9h]
  _WORD *v110; // [esp+180h] [ebp-2B8h]
  char v111; // [esp+187h] [ebp-2B1h]
  unsigned __int8 *v112; // [esp+188h] [ebp-2B0h]
  unsigned __int8 *v113; // [esp+18Ch] [ebp-2ACh]
  const char *v114; // [esp+190h] [ebp-2A8h]
  _DWORD v115[2]; // [esp+194h] [ebp-2A4h] BYREF
  _DWORD v116[2]; // [esp+19Ch] [ebp-29Ch] BYREF
  _DWORD v117[2]; // [esp+1A4h] [ebp-294h] BYREF
  _BYTE v118[8]; // [esp+1ACh] [ebp-28Ch] BYREF
  int *v119; // [esp+1B4h] [ebp-284h]
  _BYTE v120[8]; // [esp+1B8h] [ebp-280h] BYREF
  int *v121; // [esp+1C0h] [ebp-278h]
  _BYTE v122[8]; // [esp+1C4h] [ebp-274h] BYREF
  int *v123; // [esp+1CCh] [ebp-26Ch]
  _BYTE v124[8]; // [esp+1D0h] [ebp-268h] BYREF
  int *v125; // [esp+1D8h] [ebp-260h]
  _BYTE v126[8]; // [esp+1DCh] [ebp-25Ch] BYREF
  int *v127; // [esp+1E4h] [ebp-254h]
  _BYTE v128[8]; // [esp+1E8h] [ebp-250h] BYREF
  int *v129; // [esp+1F0h] [ebp-248h]
  _BYTE v130[8]; // [esp+1F4h] [ebp-244h] BYREF
  int *v131; // [esp+1FCh] [ebp-23Ch]
  int v132; // [esp+200h] [ebp-238h]
  int *v133; // [esp+204h] [ebp-234h]
  int v134; // [esp+208h] [ebp-230h]
  _DWORD *m; // [esp+20Ch] [ebp-22Ch]
  int k; // [esp+210h] [ebp-228h]
  int v137; // [esp+214h] [ebp-224h]
  int v138; // [esp+218h] [ebp-220h]
  int v139; // [esp+21Ch] [ebp-21Ch]
  int v140; // [esp+220h] [ebp-218h]
  int ***v141; // [esp+224h] [ebp-214h]
  int v142; // [esp+228h] [ebp-210h]
  char v143[68]; // [esp+22Ch] [ebp-20Ch] BYREF
  int height_select_current; // [esp+270h] [ebp-1C8h]
  _DWORD v145[16]; // [esp+274h] [ebp-1C4h]
  int v146; // [esp+2B4h] [ebp-184h]
  int team0_score_byte; // [esp+2B8h] [ebp-180h]
  _DWORD v148[16]; // [esp+2BCh] [ebp-17Ch]
  int v149; // [esp+2FCh] [ebp-13Ch]
  int v150; // [esp+300h] [ebp-138h]
  char Buffer[132]; // [esp+304h] [ebp-134h] BYREF
  int team1_score_byte; // [esp+388h] [ebp-B0h]
  int ***i; // [esp+38Ch] [ebp-ACh]
  int j; // [esp+390h] [ebp-A8h]
  int viewport_width; // [esp+394h] [ebp-A4h]
  int v156; // [esp+398h] [ebp-A0h] BYREF
  unsigned __int8 v157[132]; // [esp+39Ch] [ebp-9Ch] BYREF
  int v158; // [esp+424h] [ebp-14h]
  int viewport_height; // [esp+428h] [ebp-10h]
  int v160; // [esp+434h] [ebp-4h]

  if ( a1 && rf_local_fpgun_player && !rf_player_get_alt_zoom_in_flag_byte(rf_local_fpgun_player) )
  {
    unk_757658 = 1;
    viewport_width = rf_renderer_get_viewport_width();
    viewport_height = rf_renderer_get_viewport_height();
    team0_score_byte = 0;
    team1_score_byte = 0;
    if ( (dword_77D6CC & 1) == 0 )
    {
      dword_77D6CC |= 1u;
      `eh vector constructor iterator'(
        rf_multiplayer_score_player_list,
        0x1204u,
        33,
        (void (__thiscall *)(void *))rf_player_construct_owned_members,
        (void (__thiscall *)(void *))rf_player_destroy_owned_members);
      atexit(rf_static_destroy_array_00758448);
      v160 = -1;
    }
    v150 = 0;
    v156 = viewport_height / 2 - 17;
    height_select_current = rf_font_get_height_select_current(dword_757BB0);
    v158 = rf_player_runtime_list_count();
    rf_render_color_set_rgba8(0, 0, 0, 150);
    rf_renderer_fill_rectangle_clipped(viewport_width / 2 - 286, viewport_height / 2 - 185, 572, 370, dword_182ABB8);
    if ( rf_full_score_logo_bitmap == -1 )
      rf_full_score_logo_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                    "score_rflogo.tga",
                                    (void *)0xFFFFFFFF,
                                    1);
    rf_render_color_set_rgba8(255, 255, 255, 255);
    rf_bitmap_draw_unscaled_clipped(
      rf_full_score_logo_bitmap,
      viewport_width / 2 - 170,
      viewport_height / 2 - 171,
      unk_187CD38);
    rf_render_color_set_rgba8(215, 215, 215, 255);
    v17 = dword_182ABBC;
    v16 = dword_757BB0;
    v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty(unk_6FC314);
    rf_font_draw_text_aligned(1, viewport_width / 2, viewport_height / 2 - 123, v1, v16, v17);
    rf_network_format_endpoint_text(v143, 64, &dword_704EF4);
    v114 = rf_string_object_c_str_or_empty(unk_704EC0);
    v113 = v157;
    v112 = v157;
    do
    {
      v111 = *v114;
      *v113 = v111;
      ++v114;
      ++v113;
    }
    while ( v111 );
    v110 = (_WORD *)((char *)&v156 + 3);
    do
    {
      v109 = *((_BYTE *)v110 + 1);
      v110 = (_WORD *)((char *)v110 + 1);
    }
    while ( v109 );
    v2 = v110;
    *v110 = 10272;
    *((_BYTE *)v2 + 2) = 0;
    v107 = v143;
    v108 = &v143[strlen(v143) + 1];
    v106 = v143;
    v105 = v108 - v143;
    v104 = (char *)&v156 + 3;
    while ( *++v104 )
      ;
    qmemcpy(v104, v106, v105);
    v102 = (_WORD *)((char *)&v156 + 3);
    do
    {
      v101 = *((_BYTE *)v102 + 1);
      v102 = (_WORD *)((char *)v102 + 1);
    }
    while ( v101 );
    *v102 = 41;
    rf_font_draw_text_aligned(1, viewport_width / 2, viewport_height / 2 - 112, v157, dword_757BB0, dword_182ABBC);
    v141 = rf_scoreboard_build_sorted_player_snapshots(
             (int ***)rf_multiplayer_score_player_list,
             (_DWORD *)dword_87C324,
             v158);
    v100 = rf_multiplayer_game_mode_get();
    if ( v100 )
    {
      if ( v100 == 1 )
      {
        v68 = rf_full_score_ctf_title;
        rf_font_draw_text_aligned(
          1,
          viewport_width / 2,
          viewport_height / 2 - 143,
          rf_full_score_ctf_title,
          unk_757664,
          dword_182ABBC);
        team0_score_byte = (unsigned __int8)rf_ctf_red_capture_byte_get();
        team1_score_byte = (unsigned __int8)rf_ctf_blue_capture_byte_get();
        rf_render_color_set_rgba8(255, 255, 255, 255);
        if ( rf_full_score_red_flag_bitmap == -1 )
          rf_full_score_red_flag_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                            "hud_flag_red.tga",
                                            (void *)0xFFFFFFFF,
                                            1);
        if ( rf_full_score_red_microflag_bitmap == -1 )
          rf_full_score_red_microflag_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                                 "hud_microflag_red.tga",
                                                 (void *)0xFFFFFFFF,
                                                 1);
        rf_bitmap_draw_unscaled_clipped(
          rf_full_score_red_flag_bitmap,
          viewport_width / 2 - 115,
          viewport_height / 2 - 94,
          unk_187CD38);
        if ( rf_full_score_blue_flag_bitmap == -1 )
          rf_full_score_blue_flag_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                             "hud_flag_blue.tga",
                                             (void *)0xFFFFFFFF,
                                             1);
        if ( rf_full_score_blue_microflag_bitmap == -1 )
          rf_full_score_blue_microflag_bitmap = rf_bitmap_load_with_optional_mipmap_generation(
                                                  "hud_microflag_blue.tga",
                                                  (void *)0xFFFFFFFF,
                                                  1);
        rf_bitmap_draw_unscaled_clipped(
          rf_full_score_blue_flag_bitmap,
          viewport_width / 2 + 74,
          viewport_height / 2 - 94,
          unk_187CD38);
        v67 = rf_full_score_player_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 258,
          viewport_height / 2 - 35,
          rf_full_score_player_header,
          dword_757BB0,
          dword_182ABBC);
        v66 = rf_full_score_frags_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 151,
          viewport_height / 2 - 35,
          rf_full_score_frags_header,
          dword_757BB0,
          dword_182ABBC);
        v65 = rf_full_score_caps_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 104,
          viewport_height / 2 - 35,
          rf_full_score_caps_header,
          dword_757BB0,
          dword_182ABBC);
        v64 = rf_full_score_ping_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 52,
          viewport_height / 2 - 35,
          rf_full_score_ping_header,
          dword_757BB0,
          dword_182ABBC);
        v63 = rf_full_score_player_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 34,
          viewport_height / 2 - 35,
          rf_full_score_player_header,
          dword_757BB0,
          dword_182ABBC);
        v62 = rf_full_score_frags_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 141,
          viewport_height / 2 - 35,
          rf_full_score_frags_header,
          dword_757BB0,
          dword_182ABBC);
        v61 = rf_full_score_caps_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 188,
          viewport_height / 2 - 35,
          rf_full_score_caps_header,
          dword_757BB0,
          dword_182ABBC);
        v60 = rf_full_score_ping_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 240,
          viewport_height / 2 - 35,
          rf_full_score_ping_header,
          dword_757BB0,
          dword_182ABBC);
        v149 = 0;
        v142 = 0;
        for ( i = *(int ****)rf_multiplayer_score_player_list;
              i != (int ***)rf_multiplayer_score_player_list;
              i = (int ***)*i )
        {
          if ( *((_BYTE *)i + 48) )
          {
            if ( *((_BYTE *)i + 48) == 1 )
              v148[v149++] = i;
          }
          else
          {
            v145[v142++] = i;
          }
          ++v150;
        }
        v156 = viewport_height / 2 - 17;
        v146 = rf_ctf_blue_carrier_get();
        for ( j = 0; j < v142; ++j )
        {
          i = (int ***)v145[j];
          if ( i == v141 )
            rf_render_color_set_rgba8(224, 217, 44, 255);
          else
            rf_render_color_set_rgba8(255, 255, 255, 255);
          v17 = 110;
          v125 = &v15;
          rf_string_copy_construct_from_object(&v15, (char **)i + 2);
          v59 = v6;
          appended = (std::exception *)rf_scoreboard_string_trim_then_append_ellipsis(v124, v15, v16, v17);
          v57 = appended;
          v160 = 4;
          v56 = rf_string_object_c_str_or_empty(appended);
          v55 = Buffer;
          v54 = Buffer;
          do
          {
            v53 = *v56;
            *v55 = v53;
            ++v56;
            ++v55;
          }
          while ( v53 );
          v160 = -1;
          rf_string_destroy_buffer(v124);
          rf_font_draw_text_aligned(
            0,
            viewport_width / 2 - 269,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", *((__int16 *)i[11] + 1));
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 - 123,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", *((__int16 *)i[11] + 2));
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 - 78,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", i[1152][363]);
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 - 23,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          if ( v146 && i[5] == *(int ***)(v146 + 20) )
            rf_bitmap_draw_unscaled_clipped(
              rf_full_score_blue_microflag_bitmap,
              viewport_width / 2 - 279,
              v156 + 1,
              dword_187CC7C);
          v156 += height_select_current;
        }
        v156 = viewport_height / 2 - 17;
        v140 = rf_ctf_red_carrier_get();
        for ( j = 0; j < v149; ++j )
        {
          i = (int ***)v148[j];
          if ( i == v141 )
            rf_render_color_set_rgba8(224, 217, 44, 255);
          else
            rf_render_color_set_rgba8(255, 255, 255, 255);
          v17 = 110;
          v123 = &v15;
          rf_string_copy_construct_from_object(&v15, (char **)i + 2);
          v52 = v7;
          v51 = (std::exception *)rf_scoreboard_string_trim_then_append_ellipsis(v122, v15, v16, v17);
          v50 = v51;
          v160 = 5;
          v49 = rf_string_object_c_str_or_empty(v51);
          v48 = Buffer;
          v47 = Buffer;
          do
          {
            v46 = *v49;
            *v48 = v46;
            ++v49;
            ++v48;
          }
          while ( v46 );
          v160 = -1;
          rf_string_destroy_buffer(v122);
          rf_font_draw_text_aligned(
            0,
            viewport_width / 2 + 23,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", *((__int16 *)i[11] + 1));
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 + 169,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", *((__int16 *)i[11] + 2));
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 + 214,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", i[1152][363]);
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 + 269,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          if ( v140 && i[5] == *(int ***)(v140 + 20) )
            rf_bitmap_draw_unscaled_clipped(
              rf_full_score_red_microflag_bitmap,
              viewport_width / 2 + 12,
              v156 + 1,
              dword_187CC7C);
          v156 += height_select_current;
        }
      }
      else if ( v100 == 2 )
      {
        v45 = rf_full_score_team_deathmatch_title;
        rf_font_draw_text_aligned(
          1,
          viewport_width / 2,
          viewport_height / 2 - 143,
          rf_full_score_team_deathmatch_title,
          unk_757664,
          dword_182ABBC);
        team0_score_byte = (unsigned __int8)rf_multiplayer_get_team0_score_byte();
        team1_score_byte = (unsigned __int8)rf_multiplayer_get_team1_score_byte();
        rf_render_color_set_rgba8(255, 255, 255, 255);
        v44 = rf_full_score_player_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 248,
          viewport_height / 2 - 35,
          rf_full_score_player_header,
          dword_757BB0,
          dword_182ABBC);
        v43 = rf_full_score_frags_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 121,
          viewport_height / 2 - 35,
          rf_full_score_frags_header,
          dword_757BB0,
          dword_182ABBC);
        v42 = rf_full_score_ping_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 67,
          viewport_height / 2 - 35,
          rf_full_score_ping_header,
          dword_757BB0,
          dword_182ABBC);
        v41 = rf_full_score_player_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 43,
          viewport_height / 2 - 35,
          rf_full_score_player_header,
          dword_757BB0,
          dword_182ABBC);
        v40 = rf_full_score_frags_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 170,
          viewport_height / 2 - 35,
          rf_full_score_frags_header,
          dword_757BB0,
          dword_182ABBC);
        v39 = rf_full_score_ping_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 224,
          viewport_height / 2 - 35,
          rf_full_score_ping_header,
          dword_757BB0,
          dword_182ABBC);
        v149 = 0;
        v142 = 0;
        for ( i = *(int ****)rf_multiplayer_score_player_list;
              i != (int ***)rf_multiplayer_score_player_list;
              i = (int ***)*i )
        {
          if ( *((_BYTE *)i + 48) )
          {
            if ( *((_BYTE *)i + 48) == 1 )
              v148[v149++] = i;
          }
          else
          {
            v145[v142++] = i;
          }
        }
        v156 = viewport_height / 2 - 17;
        for ( j = 0; j < v142; ++j )
        {
          i = (int ***)v145[j];
          if ( i == v141 )
            rf_render_color_set_rgba8(224, 217, 44, 255);
          else
            rf_render_color_set_rgba8(255, 255, 255, 255);
          v17 = 128;
          v121 = &v15;
          rf_string_copy_construct_from_object(&v15, (char **)i + 2);
          v38 = v8;
          v37 = (std::exception *)rf_scoreboard_string_trim_then_append_ellipsis(v120, v15, v16, v17);
          v36 = v37;
          v160 = 6;
          v35 = rf_string_object_c_str_or_empty(v37);
          v34 = Buffer;
          v33 = Buffer;
          do
          {
            v32 = *v35;
            *v34 = v32;
            ++v35;
            ++v34;
          }
          while ( v32 );
          v160 = -1;
          rf_string_destroy_buffer(v120);
          rf_font_draw_text_aligned(
            0,
            viewport_width / 2 - 259,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", *((__int16 *)i[11] + 1));
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 - 94,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", i[1152][363]);
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 - 37,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          v156 += height_select_current;
        }
        v156 = viewport_height / 2 - 17;
        for ( j = 0; j < v149; ++j )
        {
          i = (int ***)v148[j];
          if ( i == v141 )
            rf_render_color_set_rgba8(224, 217, 44, 255);
          else
            rf_render_color_set_rgba8(255, 255, 255, 255);
          v17 = 128;
          v119 = &v15;
          rf_string_copy_construct_from_object(&v15, (char **)i + 2);
          v31 = v9;
          v30 = (std::exception *)rf_scoreboard_string_trim_then_append_ellipsis(v118, v15, v16, v17);
          v29 = v30;
          v160 = 7;
          v28 = rf_string_object_c_str_or_empty(v30);
          v27 = Buffer;
          v26 = Buffer;
          do
          {
            v25 = *v28;
            *v27 = v25;
            ++v28;
            ++v27;
          }
          while ( v25 );
          v160 = -1;
          rf_string_destroy_buffer(v118);
          rf_font_draw_text_aligned(
            0,
            viewport_width / 2 + 32,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", *((__int16 *)i[11] + 1));
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 + 199,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", i[1152][363]);
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 + 254,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          v156 += height_select_current;
        }
      }
    }
    else
    {
      v99 = rf_full_score_deathmatch_title;
      rf_font_draw_text_aligned(
        1,
        viewport_width / 2,
        viewport_height / 2 - 143,
        rf_full_score_deathmatch_title,
        unk_757664,
        dword_182ABBC);
      v156 = viewport_height / 2 - 17;
      if ( v158 > 16 )
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        v88 = rf_full_score_player_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 248,
          viewport_height / 2 - 35,
          rf_full_score_player_header,
          dword_757BB0,
          dword_182ABBC);
        v87 = rf_full_score_frags_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 121,
          viewport_height / 2 - 35,
          rf_full_score_frags_header,
          dword_757BB0,
          dword_182ABBC);
        v86 = rf_full_score_ping_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 67,
          viewport_height / 2 - 35,
          rf_full_score_ping_header,
          dword_757BB0,
          dword_182ABBC);
        v85 = rf_full_score_player_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 43,
          viewport_height / 2 - 35,
          rf_full_score_player_header,
          dword_757BB0,
          dword_182ABBC);
        v84 = rf_full_score_frags_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 170,
          viewport_height / 2 - 35,
          rf_full_score_frags_header,
          dword_757BB0,
          dword_182ABBC);
        v83 = rf_full_score_ping_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 224,
          viewport_height / 2 - 35,
          rf_full_score_ping_header,
          dword_757BB0,
          dword_182ABBC);
        i = *(int ****)rf_multiplayer_score_player_list;
        for ( j = 0; j < 16; ++j )
        {
          if ( i == v141 )
            rf_render_color_set_rgba8(224, 217, 44, 255);
          else
            rf_render_color_set_rgba8(255, 255, 255, 255);
          v17 = 128;
          v129 = &v15;
          rf_string_copy_construct_from_object(&v15, (char **)i + 2);
          v82 = v4;
          v81 = (std::exception *)rf_scoreboard_string_trim_then_append_ellipsis(v128, v15, v16, v17);
          v80 = v81;
          v160 = 2;
          v79 = rf_string_object_c_str_or_empty(v81);
          v78 = Buffer;
          v77 = Buffer;
          do
          {
            v76 = *v79;
            *v78 = v76;
            ++v79;
            ++v78;
          }
          while ( v76 );
          v160 = -1;
          rf_string_destroy_buffer(v128);
          rf_font_draw_text_aligned(
            0,
            viewport_width / 2 - 259,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", *((__int16 *)i[11] + 1));
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 - 94,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", i[1152][363]);
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 - 37,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          v156 += height_select_current;
          i = (int ***)*i;
        }
        v156 = viewport_height / 2 - 17;
        for ( j = 16; j < v158; ++j )
        {
          if ( i == v141 )
            rf_render_color_set_rgba8(224, 217, 44, 255);
          else
            rf_render_color_set_rgba8(255, 255, 255, 255);
          v17 = 128;
          v127 = &v15;
          rf_string_copy_construct_from_object(&v15, (char **)i + 2);
          v75 = v5;
          v74 = (std::exception *)rf_scoreboard_string_trim_then_append_ellipsis(v126, v15, v16, v17);
          v73 = v74;
          v160 = 3;
          v72 = rf_string_object_c_str_or_empty(v74);
          v71 = Buffer;
          v70 = Buffer;
          do
          {
            v69 = *v72;
            *v71 = v69;
            ++v72;
            ++v71;
          }
          while ( v69 );
          v160 = -1;
          rf_string_destroy_buffer(v126);
          rf_font_draw_text_aligned(
            0,
            viewport_width / 2 + 32,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", *((__int16 *)i[11] + 1));
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 + 199,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", i[1152][363]);
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 + 254,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          v156 += height_select_current;
          i = (int ***)*i;
        }
      }
      else
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        v98 = rf_full_score_player_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 - 99,
          viewport_height / 2 - 35,
          rf_full_score_player_header,
          dword_757BB0,
          dword_182ABBC);
        v97 = rf_full_score_frags_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 28,
          viewport_height / 2 - 35,
          rf_full_score_frags_header,
          dword_757BB0,
          dword_182ABBC);
        v96 = rf_full_score_ping_header;
        rf_font_draw_text_aligned(
          0,
          viewport_width / 2 + 82,
          viewport_height / 2 - 35,
          rf_full_score_ping_header,
          dword_757BB0,
          dword_182ABBC);
        j = 0;
        for ( i = *(int ****)rf_multiplayer_score_player_list;
              i != (int ***)rf_multiplayer_score_player_list;
              i = (int ***)*i )
        {
          if ( i == v141 )
            rf_render_color_set_rgba8(224, 217, 44, 255);
          else
            rf_render_color_set_rgba8(255, 255, 255, 255);
          v17 = 128;
          v131 = &v15;
          rf_string_copy_construct_from_object(&v15, (char **)i + 2);
          v95 = v3;
          v94 = (std::exception *)rf_scoreboard_string_trim_then_append_ellipsis(v130, v15, v16, v17);
          v93 = v94;
          v160 = 1;
          v92 = rf_string_object_c_str_or_empty(v94);
          v91 = Buffer;
          v90 = Buffer;
          do
          {
            v89 = *v92;
            *v91 = v89;
            ++v92;
            ++v91;
          }
          while ( v89 );
          v160 = -1;
          rf_string_destroy_buffer(v130);
          rf_font_draw_text_aligned(
            0,
            viewport_width / 2 - 110,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", *((__int16 *)i[11] + 1));
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 + 57,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          sprintf(Buffer, "%d", i[1152][363]);
          rf_font_draw_text_aligned(
            2,
            viewport_width / 2 + 112,
            v156,
            (unsigned __int8 *)Buffer,
            dword_757BB0,
            dword_182ABBC);
          v156 += height_select_current;
          ++j;
        }
      }
    }
    if ( rf_multiplayer_game_mode_get() )
    {
      rf_render_color_set_rgba8(176, 26, 32, 255);
      sprintf(Buffer, "%d", team0_score_byte);
      rf_font_draw_text_aligned(
        1,
        viewport_width / 2 - 174,
        viewport_height / 2 - 88,
        (unsigned __int8 *)Buffer,
        unk_75765C,
        dword_182ABBC);
      rf_render_color_set_rgba8(25, 22, 209, 255);
      sprintf(Buffer, "%d", team1_score_byte);
      rf_font_draw_text_aligned(
        1,
        viewport_width / 2 + 174,
        viewport_height / 2 - 88,
        (unsigned __int8 *)Buffer,
        unk_75765C,
        dword_182ABBC);
    }
  }
  else
  {
    unk_757658 = 0;
  }
  if ( unk_757BC4 )
  {
    v137 = 465;
    v139 = 32;
    v134 = 400;
    v138 = 10;
    for ( k = 0; k < 16; ++k )
    {
      v133 = &unk_757668[21 * k];
      if ( *v133 )
      {
        v132 = v133[8];
        v17 = dword_182ABBC;
        v16 = -1;
        v10 = (unsigned __int8 *)rf_string_object_c_str_or_empty((const void *)(v132 + 24));
        rf_font_draw_text_screen(v134, v139, v10, v16, v17);
        v17 = dword_182ABBC;
        v16 = -1;
        v24 = (std::exception *)rf_string_format_int32_decimal(v117, v133[1]);
        v23 = v24;
        v160 = 8;
        v11 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v24);
        rf_font_draw_text_screen(v137, v139, v11, v16, v17);
        v160 = -1;
        rf_string_destroy_buffer(v117);
        v17 = dword_182ABBC;
        v16 = -1;
        v22 = (std::exception *)rf_string_format_int32_decimal(v116, v133[3]);
        v21 = v22;
        v160 = 9;
        v12 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v22);
        rf_font_draw_text_screen(v137 + 16, v139, v12, v16, v17);
        v160 = -1;
        rf_string_destroy_buffer(v116);
        v139 += v138;
      }
    }
    for ( m = (_DWORD *)dword_87C324; m; m = v20 )
    {
      v17 = dword_182ABBC;
      v16 = -1;
      v13 = (unsigned __int8 *)rf_string_object_c_str_or_empty(m + 2);
      rf_font_draw_text_screen(v134, v139, v13, v16, v17);
      v17 = dword_182ABBC;
      v16 = -1;
      v19 = (std::exception *)rf_string_format_int32_decimal(v115, *(__int16 *)(m[11] + 2));
      v18 = v19;
      v160 = 10;
      v14 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v19);
      rf_font_draw_text_screen(v137, v139, v14, v16, v17);
      v160 = -1;
      rf_string_destroy_buffer(v115);
      v139 += v138;
      if ( *m == dword_87C324 )
        v20 = nullptr;
      else
        v20 = (_DWORD *)*m;
    }
  }
}

