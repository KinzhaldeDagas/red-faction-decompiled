// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058E020 rf_movie_play_bink_blocking
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): Cdecl filename. Only proceeds when backend187CC9C==102 and main HWND nonNULL; stored HWND return type is inference residue,not a uniform status/handle contract. If193BBD8 unset,initializes cached pixel formats/resolution. Sets tileWidth193BBCC=min(UNSIGNED cap1DAE868,256),tileHeight193BBC8=min(UNSIGNED cap1DAE86C,256). Since both<=256,the subsequent >=640 AND >=480 direct-surface choice cannot occur for these freshly assigned caps: normal path always tiled. Computes ceil(640/tileWidth),ceil(480/tileHeight) with integer division/remainder; zero cap has NO divisor guard. Creates user bitmap using cached kind193BBD0; handle-1 returns immediately. Tiled path allocates640x480 temp surface
// through device vtable108 using cached format193BBAC; negative result returns WITHOUT recycling created bitmap. Retained direct branch creates640x480 bitmap and sets tempNULL. Constructs VFile,resolves source path and copies resolved filename to264-byte local with unbounded NUL copy. Configures Bink sound(BinkOpenDirectSound,0),opens Bink with flags0. On success resets viewport,sets black RGBA,clears/presents TWICE,then synchronous loop: calls known no-op lifecycle adapter,dequeues ONE unsigned16 scan event per iteration,exits if code1,otherwise if BinkWait==0 calls frame helper58E420 until complete. Does not treat arbitrary key as abort or pump Windows messages in this function. On successful-open exit closes Bink and zeros193BBD4,recycles bitmap if handle!=-1 WITHOUT clearing stored193BBB0,and releases/NULLs temp surface. Failed VFile resolve or failed BinkOpen skips bitmap/temp cleanup
// and only invokes VFile destructor; no central rollback. Format initialization flag remains set between movies. Return paths contain main HWND,bitmap/HRESULT or VFile-destructor residue; no consistent success value,dimension validation or filename bound.
HWND __cdecl rf_movie_play_bink_blocking(char *String2)
{
  HWND result; // eax
  int v2; // eax
  char v3; // [esp+7h] [ebp-259h]
  _BYTE *v4; // [esp+Ch] [ebp-254h]
  char *filename_buffer_pointer; // [esp+10h] [ebp-250h]
  int v6; // [esp+14h] [ebp-24Ch]
  int v7; // [esp+18h] [ebp-248h]
  _BYTE v8[264]; // [esp+24h] [ebp-23Ch] BYREF
  HWND v9; // [esp+12Ch] [ebp-134h]
  int frame; // [esp+130h] [ebp-130h]
  int self[70]; // [esp+134h] [ebp-12Ch] BYREF
  HWND v12; // [esp+250h] [ebp-10h]
  int v13; // [esp+25Ch] [ebp-4h]

  result = rf_window_get_main_hwnd();
  v12 = result;
  if ( dword_187CC9C == 102 && v12 )
  {
    if ( !unk_193BBD8 )
      rf_movie_cache_bink_format_once();
    if ( unk_1DAE868 <= 0x100u )
      v7 = unk_1DAE868;
    else
      v7 = 256;
    dword_193BBCC = v7;
    if ( unk_1DAE86C <= 0x100u )
      v6 = unk_1DAE86C;
    else
      v6 = 256;
    dword_193BBC8 = v6;
    if ( dword_193BBCC >= 640 && dword_193BBC8 >= 480 )
    {
      unk_193BBC0 = 0;
    }
    else
    {
      unk_193BBC0 = 1;
      unk_193BBB8 = 640 / dword_193BBCC;
      if ( 640 % dword_193BBCC )
        ++unk_193BBB8;
      unk_193BBBC = 480 / dword_193BBC8;
      if ( 480 % dword_193BBC8 )
        ++unk_193BBBC;
    }
    if ( unk_193BBC0 )
    {
      result = (HWND)rf_bitmap_create_user_bitmap(unk_193BBD0, dword_193BBCC, dword_193BBC8);
      dword_193BBB0 = (unsigned int)result;
      if ( result == HWND_MESSAGE|0x2 )
        return result;
      result = (HWND)(*(int (__stdcall **)(int, int, int, _DWORD, _DWORD **))(*(_DWORD *)dword_1DAEDC4 + 108))(
                       dword_1DAEDC4,
                       640,
                       480,
                       unk_193BBAC,
                       &dword_193BBB4);
      v9 = result;
      if ( (int)result < 0 )
        return result;
    }
    else
    {
      result = (HWND)rf_bitmap_create_user_bitmap(unk_193BBD0, 640, 480);
      dword_193BBB0 = (unsigned int)result;
      if ( result == HWND_MESSAGE|0x2 )
        return result;
      dword_193BBB4 = nullptr;
    }
    rf_vfile_construct_unopened(self);
    v13 = 0;
    if ( rf_vfile_resolve_open_source((int)self, String2, (int)byte_98967F) )
    {
      filename_buffer_pointer = rf_vfile_get_filename_buffer_pointer((char *)self);
      v4 = v8;
      do
      {
        v3 = *filename_buffer_pointer;
        *v4++ = *filename_buffer_pointer++;
      }
      while ( v3 );
      BinkSetSoundSystem(BinkOpenDirectSound, 0);
      v2 = BinkOpen(v8, 0);
      dword_193BBD4 = v2;
      if ( v2 )
      {
        rf_renderer_reset_viewport_full_screen();
        rf_render_color_set_rgba8(0, 0, 0, 255);
        rf_renderer_clear_color_backend_dispatch();
        rf_renderer_present_with_full_viewport();
        rf_renderer_clear_color_backend_dispatch();
        rf_renderer_present_with_full_viewport();
        frame = 0;
        while ( !frame )
        {
          rf_window_noop_lifecycle_adapter();
          if ( rf_input_dequeue_event() == 1 )
            break;
          if ( !BinkWait(dword_193BBD4) )
            frame = rf_movie_bink_decode_draw_next_frame(dword_193BBD4);
        }
        if ( dword_193BBD4 )
        {
          BinkClose(dword_193BBD4);
          dword_193BBD4 = 0;
        }
        if ( dword_193BBB0 != -1 )
          rf_bitmap_handle_recycle_slot_or_animation_entry(dword_193BBB0);
        if ( dword_193BBB4 )
        {
          (*(void (__stdcall **)(_DWORD *))(*dword_193BBB4 + 8))(dword_193BBB4);
          dword_193BBB4 = nullptr;
        }
      }
      v13 = -1;
      return (HWND)rf_vfile_destruct_close_if_open(self);
    }
    else
    {
      v13 = -1;
      return (HWND)rf_vfile_destruct_close_if_open(self);
    }
  }
  return result;
}

