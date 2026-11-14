// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AFED0 rf_multiplayer_send_players_roster_packet6
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Cdecl recipient. No runtime/authority/NULL/net guards. First circular player-list walk counts peers whose netID BYTE20 differs from recipient's netID
// (compares IDs, not pointers), count wraps BYTE. Second walk serializes ALL matching peers. Each tag0 record: idBYTE,netflagsDWORD8,IPv4DWORD0,portWORD4,name bytes+NUL,teamBYTE48.
// Fixed record14 bytes plus name length. No count header. Full name scan truncated unsigned16 before memcpy; Size DWORD narrowed16 only at name advance, no512-byte packet capacity
// clamp. After exactly8 records append tag1 if signed remaining>0, else tag2 and mark completion-sent; remaining initialized from wrapped BYTE count and decremented once per actual
// record. Final payloadWORD=size-3, reliable_queue(recipient,packet,size,requireActive0); reset header/count and continue even after tag2. On loop end, if partial records OR no
// completion marker sent, append tag2 and queue. Thus empty roster sends4-byte envelope containing2, exact multiple8 sends no redundant final packet after terminal batch. For >255
// records wrapped remaining can cause premature tag2 while later records still transmit. Next circular link read after queue call. No send-failure aggregation or dedup; final EAX
// queue/list residue.
int __cdecl rf_multiplayer_send_players_roster_packet6(int a1)
{
  int result; // eax
  const char *v2; // eax
  unsigned __int16 v3; // [esp+0h] [ebp-258h]
  int v4; // [esp+10h] [ebp-248h]
  int v5; // [esp+14h] [ebp-244h]
  size_t Size; // [esp+3Ch] [ebp-21Ch]
  size_t Sizea; // [esp+3Ch] [ebp-21Ch]
  size_t Sizeb; // [esp+3Ch] [ebp-21Ch]
  size_t Sizec; // [esp+3Ch] [ebp-21Ch]
  size_t Sized; // [esp+3Ch] [ebp-21Ch]
  unsigned __int8 Src[512]; // [esp+40h] [ebp-218h] BYREF
  unsigned __int8 v12; // [esp+247h] [ebp-11h]
  int v13; // [esp+248h] [ebp-10h]
  int i; // [esp+24Ch] [ebp-Ch]
  char v15; // [esp+253h] [ebp-5h]
  int v16; // [esp+254h] [ebp-4h]

  v12 = 0;
  for ( i = dword_87C324; i; i = v5 )
  {
    if ( *(char *)(*(_DWORD *)(i + 4608) + 20) != *(char *)(*(_DWORD *)(a1 + 4608) + 20) )
      ++v12;
    if ( *(_DWORD *)i == dword_87C324 )
      v5 = 0;
    else
      v5 = *(_DWORD *)i;
  }
  v13 = 0;
  Src[0] = 6;
  Size = 3;
  result = 0;
  v15 = 0;
  v16 = v12;
  for ( i = dword_87C324; i; i = v4 )
  {
    if ( *(char *)(*(_DWORD *)(i + 4608) + 20) != *(char *)(*(_DWORD *)(a1 + 4608) + 20) )
    {
      Src[Size] = 0;
      Sizea = Size + 1;
      Src[Sizea++] = *(_BYTE *)(*(_DWORD *)(i + 4608) + 20);
      *(_DWORD *)&Src[Sizea] = *(_DWORD *)(*(_DWORD *)(i + 4608) + 8);
      Sizea += 4;
      *(_DWORD *)&Src[Sizea] = **(_DWORD **)(i + 4608);
      Sizea += 4;
      *(_WORD *)&Src[Sizea] = *(_WORD *)(*(_DWORD *)(i + 4608) + 4);
      Sizea += 2;
      v3 = strlen(rf_string_object_c_str_or_empty((const void *)(i + 8)));
      v2 = rf_string_object_c_str_or_empty((const void *)(i + 8));
      memcpy(&Src[Sizea], v2, v3);
      Sizeb = (unsigned __int16)(Sizea + v3);
      Src[Sizeb++] = 0;
      Src[Sizeb] = *(_BYTE *)(i + 48);
      Size = Sizeb + 1;
      ++v15;
      --v16;
      if ( v15 == 8 )
      {
        if ( v16 <= 0 )
        {
          v13 = 1;
          Src[Size] = 2;
        }
        else
        {
          Src[Size] = 1;
        }
        Sizec = Size + 1;
        *(_WORD *)&Src[1] = Sizec - 3;
        rf_multiplayer_queue_reliable_packet(a1, Src, Sizec, 0);
        Src[0] = 6;
        Size = 3;
        v15 = 0;
      }
    }
    result = i;
    if ( *(_DWORD *)i == dword_87C324 )
    {
      v4 = 0;
    }
    else
    {
      result = *(_DWORD *)i;
      v4 = *(_DWORD *)i;
    }
  }
  if ( v15 || !v13 )
  {
    Src[Size] = 2;
    Sized = Size + 1;
    *(_WORD *)&Src[1] = Sized - 3;
    return rf_multiplayer_queue_reliable_packet(a1, Src, Sized, 0);
  }
  return result;
}

