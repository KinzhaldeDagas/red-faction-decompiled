// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A0830 rf_client_apply_item_apply_payload40
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Recovered original [4A0830,4A09D9), cdecl(payload). Requires runtime mode1 and authority EXACTLY0, no own game-mode/null/length guard. Reads20 bytes as five DWORDs: item server
// identifier, entity server identifier, index,valueA,valueB. Packet40 association follows exact paired sender layout; no static incoming xrefs currently. Translates item id through
// low16 server-to-local table helper4B4970, resolves item handle; failure prints Ignoring item apply 1 and returns before translating entity. Translates entity id and resolves entity
// handle; failure prints Would have ignored item apply 2 then marks EXISTING item for deferred deletion, rather than simply ignoring it.
// With both objects resolves, invokes rf_item_pickup_dispatch(item,entity,0,1) FIRST. Only afterwards, if signed index>=0 and index<weapon count911C68 and weapon-record
// DWORD[912024+index*1360]>=0, writes valueA to entity DWORD[+812+index*4] and valueB to entity DWORD[+684+recordIndex*4]. No upper-bound check for that secondary recordIndex in this
// routine. Does not allocate item/entity, send feedback packet or validate remaining item lifetime after pickup delegate.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, compiled registry/dispatcher and native ABI refinement): Original PE descriptor at0x00662B28 registers opcode40 (item_apply), callback0x004A0830. Native dispatcher49FB50 indirectly calls it with(payload,source endpoint),8-byte caller cleanup,after envelope/source admission; handler receives NO payload length. Thus absence of IDA direct call/xrefs does not imply a dormant handler. Compiled registration and dispatch edge verified independently of earlier paired-layout inference; actual invocation still depends on runtime admission.
void __cdecl rf_client_apply_item_apply_payload40(const unsigned __int8 *payload)
{
  int v1; // [esp+0h] [ebp-20h]
  int v2; // [esp+0h] [ebp-20h]
  _DWORD *v3; // [esp+4h] [ebp-1Ch]
  int v4; // [esp+8h] [ebp-18h]
  int v5; // [esp+Ch] [ebp-14h]
  int v6; // [esp+10h] [ebp-10h]
  int v7; // [esp+14h] [ebp-Ch]
  int v8; // [esp+1Ch] [ebp-4h]

  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    v1 = *((_DWORD *)payload + 1);
    v6 = *((_DWORD *)payload + 2);
    v4 = *((_DWORD *)payload + 3);
    v7 = *((_DWORD *)payload + 4);
    v5 = rf_replication_server_id_to_local_handle(*(_DWORD *)payload);
    v3 = (_DWORD *)rf_item_resolve_handle(v5);
    if ( v3 )
    {
      v2 = rf_replication_server_id_to_local_handle(v1);
      v8 = rf_entity_resolve_handle(v2);
      if ( v8 )
      {
        rf_item_pickup_dispatch(v3, v8, 0, 1);
        if ( v6 >= 0 && v6 < dword_911C68 && dword_912024[340 * v6] >= 0 )
        {
          *(_DWORD *)(v8 + 4 * v6 + 812) = v4;
          *(_DWORD *)(v8 + 4 * dword_912024[340 * v6] + 684) = v7;
        }
      }
      else
      {
        printf("Would have ignored item apply 2\n");
        rf_object_mark_for_deferred_delete((int)v3);
      }
    }
    else
    {
      printf("Ignoring item apply 1\n");
    }
  }
}

