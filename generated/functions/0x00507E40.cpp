// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507E40 rf_rail_trail_update_and_recycle
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Walks active circular ring911708 through next+72, saves next-or-NULL when wrapping to head BEFORE removal. Each node first stores F32 age+64 +=frameDelta. If generic object UID+68 resolves, advances ONLY apex vector+0 by stored normalized forward+48 * F32(speed+60 * NEW age); returned object transform is NOT read. This per-frame displacement does NOT multiply by dt, is not absolute position=origin+speed*time and leaves base center+12 fixed. Then expires at ORDERED age>=DOUBLE1 for ANY nonzero multiplayer runtime byte, else ORDERED age>=DOUBLE0.800000011920929. NaN age survives native AH1/JNZ gate. Unlinks expired node, updates active head or clears singleton, clears
// links then appends node before free head91170C (or self-links singleton free ring); does not clear payload or free heap memory. Resolution failure suppresses motion but not aging/recycling; motion occurs before expiry even on expiring frame. ReturnsNULL after normal traversal.
float *rf_rail_trail_update_and_recycle()
{
  float *result; // eax
  float *v1; // eax
  float *v2; // [esp+4h] [ebp-20h]
  float scalar; // [esp+8h] [ebp-1Ch]
  float scaled_result[3]; // [esp+Ch] [ebp-18h] BYREF
  float *v6; // [esp+1Ch] [ebp-8h]
  float *i; // [esp+20h] [ebp-4h]

  result = (float *)unk_911708;
  for ( i = (float *)unk_911708; i; i = v6 )
  {
    i[16] = i[16] + rf_frame_delta_seconds;
    if ( rf_object_resolve_handle(*((_DWORD *)i + 17)) )
    {
      scalar = i[15] * i[16];
      v1 = rf_vector_multiply_scalar(i + 12, scaled_result, scalar);
      rf_vector_accumulate(i, v1);
    }
    if ( *((_DWORD *)i + 18) == unk_911708 )
      v2 = nullptr;
    else
      v2 = *((float **)i + 18);
    v6 = v2;
    if ( rf_multiplayer_runtime_mode )
    {
      if ( i[16] < 1.0 )
        goto LABEL_28;
      if ( (float *)unk_911708 == i )
      {
        if ( *((float **)i + 18) == i )
        {
          i[18] = 0.0;
          i[19] = 0.0;
          unk_911708 = 0;
          goto LABEL_15;
        }
        unk_911708 = *((_DWORD *)i + 18);
      }
      *(float *)(*((_DWORD *)i + 19) + 72) = i[18];
      *(float *)(*((_DWORD *)i + 18) + 76) = i[19];
      i[18] = 0.0;
      i[19] = 0.0;
LABEL_15:
      if ( unk_91170C )
      {
        i[19] = *(float *)(unk_91170C + 76);
        *((_DWORD *)i + 18) = unk_91170C;
        *(_DWORD *)(*(_DWORD *)(unk_91170C + 76) + 72) = i;
        *(_DWORD *)(unk_91170C + 76) = i;
      }
      else
      {
        *((_DWORD *)i + 18) = i;
        *((_DWORD *)i + 19) = i;
        unk_91170C = i;
      }
      goto LABEL_28;
    }
    if ( i[16] < 0.800000011920929 )
      goto LABEL_28;
    if ( (float *)unk_911708 == i )
    {
      if ( *((float **)i + 18) == i )
      {
        i[18] = 0.0;
        i[19] = 0.0;
        unk_911708 = 0;
        goto LABEL_25;
      }
      unk_911708 = *((_DWORD *)i + 18);
    }
    *(float *)(*((_DWORD *)i + 19) + 72) = i[18];
    *(float *)(*((_DWORD *)i + 18) + 76) = i[19];
    i[18] = 0.0;
    i[19] = 0.0;
LABEL_25:
    if ( unk_91170C )
    {
      i[19] = *(float *)(unk_91170C + 76);
      *((_DWORD *)i + 18) = unk_91170C;
      *(_DWORD *)(*(_DWORD *)(unk_91170C + 76) + 72) = i;
      *(_DWORD *)(unk_91170C + 76) = i;
    }
    else
    {
      *((_DWORD *)i + 18) = i;
      *((_DWORD *)i + 19) = i;
      unk_91170C = i;
    }
LABEL_28:
    result = v6;
  }
  return result;
}

