// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C17B0 rf_managed_particle_effect_list_add
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Thiscall sentinel,roomPtr,positionVec3,directionVec3,emitterName,foleyName RET20; canonical AL1 only after successful emitter creation/initialization, otherwise0. Counts nodes by
// next24 until sentinel. If count>=4, unlinks and scalar-deletes ONLY first/oldest node BEFORE validating requested emitter name; invalid replacement can evict existing effect. Does
// not repeatedly trim an already-oversized list. Resolves emitter index4CE330; -1 returns0. Resolves Foley set446EE0 and samples one sound before allocating node.
// Allocates32B node, ctor4C1570; NULLallocation returns0. Appends node at tail BEFORE particle_emitter_create(0,prototypeTable867800[index],roomPtr,0,0). If emitter allocation fails,
// returns0 WITHOUT unlinking/freeing node: linked empty node retains emitterNULL,voice-1,roomNULL and uninitialized position. Success copies source to node.position8 and emitter8,
// direction to emitter20. Nonnegative chosen sound event uses positional playback(volume1,global listener17F10B0,flags0) and stores returned voice handle; negative event stores-1.
// Stores roomPtr28, enables emitter, returns1 even if audio playback failed. No room refresh, particle/class/string/vec finite validation, or rollback of prior eviction/randomness.
char __thiscall rf_managed_particle_effect_list_add(
        int **this,
        int a2,
        float *source,
        float *a4,
        char *a5,
        char *String2)
{
  int v7; // eax
  _DWORD *v8; // [esp+10h] [ebp-64h]
  float v10[3]; // [esp+1Ch] [ebp-58h] BYREF
  float v11[3]; // [esp+28h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+34h] [ebp-40h] BYREF
  void *v13; // [esp+40h] [ebp-34h]
  _DWORD *v14; // [esp+44h] [ebp-30h]
  int *v15; // [esp+48h] [ebp-2Ch]
  int *v16; // [esp+4Ch] [ebp-28h]
  int *v17; // [esp+50h] [ebp-24h]
  int name; // [esp+54h] [ebp-20h]
  int i; // [esp+58h] [ebp-1Ch]
  int v20; // [esp+5Ch] [ebp-18h]
  int v21; // [esp+60h] [ebp-14h]
  int v22; // [esp+64h] [ebp-10h]
  int v23; // [esp+70h] [ebp-4h]

  v22 = 0;
  for ( i = (int)*(this + 6); (int **)i != this; i = *(_DWORD *)(i + 24) )
    ++v22;
  if ( v22 >= 4 )
  {
    v17 = *(this + 6);
    *(_DWORD *)(v17[5] + 24) = v17[6];
    *(_DWORD *)(v17[6] + 20) = v17[5];
    v17[6] = 0;
    v17[5] = 0;
    v15 = v17;
    v16 = v17;
    if ( v17 )
      rf_managed_particle_effect_node_scalar_deleting_destructor(v16, 1);
  }
  name = rf_particle_emitter_definition_find_name(a5);
  if ( name == -1 )
    return 0;
  v20 = rf_foley_definition_find_name(String2);
  v21 = rf_foley_choose_random_sound(v20);
  v13 = operator new(0x20u);
  v23 = 0;
  if ( v13 )
    v8 = rf_managed_particle_effect_node_construct(v13);
  else
    v8 = nullptr;
  v14 = v8;
  v23 = -1;
  i = (int)v8;
  if ( !v8 )
    return 0;
  *(_DWORD *)(i + 20) = *(this + 5);
  *(_DWORD *)(i + 24) = this;
  (*(this + 5))[6] = i;
  *(this + 5) = (int *)i;
  *(_DWORD *)i = rf_particle_emitter_create(0, (float *)dword_867800[name], a2, 0, 0);
  if ( !*(_DWORD *)i )
    return 0;
  rf_vector_copy((float *)(i + 8), copy_result, source);
  rf_vector_copy((float *)(*(_DWORD *)i + 8), v11, source);
  rf_vector_copy((float *)(*(_DWORD *)i + 20), v10, a4);
  if ( v21 < 0 )
  {
    *(_DWORD *)(i + 4) = -1;
  }
  else
  {
    v7 = rf_gamesound_play_positional_event(v21, source, 1.0, (int)flt_17F10B0, 0);
    *(_DWORD *)(i + 4) = v7;
  }
  *(_DWORD *)(i + 28) = a2;
  rf_particle_emitter_enable(*(_DWORD *)i);
  return 1;
}

