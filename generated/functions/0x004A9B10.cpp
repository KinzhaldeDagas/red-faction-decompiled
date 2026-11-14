// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A9B10 rf_multiplayer_queue_entity_updates_to_peers
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): No arguments and NO own runtime/authority guard; server-session caller supplies role. Walk circular player list; skip local,require net4608
// nonnull/state12==2. If net game deadline2500 unarmed OR elapsed, rearm with raw net DWORD2496. Builds512-byte opcode38 packet, scans entity list68211C to sentinel681E90 via next652
// after work. Skip entity2064 bit1/common124 bit2; dereferences entity.motion632 WITHOUT null guard before testing sampleCount1332>0 OR entity==local. Encode each admitted record
// into separate512-byte scratch. If SIGNED currentSize+recordSize>508, append DWORD-1, set payload length, queue current packet, restart header3. Then memcpy ENTIRE record even if
// oversized; no independent single-record<=505 guard. At list end ALWAYS append sentinel and queue, including header-only/empty result. Whole records not split; normal maximum
// total512 with4-byte sentinel. Iterators read next after calls; no saved-next protection or aggregate transport success.
char rf_multiplayer_queue_entity_updates_to_peers()
{
  int v0; // eax
  int v2; // [esp+0h] [ebp-430h]
  int Size; // [esp+14h] [ebp-41Ch]
  size_t v4; // [esp+1Ch] [ebp-414h]
  size_t v5; // [esp+1Ch] [ebp-414h]
  size_t v6; // [esp+1Ch] [ebp-414h]
  char v7[512]; // [esp+20h] [ebp-410h] BYREF
  int j; // [esp+220h] [ebp-210h]
  int v9; // [esp+224h] [ebp-20Ch]
  _BYTE Src[512]; // [esp+228h] [ebp-208h] BYREF
  int i; // [esp+42Ch] [ebp-4h]

  v9 = 508;
  LOBYTE(v0) = dword_87C324;
  for ( i = dword_87C324; i; i = v2 )
  {
    LOBYTE(v0) = i;
    if ( i != rf_local_fpgun_player )
    {
      if ( *(_DWORD *)(i + 4608) )
      {
        v0 = *(_DWORD *)(i + 4608);
        if ( *(_DWORD *)(v0 + 12) == 2 )
        {
          if ( !rf_replicator_is_armed((_DWORD *)(*(_DWORD *)(i + 4608) + 2500))
            || (LOBYTE(v0) = rf_replicator_has_elapsed((int *)(*(_DWORD *)(i + 4608) + 2500)), (_BYTE)v0) )
          {
            rf_replicator_arm_milliseconds(
              (int *)(*(_DWORD *)(i + 4608) + 2500),
              *(_DWORD *)(*(_DWORD *)(i + 4608) + 2496));
            v7[0] = 38;
            v4 = 3;
            for ( j = unk_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
            {
              if ( (*(_DWORD *)(j + 2064) & 1) == 0
                && (*(_DWORD *)(j + 124) & 2) == 0
                && (*(int *)(*(_DWORD *)(j + 632) + 1332) > 0 || j == dword_681E38) )
              {
                Size = rf_replication_encode_entity_record38(i, j, (int)Src);
                if ( (int)(Size + v4) > v9 )
                {
                  *(_DWORD *)&v7[v4] = -1;
                  v5 = v4 + 4;
                  *(_WORD *)&v7[1] = v5 - 3;
                  rf_network_queue_unreliable_player_packet(i, v7, v5);
                  v7[0] = 38;
                  v4 = 3;
                }
                memcpy(&v7[v4], Src, Size);
                v4 += Size;
              }
            }
            *(_DWORD *)&v7[v4] = -1;
            v6 = v4 + 4;
            *(_WORD *)&v7[1] = v6 - 3;
            LOBYTE(v0) = rf_network_queue_unreliable_player_packet(i, v7, v6);
          }
        }
      }
    }
    if ( *(_DWORD *)i == dword_87C324 )
    {
      v2 = 0;
    }
    else
    {
      LOBYTE(v0) = i;
      v2 = *(_DWORD *)i;
    }
  }
  return v0;
}

