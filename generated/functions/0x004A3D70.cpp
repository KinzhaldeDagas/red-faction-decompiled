// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A3D70 rf_browser_apply_server_info_payload1
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Recovered [4A3D70,4A4102), cdecl(payload,sender). No runtime/authority/pending-target/null/length guard or incoming xrefs currently; packet1 pairing from layout. Parses protocol
// BYTE,server name+NUL,mode BYTE,player-count BYTE,max BYTE,level-display+NUL,archive+NUL,flags BYTE. Each string scans full source before strncpy255 and forced destination[254]=0;
// cursor narrowed to uint16 after each string. Archive temp initially256 zero bytes; other string tails are not otherwise initialized. All fields parsed BEFORE protocol check.
// Protocol89h delegates browser-entry helper4660C0(senderDWORD0,senderDWORD1,name,level,archive,players,max,mode,flags). Other versions STILL call it with localized
// incompatible-version name88E224, empty map63A9E7, parsed archive,players0,max0,parsed mode/flags unchanged. No own drop of incompatible responses, extra-port validation, or string
// ownership transfer; helper receives pointers to local strings synchronously.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662954 registers opcode1 (game_info), callback0x004A3D70. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_browser_apply_server_info_payload1(const unsigned __int8 *payload, const void *sender)
{
  __int16 v2; // [esp+Ch] [ebp-350h]
  const unsigned __int8 *v3; // [esp+10h] [ebp-34Ch]
  __int16 v4; // [esp+1Ch] [ebp-340h]
  const unsigned __int8 *v5; // [esp+20h] [ebp-33Ch]
  char v6; // [esp+41h] [ebp-31Bh]
  char v7; // [esp+42h] [ebp-31Ah]
  unsigned __int8 v8; // [esp+43h] [ebp-319h]
  char Destination[256]; // [esp+44h] [ebp-318h] BYREF
  char v10[263]; // [esp+144h] [ebp-218h] BYREF
  char v11; // [esp+24Bh] [ebp-111h]
  int v12; // [esp+24Ch] [ebp-110h]
  char v13; // [esp+253h] [ebp-109h]
  char v14[260]; // [esp+254h] [ebp-108h] BYREF

  v12 = 0;
  v8 = *payload;
  v12 = 1;
  strncpy(Destination, (const char *)payload + 1, 0xFFu);
  Destination[254] = 0;
  v12 = (unsigned __int16)(v12 + strlen((const char *)payload + 1) + 1);
  v7 = payload[v12];
  v6 = payload[++v12];
  v11 = payload[++v12];
  v4 = ++v12 + (_WORD)payload + 1;
  v5 = &payload[v12 + 1 + strlen((const char *)&payload[v12])];
  strncpy(v14, (const char *)&payload[v12], 0xFFu);
  v14[254] = 0;
  v12 = (unsigned __int16)(v12 + (_WORD)v5 - v4 + 1);
  memset(v10, 0, 256);
  v2 = v12 + (_WORD)payload + 1;
  v3 = &payload[v12 + 1 + strlen((const char *)&payload[v12])];
  strncpy(v10, (const char *)&payload[v12], 0xFFu);
  v10[254] = 0;
  v12 = (unsigned __int16)(v12 + (_WORD)v3 - v2 + 1);
  v13 = payload[v12++];
  if ( v8 == 137 )
    rf_browser_apply_server_info_to_rows(
      *(_DWORD *)sender,
      *((_DWORD *)sender + 1),
      Destination,
      v14,
      v10,
      v6,
      v11,
      v7,
      v13);
  else
    rf_browser_apply_server_info_to_rows(
      *(_DWORD *)sender,
      *((_DWORD *)sender + 1),
      (char *)dword_88E224,
      (char *)&unk_63A9E7,
      v10,
      0,
      0,
      v7,
      v13);
}

