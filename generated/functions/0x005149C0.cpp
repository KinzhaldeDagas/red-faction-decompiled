// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005149C0 rf_mesh_decal_collection_release_to_pools
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdecl48-byte collection*,caller pops4,return same pointerEAX. Walk polygonring fromcollection+32 until sentinelcollection+4,saving next28 BEFORE mutation. For eachpolygon walk vertexring frompolygon+20 until sentinelpolygon,saving next20;unlink each28-byte vertex,tailappend globalvertexfree sentinel9287C4,++9287C0. Unlink each36-byte polygon,tailappend polygonfree sentinel92DD68,++9287BC. Finally unlinkcollection fromactive40/44,tailappendcollectionfree sentinel929140,++9287B8. No operator delete,texture/payload clear,source-model changes,NULL/range/count/duplicate-release guards or ring validation. Returned pointer is recycled and must not imply continued owned contents. Dead XOR/JNZ
// pairs do not repeat mutations.
_DWORD *__cdecl rf_mesh_decal_collection_release_to_pools(_DWORD *a1)
{
  _DWORD *v2; // [esp+0h] [ebp-10h]
  _DWORD *v3; // [esp+4h] [ebp-Ch]
  _DWORD *i; // [esp+8h] [ebp-8h]
  _DWORD *j; // [esp+Ch] [ebp-4h]

  for ( i = (_DWORD *)a1[8]; ; i = v2 )
  {
    v2 = (_DWORD *)i[7];
    if ( i == a1 + 1 )
      break;
    for ( j = (_DWORD *)i[5]; ; j = v3 )
    {
      v3 = (_DWORD *)j[5];
      if ( j == i )
        break;
      *(_DWORD *)(j[6] + 20) = j[5];
      *(_DWORD *)(j[5] + 24) = j[6];
      j[5] = 0;
      j[6] = 0;
      j[6] = unk_9287DC;
      j[5] = &unk_9287C4;
      *(_DWORD *)(unk_9287DC + 20) = j;
      unk_9287DC = j;
      ++dword_9287C0;
    }
    *(_DWORD *)(i[8] + 28) = i[7];
    *(_DWORD *)(i[7] + 32) = i[8];
    i[7] = 0;
    i[8] = 0;
    i[8] = unk_92DD88;
    i[7] = &unk_92DD68;
    *(_DWORD *)(unk_92DD88 + 28) = i;
    unk_92DD88 = i;
    ++dword_9287BC;
  }
  *(_DWORD *)(a1[11] + 40) = a1[10];
  *(_DWORD *)(a1[10] + 44) = a1[11];
  a1[10] = 0;
  a1[11] = 0;
  a1[11] = unk_92916C;
  a1[10] = &unk_929140;
  *(_DWORD *)(unk_92916C + 40) = a1;
  unk_92916C = a1;
  ++unk_9287B8;
  return a1;
}

