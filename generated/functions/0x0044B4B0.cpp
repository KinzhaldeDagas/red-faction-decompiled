// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044B4B0 rf_hud_message_enqueue_expand_tokens_and_rearm_head
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Four cdecl slots(required/nonempty Cstring,IGNORED secondDWORD,signed durationMilliseconds,optional DWORDcolor pointer),
// void/incidental registers. NULL text, text firstBYTE0, or countDWORD6EE6D4==EXACT8 returns before queue writes. Equality8 is the ONLY capacity test: signednegative or>8 counts are
// not rejected. Compute index=signed32_wrap(head6EE6D0+count)%8 with native signed-remainder sequence, then destination=6EE6E0+272*index; no index/head/range/alias guard.  Scan full
// input strlen first. Unsigned length>=256 writes exact24-byte PE literal 'String length exceeded!' includingNUL into ONLY first24 destination bytes; does NOT clear rest of256-byte
// text. Length<256 first memset256 text bytes to0, then scan live source untilNUL. Source/destination aliases are unprotected, so clearing destination can change source. Ordinary
// source byte copies one byte and advances both. On '$', native tests SAME sign-extended current byte PLUS1 against '$'; because entering byte was36,37!=36, so the apparent
// literal-dollar escape arm is UNREACHABLE. '$$' is treated as an empty token, not a literal-dollar escape. Always search from next source byte for closing '$'. Hitting NUL before
// close builds unbounded sprintf diagnostic into stack512 using original source pointer, then calls5708E0(sourcefile 'D:\projects\rf_pc\gamesrc\hud\hud_msg.cpp',line527,diagnostic)
// noreturn exit. Native hypothetical-return branch loops fatal call; no successful malformed-token fallback, queue-count increment or rollback of already-cleared/copied text.
// Closing '$': memset first256 bytes of stack token buffer0, strncpy interior token bytes (close-source-1), call44B800(token), then copy returned bytes into destination UNTIL FIRST
// '$' sentinel, not untilNUL. Destination increments per byte; after sentinel decrements once, then common increment restores correct next-write position. Set source=close+1 and
// continue. On ordinary successful string operations, helper replaces token buffer with resolved binding label plus '$' andNUL; unknown/empty token normally yields '$'+NUL, deleting
// token in caller. Caller neither enforces output256 capacity nor checks returned pointer/NUL; expanded binding text and source aliases retain native effects, and embedded '$' in
// label truncates this token copy. There is NO final explicit destination NUL store on normal scan exit; prezeroed text supplies termination only if expansion remains within it. No
// literal-dollar special handling or safe truncation may be invented.  After text construction, recordDWORD+260=duration if SIGNEDduration>0, else4000ms. RecordDWORD+256=*color if
// pointer nonnull, otherwiseCURRENT globalDWORD6EE6A8; no color pointer validation or source/destination overlap protection. Other8 bytes of272-byte record remain untouched.
// Increment CURRENT count with32-bit wrap. Only if new signedcount>0: overwrite activeIndex6616C8=CURRENT rawhead6EE6D0 and rearm CURRENT head deadline6EE6D8, even if another message
// was already active. Delay is current head record durationDWORD[6EE7E4+272*active]; new signedcount>1 uses signedmin(200,that duration), else full duration. Thus enqueue can
// shorten/restart oldest message timer and does not necessarily use newly enqueued record's duration. Signednonpositive wrappedcount leaves active/timer untouched after record/count
// writes. No immediate render, audio, history log, priority interpretation of ignored second argument, pause/authority gate, uniform success return or rollback. Normal
// security-cookie check605EE4 adds no EAX normalization.
void __cdecl rf_hud_message_enqueue_expand_tokens_and_rearm_head(const char *a1, int a2, int a3, _DWORD *a4)
{
  char *v4; // eax
  int v5; // eax
  char Buffer[512]; // [esp+10h] [ebp-320h] BYREF
  char *j; // [esp+210h] [ebp-120h]
  _BYTE *i; // [esp+214h] [ebp-11Ch]
  char Destination[260]; // [esp+218h] [ebp-118h] BYREF
  void *v10; // [esp+320h] [ebp-10h]
  const char *v11; // [esp+324h] [ebp-Ch]
  int v12; // [esp+328h] [ebp-8h]
  _DWORD *v13; // [esp+32Ch] [ebp-4h]

  if ( a1 && *a1 && dword_6EE6D4 != 8 )
  {
    v12 = (dword_6EE6D4 + unk_6EE6D0) % 8;
    v13 = (_DWORD *)((char *)&unk_6EE6E0 + 272 * v12);
    if ( strlen(a1) < 0x100 )
    {
      v11 = a1;
      v10 = v13;
      memset(v13, 0, 0x100u);
      while ( *v11 )
      {
        if ( *v11 == 36 )
        {
          if ( *v11 == 35 )
          {
            *(_BYTE *)v10 = 36;
            v11 += 2;
          }
          else
          {
            for ( i = v11 + 1; *i != 36; ++i )
            {
              if ( !*i )
              {
                sprintf(Buffer, "String contains unterminated special character token: %s\n", a1);
                rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\gamesrc\\hud\\hud_msg.cpp", 527, Buffer);
              }
            }
            memset(Destination, 0, 0x100u);
            strncpy(Destination, v11 + 1, i - v11 - 1);
            for ( j = rf_hud_expand_control_token_in_place(Destination); *j != 36; ++j )
            {
              *(_BYTE *)v10 = *j;
              v10 = (char *)v10 + 1;
            }
            v10 = (char *)v10 - 1;
            v11 = i + 1;
          }
        }
        else
        {
          *(_BYTE *)v10 = *v11++;
        }
        v10 = (char *)v10 + 1;
      }
    }
    else
    {
      v4 = (char *)v13;
      *v13 = 1769108563;
      strcpy(v4 + 4, "ng length exceeded!");
    }
    if ( a3 > 0 )
      v13[65] = a3;
    else
      v13[65] = 4000;
    if ( a4 )
      v13[64] = *a4;
    else
      v13[64] = *(_DWORD *)byte_6EE6A8;
    if ( ++dword_6EE6D4 > 0 )
    {
      dword_6616C8 = unk_6EE6D0;
      if ( dword_6EE6D4 <= 1 )
      {
        rf_replicator_arm_milliseconds(unk_6EE6D8, unk_6EE7E4[68 * dword_6616C8]);
      }
      else
      {
        v5 = rf_int_min_signed(200, unk_6EE7E4[68 * dword_6616C8]);
        rf_replicator_arm_milliseconds(unk_6EE6D8, v5);
      }
    }
  }
}

