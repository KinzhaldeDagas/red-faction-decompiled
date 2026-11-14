// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054AA10 rf_world_packet_append_decal_derived_faces
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Cdecl(world,sourceFace,faceDomainCountPointer). If debug flagsA4208C/A42090/A4209C set,does nothing with incidental EAX. Otherwise asks decal partition helper for up to16 flag8 polygon associations. For each,subject16384 global face cap and temporary arena end663D40,allocates100-byte face then28-byte per original vertex/corner node. Copies96-byte face prefix,builds circular doubly linked copied corner ring,overwrites UV0/1 from associated decal polygon8-byte pairs (retains otherUV fields),stores original face at+96,ORs flag20000,sets descriptor+76=association. Appends derived face pointer18BCFB8,aux0,bumps globalfacecount and caller face-domain count. Allocation checks AFTER cursor advance;on failure can
// leave advanced cursor/partial unappended ring. No vertex-count match validation or transactional cleanup;return varies loop/pointer paths,not reliable status and builder ignores it.
int __cdecl rf_world_packet_append_decal_derived_faces(int a1, int a2, _DWORD *a3)
{
  int result; // eax
  _DWORD *v4; // [esp+8h] [ebp-A8h]
  int v5; // [esp+Ch] [ebp-A4h]
  int v6; // [esp+10h] [ebp-A0h]
  _DWORD *v7; // [esp+18h] [ebp-98h]
  int i; // [esp+1Ch] [ebp-94h]
  _DWORD *j; // [esp+20h] [ebp-90h]
  int v10; // [esp+24h] [ebp-8Ch] BYREF
  _DWORD v11[17]; // [esp+28h] [ebp-88h] BYREF
  int v12; // [esp+6Ch] [ebp-44h] BYREF
  char v13[64]; // [esp+70h] [ebp-40h] BYREF

  if ( !dword_A4208C && !dword_A42090 && !dword_A4209C )
  {
    v10 = 16;
    v12 = 16;
    result = rf_face_partition_decal_polygons_flag8(a2, a1, (int)v11, &v10, (int)v13, &v12);
    if ( v10 )
    {
      for ( i = 0; i < v10; ++i )
      {
        if ( dword_18CCFC4 >= 0x4000 )
          break;
        v7 = (_DWORD *)unk_149CB18;
        result = unk_149CB18 + 100;
        unk_149CB18 += 100;
        if ( unk_149CB18 >= (unsigned int)off_663D40 )
          break;
        rf_world_face_copy_prefix96((int)v7, a2);
        v7[16] = 0;
        v6 = 0;
        for ( j = *(_DWORD **)(a2 + 64); j; j = v4 )
        {
          v5 = unk_149CB18;
          unk_149CB18 += 28;
          result = unk_149CB18;
          if ( unk_149CB18 >= (unsigned int)off_663D40 )
            return result;
          qmemcpy((void *)v5, j, 0x1Cu);
          if ( v7[16] )
          {
            *(_DWORD *)(v5 + 24) = *(_DWORD *)(v7[16] + 24);
            *(_DWORD *)(v5 + 20) = v7[16];
            *(_DWORD *)(*(_DWORD *)(v7[16] + 24) + 20) = v5;
            *(_DWORD *)(v7[16] + 24) = v5;
          }
          else
          {
            *(_DWORD *)(v5 + 20) = v5;
            *(_DWORD *)(v5 + 24) = v5;
            v7[16] = v5;
          }
          *(float *)(v5 + 4) = *(float *)(v11[i] + 8 * v6);
          *(float *)(v5 + 8) = *(float *)(v11[i] + 8 * v6++ + 4);
          if ( j[5] == *(_DWORD *)(a2 + 64) )
            v4 = nullptr;
          else
            v4 = (_DWORD *)j[5];
        }
        v7[24] = a2;
        v7[10] |= 0x20000u;
        v7[19] = v11[i];
        unk_18BCFB8[dword_18CCFC4] = (int)v7;
        unk_1484718[dword_18CCFC4++] = 0;
        ++*a3;
        result = i + 1;
      }
    }
  }
  return result;
}

