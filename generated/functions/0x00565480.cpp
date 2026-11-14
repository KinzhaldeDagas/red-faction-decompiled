// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565480 rf_model_handle_allocate_private_materials
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Allocates cookie-prefixed array of200byte materials with per-element initializer5C9340 and destructor5C94A0. Size multiplication/addition overflow maps requested size toFFFFFFFF. Tag1 allocates ONLY when collection DWORD80<=1 AND first hierarchy DWORD0<=1; otherwise leaves pointer80 unchanged. Copies first referenced mesh material table. Tag2 allocates summed count across all148byte LOD containers, copies each source table consecutively. Tag3 allocates definition136 count and clones definition140 table. Stores array element pointer at handle80; does not set active byte84 or free previous table. Conditional null allocation result still reaches copy routine, no general graceful-failure contract.
void __cdecl rf_model_handle_allocate_private_materials(int *a1)
{
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  int v4; // [esp+4h] [ebp-60h]
  int v5; // [esp+8h] [ebp-5Ch]
  int v6; // [esp+Ch] [ebp-58h]
  int v7; // [esp+10h] [ebp-54h]
  char *v8; // [esp+14h] [ebp-50h]
  char *v9; // [esp+20h] [ebp-44h]
  int v10; // [esp+28h] [ebp-3Ch]
  char *v11; // [esp+2Ch] [ebp-38h]
  int v12; // [esp+34h] [ebp-30h]
  int v13; // [esp+38h] [ebp-2Ch]
  int v14; // [esp+44h] [ebp-20h] BYREF
  int v15; // [esp+48h] [ebp-1Ch] BYREF
  int i; // [esp+4Ch] [ebp-18h]
  int v17; // [esp+50h] [ebp-14h]
  int v18; // [esp+54h] [ebp-10h]
  int v19; // [esp+60h] [ebp-4h]

  v7 = *a1;
  if ( *a1 == 1 )
  {
    if ( *(int *)(a1[1] + 80) <= 1 && **(int **)(a1[1] + 84) <= 1 )
    {
      v10 = rf_model_handle_private_material_count(a1);
      v2 = (200 * (unsigned __int64)(unsigned int)v10) >> 32 != 0 ? -1 : 200 * v10;
      v9 = (char *)operator new(__CFADD__(v2, 4) ? -1 : v2 + 4);
      v19 = 1;
      if ( v9 )
      {
        *(_DWORD *)v9 = v10;
        `eh vector constructor iterator'(
          v9 + 4,
          0xC8u,
          v10,
          (void (__thiscall *)(void *))rf_material_initialize,
          rf_material200_destroy_owned_float_arrays);
        v5 = (int)(v9 + 4);
      }
      else
      {
        v5 = 0;
      }
      v19 = -1;
      a1[20] = v5;
      rf_material200_clone_for_model_handle(
        a1,
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1[1] + 84) + 4) + 132),
        a1[20],
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a1[1] + 84) + 4) + 136));
    }
  }
  else if ( v7 == 2 )
  {
    v17 = rf_model_handle_private_material_count(a1);
    v12 = v17;
    v1 = (200 * (unsigned __int64)(unsigned int)v17) >> 32 != 0 ? -1 : 200 * v17;
    v11 = (char *)operator new(__CFADD__(v1, 4) ? -1 : v1 + 4);
    v19 = 0;
    if ( v11 )
    {
      *(_DWORD *)v11 = v17;
      `eh vector constructor iterator'(
        v11 + 4,
        0xC8u,
        v12,
        (void (__thiscall *)(void *))rf_material_initialize,
        rf_material200_destroy_owned_float_arrays);
      v6 = (int)(v11 + 4);
    }
    else
    {
      v6 = 0;
    }
    v19 = -1;
    a1[20] = v6;
    v18 = 0;
    for ( i = 0; i < *(_DWORD *)(a1[2] + 6588); ++i )
    {
      rf_model_container_get_reference_mesh_materials((_DWORD *)(a1[2] + 148 * i + 6592), &v15, &v14);
      rf_material200_clone_for_model_handle(a1, v15, a1[20] + 200 * v18, v14);
      v18 += v15;
    }
  }
  else if ( v7 == 3 )
  {
    v13 = rf_model_handle_private_material_count(a1);
    v3 = (200 * (unsigned __int64)(unsigned int)v13) >> 32 != 0 ? -1 : 200 * v13;
    v8 = (char *)operator new(__CFADD__(v3, 4) ? -1 : v3 + 4);
    v19 = 2;
    if ( v8 )
    {
      *(_DWORD *)v8 = v13;
      `eh vector constructor iterator'(
        v8 + 4,
        0xC8u,
        v13,
        (void (__thiscall *)(void *))rf_material_initialize,
        rf_material200_destroy_owned_float_arrays);
      v4 = (int)(v8 + 4);
    }
    else
    {
      v4 = 0;
    }
    v19 = -1;
    a1[20] = v4;
    rf_material200_clone_for_model_handle(a1, v13, a1[20], *(_DWORD *)(a1[2] + 140));
  }
}

