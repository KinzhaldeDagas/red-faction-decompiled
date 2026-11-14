// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EFD0 rf_world_submit_render_callback_entry
// UNREALRED VERIFIED [room-render-20261028]: Arguments include payload,stored position,culling center,radius,callback,sort byte,optional plane/minpoint/maxpoint pointers and two lighting bytes. Transforms culling center with globals0x930A38/0xA42064 when enabled: subtract pivot0xA420BC,inverse-rotate,then add offset0xA5A0EC+pivot; otherwise adds offset only. Outside-frustum sphere0x581B60 returns0. If callbacknonnull, count>=2048 returns0; else increments submission counter0xA42060 and appends48-byte packet at0xA420C8. Stores payload+0,position+4,radius+16,sortbyte+20,clears drawn/grouped bytes+21/+22,lighting bytes+23/+24,optional pointers+28/+32/+36,callback+44. Null callback still returns1 after successful culling but appends nothing. No null position/center or radius-range validation.
char __cdecl rf_world_submit_render_callback_entry(
        int a1,
        float *source,
        float *lhs,
        float a4,
        int a5,
        char a6,
        int a7,
        int a8,
        int a9,
        char a10,
        char a11)
{
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float v15[3]; // [esp+4h] [ebp-58h] BYREF
  float v16[3]; // [esp+10h] [ebp-4Ch] BYREF
  float v17[3]; // [esp+1Ch] [ebp-40h] BYREF
  float sum_result[3]; // [esp+28h] [ebp-34h] BYREF
  float copy_result[3]; // [esp+34h] [ebp-28h] BYREF
  float out_vector[3]; // [esp+40h] [ebp-1Ch] BYREF
  float *v21; // [esp+4Ch] [ebp-10h]
  float destination[3]; // [esp+50h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  if ( unk_930A38 && *(_DWORD *)&byte_98967F[756197] )
  {
    v11 = rf_vector_subtract(lhs, out_vector, &flt_A420BC);
    rf_vector_copy(destination, copy_result, v11);
    rf_matrix3_inverse_rotate_vector(destination, *(float **)&byte_98967F[756197]);
    v12 = rf_vector_add(&flt_A5A0EC, sum_result, &flt_A420BC);
    rf_vector_accumulate(destination, v12);
  }
  else
  {
    v13 = rf_vector_add(lhs, v17, &flt_A5A0EC);
    rf_vector_copy(destination, v16, v13);
  }
  if ( rf_frustum_reject_sphere(destination, a4) )
    return 0;
  if ( a5 )
  {
    if ( *(int *)&byte_98967F[756169] >= 2048 )
      return 0;
    ++*(_DWORD *)&byte_98967F[756193];
    v21 = (float *)((char *)&unk_A420C8 + 48 * (*(_DWORD *)&byte_98967F[756169])++);
    rf_vector_copy(v21 + 1, v15, source);
    *(_DWORD *)v21 = a1;
    v21[4] = a4;
    *((_DWORD *)v21 + 11) = a5;
    *((_DWORD *)v21 + 7) = a7;
    *((_DWORD *)v21 + 8) = a8;
    *((_DWORD *)v21 + 9) = a9;
    *((_BYTE *)v21 + 20) = a6;
    *((_BYTE *)v21 + 21) = 0;
    *((_BYTE *)v21 + 22) = 0;
    *((_BYTE *)v21 + 23) = a10;
    *((_BYTE *)v21 + 24) = a11;
  }
  return 1;
}

