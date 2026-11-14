// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F5FA0 rf_object_queue_model_rebuild
// UNREALRED VERIFIED [object-entity-snapshot-continuation-20261027] When owner model pointer+0x80 signed>0, append owner to0x8900A0 at count0x894D2C, uncapped copy model descriptor filename pointer+0xC into32-byte queue name slot0x890100, store model kind dword+0 at parallel0x890040, increment count. Otherwise leave queue unchanged. No direct model release/reload or object-id fixup; consumer0x4F6050 is a distinct by-runtime-type phase.
int __cdecl rf_object_queue_model_rebuild(int a1)
{
  int result; // eax
  char v2; // cl
  char *v3; // [esp+8h] [ebp-Ch]
  char *v4; // [esp+Ch] [ebp-8h]
  int v5; // [esp+10h] [ebp-4h]

  result = a1;
  v5 = *(_DWORD *)(a1 + 128);
  if ( v5 > 0 )
  {
    dword_8900A0[unk_894D2C] = a1;
    v4 = (char *)rf_model_descriptor_filename_pointer(v5);
    v3 = &unk_890100[32 * unk_894D2C];
    do
    {
      v2 = *v4;
      *v3++ = *v4++;
    }
    while ( v2 );
    unk_890040[unk_894D2C] = rf_model_descriptor_get_kind(v5);
    return ++unk_894D2C;
  }
  return result;
}

