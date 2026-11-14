// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C2220 rf_explosion_graph_update_runtime
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Cdecl no args, walks circular active graph head814340, free head814344. Graph308B: room24,size28,age32,head positions36+12*j,velocities132+12*j,tracked particle
// pointers228+4*j,tail-enable BYTE260+j,headCount268,central emitter pointers272+4*j,definition296,next300,prev304. Caches next (or NULL when next==CURRENT active head) BEFORE
// emissions/removal; current-head changes during expiry do not cause a second traversal. Stores age+=frameSeconds binary32.
// Head mode ONLY when definition head-duration140 is ORDERED >age. Native FCOMPP/TEST AH41/JNZ goes to tail mode for <= OR unordered; do not use pseudocode else from an ordered <=
// test for NaN. Head mode samples one direct prototype4C2690 using headIndex36 WITHOUT checking index>=0 even if headCount0, scales descriptor radius24 by graph size (binary32),
// retains unscaled lifetime40. For every signed j<headCount268, overwrites prototype position/velocity from graph arrays and allocates
// particle(room24,owner-1,trackingOutput=&graph228+4*j). No frame-delta-based emission budget: one per head per call; pointers may be replaced by allocator.
// Tail mode requires signed tailIndex40>-1. Samples one direct prototype, scales radius24 by size, leaves lifetime40 unscaled. For each j<headCount, only nonnull tracked particle AND
// tail-enable BYTE exactly1: if particle flags88&1, copies particle vector108 into prototype position and allocates untracked particle(room24,owner-1). Does NOT replace prototype
// velocity from tracked head; uses tail prototype velocity. If particle flag1 clear, sets tail-enable BYTE0; NULL pointer does not clear byte. Sampled prototype shared across all
// tails this call.
// Then each central j<definition.count124: emitter pointer nonnull AND definition process BYTE68+j exactly1 AND ORDERED age < definition.factor100+4*j * graph.size ->emitter_process.
// Product remains x87 until compare (no intermediate F32store). Equality/NaN skips; flags byte2 is not true here. This per-emitter stop does not destroy emitter.
// Expiry only when definition playTime136 is ORDERED <age; equality/NaN does not expire. Occurs AFTER head/tail allocation and central processing, so expiring graph still
// emits/processes this call. Destroys nonnull central emitters and clears their graph pointers, unlinks graph (singleton clears active head; head removal advances it), then appends
// record to circular FREE tail, or makes singleton free list if empty. Does NOT memset reused graph, clear head tracking pointers/flags/position/age, free tracked particles or stop
// audio. Record remains pool-owned. No pause, room/visibility, finite, definition/index/headCount/centralCount bounds checks or renderer-light constructor. Return EAX incidental loop
// value, normally0 after traversal.
int rf_explosion_graph_update_runtime()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-D8h]
  float v2[3]; // [esp+4h] [ebp-D4h] BYREF
  float v3[3]; // [esp+10h] [ebp-C8h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-BCh] BYREF
  float v5[6]; // [esp+28h] [ebp-B0h] BYREF
  float v6; // [esp+40h] [ebp-98h]
  float destination[3]; // [esp+78h] [ebp-60h] BYREF
  float v8[3]; // [esp+84h] [ebp-54h] BYREF
  float v9; // [esp+90h] [ebp-48h]
  int v10; // [esp+CCh] [ebp-Ch]
  int j; // [esp+D0h] [ebp-8h]
  int i; // [esp+D4h] [ebp-4h]

  result = unk_814340;
  for ( i = unk_814340; i; i = v10 )
  {
    if ( *(_DWORD *)(i + 300) == unk_814340 )
      v1 = 0;
    else
      v1 = *(_DWORD *)(i + 300);
    v10 = v1;
    *(float *)(i + 32) = *(float *)(i + 32) + rf_frame_delta_seconds;
    if ( *(float *)(*(_DWORD *)(i + 296) + 140) <= (double)*(float *)(i + 32) )
    {
      if ( *(int *)(*(_DWORD *)(i + 296) + 40) > -1 )
      {
        rf_particle_descriptor76_construct_noop((int)v5);
        rf_explosion_sample_direct_particle_prototype(dword_867800[*(_DWORD *)(*(_DWORD *)(i + 296) + 40)], (int)v5);
        v6 = v6 * *(float *)(i + 28);
        for ( j = 0; j < *(_DWORD *)(i + 268); ++j )
        {
          if ( *(_DWORD *)(i + 4 * j + 228) && *(_BYTE *)(j + i + 260) == 1 )
          {
            if ( (*(_DWORD *)(*(_DWORD *)(i + 4 * j + 228) + 88) & 1) != 0 )
            {
              rf_vector_copy(v5, v2, (const float *)(*(_DWORD *)(i + 4 * j + 228) + 108));
              rf_particle_allocate_and_initialize(0, (int)v5, *(_DWORD *)(i + 24), 0, -1, nullptr, 0);
            }
            else
            {
              *(_BYTE *)(j + i + 260) = 0;
            }
          }
        }
      }
    }
    else
    {
      rf_particle_descriptor76_construct_noop((int)destination);
      rf_explosion_sample_direct_particle_prototype(
        dword_867800[*(_DWORD *)(*(_DWORD *)(i + 296) + 36)],
        (int)destination);
      v9 = v9 * *(float *)(i + 28);
      for ( j = 0; j < *(_DWORD *)(i + 268); ++j )
      {
        rf_vector_copy(destination, copy_result, (const float *)(i + 12 * j + 36));
        rf_vector_copy(v8, v3, (const float *)(i + 12 * j + 132));
        rf_particle_allocate_and_initialize(
          0,
          (int)destination,
          *(_DWORD *)(i + 24),
          0,
          -1,
          (_DWORD *)(i + 4 * j + 228),
          0);
      }
    }
    for ( j = 0; j < *(_DWORD *)(*(_DWORD *)(i + 296) + 124); ++j )
    {
      if ( *(_DWORD *)(i + 4 * j + 272)
        && *(_BYTE *)(*(_DWORD *)(i + 296) + j + 68) == 1
        && *(float *)(i + 32) < *(float *)(*(_DWORD *)(i + 296) + 4 * j + 100) * *(float *)(i + 28) )
      {
        rf_particle_emitter_process(*(_DWORD *)(i + 4 * j + 272));
      }
    }
    if ( *(float *)(*(_DWORD *)(i + 296) + 136) < (double)*(float *)(i + 32) )
    {
      for ( j = 0; j < *(_DWORD *)(*(_DWORD *)(i + 296) + 124); ++j )
      {
        if ( *(_DWORD *)(i + 4 * j + 272) )
        {
          rf_particle_emitter_destroy(*(_DWORD *)(i + 4 * j + 272));
          *(_DWORD *)(i + 4 * j + 272) = 0;
        }
      }
      if ( unk_814340 == i )
      {
        if ( *(_DWORD *)(i + 300) == i )
        {
          *(_DWORD *)(i + 300) = 0;
          *(_DWORD *)(i + 304) = 0;
          unk_814340 = 0;
          goto LABEL_39;
        }
        unk_814340 = *(_DWORD *)(i + 300);
      }
      *(_DWORD *)(*(_DWORD *)(i + 304) + 300) = *(_DWORD *)(i + 300);
      *(_DWORD *)(*(_DWORD *)(i + 300) + 304) = *(_DWORD *)(i + 304);
      *(_DWORD *)(i + 300) = 0;
      *(_DWORD *)(i + 304) = 0;
LABEL_39:
      if ( unk_814344 )
      {
        *(_DWORD *)(i + 304) = *(_DWORD *)(unk_814344 + 304);
        *(_DWORD *)(i + 300) = unk_814344;
        *(_DWORD *)(*(_DWORD *)(unk_814344 + 304) + 300) = i;
        *(_DWORD *)(unk_814344 + 304) = i;
      }
      else
      {
        *(_DWORD *)(i + 300) = i;
        *(_DWORD *)(i + 304) = i;
        unk_814344 = i;
      }
    }
    result = v10;
  }
  return result;
}

