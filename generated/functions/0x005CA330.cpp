// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CA330 rf_scene_instance_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Binds definition+8;currentFrame+16=definition frameCount132,elapsedSeconds12=currentFrame/15. For positive counts creates cookie arrays:model152 at+20 from definition292,point60 at+24 from180,emitter164 at+28 from220,transform40 at+32 from172;default member constructors run before per-element bind constructors. Nonpositive counts storeNULL. Compiler guards allocation size multiplication/addition; NULL allocation still followed by binding loop with positive count. Final flags OR0x4,clear masks0x1/0x2/0x8/0x10/0x20,preserve higher bits;overrideSeconds4=0. Newly constructed instance starts inactive at endpoint. Returns receiver;no old-resource release or full flag-word initialization.
float *__thiscall rf_scene_instance_construct(float *this, int a2)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  char *v7; // [esp+4h] [ebp-54h]
  char *v8; // [esp+8h] [ebp-50h]
  char *v9; // [esp+Ch] [ebp-4Ch]
  char *v10; // [esp+10h] [ebp-48h]
  char *v12; // [esp+18h] [ebp-40h]
  int v13; // [esp+20h] [ebp-38h]
  char *v14; // [esp+24h] [ebp-34h]
  int v15; // [esp+2Ch] [ebp-2Ch]
  char *v16; // [esp+30h] [ebp-28h]
  int v17; // [esp+38h] [ebp-20h]
  char *v18; // [esp+3Ch] [ebp-1Ch]
  int v19; // [esp+44h] [ebp-14h]
  int i; // [esp+48h] [ebp-10h]
  int j; // [esp+48h] [ebp-10h]
  int k; // [esp+48h] [ebp-10h]
  int m; // [esp+48h] [ebp-10h]

  *((_DWORD *)this + 2) = a2;
  *(this + 4) = (float)*(int *)(*((_DWORD *)this + 2) + 132);
  *(this + 3) = *(this + 4) / 15.0;
  if ( *(int *)(*((_DWORD *)this + 2) + 76) <= 0 )
  {
    *(this + 5) = 0.0;
  }
  else
  {
    v19 = *(_DWORD *)(*((_DWORD *)this + 2) + 76);
    v2 = (152 * (unsigned __int64)(unsigned int)v19) >> 32 != 0 ? -1 : 152 * v19;
    v18 = (char *)operator new(__CFADD__(v2, 4) ? -1 : v2 + 4);
    if ( v18 )
    {
      *(_DWORD *)v18 = v19;
      `eh vector constructor iterator'(
        v18 + 4,
        0x98u,
        v19,
        (void (__thiscall *)(void *))rf_scene_model_state152_default_construct_members,
        (void (__thiscall *)(void *))rf_scene_model_state152_destroy_arrays);
      v10 = v18 + 4;
    }
    else
    {
      v10 = nullptr;
    }
    *((_DWORD *)this + 5) = v10;
    for ( i = 0; i < *(_DWORD *)(*((_DWORD *)this + 2) + 76); ++i )
      rf_scene_model_instance_bind_definition(
        (float *)(*((_DWORD *)this + 5) + 152 * i),
        *(_DWORD *)(*((_DWORD *)this + 2) + 72) + 292 * i);
  }
  if ( *(int *)(*((_DWORD *)this + 2) + 84) <= 0 )
  {
    *(this + 6) = 0.0;
  }
  else
  {
    v17 = *(_DWORD *)(*((_DWORD *)this + 2) + 84);
    v3 = (60 * (unsigned __int64)(unsigned int)v17) >> 32 != 0 ? -1 : 60 * v17;
    v16 = (char *)operator new(__CFADD__(v3, 4) ? -1 : v3 + 4);
    if ( v16 )
    {
      *(_DWORD *)v16 = v17;
      `eh vector constructor iterator'(
        v16 + 4,
        0x3Cu,
        v17,
        (void (__thiscall *)(void *))rf_scene_point_state60_default_construct_members,
        (void (__thiscall *)(void *))rf_scene_point_track_release_pool_slot);
      v9 = v16 + 4;
    }
    else
    {
      v9 = nullptr;
    }
    *((_DWORD *)this + 6) = v9;
    for ( j = 0; j < *(_DWORD *)(*((_DWORD *)this + 2) + 84); ++j )
      rf_scene_point_track_bind_definition(
        (float *)(*((_DWORD *)this + 6) + 60 * j),
        *(_DWORD *)(*((_DWORD *)this + 2) + 80) + 180 * j);
  }
  if ( *(int *)(*((_DWORD *)this + 2) + 92) <= 0 )
  {
    *(this + 7) = 0.0;
  }
  else
  {
    v15 = *(_DWORD *)(*((_DWORD *)this + 2) + 92);
    v4 = (164 * (unsigned __int64)(unsigned int)v15) >> 32 != 0 ? -1 : 164 * v15;
    v14 = (char *)operator new(__CFADD__(v4, 4) ? -1 : v4 + 4);
    if ( v14 )
    {
      *(_DWORD *)v14 = v15;
      `eh vector constructor iterator'(
        v14 + 4,
        0xA4u,
        v15,
        (void (__thiscall *)(void *))rf_particle_instance_default_construct_members,
        rf_particle_instance_destroy);
      v8 = v14 + 4;
    }
    else
    {
      v8 = nullptr;
    }
    *((_DWORD *)this + 7) = v8;
    for ( k = 0; k < *(_DWORD *)(*((_DWORD *)this + 2) + 92); ++k )
      rf_particle_instance_construct(
        (char *)(*((_DWORD *)this + 7) + 164 * k),
        *(_DWORD *)(*((_DWORD *)this + 2) + 88) + 220 * k);
  }
  if ( *(int *)(*((_DWORD *)this + 2) + 100) <= 0 )
  {
    *(this + 8) = 0.0;
  }
  else
  {
    v13 = *(_DWORD *)(*((_DWORD *)this + 2) + 100);
    v5 = (40 * (unsigned __int64)(unsigned int)v13) >> 32 != 0 ? -1 : 40 * v13;
    v12 = (char *)operator new(__CFADD__(v5, 4) ? -1 : v5 + 4);
    if ( v12 )
    {
      *(_DWORD *)v12 = v13;
      `eh vector constructor iterator'(
        v12 + 4,
        0x28u,
        v13,
        (void (__thiscall *)(void *))rf_scene_transform_state40_default_construct_members,
        rf_saved_receiver_noop_5FADF0);
      v7 = v12 + 4;
    }
    else
    {
      v7 = nullptr;
    }
    *((_DWORD *)this + 8) = v7;
    for ( m = 0; m < *(_DWORD *)(*((_DWORD *)this + 2) + 100); ++m )
      rf_scene_transform_track_state_construct(
        (void *)(*((_DWORD *)this + 8) + 40 * m),
        *(_DWORD *)(*((_DWORD *)this + 2) + 96) + 172 * m);
  }
  *(_DWORD *)this |= 4u;
  *(_DWORD *)this &= ~2u;
  *(_DWORD *)this &= ~8u;
  *(_DWORD *)this &= ~1u;
  *(_DWORD *)this &= ~0x10u;
  *(_DWORD *)this &= ~0x20u;
  *(this + 1) = 0.0;
  return this;
}

