// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043ECF0 sub_43ECF0
// UNREALRED VERIFIED [burn-motion-20261029]: Burn attachment resolution requires all four bones: left lowerleg-l then tech- leg-l-lower; right lowerleg-r then tech- leg-r-lower; spine spine01 then spine03 then tech- 1spine then tech- 1spine01; head head. A missing final slot makes allocation fail. These are explicit native alternatives, not nearest-bone heuristics.
bool __cdecl sub_43ECF0(_DWORD *a1, int a2)
{
  _DWORD v3[2]; // [esp-8h] [ebp-74h] BYREF
  int v4; // [esp+0h] [ebp-6Ch]
  _DWORD *v5; // [esp+4h] [ebp-68h]
  int v6; // [esp+8h] [ebp-64h]
  _DWORD *v7; // [esp+Ch] [ebp-60h]
  int v8; // [esp+10h] [ebp-5Ch]
  _DWORD *v9; // [esp+14h] [ebp-58h]
  int v10; // [esp+18h] [ebp-54h]
  _DWORD *v11; // [esp+1Ch] [ebp-50h]
  int v12; // [esp+20h] [ebp-4Ch]
  _DWORD *v13; // [esp+24h] [ebp-48h]
  int v14; // [esp+28h] [ebp-44h]
  _DWORD *v15; // [esp+2Ch] [ebp-40h]
  int v16; // [esp+30h] [ebp-3Ch]
  _DWORD *v17; // [esp+34h] [ebp-38h]
  int v18; // [esp+38h] [ebp-34h]
  _DWORD *v19; // [esp+3Ch] [ebp-30h]
  int v20; // [esp+40h] [ebp-2Ch]
  _DWORD *v21; // [esp+44h] [ebp-28h]
  _DWORD *v22; // [esp+48h] [ebp-24h]
  _DWORD *v23; // [esp+4Ch] [ebp-20h]
  _DWORD *v24; // [esp+50h] [ebp-1Ch]
  _DWORD *v25; // [esp+54h] [ebp-18h]
  _DWORD *v26; // [esp+58h] [ebp-14h]
  _DWORD *v27; // [esp+5Ch] [ebp-10h]
  _DWORD *v28; // [esp+60h] [ebp-Ch]
  _DWORD *v29; // [esp+64h] [ebp-8h]
  _DWORD *v30; // [esp+68h] [ebp-4h]

  v30 = v3;
  v21 = rf_string_construct_from_cstr(v3, "lowerleg-l");
  v20 = sub_43EEF0(a2);
  a1[5] = v20;
  if ( a1[5] == -1 )
  {
    v29 = v3;
    v19 = rf_string_construct_from_cstr(v3, "tech- leg-l-lower");
    v18 = sub_43EEF0(a2);
    a1[5] = v18;
  }
  v28 = v3;
  v17 = rf_string_construct_from_cstr(v3, "lowerleg-r");
  v16 = sub_43EEF0(a2);
  a1[6] = v16;
  if ( a1[6] == -1 )
  {
    v27 = v3;
    v15 = rf_string_construct_from_cstr(v3, "tech- leg-r-lower");
    v14 = sub_43EEF0(a2);
    a1[6] = v14;
  }
  v26 = v3;
  v13 = rf_string_construct_from_cstr(v3, "spine01");
  v12 = sub_43EEF0(a2);
  a1[7] = v12;
  if ( a1[7] == -1 )
  {
    v25 = v3;
    v11 = rf_string_construct_from_cstr(v3, "spine03");
    v10 = sub_43EEF0(a2);
    a1[7] = v10;
  }
  if ( a1[7] == -1 )
  {
    v24 = v3;
    v9 = rf_string_construct_from_cstr(v3, "tech- 1spine");
    v8 = sub_43EEF0(a2);
    a1[7] = v8;
  }
  if ( a1[7] == -1 )
  {
    v23 = v3;
    v7 = rf_string_construct_from_cstr(v3, "tech- 1spine01");
    v6 = sub_43EEF0(a2);
    a1[7] = v6;
  }
  v22 = v3;
  v5 = rf_string_construct_from_cstr(v3, "head");
  v4 = sub_43EEF0(a2);
  a1[8] = v4;
  return a1[5] != -1 && a1[6] != -1 && a1[7] != -1 && a1[8] != -1;
}

