// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CA7D0 rf_scene_definition_destroy_owned_pools
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): For nonNULL owned pointers: cookie-deletes model292+72,point180+80,emitter220+88,transform172+96,force-channel224+104,range148+112,reference-list144+120;scalar-deletes binding+128;cookie-deletes material200+140. Plain operator deletes pools at148,156,164,172,180,188,196,220,236,244,252,292,300. Cookie adapters for pools+204(stride40),+212(4),+228(20),+260(36),+268(28),+276(52),+284(48). Does NOT NULL any pointer,clear counts,delete containing scene or validate ownership;repeated destruction can double free. Several former Concurrency types in adapters are false SDK matches.
void __thiscall rf_scene_definition_destroy_owned_pools(int this)
{
  char *v2; // [esp+50h] [ebp-A8h]
  char *v3; // [esp+58h] [ebp-A0h]
  char *v4; // [esp+60h] [ebp-98h]
  Concurrency::details::GlobalCore *v5; // [esp+68h] [ebp-90h]
  char *v6; // [esp+7Ch] [ebp-7Ch]
  char *v7; // [esp+88h] [ebp-70h]
  Concurrency::details::GlobalNode *v8; // [esp+90h] [ebp-68h]
  char *v9; // [esp+B4h] [ebp-44h]
  void *v10; // [esp+BCh] [ebp-3Ch]
  char *v11; // [esp+C4h] [ebp-34h]
  char *v12; // [esp+CCh] [ebp-2Ch]
  char *v13; // [esp+D4h] [ebp-24h]
  char *v14; // [esp+DCh] [ebp-1Ch]
  char *v15; // [esp+E4h] [ebp-14h]
  char *v16; // [esp+ECh] [ebp-Ch]
  char *v17; // [esp+F4h] [ebp-4h]

  if ( *(_DWORD *)(this + 72) )
  {
    v17 = *(char **)(this + 72);
    if ( v17 )
      rf_scene_model_definition292_vector_deleting_destructor(v17, 3);
  }
  if ( *(_DWORD *)(this + 80) )
  {
    v16 = *(char **)(this + 80);
    if ( v16 )
      rf_scene_point_definition180_vector_deleting_destructor(v16, 3);
  }
  if ( *(_DWORD *)(this + 88) )
  {
    v15 = *(char **)(this + 88);
    if ( v15 )
      rf_particle_definition220_vector_deleting_destructor(v15, 3);
  }
  if ( *(_DWORD *)(this + 96) )
  {
    v14 = *(char **)(this + 96);
    if ( v14 )
      rf_scene_transform_definition172_vector_deleting_destructor(v14, 3);
  }
  if ( *(_DWORD *)(this + 104) )
  {
    v13 = *(char **)(this + 104);
    if ( v13 )
      rf_scene_force_channel224_vector_deleting_destructor(v13, 3);
  }
  if ( *(_DWORD *)(this + 112) )
  {
    v12 = *(char **)(this + 112);
    if ( v12 )
      rf_scene_transform_range148_vector_deleting_destructor(v12, 3);
  }
  if ( *(_DWORD *)(this + 120) )
  {
    v11 = *(char **)(this + 120);
    if ( v11 )
      rf_scene_reference_list144_vector_deleting_destructor(v11, 3);
  }
  if ( *(_DWORD *)(this + 128) )
  {
    v10 = *(void **)(this + 128);
    if ( v10 )
      rf_scene_material_binding_scalar_deleting_destructor(v10, 1);
  }
  if ( *(_DWORD *)(this + 140) )
  {
    v9 = *(char **)(this + 140);
    if ( v9 )
      rf_material200_vector_deleting_destructor(v9, 3);
  }
  if ( *(_DWORD *)(this + 148) )
    operator delete(*(void **)(this + 148));
  if ( *(_DWORD *)(this + 156) )
    operator delete(*(void **)(this + 156));
  if ( *(_DWORD *)(this + 164) )
    operator delete(*(void **)(this + 164));
  if ( *(_DWORD *)(this + 172) )
    operator delete(*(void **)(this + 172));
  if ( *(_DWORD *)(this + 180) )
    operator delete(*(void **)(this + 180));
  if ( *(_DWORD *)(this + 188) )
    operator delete(*(void **)(this + 188));
  if ( *(_DWORD *)(this + 196) )
    operator delete(*(void **)(this + 196));
  if ( *(_DWORD *)(this + 204) )
  {
    v8 = *(Concurrency::details::GlobalNode **)(this + 204);
    if ( v8 )
      rf_scene_pool40_vector_deleting_destructor(v8, 3u);
  }
  if ( *(_DWORD *)(this + 212) )
  {
    v7 = *(char **)(this + 212);
    if ( v7 )
      rf_scene_pool4_vector_deleting_destructor(v7, 3);
  }
  if ( *(_DWORD *)(this + 220) )
    operator delete(*(void **)(this + 220));
  if ( *(_DWORD *)(this + 228) )
  {
    v6 = *(char **)(this + 228);
    if ( v6 )
      rf_scene_pool20_vector_deleting_destructor(v6, 3);
  }
  if ( *(_DWORD *)(this + 236) )
    operator delete(*(void **)(this + 236));
  if ( *(_DWORD *)(this + 244) )
    operator delete(*(void **)(this + 244));
  if ( *(_DWORD *)(this + 252) )
    operator delete(*(void **)(this + 252));
  if ( *(_DWORD *)(this + 260) )
  {
    v5 = *(Concurrency::details::GlobalCore **)(this + 260);
    if ( v5 )
      rf_scene_pool36_vector_deleting_destructor(v5, 3u);
  }
  if ( *(_DWORD *)(this + 268) )
  {
    v4 = *(char **)(this + 268);
    if ( v4 )
      rf_scene_pool28_vector_deleting_destructor(v4, 3);
  }
  if ( *(_DWORD *)(this + 276) )
  {
    v3 = *(char **)(this + 276);
    if ( v3 )
      rf_particle_key52_vector_deleting_destructor(v3, 3);
  }
  if ( *(_DWORD *)(this + 284) )
  {
    v2 = *(char **)(this + 284);
    if ( v2 )
      rf_scene_pool48_vector_deleting_destructor(v2, 3);
  }
  if ( *(_DWORD *)(this + 292) )
    operator delete(*(void **)(this + 292));
  if ( *(_DWORD *)(this + 300) )
    operator delete(*(void **)(this + 300));
}

