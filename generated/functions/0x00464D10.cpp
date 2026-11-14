// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00464D10 rf_browser_accept_manual_address
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Noarg modal confirm callback. Zero100-byte record,set pingWORD94=-1. Copy modal edit text with capacity31 (max30 chars+NUL) to local buffer. strtok first token using
// colon/space delimiters;reject NULL/empty,inet_addr==FFFFFFFF (also rejects broadcast255.255.255.255). Store ntohlIPv4;second token via strtok delimiter colon/space ->atoi then
// LOWWORD port;missing token defaults7755. No DNS/IPv6/numeric port-range check;extra tokens ignored. Import100 favorite0;valid returned raw index ->addfavorite462230,OR
// queued40000000,reset retryBYTE1000,rebuild indices. No cancel/UIhold/cursor reset,immediate packet or rollback when favorite array full. Whole record zeroing does not cure
// importer's uninitialized108-byte query fields.
void rf_browser_accept_manual_address()
{
  int v0; // [esp+10h] [ebp-A0h]
  const char *v1; // [esp+14h] [ebp-9Ch]
  _DWORD v2[26]; // [esp+18h] [ebp-98h] BYREF
  u_long netlong; // [esp+80h] [ebp-30h]
  char *cp; // [esp+84h] [ebp-2Ch]
  char Destination[32]; // [esp+88h] [ebp-28h] BYREF
  char *String; // [esp+ACh] [ebp-4h]

  String = Destination;
  memset(v2, 0, 0x64u);
  HIWORD(v2[23]) = -1;
  rf_ui_copy_modal_edit_text(Destination, 31);
  cp = strtok(String, ": ");
  if ( cp )
  {
    if ( strlen(cp) )
    {
      netlong = inet_addr(cp);
      if ( netlong != -1 )
      {
        v2[0] = ntohl(netlong);
        v1 = strtok(nullptr, ": ");
        if ( v1 )
          LOWORD(v2[1]) = atoi(v1);
        else
          LOWORD(v2[1]) = 7755;
        v0 = rf_browser_import_cache100((int)v2, 0);
        if ( v0 >= 0 && v0 < dword_6F51A8 )
        {
          rf_browser_add_favorite_row(v0);
          *((_DWORD *)dword_6F52CC + 27 * v0 + 26) |= 0x40000000u;
          *((_BYTE *)dword_6F52CC + 108 * v0 + 100) = 0;
          rf_browser_rebuild_filtered_sorted_row_indices();
        }
      }
    }
  }
}

