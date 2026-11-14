// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510BC0 rf_projectile_snapshot_collect
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Collect actual PROJECTILE records from list0x911F74,sentinel0x911CE8,next+0x28C. Skip common masks0x800 or0x20000000; cap8 successful records, stride152. Common60 prefix plus definition+0x298 at+60; float+0x29C at+64; dword+0x2A8 at+68; saved refs+0x2B0/+0x2E8 at+72/+128; vectors+0x2B4/+0x308 at+76/+140; orientation+0x2C0 at+88; low byte+0x2E4 at+124; floats+0x2F0/+0x2F4 at+132/+136. BYTE count. No standard firing schedule or ammo mutation here beyond common pack side effects.
int __cdecl rf_projectile_snapshot_collect(int a1, _BYTE *a2)
{
  int result; // eax
  int v3; // eax
  int v4; // eax
  float v5[3]; // [esp+0h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-14h] BYREF
  int i; // [esp+18h] [ebp-8h]
  int v8; // [esp+1Ch] [ebp-4h]

  v8 = 0;
  result = dword_911F74;
  for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
  {
    result = i;
    if ( (*(_DWORD *)(i + 124) & 0x800) == 0 )
    {
      result = *(_DWORD *)(i + 124) & 0x20000000;
      if ( !result && v8 < 8 )
      {
        rf_object_snapshot_pack_common60(i, a1 + 152 * v8);
        *(_DWORD *)(a1 + 152 * v8 + 60) = *(_DWORD *)(i + 664);
        *(float *)(a1 + 152 * v8 + 64) = *(float *)(i + 668);
        *(_DWORD *)(a1 + 152 * v8 + 68) = *(_DWORD *)(i + 680);
        v3 = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(i + 688));
        *(_DWORD *)(a1 + 152 * v8 + 72) = v3;
        rf_vector_copy((float *)(a1 + 152 * v8 + 76), copy_result, (const float *)(i + 692));
        rf_matrix3_copy((float *)(a1 + 152 * v8 + 88), (const float *)(i + 704));
        *(_BYTE *)(a1 + 152 * v8 + 124) = *(_BYTE *)(i + 740);
        v4 = rf_object_runtime_identifier_to_saved_identifier(*(_DWORD *)(i + 744));
        *(_DWORD *)(a1 + 152 * v8 + 128) = v4;
        *(float *)(a1 + 152 * v8 + 132) = *(float *)(i + 752);
        *(float *)(a1 + 152 * v8 + 136) = *(float *)(i + 756);
        rf_vector_copy((float *)(a1 + 152 * v8 + 140), v5, (const float *)(i + 776));
        result = ++v8;
      }
    }
  }
  *a2 = v8;
  return result;
}

