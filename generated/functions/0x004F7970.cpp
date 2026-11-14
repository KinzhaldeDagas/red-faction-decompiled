// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7970 rf_mission_event_create_by_type
// UNREALRED VERIFIED [mission-event-runtime]: Allocates the exact concrete event subclass for a numeric retail event type; unsupported/default types use the base event object.
char *__cdecl rf_mission_event_create_by_type(int a1)
{
  char *v2; // [esp+4h] [ebp-2B4h]
  char *v3; // [esp+8h] [ebp-2B0h]
  char *v4; // [esp+Ch] [ebp-2ACh]
  char *v5; // [esp+10h] [ebp-2A8h]
  char *v6; // [esp+14h] [ebp-2A4h]
  char *v7; // [esp+18h] [ebp-2A0h]
  char *v8; // [esp+1Ch] [ebp-29Ch]
  char *v9; // [esp+20h] [ebp-298h]
  char *v10; // [esp+24h] [ebp-294h]
  int v11; // [esp+28h] [ebp-290h]
  char *v12; // [esp+2Ch] [ebp-28Ch]
  char *v13; // [esp+30h] [ebp-288h]
  char *v14; // [esp+34h] [ebp-284h]
  char *v15; // [esp+38h] [ebp-280h]
  char *v16; // [esp+3Ch] [ebp-27Ch]
  char *v17; // [esp+40h] [ebp-278h]
  char *v18; // [esp+44h] [ebp-274h]
  char *v19; // [esp+48h] [ebp-270h]
  char *v20; // [esp+4Ch] [ebp-26Ch]
  char *v21; // [esp+50h] [ebp-268h]
  char *v22; // [esp+54h] [ebp-264h]
  int started; // [esp+58h] [ebp-260h]
  char *v24; // [esp+5Ch] [ebp-25Ch]
  char *v25; // [esp+60h] [ebp-258h]
  char *v26; // [esp+64h] [ebp-254h]
  char *construct; // [esp+68h] [ebp-250h]
  int v28; // [esp+6Ch] [ebp-24Ch]
  int v29; // [esp+70h] [ebp-248h]
  char *invulnerable_construct; // [esp+74h] [ebp-244h]
  char *v31; // [esp+78h] [ebp-240h]
  char *v32; // [esp+7Ch] [ebp-23Ch]
  char *v33; // [esp+80h] [ebp-238h]
  int v34; // [esp+84h] [ebp-234h]
  char *v35; // [esp+88h] [ebp-230h]
  char *v36; // [esp+8Ch] [ebp-22Ch]
  int v37; // [esp+90h] [ebp-228h]
  char *v38; // [esp+94h] [ebp-224h]
  int level_construct; // [esp+98h] [ebp-220h]
  int v40; // [esp+9Ch] [ebp-21Ch]
  char *v41; // [esp+A0h] [ebp-218h]
  char *v42; // [esp+A4h] [ebp-214h]
  char *v43; // [esp+A8h] [ebp-210h]
  char *v44; // [esp+ACh] [ebp-20Ch]
  char *v45; // [esp+B0h] [ebp-208h]
  int v46; // [esp+B4h] [ebp-204h]
  char *v47; // [esp+B8h] [ebp-200h]
  char *v48; // [esp+BCh] [ebp-1FCh]
  int v49; // [esp+C0h] [ebp-1F8h]
  char *v50; // [esp+C4h] [ebp-1F4h]
  int v51; // [esp+C8h] [ebp-1F0h]
  char *v52; // [esp+CCh] [ebp-1ECh]
  char *v53; // [esp+D0h] [ebp-1E8h]
  char *v54; // [esp+D4h] [ebp-1E4h]
  char *v55; // [esp+D8h] [ebp-1E0h]
  char *v56; // [esp+DCh] [ebp-1DCh]
  int v57; // [esp+E0h] [ebp-1D8h]
  char *v58; // [esp+E8h] [ebp-1D0h]
  void *v59; // [esp+F0h] [ebp-1C8h]
  void *v60; // [esp+F8h] [ebp-1C0h]
  void *v61; // [esp+100h] [ebp-1B8h]
  char *v62; // [esp+108h] [ebp-1B0h]
  char *v63; // [esp+110h] [ebp-1A8h]
  char *v64; // [esp+118h] [ebp-1A0h]
  char *v65; // [esp+120h] [ebp-198h]
  char *v66; // [esp+128h] [ebp-190h]
  void *v67; // [esp+130h] [ebp-188h]
  char *v68; // [esp+138h] [ebp-180h]
  char *v69; // [esp+140h] [ebp-178h]
  char *v70; // [esp+148h] [ebp-170h]
  char *v71; // [esp+150h] [ebp-168h]
  char *v72; // [esp+158h] [ebp-160h]
  char *v73; // [esp+160h] [ebp-158h]
  char *v74; // [esp+168h] [ebp-150h]
  char *v75; // [esp+170h] [ebp-148h]
  char *v76; // [esp+178h] [ebp-140h]
  char *v77; // [esp+180h] [ebp-138h]
  char *v78; // [esp+188h] [ebp-130h]
  void *v79; // [esp+190h] [ebp-128h]
  char *v80; // [esp+198h] [ebp-120h]
  char *v81; // [esp+1A0h] [ebp-118h]
  char *v82; // [esp+1A8h] [ebp-110h]
  char *v83; // [esp+1B0h] [ebp-108h]
  void *v84; // [esp+1B8h] [ebp-100h]
  void *v85; // [esp+1C0h] [ebp-F8h]
  char *v86; // [esp+1C8h] [ebp-F0h]
  char *v87; // [esp+1D0h] [ebp-E8h]
  char *v88; // [esp+1D8h] [ebp-E0h]
  char *v89; // [esp+1E0h] [ebp-D8h]
  void *v90; // [esp+1E8h] [ebp-D0h]
  char *v91; // [esp+1F0h] [ebp-C8h]
  char *v92; // [esp+1F8h] [ebp-C0h]
  void *v93; // [esp+200h] [ebp-B8h]
  char *v94; // [esp+208h] [ebp-B0h]
  void *v95; // [esp+210h] [ebp-A8h]
  void *v96; // [esp+218h] [ebp-A0h]
  char *v97; // [esp+220h] [ebp-98h]
  char *v98; // [esp+228h] [ebp-90h]
  char *v99; // [esp+230h] [ebp-88h]
  char *v100; // [esp+238h] [ebp-80h]
  void *v101; // [esp+240h] [ebp-78h]
  void *v102; // [esp+248h] [ebp-70h]
  char *v103; // [esp+250h] [ebp-68h]
  char *v104; // [esp+258h] [ebp-60h]
  void *v105; // [esp+260h] [ebp-58h]
  char *v106; // [esp+268h] [ebp-50h]
  void *v107; // [esp+270h] [ebp-48h]
  char *v108; // [esp+278h] [ebp-40h]
  char *v109; // [esp+280h] [ebp-38h]
  char *v110; // [esp+288h] [ebp-30h]
  char *v111; // [esp+290h] [ebp-28h]
  char *v112; // [esp+298h] [ebp-20h]
  void *v113; // [esp+2A0h] [ebp-18h]
  char *v114; // [esp+2A8h] [ebp-10h]

  switch ( a1 )
  {
    case 0:
      v113 = operator new(0x2E8u);
      if ( v113 )
        v57 = rf_event_sound_construct((int)v113);
      else
        v57 = 0;
      v114 = (char *)v57;
      break;
    case 1:
      v112 = (char *)operator new(0x2BCu);
      if ( v112 )
        v56 = rf_event_slay_construct(v112);
      else
        v56 = nullptr;
      v114 = v56;
      break;
    case 5:
      v111 = (char *)operator new(0x2BCu);
      if ( v111 )
        v55 = rf_event_goto_construct(v111);
      else
        v55 = nullptr;
      v114 = v55;
      break;
    case 6:
      v110 = (char *)operator new(0x2BCu);
      if ( v110 )
        v54 = rf_event_goto_player_construct(v110);
      else
        v54 = nullptr;
      v114 = v54;
      break;
    case 7:
      v109 = (char *)operator new(0x2BCu);
      if ( v109 )
        v53 = rf_event_look_at_construct(v109);
      else
        v53 = nullptr;
      v114 = v53;
      break;
    case 9:
      v108 = (char *)operator new(0x2BCu);
      if ( v108 )
        v52 = rf_event_shoot_once_construct(v108);
      else
        v52 = nullptr;
      v114 = v52;
      break;
    case 10:
      v107 = operator new(0x2D0u);
      if ( v107 )
        v51 = rf_event_explode_construct((int)v107);
      else
        v51 = 0;
      v114 = (char *)v51;
      break;
    case 11:
      v106 = (char *)operator new(0x2C0u);
      if ( v106 )
        v50 = rf_event_play_animation_construct(v106);
      else
        v50 = nullptr;
      v114 = v50;
      break;
    case 12:
      v105 = operator new(0x2CCu);
      if ( v105 )
        v49 = rf_event_play_custom_animation_construct((int)v105);
      else
        v49 = 0;
      v114 = (char *)v49;
      break;
    case 13:
      v104 = (char *)operator new(0x2C0u);
      if ( v104 )
        v48 = rf_event_heal_construct(v104);
      else
        v48 = nullptr;
      v114 = v48;
      break;
    case 14:
      v103 = (char *)operator new(0x2C0u);
      if ( v103 )
        v47 = rf_event_shield_construct(v103);
      else
        v47 = nullptr;
      v114 = v47;
      break;
    case 15:
      v102 = operator new(0x2D8u);
      if ( v102 )
        v46 = rf_event_message_construct((int)v102);
      else
        v46 = 0;
      v114 = (char *)v46;
      break;
    case 16:
      v101 = operator new(0x2BCu);
      if ( v101 )
        v45 = (char *)rf_event_when_dead_construct(v101);
      else
        v45 = nullptr;
      v114 = v45;
      break;
    case 17:
      v100 = (char *)operator new(0x2C0u);
      if ( v100 )
        v44 = rf_event_continuous_damage_construct(v100);
      else
        v44 = nullptr;
      v114 = v44;
      break;
    case 18:
      v99 = (char *)operator new(0x2C0u);
      if ( v99 )
        v43 = rf_event_shake_player_construct(v99);
      else
        v43 = nullptr;
      v114 = v43;
      break;
    case 19:
      v98 = (char *)operator new(0x2BCu);
      if ( v98 )
        v42 = rf_event_give_item_to_player_construct(v98);
      else
        v42 = nullptr;
      v114 = v42;
      break;
    case 20:
      v97 = (char *)operator new(0x2D0u);
      if ( v97 )
        v41 = rf_event_cyclic_timer_construct(v97);
      else
        v41 = nullptr;
      v114 = v41;
      break;
    case 21:
      v96 = operator new(0x2C0u);
      if ( v96 )
        v40 = rf_event_switch_model_construct((int)v96);
      else
        v40 = 0;
      v114 = (char *)v40;
      break;
    case 22:
      v95 = operator new(0x2C4u);
      if ( v95 )
        level_construct = rf_event_load_level_construct((int)v95);
      else
        level_construct = 0;
      v114 = (char *)level_construct;
      break;
    case 23:
      v94 = (char *)operator new(0x2C8u);
      if ( v94 )
        v38 = rf_event_spawn_object_construct(v94);
      else
        v38 = nullptr;
      v114 = v38;
      break;
    case 24:
      v86 = (char *)operator new(0x2C0u);
      if ( v86 )
        invulnerable_construct = rf_event_make_invulnerable_construct(v86);
      else
        invulnerable_construct = nullptr;
      v114 = invulnerable_construct;
      break;
    case 28:
      v93 = operator new(0x2C8u);
      if ( v93 )
        v37 = rf_event_follow_waypoints_construct((int)v93);
      else
        v37 = 0;
      v114 = (char *)v37;
      break;
    case 30:
      v92 = (char *)operator new(0x2BCu);
      if ( v92 )
        v36 = rf_event_set_friendliness_construct(v92);
      else
        v36 = nullptr;
      v114 = v36;
      break;
    case 31:
      v91 = (char *)operator new(0x2BCu);
      if ( v91 )
        v35 = rf_event_set_light_state_construct(v91);
      else
        v35 = nullptr;
      v114 = v35;
      break;
    case 32:
      v90 = operator new(0x2D8u);
      if ( v90 )
        v34 = rf_event_switch_construct((int)v90);
      else
        v34 = 0;
      v114 = (char *)v34;
      break;
    case 33:
      v89 = (char *)operator new(0x2D0u);
      if ( v89 )
        v33 = rf_event_swap_textures_construct(v89);
      else
        v33 = nullptr;
      v114 = v33;
      break;
    case 34:
      v88 = (char *)operator new(0x2BCu);
      if ( v88 )
        v32 = rf_event_set_ai_mode_construct(v88);
      else
        v32 = nullptr;
      v114 = v32;
      break;
    case 35:
      v83 = (char *)operator new(0x2C8u);
      if ( v83 )
        construct = rf_event_goal_create_construct(v83);
      else
        construct = nullptr;
      v114 = construct;
      break;
    case 36:
      v85 = operator new(0x2C8u);
      if ( v85 )
        v29 = rf_event_goal_check_construct((int)v85);
      else
        v29 = 0;
      v114 = (char *)v29;
      break;
    case 37:
      v84 = operator new(0x2C0u);
      if ( v84 )
        v28 = rf_event_goal_set_construct((int)v84);
      else
        v28 = 0;
      v114 = (char *)v28;
      break;
    case 38:
      v82 = (char *)operator new(0x2BCu);
      if ( v82 )
        v26 = rf_event_attack_construct(v82);
      else
        v26 = nullptr;
      v114 = v26;
      break;
    case 40:
      v81 = (char *)operator new(0x2C0u);
      if ( v81 )
        v25 = rf_event_set_liquid_depth_construct(v81);
      else
        v25 = nullptr;
      v114 = v25;
      break;
    case 41:
      v79 = operator new(0x2C4u);
      if ( v79 )
        started = rf_event_music_start_construct((int)v79);
      else
        started = 0;
      v114 = (char *)started;
      break;
    case 42:
      v78 = (char *)operator new(0x2BCu);
      if ( v78 )
        v22 = rf_event_music_stop_construct(v78);
      else
        v22 = nullptr;
      v114 = v22;
      break;
    case 44:
      v80 = (char *)operator new(0x2BCu);
      if ( v80 )
        v24 = rf_event_set_gravity_construct(v80);
      else
        v24 = nullptr;
      v114 = v24;
      break;
    case 45:
      v77 = (char *)operator new(0x2C0u);
      if ( v77 )
        v21 = rf_event_alarm_siren_construct(v77);
      else
        v21 = nullptr;
      v114 = v21;
      break;
    case 46:
      v76 = (char *)operator new(0x2B8u);
      if ( v76 )
        v20 = rf_event_alarm_construct(v76);
      else
        v20 = nullptr;
      v114 = v20;
      break;
    case 47:
      v70 = (char *)operator new(0x2BCu);
      if ( v70 )
        v14 = rf_event_go_undercover_construct(v70);
      else
        v14 = nullptr;
      v114 = v14;
      break;
    case 49:
      v75 = (char *)operator new(0x2C4u);
      if ( v75 )
        v19 = rf_event_monitor_state_construct(v75);
      else
        v19 = nullptr;
      v114 = v19;
      break;
    case 50:
      v69 = (char *)operator new(0x2C0u);
      if ( v69 )
        v13 = rf_event_unhide_construct(v69);
      else
        v13 = nullptr;
      v114 = v13;
      break;
    case 57:
      v74 = (char *)operator new(0x2B8u);
      if ( v74 )
        v18 = rf_event_fog_state_construct(v74);
      else
        v18 = nullptr;
      v114 = v18;
      break;
    case 58:
      v73 = (char *)operator new(0x2B8u);
      if ( v73 )
        v17 = rf_event_detach_construct(v73);
      else
        v17 = nullptr;
      v114 = v17;
      break;
    case 59:
      v72 = (char *)operator new(0x2C0u);
      if ( v72 )
        v16 = rf_event_skybox_state_construct(v72);
      else
        v16 = nullptr;
      v114 = v16;
      break;
    case 61:
      v63 = (char *)operator new(0x2C0u);
      if ( v63 )
        v7 = rf_event_blackout_player_construct(v63);
      else
        v7 = nullptr;
      v114 = v7;
      break;
    case 66:
      v71 = (char *)operator new(0x2C0u);
      if ( v71 )
        v15 = rf_event_modify_rotating_mover_construct(v71);
      else
        v15 = nullptr;
      v114 = v15;
      break;
    case 69:
      v68 = (char *)operator new(0x2B8u);
      if ( v68 )
        v12 = rf_event_enable_nav_point_construct(v68);
      else
        v12 = nullptr;
      v114 = v12;
      break;
    case 70:
      v67 = operator new(0x2C8u);
      if ( v67 )
        v11 = rf_event_play_vclip_construct((int)v67);
      else
        v11 = 0;
      v114 = (char *)v11;
      break;
    case 71:
      v66 = (char *)operator new(0x2B8u);
      if ( v66 )
        v10 = rf_event_endgame_construct(v66);
      else
        v10 = nullptr;
      v114 = v10;
      break;
    case 72:
      v65 = (char *)operator new(0x2B8u);
      if ( v65 )
        v9 = rf_event_mover_pause_construct(v65);
      else
        v9 = nullptr;
      v114 = v9;
      break;
    case 73:
      v64 = (char *)operator new(0x2BCu);
      if ( v64 )
        v8 = rf_event_countdown_begin_construct(v64);
      else
        v8 = nullptr;
      v114 = v8;
      break;
    case 84:
      v61 = operator new(0x2C0u);
      if ( v61 )
        v5 = (char *)rf_event_when_countdown_reaches_construct(v61);
      else
        v5 = nullptr;
      v114 = v5;
      break;
    case 85:
      v62 = (char *)operator new(0x2BCu);
      if ( v62 )
        v6 = rf_event_display_fullscreen_image_construct(v62);
      else
        v6 = nullptr;
      v114 = v6;
      break;
    case 87:
      v60 = operator new(0x2C0u);
      if ( v60 )
        v4 = (char *)rf_event_when_life_reaches_construct(v60);
      else
        v4 = nullptr;
      v114 = v4;
      break;
    case 88:
      v59 = operator new(0x2C0u);
      if ( v59 )
        v3 = (char *)rf_event_when_armor_reaches_construct(v59);
      else
        v3 = nullptr;
      v114 = v3;
      break;
    case 89:
      v87 = (char *)operator new(0x2BCu);
      if ( v87 )
        v31 = rf_event_reverse_mover_construct(v87);
      else
        v31 = nullptr;
      v114 = v31;
      break;
    default:
      v58 = (char *)operator new(0x2B8u);
      if ( v58 )
        v2 = rf_mission_event_construct_base(v58);
      else
        v2 = nullptr;
      v114 = v2;
      break;
  }
  return v114;
}

