// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058E420 rf_movie_bink_decode_draw_next_frame
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Cdecl Bink handle. Calls BinkDoFrame first. Tiled193BBC0 path locks temp surface via vtable36 into(pitch,pixels); negative result fatals bink_player.cpp157. Direct path locks user bitmap with backend(mode0,option1); false fatals168,reads pixels descriptor[3] and pitch[6]. If pixelsNULL,skips copy AND unlock,still checks/advances frame. Otherwise calls BinkCopyToBuffer(handle,pixels,pitch,480,0,0,cachedFormat193BBC4|80000000h),then unlocks temp via vtable40 or bitmap descriptor. Copy return0 permits rendering; nonzero skips draw/present but still advances. Tiled draw obtains first GPU texture and level0 surface via texture vtable60(return ignored,surface initiallyNULL); no local release
// of obtained level surface. Iterates ceil tile rows/columns covering fixed640x480. For each tile,device vtable112 copies sourceRECT from temp to texture destinationPOINT(0,0),ignores result,blits source(0,0,tileW,tileH) to integer-scaled screen rectangles based on current187CC94/98,then flushes immediate buffers. Final partial tiles recalculate scaled width/height by integer division. Direct branch blits full640x480 using cached screen dimensions664760/4. Presents once after successful copy/draw. Finally if Bink DWORD12==DWORD8 returns1 without NextFrame; else BinkNextFrame and returns0. Does not wait for decode readiness itself,validate handle/texture/surface pointers/COM results,clear letterboxing per frame or reset viewport/color here.
int __cdecl rf_movie_bink_decode_draw_next_frame(int a1)
{
  _DWORD v2[4]; // [esp+0h] [ebp-88h] BYREF
  int v3; // [esp+10h] [ebp-78h]
  int j; // [esp+14h] [ebp-74h]
  int v5; // [esp+18h] [ebp-70h]
  int v6; // [esp+1Ch] [ebp-6Ch]
  int v7; // [esp+20h] [ebp-68h]
  int v8; // [esp+24h] [ebp-64h]
  int v9; // [esp+28h] [ebp-60h]
  int i; // [esp+2Ch] [ebp-5Ch]
  int v11; // [esp+30h] [ebp-58h]
  int v12; // [esp+34h] [ebp-54h]
  int v13; // [esp+38h] [ebp-50h] BYREF
  int first_gpu_texture; // [esp+3Ch] [ebp-4Ch]
  int v15; // [esp+40h] [ebp-48h]
  int v16; // [esp+44h] [ebp-44h]
  _DWORD v17[2]; // [esp+48h] [ebp-40h] BYREF
  int v18; // [esp+50h] [ebp-38h]
  int v19; // [esp+54h] [ebp-34h]
  unsigned int v20; // [esp+58h] [ebp-30h]
  unsigned int v21[8]; // [esp+5Ch] [ebp-2Ch] BYREF
  unsigned int v22; // [esp+7Ch] [ebp-Ch]
  _DWORD v23[2]; // [esp+80h] [ebp-8h] BYREF

  BinkDoFrame(a1);
  v20 = 0;
  v22 = -1;
  if ( unk_193BBC0 )
  {
    v19 = (*(int (__stdcall **)(_DWORD *, _DWORD *, _DWORD, _DWORD))(*dword_193BBB4 + 36))(dword_193BBB4, v23, 0, 0);
    if ( v19 < 0 )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\vsdk\\bink_player\\bink_player.cpp",
        157,
        "Couldn't lock temp surface while playing movie!");
    v20 = v23[1];
    v22 = v23[0];
  }
  else
  {
    if ( !rf_bitmap_lock_pixels_backend_dispatch(dword_193BBB0, 0, v21, 1u) )
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\vsdk\\bink_player\\bink_player.cpp",
        168,
        "Couldn't lock off screen surface while playing movie");
    v20 = v21[3];
    v22 = v21[6];
  }
  if ( v20 )
  {
    v18 = BinkCopyToBuffer(a1, v20, v22, 480, 0, 0, unk_193BBC4 | 0x80000000);
    if ( unk_193BBC0 )
      (*(void (__stdcall **)(_DWORD *))(*dword_193BBB4 + 40))(dword_193BBB4);
    else
      rf_bitmap_unlock_pixels_backend_dispatch(v21);
    if ( !v18 )
    {
      if ( unk_193BBC0 )
      {
        v17[0] = 0;
        v17[1] = 0;
        first_gpu_texture = rf_d3d8_bitmap_get_first_gpu_texture(dword_193BBB0);
        v13 = 0;
        (*(void (__stdcall **)(int, _DWORD, int *))(*(_DWORD *)first_gpu_texture + 60))(first_gpu_texture, 0, &v13);
        v12 = 480;
        v15 = 0;
        v16 = 0;
        v11 = dword_187CC98 * dword_193BBC8 / 480;
        for ( i = 0; i < unk_193BBBC; ++i )
        {
          if ( v12 >= dword_193BBC8 )
          {
            v9 = dword_193BBC8;
          }
          else
          {
            v9 = v12;
            v11 = dword_187CC98 * v12 / 480;
          }
          v8 = 640;
          v6 = 0;
          v5 = 0;
          v7 = dword_187CC94 * dword_193BBCC / 640;
          for ( j = 0; j < unk_193BBB8; ++j )
          {
            if ( v8 >= dword_193BBCC )
            {
              v3 = dword_193BBCC;
            }
            else
            {
              v3 = v8;
              v7 = dword_187CC94 * v8 / 640;
            }
            v2[0] = v6;
            v2[1] = v15;
            v2[2] = v3 + v6;
            v2[3] = v9 + v15;
            (*(void (__thiscall **)(int, int, _DWORD *, _DWORD *, int, int, _DWORD *))(*(_DWORD *)dword_1DAEDC4 + 112))(
              dword_1DAEDC4,
              dword_1DAEDC4,
              dword_193BBB4,
              v2,
              1,
              v13,
              v17);
            rf_bitmap_blit_subrectangle_backend_dispatch(
              dword_193BBB0,
              v5,
              v16,
              v7,
              v11,
              0,
              0,
              v3,
              v9,
              0,
              0,
              dword_187CC7C);
            rf_renderer_flush_immediate_buffers();
            v8 -= v3;
            v6 += v3;
            v5 += v7;
          }
          v12 -= v9;
          v15 += v9;
          v16 += v11;
        }
      }
      else
      {
        rf_bitmap_blit_subrectangle_backend_dispatch(
          dword_193BBB0,
          0,
          0,
          dword_664760,
          dword_664764,
          0,
          0,
          640,
          480,
          0,
          0,
          dword_187CC7C);
      }
      rf_renderer_present_with_full_viewport();
    }
  }
  if ( *(_DWORD *)(a1 + 12) == *(_DWORD *)(a1 + 8) )
    return 1;
  BinkNextFrame(a1);
  return 0;
}

