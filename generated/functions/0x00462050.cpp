// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462050 rf_browser_export_row_to_cache100
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Cdecl(rawRow,dest100),returns flags&3. Unguarded108-byte row atbase6F52CC:copy IPv4DWORD84->dest0 and entireDWORD88->dest4 (portWORD plus paddingWORD90). Copy
// serverName0->dest8 withstrncpy31/NUL39,map32->dest40 with31/NUL71,mod/archive64->dest72 with15/NUL87. Copy modeDWORD80->dest88,playersBYTE92/max93 unchanged,pingWORD94
// unchanged,flagsDWORD104&3->dest96. Disk100 format excludes query timestamp96,retry100,and high runtime flags;favorite membership is represented by the separate favorites file. No
// allocation,index/pointer/capacity validation or I/O here.
int __cdecl rf_browser_export_row_to_cache100(int a1, int a2)
{
  int v2; // eax
  int result; // eax

  v2 = *((_DWORD *)dword_6F52CC + 27 * a1 + 22);
  *(_DWORD *)a2 = *((_DWORD *)dword_6F52CC + 27 * a1 + 21);
  *(_DWORD *)(a2 + 4) = v2;
  strncpy((char *)(a2 + 8), (const char *)dword_6F52CC + 108 * a1, 0x1Fu);
  *(_BYTE *)(a2 + 39) = 0;
  strncpy((char *)(a2 + 40), (const char *)dword_6F52CC + 108 * a1 + 32, 0x1Fu);
  *(_BYTE *)(a2 + 71) = 0;
  strncpy((char *)(a2 + 72), (const char *)dword_6F52CC + 108 * a1 + 64, 0xFu);
  *(_BYTE *)(a2 + 87) = 0;
  *(_DWORD *)(a2 + 88) = *((_DWORD *)dword_6F52CC + 27 * a1 + 20);
  *(_BYTE *)(a2 + 92) = *((_BYTE *)dword_6F52CC + 108 * a1 + 92);
  *(_BYTE *)(a2 + 93) = *((_BYTE *)dword_6F52CC + 108 * a1 + 93);
  *(_WORD *)(a2 + 94) = *((_WORD *)dword_6F52CC + 54 * a1 + 47);
  result = *((_DWORD *)dword_6F52CC + 27 * a1 + 26) & 3;
  *(_DWORD *)(a2 + 96) = result;
  return result;
}

