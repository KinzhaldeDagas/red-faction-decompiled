// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044FB80 rf_bomb_defuse_panel_update_and_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, sequence panel and input/binding natives, credits/endgame parsing and Extras-menu X-motion/lifecycle, native
// callback and text-draw argument roles and native signed/x87/stack/callback ABI): Cdecl(LOWBYTE suppressNormalUpdate), saved int return is path-dependent EAX; no ECX
// receiver/incoming ST0. Complete4732B body uses sequential branches and indexed render arrays, NO switch/jump table. F32 below denotes explicit DWORD store; T denotes605F00
// x87-to-integer helper lowEAX (ordinary representable finite values truncate toward0). All literal values verified by struct.unpack against original PE. HEAD PRIORITY: ANY nonzero
// BYTE6EFDA4 queries voice6619A0; full EAX!=0 skips completion work. EAX0 calls4426C0 end-movie/credits delegate, THEN sets one-frame BYTE6EFE79=1 and stops EXACT3 warning voice
// handles661964+16*i; helper results ignored and success flag is not cleared. This branch skips normal/failure update but does not bypass common door/tail logic. Else ANY nonzero
// BYTE6EFDA7 enters failure fade. If BYTE6EFDA6 nonzero: fade FLOAT6EFD88=F32(fade-frameDelta*DOUBLE85), draw opaque black current-viewport rectangle, then ONLY ordered fade<0
// clamps0 and requests panel2(force0). Exact0 and NaN do not request. If6EFDA6 zero: fade=F32(frameDelta*DOUBLE424.999969482421875+fade); ONLY ordered fade>DOUBLE255 sets6EFDA6=1,
// stores original FLOAT255.0, calls4DF5E0(raw localPlayer87C318). Exact255/NaN do not trigger. Failure/completion heads ignore suppressNormalUpdate and pause BYTE6EFE78; no own
// player guard or rollback. NORMAL UPDATE (only when neither head flag admitted): only suppressNormalUpdate BYTE0 AND pause6EFE78 BYTE0 enter normal simulation. Door-transition
// BYTE6EFE34 ANY nonzero skips BOTH sequence-input helper and mouse poll, but not countdown/warnings. Otherwise phase BYTE6EFDA5==0 calls450E00; current count DWORD6EFDA0 EXACT4 then
// sets phase=1, transition=1,count=0, plays events56 THEN54 with raw four slots(event,0,FLOAT0,FLOAT1). Phase ANY nonzero instead calls451180; count EXACT7 sets success6EFDA4=1,
// plays event57 into6619A0, stops loop voice66199C. No helper-result test or >=count substitute. Both paths then58A100 mouse poll. Even when count7 sets success, execution CONTINUES
// same invocation: countdown FLOAT6EFDBC=F32(old-frameDelta); ONLY ordered value<0 stops loop66199C,sets failure6EFDA7=1,clamps countdown0. Exact0 and NaN do not fail. EXACT3 warning
// records at661960+16*i: played BYTE+8 ANY nonzero skips; otherwise ordered FLOAT threshold+12>current countdown plays record eventDWORD+0,stores returned voiceDWORD+4,sets played=1
// EVEN if play fails. Original threshold defaults are30.0f,10.0f,0.0010000000474974513f; mutable values re-read. Same-frame completion and timeout/warnings can coexist; warning
// voices are not all stopped by timeout. Still inside normal-head branch, independent of prior pause value: suppressNormalUpdate BYTE0 consumes scan69 press count58BB80. ONLY full
// EAX EXACT1 toggles pause BYTE6EFE78 to(old==0), normalizing any nonzero old byte to0. New nonzero stops66199C; new zero plays event55(raw slots55,0,FLOAT0,FLOAT1) and stores
// returned loop handle. Every count other than1, including>1, instead calls58BC90(scan1) and IGNORES its byte; this is not escape/cancel behavior. Toggle occurs AFTER normal
// countdown update: newly paused invocation may already have simulated, newly resumed invocation skipped that earlier simulation. Common door motion then runs independently of head
// branch whenever suppressNormalUpdate==0,pause==0,transition6EFE34 ANY nonzero: doorY6EFDB8=F32(frameDelta*DOUBLE100/DOUBLE1+old); ONLY ordered doorY>DOUBLE293 clamps original
// FLOAT293 and clears transition. Exact293/NaN retain transition. DRAW GATES: current skip BYTE6EFE79 ANY nonzero is cleared and skips main panel/hint drawing for THIS invocation.
// Otherwise current6EFDA6 ANY nonzero skips it without clearing. Either skip still reaches failure/pause tail overlays. Main path sets whiteRGBA and blits background handle6EFE14
// at(0,0,current viewportWidth,T(yScale*448)) from fixed source640x448. Cached FLOAT xScale6EFD9C/yScale6EFDE8 are used, not recomputed. Every sprite call
// is572180(handle,dstX,dstY,dstW,dstH,src0,0,sourceW,sourceH,flip0,0,modeDWORD187CC7C), all results ignored and mode/globals re-read. Geometric products use x87 arithmetic directly
// into T, with no extra F32 store. SEQUENCE/CUE: phase6EFDA5 ANY nonzero draws EXACT4 dull-direction handles6EFE00[sequence6EFDEC[j]], common source dimensions queried from6EFE00[0],
// at X=integer table661930[j] (original271,346,419,492),Y=integer661928(original120), separately scaled/truncated. Then signed loop i0..<LIVE count6EFDA0 draws bright
// handles6EFDA8[received6EFE18[i]] at X661940[i](original276,311,346,381,416,451,486),Y66192C(original230), dimensions queried from6EFDA8[0]. Phase0 instead only draws
// bright6EFDA8[sequence6EFDEC[i]] under same signed live-count loop, at X661930[i]/Y661928. These mutable tables are not snapped or bounded to4/7 in this body; bitmap indices are raw
// unchecked DWORDs. Count SIGNED>0 chooses green-glow handle661918, otherwise red66191C; own queried dimensions, both placed at(T(xScale*78),T(yScale*130)). COUNTDOWN DISPLAY:
// M=T(countdown)/60 using SIGNED IDIV, S=T(countdown-M*DOUBLE60), C=T((countdown-M*DOUBLE60-S)*DOUBLE100); countdown is reloaded in each expression, no extra F32 intermediate/clamp.
// Query dimensions from digit0 handle6EFDC0[0]; use those source/scaled dimensions for ALL8 digit blits at y=T(yScale*61). Two leading digit0 handles at x bases292,317; then raw
// digit indices M/10,M-10*(M/10),S/10,S-10*(S/10),C/10,C-10*(C/10) at x bases348,373,405,430,463,488 (all scaled/T). Quotient/remainder arithmetic is signed/wrapped; no
// nonnegative,finite or0..9 index validation. Query colon handle6EFDFC once; draw it at x341,398 and period handle6EFE10 at455, ALL using colon source/scaled dimensions, y61. Invalid
// time/conversion may index outside digit array; no safe formatting fallback. HIGHLIGHT ONLY: read raw held mouse button0, then58AB60(&localX,&localY,&GLOBAL193A03C), writing
// cumulative wheel/Z to that global (not a button mask). Query source dimensions from UP bomb handle6EFD8C and reuse for every highlight. Else-if priority is
// scan208/down,200/up,203/left,205/right; ANY nonzero scan AL wins immediately. Otherwise that direction requires held byte ANY nonzero AND strict ordered open rectangle bounds: down
// X(6EFE50,54),Y(48,4C);up X(40,44),Y(38,3C);left X(60,64),Y(58,5C);right X(70,74),Y(68,6C), all in6EFE00 page. Equality and unordered reject. Draw at most ONE bomb handle:
// down6EFD98 at(387,366),up6EFD8C(386,322),left6EFD94(344,344),right6EFD90(426,344), scaled/T. This late path still queries mouse/keys while suppressNormalUpdate or pause is nonzero;
// it only draws and does not advance sequence. DOOR/HINT: set white again, query door661920 dimensions, save current viewport rectangle571BD0. Temporarily set
// viewport(0,0,T(xScale*640),T(yScale*295)), draw door at(T(xScale*244),T(doorY*yScale)), restore saved rectangle through571A30; restoring rectangle resets relative clipping rather
// than preserving arbitrary prior clip bounds. Hint deadline6EFE7C elapsed ANY nonzero AL resets it to-1 and skips hint; else armed ANY nonzero draws centered
// text(0x8000,T(yScale*13),pointer88E228,fontID-1,renderMode182ABBC). XOR/JZ makes English hint literal branch unreachable; no NULL-localization fallback. Hint is checked only on
// main drawing path, independently of normal-update suppression/pause. TAIL ALWAYS: load failure BYTE6EFDA7 with MOVZX intoEAX. If nonzero, set RGBA(255,255,255,T(fade6EFD88)), then
// fill current viewport with mode182ABB8; alpha is not locally clamped and color delegate retains low byte. ANY nonzero pause6EFE78 finally calls448CB0 pause-overlay helper,
// independent of suppressNormalUpdate/failure/skipped main draw, and forwards its EAX. Otherwise failure path returns rectangle-helper residue; no-failure/unpaused path returns
// explicit fullEAX0 regardless earlier rendering/audio results. No consistent success status, bitmap/index/player/finite validation, backend admission, full input/global snapshot,
// color restoration or rollback. Earlier state/audio/viewport effects remain if later delegates fail.
int __cdecl rf_bomb_defuse_panel_update_and_render(char a1)
{
  int viewport_width; // eax
  int v2; // eax
  int result; // eax
  int v4; // eax
  int v5; // [esp-18h] [ebp-68h]
  int viewport_height; // [esp+0h] [ebp-50h]
  int v7; // [esp+0h] [ebp-50h]
  int v8; // [esp+4h] [ebp-4Ch]
  int v9; // [esp+4h] [ebp-4Ch]
  int v10; // [esp+4h] [ebp-4Ch]
  int v11; // [esp+Ch] [ebp-44h] BYREF
  int v12; // [esp+10h] [ebp-40h] BYREF
  int v13; // [esp+14h] [ebp-3Ch]
  int v14; // [esp+18h] [ebp-38h]
  int v15; // [esp+1Ch] [ebp-34h] BYREF
  int v16; // [esp+20h] [ebp-30h] BYREF
  int v17; // [esp+24h] [ebp-2Ch] BYREF
  int v18; // [esp+28h] [ebp-28h] BYREF
  int v19; // [esp+2Ch] [ebp-24h]
  char button_held_byte; // [esp+33h] [ebp-1Dh]
  int v21; // [esp+34h] [ebp-1Ch]
  int v22; // [esp+38h] [ebp-18h]
  int v23; // [esp+3Ch] [ebp-14h] BYREF
  int v24; // [esp+40h] [ebp-10h] BYREF
  int v25; // [esp+44h] [ebp-Ch]
  int i; // [esp+48h] [ebp-8h]
  int j; // [esp+4Ch] [ebp-4h]

  if ( unk_6EFDA4 )
  {
    if ( !rf_gamesound_voice_is_playing(dword_6619A0) )
    {
      rf_play_end_movie_then_request_credits_panel();
      unk_6EFE79 = 1;
      for ( i = 0; i < 3; ++i )
        rf_gamesound_stop_voice_handle(dword_661964[4 * i]);
    }
  }
  else if ( unk_6EFDA7 )
  {
    if ( unk_6EFDA6 )
    {
      unk_6EFD88 = unk_6EFD88 - rf_frame_delta_seconds * 85.0;
      rf_render_color_set_rgba8(0, 0, 0, 255);
      v8 = dword_182ABB8;
      viewport_height = rf_renderer_get_viewport_height();
      viewport_width = rf_renderer_get_viewport_width();
      rf_renderer_fill_rectangle_clipped(0, 0, viewport_width, viewport_height, v8);
      if ( unk_6EFD88 < 0.0 )
      {
        unk_6EFD88 = 0.0;
        rf_ui_request_panel_immediate(2, 0);
      }
    }
    else
    {
      unk_6EFD88 = rf_frame_delta_seconds * 424.9999694824219 + unk_6EFD88;
      if ( unk_6EFD88 > 255.0 )
      {
        unk_6EFDA6 = 1;
        unk_6EFD88 = 255.0;
        rf_player_request_suicide_or_apply_fixed_damage(rf_local_fpgun_player);
      }
    }
  }
  else
  {
    if ( !a1 && !unk_6EFE78 )
    {
      if ( !unk_6EFE34 )
      {
        if ( unk_6EFDA5 )
        {
          rf_direction_sequence6EFE18_consume_input();
          if ( dword_6EFDA0 == 7 )
          {
            unk_6EFDA4 = 1;
            dword_6619A0 = rf_gamesound_play_event(57, 0, 0.0, 1.0);
            rf_gamesound_stop_voice_handle(dword_66199C);
          }
        }
        else
        {
          rf_direction_sequence6EFDEC_consume_input();
          if ( dword_6EFDA0 == 4 )
          {
            unk_6EFDA5 = 1;
            unk_6EFE34 = 1;
            dword_6EFDA0 = 0;
            rf_gamesound_play_event(56, 0, 0.0, 1.0);
            rf_gamesound_play_event(54, 0, 0.0, 1.0);
          }
        }
        rf_mouse_poll_frame_snapshot_and_motion();
      }
      unk_6EFDBC = unk_6EFDBC - rf_frame_delta_seconds;
      if ( unk_6EFDBC < 0.0 )
      {
        rf_gamesound_stop_voice_handle(dword_66199C);
        unk_6EFDA7 = 1;
        unk_6EFDBC = 0.0;
      }
      for ( i = 0; i < 3; ++i )
      {
        if ( !byte_661968[16 * i] && flt_66196C[4 * i] > (double)unk_6EFDBC )
        {
          dword_661964[4 * i] = rf_gamesound_play_event(dword_661960[4 * i], 0, 0.0, 1.0);
          byte_661968[16 * i] = 1;
        }
      }
    }
    if ( !a1 )
    {
      if ( rf_input_take_press_count(0x45u) == 1 )
      {
        unk_6EFE78 = unk_6EFE78 == 0;
        if ( unk_6EFE78 )
          rf_gamesound_stop_voice_handle(dword_66199C);
        else
          dword_66199C = rf_gamesound_play_event(55, 0, 0.0, 1.0);
      }
      else
      {
        rf_input_get_scan_code_state_byte(1);
      }
    }
  }
  if ( !a1 && !unk_6EFE78 )
  {
    if ( unk_6EFE34 )
    {
      unk_6EFDB8 = rf_frame_delta_seconds * 100.0 / 1.0 + unk_6EFDB8;
      if ( unk_6EFDB8 > 293.0 )
      {
        unk_6EFDB8 = 293.0;
        unk_6EFE34 = 0;
      }
    }
  }
  if ( unk_6EFE79 )
  {
    unk_6EFE79 = 0;
  }
  else if ( !unk_6EFDA6 )
  {
    rf_render_color_set_rgba8(255, 255, 255, 255);
    v9 = dword_187CC7C;
    v5 = (int)(unk_6EFDE8 * 448.0);
    v2 = rf_renderer_get_viewport_width();
    rf_bitmap_blit_subrectangle_backend_dispatch(unk_6EFE14, 0, 0, v2, v5, 0, 0, 640, 448, 0, 0, v9);
    if ( unk_6EFDA5 )
    {
      rf_bitmap_get_resolved_dimensions(dword_6EFE00[0], &v15, &v16);
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_6EFE00[dword_6EFDEC[0]],
        (int)((double)dword_661930[0] * unk_6EFD9C),
        (int)((double)dword_661928 * unk_6EFDE8),
        (int)((double)v15 * unk_6EFD9C),
        (int)((double)v16 * unk_6EFDE8),
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_6EFE00[unk_6EFDF0],
        (int)((double)dword_661934 * unk_6EFD9C),
        (int)((double)dword_661928 * unk_6EFDE8),
        (int)((double)v15 * unk_6EFD9C),
        (int)((double)v16 * unk_6EFDE8),
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_6EFE00[unk_6EFDF4],
        (int)((double)dword_661938 * unk_6EFD9C),
        (int)((double)dword_661928 * unk_6EFDE8),
        (int)((double)v15 * unk_6EFD9C),
        (int)((double)v16 * unk_6EFDE8),
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_6EFE00[unk_6EFDF8],
        (int)((double)dword_66193C * unk_6EFD9C),
        (int)((double)dword_661928 * unk_6EFDE8),
        (int)((double)v15 * unk_6EFD9C),
        (int)((double)v16 * unk_6EFDE8),
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
      rf_bitmap_get_resolved_dimensions(dword_6EFDA8[0], &v15, &v16);
      for ( j = 0; j < dword_6EFDA0; ++j )
        rf_bitmap_blit_subrectangle_backend_dispatch(
          dword_6EFDA8[dword_6EFE18[j]],
          (int)((double)dword_661940[j] * unk_6EFD9C),
          (int)((double)dword_66192C * unk_6EFDE8),
          (int)((double)v15 * unk_6EFD9C),
          (int)((double)v16 * unk_6EFDE8),
          0,
          0,
          v15,
          v16,
          0,
          0,
          dword_187CC7C);
    }
    else
    {
      rf_bitmap_get_resolved_dimensions(dword_6EFDA8[0], &v15, &v16);
      for ( j = 0; j < dword_6EFDA0; ++j )
        rf_bitmap_blit_subrectangle_backend_dispatch(
          dword_6EFDA8[dword_6EFDEC[j]],
          (int)((double)dword_661930[j] * unk_6EFD9C),
          (int)((double)dword_661928 * unk_6EFDE8),
          (int)((double)v15 * unk_6EFD9C),
          (int)((double)v16 * unk_6EFDE8),
          0,
          0,
          v15,
          v16,
          0,
          0,
          dword_187CC7C);
    }
    if ( dword_6EFDA0 <= 0 )
    {
      rf_bitmap_get_resolved_dimensions(dword_66191C, &v15, &v16);
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_66191C,
        (int)(unk_6EFD9C * 78.0),
        (int)(unk_6EFDE8 * 130.0),
        (int)((double)v15 * unk_6EFD9C),
        (int)((double)v16 * unk_6EFDE8),
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
    }
    else
    {
      rf_bitmap_get_resolved_dimensions(dword_661918, &v15, &v16);
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_661918,
        (int)(unk_6EFD9C * 78.0),
        (int)(unk_6EFDE8 * 130.0),
        (int)((double)v15 * unk_6EFD9C),
        (int)((double)v16 * unk_6EFDE8),
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
    }
    v13 = (int)unk_6EFDBC / 60;
    v19 = (int)(unk_6EFDBC - (double)v13 * 60.0);
    v14 = (int)((unk_6EFDBC - (double)v13 * 60.0 - (double)v19) * 100.0);
    rf_bitmap_get_resolved_dimensions(dword_6EFDC0[0], &v15, &v16);
    v21 = (int)((double)v15 * unk_6EFD9C);
    v22 = (int)((double)v16 * unk_6EFDE8);
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDC0[0],
      (int)(unk_6EFD9C * 292.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDC0[0],
      (int)(unk_6EFD9C * 317.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    v25 = v13 / 10;
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDC0[v13 / 10],
      (int)(unk_6EFD9C * 348.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    v25 = v13 - 10 * v25;
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDC0[v25],
      (int)(unk_6EFD9C * 373.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    v25 = v19 / 10;
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDC0[v19 / 10],
      (int)(unk_6EFD9C * 405.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    v25 = v19 - 10 * v25;
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDC0[v25],
      (int)(unk_6EFD9C * 430.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    v25 = v14 / 10;
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDC0[v14 / 10],
      (int)(unk_6EFD9C * 463.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    v25 = v14 - 10 * v25;
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDC0[v25],
      (int)(unk_6EFD9C * 488.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    rf_bitmap_get_resolved_dimensions(dword_6EFDFC, &v15, &v16);
    v21 = (int)((double)v15 * unk_6EFD9C);
    v22 = (int)((double)v16 * unk_6EFDE8);
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDFC,
      (int)(unk_6EFD9C * 341.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_6EFDFC,
      (int)(unk_6EFD9C * 398.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    rf_bitmap_blit_subrectangle_backend_dispatch(
      unk_6EFE10,
      (int)(unk_6EFD9C * 455.0),
      (int)(unk_6EFDE8 * 61.0),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    button_held_byte = rf_mouse_get_button_held_byte(0);
    rf_mouse_get_absolute_state(&v23, &v24, &unk_193A03C);
    rf_bitmap_get_resolved_dimensions(dword_6EFD8C, &v15, &v16);
    v21 = (int)((double)v15 * unk_6EFD9C);
    v22 = (int)((double)v16 * unk_6EFDE8);
    if ( rf_input_get_scan_code_state_byte(208)
      || button_held_byte
      && unk_6EFE54 > (double)v23
      && unk_6EFE50 < (double)v23
      && unk_6EFE48 < (double)v24
      && unk_6EFE4C > (double)v24 )
    {
      rf_bitmap_blit_subrectangle_backend_dispatch(
        unk_6EFD98,
        (int)(unk_6EFD9C * 387.0),
        (int)(unk_6EFDE8 * 366.0),
        v21,
        v22,
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
    }
    else if ( rf_input_get_scan_code_state_byte(200)
           || button_held_byte
           && unk_6EFE44 > (double)v23
           && unk_6EFE40 < (double)v23
           && unk_6EFE38 < (double)v24
           && unk_6EFE3C > (double)v24 )
    {
      rf_bitmap_blit_subrectangle_backend_dispatch(
        dword_6EFD8C,
        (int)(unk_6EFD9C * 386.0),
        (int)(unk_6EFDE8 * 322.0),
        v21,
        v22,
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
    }
    else if ( rf_input_get_scan_code_state_byte(203)
           || button_held_byte
           && unk_6EFE64 > (double)v23
           && unk_6EFE60 < (double)v23
           && unk_6EFE58 < (double)v24
           && unk_6EFE5C > (double)v24 )
    {
      rf_bitmap_blit_subrectangle_backend_dispatch(
        unk_6EFD94,
        (int)(unk_6EFD9C * 344.0),
        (int)(unk_6EFDE8 * 344.0),
        v21,
        v22,
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
    }
    else if ( rf_input_get_scan_code_state_byte(205)
           || button_held_byte
           && unk_6EFE74 > (double)v23
           && unk_6EFE70 < (double)v23
           && unk_6EFE68 < (double)v24
           && unk_6EFE6C > (double)v24 )
    {
      rf_bitmap_blit_subrectangle_backend_dispatch(
        unk_6EFD90,
        (int)(unk_6EFD9C * 426.0),
        (int)(unk_6EFDE8 * 344.0),
        v21,
        v22,
        0,
        0,
        v15,
        v16,
        0,
        0,
        dword_187CC7C);
    }
    rf_render_color_set_rgba8(255, 255, 255, 255);
    rf_bitmap_get_resolved_dimensions(dword_661920, &v15, &v16);
    v21 = (int)((double)v15 * unk_6EFD9C);
    v22 = (int)((double)v16 * unk_6EFDE8);
    rf_renderer_get_viewport_rectangle(&v17, &v12, &v18, &v11);
    rf_renderer_set_viewport_and_relative_clip(0, 0, (int)(unk_6EFD9C * 640.0), (int)(unk_6EFDE8 * 295.0));
    rf_bitmap_blit_subrectangle_backend_dispatch(
      dword_661920,
      (int)(unk_6EFD9C * 244.0),
      (int)(unk_6EFDB8 * unk_6EFDE8),
      v21,
      v22,
      0,
      0,
      v15,
      v16,
      0,
      0,
      dword_187CC7C);
    rf_renderer_set_viewport_and_relative_clip(v17, v12, v18, v11);
    if ( rf_replicator_has_elapsed(&unk_6EFE7C) )
    {
      rf_replicator_reset(&unk_6EFE7C);
    }
    else if ( rf_replicator_is_armed(&unk_6EFE7C) )
    {
      rf_render_color_set_rgba8(255, 255, 255, 255);
      rf_font_draw_text_screen(0x8000, (int)(unk_6EFDE8 * 13.0), unk_88E228, -1, dword_182ABBC);
    }
  }
  result = unk_6EFDA7;
  if ( unk_6EFDA7 )
  {
    rf_render_color_set_rgba8(255, 255, 255, (int)unk_6EFD88);
    v10 = dword_182ABB8;
    v7 = rf_renderer_get_viewport_height();
    v4 = rf_renderer_get_viewport_width();
    result = rf_renderer_fill_rectangle_clipped(0, 0, v4, v7, v10);
  }
  if ( unk_6EFE78 )
    return rf_pause_overlay_render();
  return result;
}

