// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004490B0 rf_screenshot_schedule_first_unresolved_date_path
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(optional writable outputCstring pointer), no normalized success/failure return. Build stack prefix from _strdate
// wrapper5951A0 output bytes0,1,3,4, append literal '_screen' via exact8-byte copy including NUL. No date-format result check. Construct ONE280-byte VFile5923E0 reused for all
// candidates. Signed i runs0..999. sprintf four-byte local with original '%3d'; i<10 explicitly overwrites firstTWO bytes with'0',10<=i<100 firstONE byte with'0', so ordinary
// candidates are000..999. Construct RFString from number, concat prefix+number into second RFString, get borrowed Cstring, then57B560(globalDWORD88E3F4,name,GLOBAL path
// buffer6EDC38). Destroy concat string then number string each iteration. Reread format BYTE6EDD40 each candidate: EXACT1 appends '.tga', all other bytes append '.jpg', by raw5-byte
// copies includingNUL. Call5929A0(this=stackVFile,current GLOBAL path,rawDWORD0x0098967F decimal9999999). ANYnonzero AL means source resolved and advances candidate; AL0 immediately
// selects that candidate. There is no separate existence/writability/capture-success query, file reservation, deletion or explicit per-iteration VFile destructor; resolver side
// effects remain native.  If all1000 queries return nonzero, call568050(event2,group0,FLOAT0,FLOAT1), then44B4B0(original fixed 'No free screenshot filenames found... maybe you
// should delete some of those 1000 jpgs!',0,0,NULL), even when selected format wasTGA. Do not write optional output, strip path extension or set pending flag on this branch;
// preexisting pending/path state is not cleared. Both normal outcomes finally destroy/close stack VFile592420 once. Normal605EE4 cookie check preserves EAX (original CMP
// ECX,cookie/JNE/REP RET), so EAX is VFile destructor/close residue on BOTH branches, not success1/failure0.  First unresolved candidate: if output pointer nonnull, forward-copy full
// GLOBAL path INCLUDING extension and terminatingNUL with no capacity/overlap guard. AFTER that optional copy, rescan CURRENT global path to obtain length L and write
// byte[6EDC34+L]=0, i.e. GLOBAL path[L-4]=0; strip four extension bytes from pending capture base path, not from already-copied caller result. No length>=4 check; aliasing can change
// rescan input. Set pending BYTE6EDD39=EXACT1, then destroy VFile. Actual renderer capture is deferred to449460, not performed here. Compiler SEH state/cleanup funclets cover stack
// VFile and the two RFStrings; application state has no rollback. There is no pending-flag admission: another request overwrites global path and can schedule over an already pending
// capture; capture later rereads format rather than retaining this extension choice. No input mode/pause/dead/authority gate or own finite arithmetic; onlyx87 operations push sound
// FLOAT0/1.
int __cdecl rf_screenshot_schedule_first_unresolved_date_path(_BYTE *a1)
{
  const char *v1; // eax
  char v3; // [esp+23h] [ebp-1A5h]
  _BYTE *v4; // [esp+28h] [ebp-1A0h]
  char *v5; // [esp+2Ch] [ebp-19Ch]
  std::exception *v6; // [esp+40h] [ebp-188h]
  const void **v7; // [esp+48h] [ebp-180h]
  char *v9; // [esp+54h] [ebp-174h]
  char v10[8]; // [esp+58h] [ebp-170h] BYREF
  char v11[7]; // [esp+60h] [ebp-168h] BYREF
  char v12; // [esp+67h] [ebp-161h] BYREF
  char v13[32]; // [esp+68h] [ebp-160h] BYREF
  char v14[16]; // [esp+88h] [ebp-140h] BYREF
  char Buffer[4]; // [esp+98h] [ebp-130h] BYREF
  int self[70]; // [esp+9Ch] [ebp-12Ch] BYREF
  int i; // [esp+1B8h] [ebp-10h]
  int v18; // [esp+1C4h] [ebp-4h]

  rf_system_format_local_date_strdate(v14);
  v13[0] = v14[0];
  v13[1] = v14[1];
  v13[2] = v14[3];
  v13[3] = v14[4];
  v13[4] = 0;
  v9 = &v12;
  while ( *++v9 )
    ;
  *(_DWORD *)v9 = 1919120223;
  *((_DWORD *)v9 + 1) = &unk_6E6565;
  rf_vfile_construct_unopened(self);
  v18 = 0;
  for ( i = 0; i < 1000; ++i )
  {
    sprintf(Buffer, off_633FA8, i);
    if ( i >= 10 )
    {
      if ( i < 100 )
        Buffer[0] = 48;
    }
    else
    {
      memset(Buffer, 48, 2);
    }
    v7 = (const void **)rf_string_construct_from_cstr(v11, Buffer);
    LOBYTE(v18) = 1;
    v6 = (std::exception *)rf_string_concat_cstr_object(v10, v13, v7);
    LOBYTE(v18) = 2;
    v1 = rf_string_object_c_str_or_empty(v6);
    rf_vfile_build_loose_path(dword_88E3F4, v1, unk_6EDC38);
    LOBYTE(v18) = 1;
    rf_string_destroy_buffer(v10);
    LOBYTE(v18) = 0;
    rf_string_destroy_buffer(v11);
    if ( unk_6EDD40 == 1 )
      strcat(unk_6EDC38, ".tga");
    else
      strcat(unk_6EDC38, ".jpg");
    if ( !rf_vfile_resolve_open_source((int)self, unk_6EDC38, (int)byte_98967F) )
      break;
  }
  if ( i == 1000 )
  {
    rf_gamesound_play_event(2, 0, 0.0, 1.0);
    rf_hud_message_enqueue_expand_tokens_and_rearm_head(
      "No free screenshot filenames found... maybe you should delete some of those 1000 jpgs!",
      0,
      0,
      nullptr);
    v18 = -1;
    return rf_vfile_destruct_close_if_open(self);
  }
  else
  {
    if ( a1 )
    {
      v5 = unk_6EDC38;
      v4 = a1;
      do
      {
        v3 = *v5;
        *v4++ = *v5++;
      }
      while ( v3 );
    }
    byte_6EDC34[&unk_6EDC38[strlen(unk_6EDC38) + 1] - (char *)&unk_6EDC39] = 0;
    unk_6EDD39 = 1;
    v18 = -1;
    return rf_vfile_destruct_close_if_open(self);
  }
}

