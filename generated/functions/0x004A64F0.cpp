// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A64F0 rf_multiplayer_log_write_line
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl(message,raw timestamp flag). Requires FILE7B1530 nonnull and message nonnull. Any nonzero flag fetches time64/localtime64 and strftime(max128) prefix %m/%d %H:%M:%S~ followed
// by3 spaces, copies prefix into1024-byte format buffer then appends full message including NUL using native copy loops/rep movs. Zero flag copies message directly. No
// message/combined-size limit, time-conversion or strftime-result check. Appends PE word63B0CC=000Ah (newline thenNUL), overwriting final terminator.
// Calls fputs(buffer,FILE),fflush(FILE),then printf(buffer) with buffer ITSELF as format and NO format arguments, ignoring file/console results. Thus percent sequences are preserved
// for the final printf interpretation. No mode/authority guard or filename operation; existing LF within message remains and an additional LF is always appended.
void __cdecl rf_multiplayer_log_write_line(const char *a1, int a2)
{
  struct tm *v2; // eax
  char v3; // [esp+Bh] [ebp-4D1h]
  _WORD *v4; // [esp+Ch] [ebp-4D0h]
  char v5; // [esp+13h] [ebp-4C9h]
  char *v6; // [esp+18h] [ebp-4C4h]
  const char *v7; // [esp+1Ch] [ebp-4C0h]
  char *v9; // [esp+24h] [ebp-4B8h]
  const char *v10; // [esp+38h] [ebp-4A4h]
  char v11; // [esp+3Fh] [ebp-49Dh]
  char *v12; // [esp+44h] [ebp-498h]
  char *v13; // [esp+48h] [ebp-494h] BYREF
  char Format[1024]; // [esp+4Ch] [ebp-490h] BYREF
  __time64_t Time; // [esp+44Ch] [ebp-90h] BYREF
  char Buffer[132]; // [esp+454h] [ebp-88h] BYREF

  if ( MEMORY[0x7B1530] && a1 )
  {
    if ( a2 )
    {
      Time = rf_crt_time64_forward(nullptr);
      v2 = rf_crt_localtime64_forward(&Time);
      strftime(Buffer, 0x80u, "%m/%d %H:%M:%S~   ", v2);
      v13 = Buffer;
      v12 = Format;
      do
      {
        v11 = *v13;
        *v12++ = *v13++;
      }
      while ( v11 );
      v10 = &a1[strlen(a1) + 1];
      v9 = (char *)&v13 + 3;
      while ( *++v9 )
        ;
      qmemcpy(v9, a1, v10 - a1);
    }
    else
    {
      v7 = a1;
      v6 = Format;
      do
      {
        v5 = *v7;
        *v6++ = *v7++;
      }
      while ( v5 );
    }
    v4 = (_WORD *)((char *)&v13 + 3);
    do
    {
      v3 = *((_BYTE *)v4 + 1);
      v4 = (_WORD *)((char *)v4 + 1);
    }
    while ( v3 );
    *v4 = 10;
    fputs(Format, MEMORY[0x7B1530]);
    fflush(MEMORY[0x7B1530]);
    printf(Format);
  }
}

