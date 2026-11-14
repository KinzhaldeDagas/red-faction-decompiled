// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A0D0 rf_geomod_execution_queue_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl operation100 pointer. Scans actual pending list (not pending-count global); on sixth existing node, removes/deletes OLDEST head and breaks scan, then appends new node. Normal
// invariant caps pending list at6; only one eviction per append, not a general repair of an already-overlong list. Active operation is already unlinked and is not evicted. Eviction
// happens BEFORE resolving new cutter or allocating node, so later failure cannot restore the evicted node.
// Resolves source cutter id, computes FLOAT R=cutter.radius96*operation.scale60, with no NULL/finite validation. Allocates132 bytes, optional no-op ctor, unconditionally
// operation100_assign into+8, appends tail, increments pending count BEFORE creating smoke. No local allocation-NULL rejection or later transaction rollback. For each six smoke
// slots108+4*i: if operation flag1 set OR normal template==-1 OR driller template==-1, writes NULL. Otherwise indexes world room pointer array+144 by operation room id4 unchecked,
// selects driller template iff operation flag8, calls emitter_create(parent0,definition,room,previousNULL,enabled0). Both template ids must exist even when using one.
// NonNULL emitter: writes FLOAT+68=F32(R*double0.699999988079071), FLOAT+72=F32(R*1), position+8=node+16 (operation position), packed color+132=(255,255,255,200), enables emitter
// then explicitly spawns one particle. No per-slot random position/delay or emission-count check. A failed emitter allocation leaves NULL and does not reject queue node or roll back
// other slots. Normal EAX6 comes from loop increment, not node handle/success flag. Unwind deletes raw node only if its constructor throws; this is not an all-emitter transaction.
int __cdecl rf_geomod_execution_queue_append(int a1)
{
  int result; // eax
  int v2; // eax
  int v3; // [esp+4h] [ebp-40h]
  char *v4; // [esp+8h] [ebp-3Ch]
  float copy_result[3]; // [esp+Ch] [ebp-38h] BYREF
  void *v6; // [esp+18h] [ebp-2Ch]
  char *v7; // [esp+1Ch] [ebp-28h]
  int v8; // [esp+20h] [ebp-24h]
  int v9; // [esp+24h] [ebp-20h]
  int i; // [esp+28h] [ebp-1Ch]
  int j; // [esp+2Ch] [ebp-18h]
  float v12; // [esp+30h] [ebp-14h]
  int v13; // [esp+34h] [ebp-10h]
  int v14; // [esp+40h] [ebp-4h]

  j = 0;
  for ( i = rf_geomod_execution_queue_head; (_DWORD *)i != &rf_geomod_execution_queue_head; i = *(_DWORD *)i )
  {
    if ( ++j > 5 )
    {
      i = rf_geomod_execution_queue_head;
      rf_geomod_execution_queue_node_remove_destroy((_DWORD **)rf_geomod_execution_queue_head);
      break;
    }
  }
  v13 = rf_geomod_cutter_resolve(*(_DWORD *)a1);
  v12 = *(float *)(v13 + 96) * *(float *)(a1 + 60);
  v6 = operator new(0x84u);
  v14 = 0;
  if ( v6 )
    v4 = rf_geomod_operation_node132_construct_noop((char *)v6);
  else
    v4 = nullptr;
  v7 = v4;
  v14 = -1;
  i = (int)v4;
  rf_geomod_operation100_assign((float *)v4 + 2, (float *)a1);
  *((_DWORD *)v4 + 1) = rf_geomod_execution_queue_tail;
  *(_DWORD *)i = &rf_geomod_execution_queue_head;
  *rf_geomod_execution_queue_tail = i;
  result = i;
  rf_geomod_execution_queue_tail = i;
  ++rf_geomod_execution_queue_count;
  for ( j = 0; j < 6; ++j )
  {
    if ( (*(_DWORD *)(a1 + 56) & 1) != 0 || rf_geomod_smoke_template == -1 || rf_geomod_driller_smoke_template == -1 )
    {
      *(_DWORD *)(i + 4 * j + 108) = 0;
    }
    else
    {
      v8 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 144), *(_DWORD *)(a1 + 4));
      if ( (*(_DWORD *)(a1 + 56) & 8) != 0 )
        v3 = rf_geomod_driller_smoke_template;
      else
        v3 = rf_geomod_smoke_template;
      v9 = v3;
      v2 = rf_particle_emitter_create(0, (float *)dword_867800[v3], v8, 0, 0);
      *(_DWORD *)(i + 4 * j + 108) = v2;
      if ( *(_DWORD *)(i + 4 * j + 108) )
      {
        *(float *)(*(_DWORD *)(i + 4 * j + 108) + 68) = v12 * 0.699999988079071;
        *(float *)(*(_DWORD *)(i + 4 * j + 108) + 72) = v12 * 1.0;
        rf_vector_copy((float *)(*(_DWORD *)(i + 4 * j + 108) + 8), copy_result, (const float *)(i + 16));
        rf_color4_set_bytes_return_destination((_BYTE *)(*(_DWORD *)(i + 4 * j + 108) + 132), 255, 255, 255, 200);
        rf_particle_emitter_enable(*(_DWORD *)(i + 4 * j + 108));
        rf_particle_emitter_spawn_particle(*(_DWORD *)(i + 4 * j + 108));
      }
    }
    result = j + 1;
  }
  return result;
}

